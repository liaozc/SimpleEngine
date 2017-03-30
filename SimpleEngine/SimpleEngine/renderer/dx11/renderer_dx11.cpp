#include"../../precompiled.h"
#pragma hdrstop

#include "windows.h"
#include "renderer_dx11.h"
#include "../../sys/sys_wnd_public.h"
#include "ProgramSource.h"
#include "Program.h"

#include "../../geometry/DrawVert.h"

#define Tutorial02_Flat_Triangel	0
#define Tutorial03_Simple_3D	1

seProgram* testPro = nullptr;
ID3D11Buffer* testVertexBuffer = nullptr;
ID3D11Buffer* testIndexBuffer = nullptr;
ID3D11Buffer* testConstantBuffer = nullptr;
XMMATRIX testWorld;
XMMATRIX testView;
XMMATRIX testProjection;

struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
};

seRenderer_Dx11* gRenderer = nullptr;
seRenderer* CreateRenderer()
{
	if (!gRenderer) {
		gRenderer = new seRenderer_Dx11();
	}
	return gRenderer;
}

void seRenderer_Dx11::DrawPrimitive(seDrawVert* vertList, unsigned short* indices)
{
	
}

void seRenderer_Dx11::Init(seSysWnd* sysWnd)
{
	WindowHandle handle = sysWnd->GetHandle();
	int width = sysWnd->GetWidth();
	int height = sysWnd->GetHeight();

	D3D_DRIVER_TYPE driverTypes[] =	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = handle;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	HRESULT hr = S_OK;
	UINT createDeviceFlags = 0;	//D3D11_CREATE_DEVICE_DEBUG;	win10 要开启图形诊断工具才能使用这个标识

	D3D_DRIVER_TYPE  driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL	featureLevel = D3D_FEATURE_LEVEL_11_0;
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &mSwapChain, &mDevice, &featureLevel, &mContext);
		BreakIf(SUCCEEDED(hr));
	}
	ReturnIf(FAILED(hr));
	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	ReturnIf(FAILED(hr));
	hr = mDevice->CreateRenderTargetView(pBackBuffer, NULL, &mRenderTargetView);
	pBackBuffer->Release();
	ReturnIf(FAILED(hr));
	mContext->OMSetRenderTargets(1, &mRenderTargetView, NULL);
	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mContext->RSSetViewports(1, &vp);

//TEST THE TUTORIAL PROGRAM
#if Tutorial02_Flat_Triangel == 1
	//init some bulit-in program to shade
	// Create the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	testPro = new seProgram(mDevice);
	testPro->FromSource(pSrc_Flat, layout, numElements);
	//create a triangle and apply the program to it.
	seDrawVert vertList[] =
	{
		{seVec3(0.0f, 0.5f, 0.5f)},
		{seVec3(0.5f, -0.5f, 0.5f)},
		{seVec3(-0.5f, -0.5f, 0.5f)}
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(seDrawVert) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertList;
	hr = mDevice->CreateBuffer(&bd, &InitData, &testVertexBuffer);
#elif Tutorial03_Simple_3D == 1
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	testPro = new seProgram(mDevice);
	testPro->FromSource(pSrc_Simple3D,layout,numElements);
	
	seDrawVert vertices[] = {
		{ seVec3(-1.0f, -1.0f, 0), seVec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ seVec3(1.0f, 1.0f, 0), seVec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ seVec3(1.0f, 1.0f, 1.0f), seVec4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ seVec3(-1.0f, 1.0f, 0), seVec4(1.0f, 0.0f, 0.0f, 1.0f) },
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
	hr = mDevice->CreateBuffer(&bd, &InitData, &testVertexBuffer);
	
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
	hr = mDevice->CreateBuffer(&bd, &InitData, &testIndexBuffer);

	// Create the constant buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = mDevice->CreateBuffer(&bd, NULL, &testConstantBuffer);
	
	testWorld = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	testView = XMMatrixLookAtLH(Eye, At, Up);
	// Initialize the projection matrix
	testProjection = XMMatrixPerspectiveFovLH(XM_PIDIV2, width / (FLOAT)height, 0.01f, 100.0f);

#endif
	UINT stride = sizeof(seDrawVert);
	UINT offset = 0;
	mContext->IASetVertexBuffers(0, 1, &testVertexBuffer, &stride, &offset);
	mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void seRenderer_Dx11::UnInit()
{
	if (mContext) 
		mContext->ClearState();	
	ReleaseOBJ(mRenderTargetView);
	ReleaseOBJ(mSwapChain);
	ReleaseOBJ(mContext);
	ReleaseOBJ(mDevice);
}

void seRenderer_Dx11::DoRender()
{
	float ClearColor[4] = {0.5f,0.5f,0.9f,1}; // red,green,blue,alpha
	mContext->ClearRenderTargetView(mRenderTargetView, ClearColor);

#if Tutorial02_Flat_Triangel == 1
	testPro->Apply(mContext,NULL,NULL);
	mContext->Draw(3, 0);
#elif Tutorial03_Simple_3D == 1
	static float t = 0.0f;
	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	t = (dwTimeCur - dwTimeStart) / 1000.0f;
	//testWorld = XMMatrixRotationY(t);
	// Update variables
	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(testWorld);
	cb.mView = XMMatrixTranspose(testView);
	cb.mProjection = XMMatrixTranspose(testProjection);
	mContext->UpdateSubresource(testConstantBuffer, 0, NULL, &cb, 0, 0);

	testPro->Apply(mContext, testConstantBuffer, NULL);
	
	mContext->IASetIndexBuffer(testIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	mContext->DrawIndexed(36, 0, 0);

#endif
	mSwapChain->Present(0, 0);
}