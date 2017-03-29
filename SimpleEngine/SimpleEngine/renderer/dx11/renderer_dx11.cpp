#include"../../precompiled.h"
#pragma hdrstop

#include "windows.h"
#include "renderer_dx11.h"
#include "../../sys/sys_wnd_public.h"
#include "ProgramSource.h"
#include "Program.h"

#include "../../geometry/DrawVert.h"

seProgram* testPro = nullptr;
ID3D11Buffer* testVertexBuffer = nullptr;

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

	//init some bulit-in program to shade
	testPro = new seProgram(mDevice);
	testPro->FromSource(pSrc_Flat);
	//create a triangle and apply the program to it.
	seDrawVert vertList[] =
	{
		seVec3(0.0f, 0.5f, 0.5f),
		seVec3(0.5f, -0.5f, 0.5f),
		seVec3(-0.5f, -0.5f, 0.5f)
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
	//
	testPro->Apply(mContext);
	UINT stride = sizeof(seDrawVert);
	UINT offset = 0;
	mContext->IASetVertexBuffers(0, 1, &testVertexBuffer, &stride, &offset);
	mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mContext->Draw(3, 0);
	//
	mSwapChain->Present(0, 0);
}