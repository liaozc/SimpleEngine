#include "../../precompiled.h"
#pragma hdrstop

#include "dx_header.h"
#include "program.h"
#include "programSource.h"
#include "../../geometry/DrawVert.h"
#include "../../sys/sys_wnd_public.h"

#include "sample_transformation.h"

struct ConstantBuffer
{
	XMMATRIX mat_world;
	XMMATRIX mat_view;
	XMMATRIX mat_proj;
};

static XMMATRIX                mat_world1;
static XMMATRIX                mat_world2;
static XMMATRIX                mat_view;
static XMMATRIX                mat_proj;

void seSample_Transformation::Init(ID3D11Device* device, ID3D11DeviceContext* context)
{
	seSample::Init(device, context);
	
	D3D11_INPUT_ELEMENT_DESC layout[] =	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	mProgram = new seProgram(mDevice);
	mProgram->FromSource(pSrc_Transformation, layout, numElements);

	// Create vertex buffer
	seDrawVert vertices[] =
	{
		{ seVec3(-1.0f, 1.0f, -1.0f), seVec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ seVec3(1.0f, 1.0f, -1.0f), seVec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ seVec3(1.0f, 1.0f, 1.0f), seVec4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ seVec3(-1.0f, 1.0f, 1.0f), seVec4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ seVec3(-1.0f, -1.0f, -1.0f), seVec4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ seVec3(1.0f, -1.0f, -1.0f), seVec4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ seVec3(1.0f, -1.0f, 1.0f), seVec4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ seVec3(-1.0f, -1.0f, 1.0f), seVec4(0.0f, 0.0f, 0.0f, 1.0f) },
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(seDrawVert) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	mDevice->CreateBuffer(&bd, &InitData, &mVB);

	// Create index buffer
	WORD indices[] =
	{
		3,1,0,
		2,1,3,

		0,5,4,
		1,5,0,

		3,4,7,
		0,4,3,

		1,6,5,
		2,6,1,

		2,7,6,
		3,7,2,

		6,4,5,
		7,4,6,
	};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	mDevice->CreateBuffer(&bd, &InitData, &mIB);

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	mDevice->CreateBuffer(&bd, NULL, &mCB);

	// Initialize the world matrix
	mat_world1 = XMMatrixIdentity();
	mat_world2 = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 2.0f, -5.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	mat_view = XMMatrixLookAtLH(Eye, At, Up);

	// Initialize the projection matrix
	seSysWnd* syswnd = CreateSysWnd(nullptr);
	mat_proj = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)syswnd->GetWidth() / (FLOAT)syswnd->GetHeight(), 0.01f, 100.0f);

}

void seSample_Transformation::Render()
{
	// Update our time
	static float t = 0.0f;
	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	t = (dwTimeCur - dwTimeStart) / 1000.0f;

	// 1st Cube: Rotate around the origin
	mat_world1 = XMMatrixRotationY(t);
	// 2nd Cube:  Rotate around origin
	XMMATRIX mat_spin = XMMatrixRotationZ(-t);
	XMMATRIX mat_orbit = XMMatrixRotationY(-t * 2.0f);
	XMMATRIX mat_translate = XMMatrixTranslation(-4.0f, 0.0f, 0.0f);
	XMMATRIX mat_scale = XMMatrixScaling(0.3f, 0.3f, 0.3f);

	mat_world2 = mat_scale * mat_spin * mat_translate * mat_orbit;

	ConstantBuffer cb1;
	cb1.mat_world = mat_world1;
	cb1.mat_view = mat_view;
	cb1.mat_proj = mat_proj;
	mContext->UpdateSubresource(mCB, 0, NULL, &cb1, 0, 0);

	//
	// Render the first cube
	//
	mProgram->Apply(mContext);
	mProgram->UpdateVSConstantBuffer(mContext, mCB, 0);
	
	UINT stride = sizeof(seDrawVert);
	UINT offset = 0;
	mContext->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	mContext->IASetIndexBuffer(mIB, DXGI_FORMAT_R16_UINT, 0);

	mContext->DrawIndexed(36, 0, 0);

	//
	// Update variables for the second cube
	//
	ConstantBuffer cb2;
	cb2.mat_world = mat_world2;
	cb2.mat_view = mat_view;
	cb2.mat_proj = mat_proj;
	mContext->UpdateSubresource(mCB, 0, NULL, &cb2, 0, 0);
	//mProgram->Apply(mContext, mCB, NULL); once constant-buffer is attached to the vs or ps,it is not need to set it agian when the buffer is update.
	mContext->DrawIndexed(36, 0, 0);
}


void seSample_Transformation::UnInit()
{
	DelOBJ(mProgram);
	ReleaseOBJ(mVB);
	ReleaseOBJ(mIB);
	ReleaseOBJ(mCB);
}

void seSample_Transformation::OnSceneSizeChanged(int width, int height)
{
	mat_proj = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)width / (FLOAT)height, 0.01f, 100.0f);
}