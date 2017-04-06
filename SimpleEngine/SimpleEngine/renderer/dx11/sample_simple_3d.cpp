#include "../../precompiled.h"
#pragma hdrstop

#include "dx_header.h"
#include "program.h"
#include "programSource.h"
#include "../../geometry/DrawVert.h"
#include "../../sys/sys_wnd_public.h"


#include "sample_simple_3d.h"


struct ConstantBuffer
{
	XMMATRIX mat_world;
	XMMATRIX mat_view;
	XMMATRIX mat_proj;
};

static XMMATRIX mat_word;
static XMMATRIX mat_view;
static XMMATRIX mat_proj;

void seSample_Simple3D::Init(ID3D11Device* device, ID3D11DeviceContext* context)
{
	seSample::Init(device, context);

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	mProgram = new seProgram(mDevice);
	mProgram->FromSource(pSrc_Simple3D, layout, numElements);

	seDrawVert vertices[] = {
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
	WORD indices[] = {
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
	bd.ByteWidth = sizeof(WORD) * 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	mDevice->CreateBuffer(&bd, &InitData, &mIB);

	// Create the constant buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	mDevice->CreateBuffer(&bd, NULL, &mCB);

	mat_word = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 2.0f, -5.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	mat_view = XMMatrixLookAtLH(Eye, At, Up);
	// Initialize the projection matrix
	seSysWnd* syswnd = CreateSysWnd(nullptr);
	mat_proj = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)syswnd->GetWidth() / (FLOAT)syswnd->GetHeight(), 0.01f, 100.0f);
}

void seSample_Simple3D::Render()
{
	static float t = 0.0f;
	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	t = (dwTimeCur - dwTimeStart) / 1000.0f;
	mat_word = XMMatrixRotationY(t);
	// Update variables
	ConstantBuffer cb;
	cb.mat_world = mat_word;
	cb.mat_view = mat_view;
	cb.mat_proj = mat_proj;
	mContext->UpdateSubresource(mCB, 0, NULL, &cb, 0, 0);

	mProgram->Apply(mContext);
	mProgram->UpdateVSConstantBuffer(mContext, mCB, 0);

	UINT stride = sizeof(seDrawVert);
	UINT offset = 0;
	mContext->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	mContext->IASetIndexBuffer(mIB, DXGI_FORMAT_R16_UINT, 0);

	mContext->DrawIndexed(36, 0, 0);

}

void seSample_Simple3D::UnInit()
{
	DelOBJ(mProgram);
	ReleaseOBJ(mVB);
	ReleaseOBJ(mIB);
	ReleaseOBJ(mCB);
}

void seSample_Simple3D::OnSceneSizeChanged(int width, int height)
{
	mat_proj = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)width / (FLOAT)height, 0.01f, 100.0f);
}