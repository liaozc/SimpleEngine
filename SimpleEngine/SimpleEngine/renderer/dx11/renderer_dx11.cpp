#include"../../precompiled.h"
#pragma hdrstop

#include "windows.h"
#include "renderer_dx11.h"
#include "../../sys/sys_wnd_public.h"

#include "sample_public.h"
#include "sample_basic_shader.h"
#include "sample_simple_3d.h"
#include "sample_transformation.h"
#include "sample_lighting.h"
#include "sample_texture.h"

#define SAMPLE_BASIC_SHADER 	0
#define SAMPLE_SIMPLE_3D	0
#define SAMPLE_TRANSFORMATION	0
#define SAMPLE_LIGHTING	0
#define SAMPLE_TEXTURE 1

seSample* sample = nullptr;

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

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = mDevice->CreateTexture2D(&descDepth, NULL, &mDepthStencil);
	ReturnIf(FAILED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = mDevice->CreateDepthStencilView(mDepthStencil, &descDSV, &mDepthStencilView);
	ReturnIf(FAILED(hr));
		
	mContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
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
#if SAMPLE_BASIC_SHADER == 1
	sample = new seSample_BasicShader();
#elif SAMPLE_SIMPLE_3D == 1
	sample = new seSample_Simple3D();
#elif SAMPLE_TRANSFORMATION == 1
	sample = new seSample_Transformation();
#elif SAMPLE_LIGHTING == 1
	sample = new seSample_Lighting();
#elif SAMPLE_TEXTURE == 1
	sample = new seSample_Texture();
#endif
	sample->Init(mDevice, mContext);

	mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void seRenderer_Dx11::UnInit()
{
	if (mContext) 
		mContext->ClearState();	
	
	if(sample)
		sample->UnInit();
	DelOBJ(sample);

	ReleaseOBJ(mDepthStencil);
	ReleaseOBJ(mDepthStencilView);
	ReleaseOBJ(mRenderTargetView);
	ReleaseOBJ(mSwapChain);
	ReleaseOBJ(mContext);
	ReleaseOBJ(mDevice);
}

void seRenderer_Dx11::DoRender()
{
	float ClearColor[4] = {0.5f,0.5f,0.9f,1}; // red,green,blue,alpha
	mContext->ClearRenderTargetView(mRenderTargetView, ClearColor);
	mContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	sample->Render();

	mSwapChain->Present(0, 0);
}

void seRenderer_Dx11::OnSize(int width, int height)
{
	sample?	sample->OnSceneSizeChanged(width, height) : 0;
}