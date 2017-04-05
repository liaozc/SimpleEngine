#include "../../precompiled.h"
#pragma hdrstop

#include "dx_header.h"
#include "program.h"

seProgram::seProgram(ID3D11Device* device)
{
	mDevice = device;
	mVS = nullptr;
	mPS = nullptr;
}

seProgram::~seProgram()
{
	ReleaseOBJ(mVS);
	ReleaseOBJ(mPS);
}
	
bool seProgram::FromSource(const char* src,D3D11_INPUT_ELEMENT_DESC layout[],int numLayout)
{
	ID3DBlob* pVSBlob = NULL;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
	ID3DBlob* pErrorBlob;
	HRESULT hr = D3DX11CompileFromMemory(
		src,strnlen_s(src,10000),
		"Flat.hlsl",
		NULL,NULL,
		"VS","vs_4_0",
		D3D10_SHADER_PACK_MATRIX_ROW_MAJOR,
		NULL,NULL,
		&pVSBlob,&pErrorBlob,NULL);

	if (FAILED(hr)){
		if (pErrorBlob) {
			printf((char*)pErrorBlob->GetBufferPointer());
			pErrorBlob->Release();
		}
		return false;
	}

	// Create the vertex shader
	hr = mDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &mVS);
	if (FAILED(hr)){
		pVSBlob->Release();
		printf("creating vs faild at %d\n", __LINE__);
		return false;
	}
	hr = mDevice->CreateInputLayout(layout, numLayout, pVSBlob->GetBufferPointer(),pVSBlob->GetBufferSize(), &mLayout);
	pVSBlob->Release();
	if (FAILED(hr)) {
		printf("creating Input layout fails at line :%d\n", __LINE__);
		return false;
	}

	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
	hr = D3DX11CompileFromMemory(
		src, strnlen_s(src, 10000),
		"Flat.hlsl",
		NULL, NULL,
		"PS", "ps_4_0",
		D3D10_SHADER_PACK_MATRIX_ROW_MAJOR,
		NULL, NULL,
		&pPSBlob, &pErrorBlob, NULL);
	if (FAILED(hr))	{
		if (pErrorBlob) {
			printf("compiling PS fails at line :%d for: %s \n", __LINE__, (char*)pErrorBlob->GetBufferPointer());
			pErrorBlob->Release();
		}
		return false;
	}
	// Create the pixel shader
	hr = mDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &mPS);
	pPSBlob->Release();
	if (FAILED(hr)) {
		printf("compiling PS fails at line :%d\n", __LINE__);
		return false;
	}

	return true;
}

void seProgram::Apply(ID3D11DeviceContext* context, ID3D11Buffer* vsCB, ID3D11Buffer* psCB)
{
	context->IASetInputLayout(mLayout);
	context->VSSetShader(mVS,NULL,0);
	if(vsCB)
		context->VSSetConstantBuffers(0, 1, &vsCB);
	context->PSSetShader(mPS, NULL, 0);
	if(psCB)
		context->PSSetConstantBuffers(0, 1, &psCB);
}