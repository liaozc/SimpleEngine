#ifndef SAMPLE_BASIC_SHADER_H
#define SAMPLE_BASIC_SHADER_H

#include "sample_public.h"

class seSample_BasicShader :
	public seSample
{
public:
	virtual void Init(ID3D11Device* device, ID3D11DeviceContext* context);
	virtual void Render();
	virtual void UnInit();
	virtual void OnSceneSizeChanged(int width, int height) {};
protected:
	seProgram* mProgram;
	ID3D11Buffer* mVB;

};



#endif