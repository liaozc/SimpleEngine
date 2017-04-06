#include "../../precompiled.h"
#pragma hdrstop

#include "dx_header.h"
#include "program.h"
#include "programSource.h"
#include "../../geometry/DrawVert.h"
#include "../../sys/sys_wnd_public.h"


#include "sample_lighting.h"

struct ConstantBuffer
{
	XMMATRIX mat_world;
	XMMATRIX mat_view;
	XMMATRIX mat_proj;
	XMFLOAT4 vLightDir[2];
	XMFLOAT4 vLightColor[2];
};

struct ConstantBufferLight
{
	XMMATRIX mat_world;
	XMMATRIX mat_view;
	XMMATRIX mat_proj;
	XMFLOAT4 vColor;
};

static XMMATRIX mat_world;
static XMMATRIX mat_view;
static XMMATRIX mat_proj;

void seSample_Lighting::Init(ID3D11Device* device, ID3D11DeviceContext* context)
{
	seSample::Init(device, context);
	
	D3D11_INPUT_ELEMENT_DESC layout[] =	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	mProgram = new seProgram(mDevice);
	mProgram->FromSource(pSrc_Lighting, layout, numElements);

	mProgramLight = new seProgram(mDevice);
	mProgramLight->FromSource(pSrc_LightingSolid, layout, numElements);

	seDrawVert vertices[] =	{
		{ seVec3(-1.0f, 1.0f, -1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 1.0f, 0.0f) },
		{ seVec3(1.0f, 1.0f, -1.0f),seVec4(0.5f,0.5f,0.5f,0.5f), seVec3(0.0f, 1.0f, 0.0f) },
		{ seVec3(1.0f, 1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 1.0f, 0.0f) },
		{ seVec3(-1.0f, 1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 1.0f, 0.0f) },

		{ seVec3(-1.0f, -1.0f, -1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, -1.0f, 0.0f) },
		{ seVec3(1.0f, -1.0f, -1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, -1.0f, 0.0f) },
		{ seVec3(1.0f, -1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, -1.0f, 0.0f) },
		{ seVec3(-1.0f, -1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, -1.0f, 0.0f) },

		{ seVec3(-1.0f, -1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(-1.0f, 0.0f, 0.0f) },
		{ seVec3(-1.0f, -1.0f, -1.0f),seVec4(0.5f,0.5f,0.5f,0.5f), seVec3(-1.0f, 0.0f, 0.0f) },
		{ seVec3(-1.0f, 1.0f, -1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(-1.0f, 0.0f, 0.0f) },
		{ seVec3(-1.0f, 1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(-1.0f, 0.0f, 0.0f) },

		{ seVec3(1.0f, -1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(1.0f, 0.0f, 0.0f) },
		{ seVec3(1.0f, -1.0f, -1.0f),seVec4(0.5f,0.5f,0.5f,0.5f), seVec3(1.0f, 0.0f, 0.0f) },
		{ seVec3(1.0f, 1.0f, -1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(1.0f, 0.0f, 0.0f) },
		{ seVec3(1.0f, 1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(1.0f, 0.0f, 0.0f) },

		{ seVec3(-1.0f, -1.0f, -1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 0.0f, -1.0f) },
		{ seVec3(1.0f, -1.0f, -1.0f),seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 0.0f, -1.0f) },
		{ seVec3(1.0f, 1.0f, -1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 0.0f, -1.0f) },
		{ seVec3(-1.0f, 1.0f, -1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 0.0f, -1.0f) },

		{ seVec3(-1.0f, -1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 0.0f, 1.0f) },
		{ seVec3(1.0f, -1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 0.0f, 1.0f) },
		{ seVec3(1.0f, 1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 0.0f, 1.0f) },
		{ seVec3(-1.0f, 1.0f, 1.0f), seVec4(0.5f,0.5f,0.5f,0.5f),seVec3(0.0f, 0.0f, 1.0f) },
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(seDrawVert) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	mDevice->CreateBuffer(&bd, &InitData, &mVB);

	WORD indices[] = {
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
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
	
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBufferLight);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	mDevice->CreateBuffer(&bd, NULL, &mCBLight);

	// Initialize the world matrices
	mat_world = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 4.0f, -10.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	mat_view = XMMatrixLookAtLH(Eye, At, Up);
	// Initialize the projection matrix
	seSysWnd* syswnd = CreateSysWnd(nullptr);
	mat_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)syswnd->GetWidth() / (FLOAT)syswnd->GetHeight(), 0.01f, 100.0f);

}

void seSample_Lighting::Render()
{
	static float t = 0.0f;
	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	t = (dwTimeCur - dwTimeStart) / 1000.0f;
	
	// Rotate cube around the origin
	mat_world = XMMatrixRotationY(t);
	// Setup our lighting parameters
	XMFLOAT4 vLightDirs[2] = 
	{
		XMFLOAT4(-0.577f, 0.577f, -0.577f, 1.0f),
		XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f),
	};

	XMFLOAT4 vLightColors[2] = {
		XMFLOAT4(1.0f,1.0f, 0.5f, 1.0f),
		XMFLOAT4(0, 0.0f, 1.0f, 1.0f)
	};

	// Rotate the second light around the origin
	XMMATRIX mat_rotate = XMMatrixRotationY(-2.0f * t);
	XMVECTOR vLightDir = XMLoadFloat4(&vLightDirs[1]);
	vLightDir = XMVector3Transform(vLightDir, mat_rotate);
	XMStoreFloat4(&vLightDirs[1], vLightDir);

	ConstantBuffer cb;
	cb.mat_world = mat_world;
	cb.mat_view = mat_view;
	cb.mat_proj = mat_proj;
	cb.vLightDir[0] = vLightDirs[0];
	cb.vLightDir[1] = vLightDirs[1];
	cb.vLightColor[0] = vLightColors[0];
	cb.vLightColor[1] = vLightColors[1];
	mContext->UpdateSubresource(mCB, 0, NULL, &cb, 0, 0);
	
	mProgram->Apply(mContext);
	mProgram->UpdateVSConstantBuffer(mContext,mCB,0);
	mProgram->UpdatePSConstantBuffer(mContext, mCB, 0);

	UINT stride = sizeof(seDrawVert);
	UINT offset = 0;
	mContext->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	mContext->IASetIndexBuffer(mIB, DXGI_FORMAT_R16_UINT, 0);

	mContext->DrawIndexed(36, 0, 0);

	//
	// Render each light
	//
	ConstantBufferLight cbl;
	cbl.mat_world = mat_world;
	cbl.mat_view = mat_view;
	cbl.mat_proj = mat_proj;
	mProgramLight->Apply(mContext);
	mProgramLight->UpdateVSConstantBuffer(mContext, mCBLight, 0);
	mProgramLight->UpdatePSConstantBuffer(mContext, mCBLight, 0);
	for( int m = 0; m < 2; m++ ){
		XMMATRIX mat_light = XMMatrixTranslationFromVector( 5.0f * XMLoadFloat4( &vLightDirs[m] ) );
		XMMATRIX mat_lightScale = XMMatrixScaling( 0.2f, 0.2f, 0.2f );
		mat_light = mat_lightScale * mat_light;

		// Update the world variable to reflect the current light
		cbl.mat_world = mat_light;
		cbl.vColor = vLightColors[m];
		mContext->UpdateSubresource( mCBLight, 0, NULL, &cbl, 0, 0 );
		mContext->DrawIndexed( 36, 0, 0 );
	}
	
}

void seSample_Lighting::UnInit()
{
	DelOBJ(mProgram);
	DelOBJ(mProgramLight);
	ReleaseOBJ(mVB);
	ReleaseOBJ(mIB);
	ReleaseOBJ(mCB);
	ReleaseOBJ(mCBLight);
}

void seSample_Lighting::OnSceneSizeChanged(int width, int height)
{
	mat_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)width / (FLOAT)height, 0.01f, 100.0f);
}