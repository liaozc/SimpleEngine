#include "../../precompiled.h"
#pragma hdrstop

#include "dx_header.h"
#include "program.h"
#include "programSource.h"
#include "../../geometry/DrawVert.h"
#include "../../sys/sys_wnd_public.h"

#include "sample_texture.h"

struct CBNeverChanges
{
	XMMATRIX mat_view;
};

struct CBChangeOnResize
{
	XMMATRIX mat_proj;
};

struct CBChangesEveryFrame
{
	XMMATRIX mWorld;
	XMFLOAT4 vMeshColor;
};


XMMATRIX mat_world;
XMMATRIX mat_view;
XMMATRIX mat_proj;
XMFLOAT4 vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

void seSample_Texture::Init(ID3D11Device* device, ID3D11DeviceContext* context)
{
	seSample::Init(device, context);

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	mProgram = new seProgram(device);
	mProgram->FromSource(pSrc_Texture, layout, numElements);

	seDrawVert vertices[] = {
		{ seVec3(-1.0f, 1.0f, -1.0f), seVec4(0,0,0,0),seVec3(0,0,0),seVec2(0.0f, 0.0f) },
		{ seVec3(1.0f, 1.0f, -1.0f),  seVec4(0,0,0,0),seVec3(0,0,0),seVec2(1.0f, 0.0f) },
		{ seVec3(1.0f, 1.0f, 1.0f),   seVec4(0,0,0,0),seVec3(0,0,0),seVec2(1.0f, 1.0f) },
		{ seVec3(-1.0f, 1.0f, 1.0f),  seVec4(0,0,0,0),seVec3(0,0,0), seVec2(0.0f, 1.0f) },

		{ seVec3(-1.0f, -1.0f, -1.0f), seVec4(0,0,0,0),seVec3(0,0,0),seVec2(0.0f, 0.0f) },
		{ seVec3(1.0f, -1.0f, -1.0f),  seVec4(0,0,0,0),seVec3(0,0,0),seVec2(1.0f, 0.0f) },
		{ seVec3(1.0f, -1.0f, 1.0f),   seVec4(0,0,0,0),seVec3(0,0,0),seVec2(1.0f, 1.0f) },
		{ seVec3(-1.0f, -1.0f, 1.0f),  seVec4(0,0,0,0),seVec3(0,0,0), seVec2(0.0f, 1.0f) },

		{ seVec3(-1.0f, -1.0f, 1.0f), seVec4(0,0,0,0),seVec3(0,0,0),seVec2(0.0f, 0.0f) },
		{ seVec3(-1.0f, -1.0f, -1.0f),seVec4(0,0,0,0),seVec3(0,0,0), seVec2(1.0f, 0.0f) },
		{ seVec3(-1.0f, 1.0f, -1.0f), seVec4(0,0,0,0),seVec3(0,0,0),seVec2(1.0f, 1.0f) },
		{ seVec3(-1.0f, 1.0f, 1.0f),  seVec4(0,0,0,0),seVec3(0,0,0), seVec2(0.0f, 1.0f) },

		{ seVec3(1.0f, -1.0f, 1.0f),  seVec4(0,0,0,0),seVec3(0,0,0),seVec2(0.0f, 0.0f) },
		{ seVec3(1.0f, -1.0f, -1.0f), seVec4(0,0,0,0),seVec3(0,0,0), seVec2(1.0f, 0.0f) },
		{ seVec3(1.0f, 1.0f, -1.0f),  seVec4(0,0,0,0),seVec3(0,0,0),seVec2(1.0f, 1.0f) },
		{ seVec3(1.0f, 1.0f, 1.0f),   seVec4(0,0,0,0),seVec3(0,0,0), seVec2(0.0f, 1.0f) },

		{ seVec3(-1.0f, -1.0f, -1.0f), seVec4(0,0,0,0),seVec3(0,0,0),seVec2(0.0f, 0.0f) },
		{ seVec3(1.0f, -1.0f, -1.0f),  seVec4(0,0,0,0),seVec3(0,0,0),seVec2(1.0f, 0.0f) },
		{ seVec3(1.0f, 1.0f, -1.0f),   seVec4(0,0,0,0),seVec3(0,0,0),seVec2(1.0f, 1.0f) },
		{ seVec3(-1.0f, 1.0f, -1.0f),  seVec4(0,0,0,0),seVec3(0,0,0), seVec2(0.0f, 1.0f) },

		{ seVec3(-1.0f, -1.0f, 1.0f), seVec4(0,0,0,0),seVec3(0,0,0),seVec2(0.0f, 0.0f) },
		{ seVec3(1.0f, -1.0f, 1.0f),  seVec4(0,0,0,0),seVec3(0,0,0),seVec2(1.0f, 0.0f) },
		{ seVec3(1.0f, 1.0f, 1.0f),   seVec4(0,0,0,0),seVec3(0,0,0),seVec2(1.0f, 1.0f) },
		{ seVec3(-1.0f, 1.0f, 1.0f),  seVec4(0,0,0,0),seVec3(0,0,0),seVec2(0.0f, 1.0f) },
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
	bd.ByteWidth = sizeof(WORD) * 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	mDevice->CreateBuffer(&bd, &InitData, &mIB);

	// Create the constant buffers
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CBNeverChanges);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	mDevice->CreateBuffer(&bd, NULL, &mCBNeverChange);

	bd.ByteWidth = sizeof(CBChangeOnResize);
	mDevice->CreateBuffer(&bd, NULL, &mCBOnSize);

	bd.ByteWidth = sizeof(CBChangesEveryFrame);
	mDevice->CreateBuffer(&bd, NULL, &mCBPerFrame);
	// Load the Texture
	D3DX11CreateShaderResourceViewFromFile(mDevice, L"seafloor.dds", NULL, NULL, &mSRV, NULL);
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	mDevice->CreateSamplerState(&sampDesc, &mSS);

	// Initialize the world matrices
	mat_world = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	mat_view = XMMatrixLookAtLH(Eye, At, Up);

	CBNeverChanges cbNeverChanges;
	cbNeverChanges.mat_view = mat_view;
	mContext->UpdateSubresource(mCBNeverChange, 0, NULL, &cbNeverChanges, 0, 0);

	// Initialize the projection matrix
	seSysWnd* syswnd = CreateSysWnd(nullptr);
	mat_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)syswnd->GetWidth() / (FLOAT)syswnd->GetHeight(), 0.01f, 100.0f);
	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mat_proj = mat_proj;
	mContext->UpdateSubresource(mCBOnSize, 0, NULL, &cbChangesOnResize, 0, 0);
}

void seSample_Texture::Render()
{
	// Update our time
	static float t = 0.0f;
	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	t = (dwTimeCur - dwTimeStart) / 1000.0f;
	
	// Rotate cube around the origin
	mat_world = XMMatrixRotationY(t);
	// Modify the color
	vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

	// Update variables that change once per frame
	CBChangesEveryFrame cb;
	cb.mWorld = mat_world;
	cb.vMeshColor = vMeshColor;
	mContext->UpdateSubresource(mCBPerFrame, 0, NULL, &cb, 0, 0);

	// Render the cube
	mProgram->Apply(mContext);
	mProgram->UpdateVSConstantBuffer(mContext, mCBNeverChange, 0);
	mProgram->UpdateVSConstantBuffer(mContext, mCBOnSize, 1);
	mProgram->UpdateVSConstantBuffer(mContext, mCBPerFrame, 2);
	mProgram->UpdatePSConstantBuffer(mContext, mCBPerFrame, 2);
	mProgram->UpdatePSTexture(mContext, mSRV, 0);
	mProgram->UpdatePSSampleState(mContext, mSS, 0);


	UINT stride = sizeof(seDrawVert);
	UINT offset = 0;
	mContext->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	mContext->IASetIndexBuffer(mIB, DXGI_FORMAT_R16_UINT, 0);
	
	mContext->DrawIndexed(36, 0, 0);

}

void seSample_Texture::UnInit()
{
	DelOBJ(mProgram);
	ReleaseOBJ(mSS);
	ReleaseOBJ(mSRV);
	ReleaseOBJ(mCBNeverChange);
	ReleaseOBJ(mCBOnSize);
	ReleaseOBJ(mCBPerFrame);
	ReleaseOBJ(mVB);
	ReleaseOBJ(mIB);
}

void seSample_Texture::OnSceneSizeChanged(int width, int height)
{
	mat_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)width / (FLOAT)height, 0.01f, 100.0f);
	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mat_proj = mat_proj;
	mContext->UpdateSubresource(mCBOnSize, 0, NULL, &cbChangesOnResize, 0, 0);
}