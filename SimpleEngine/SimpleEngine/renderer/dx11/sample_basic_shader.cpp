#include "../../precompiled.h"
#pragma hdrstop

#include "dx_header.h"
#include "program.h"
#include "programSource.h"
#include "../../geometry/DrawVert.h"

#include "sample_basic_shader.h"

void seSample_BasicShader::Init(ID3D11Device* device, ID3D11DeviceContext* context)
{
	seSample::Init(device,context);

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	mProgram = new seProgram(mDevice);
	mProgram->FromSource(pSrc_Flat, layout, numElements);
	//create a triangle and apply the program to it.
	seDrawVert vertList[] =
	{
		{ seVec3(0.0f, 0.5f, 0.5f) },
		{ seVec3(0.5f, -0.5f, 0.5f) },
		{ seVec3(-0.5f, -0.5f, 0.5f) }
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
	mDevice->CreateBuffer(&bd, &InitData, &mVB);
}


void seSample_BasicShader::Render()
{
	UINT stride = sizeof(seDrawVert);
	UINT offset = 0;
	mContext->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);

	mProgram->Apply(mContext, NULL, NULL);
	mContext->Draw(3, 0);
}

void seSample_BasicShader::UnInit()
{
	ReleaseOBJ(mVB);
	DelOBJ(mProgram);
}