#ifndef SAMPLE_TRANSFORMATION_H
#define SAMPLE_TRANSFORMATION_H

#include "sample_public.h"

class seSample_Transformation : public seSample
{
public:
	virtual void Init(ID3D11Device* device, ID3D11DeviceContext* context);
	virtual void Render();
	virtual void UnInit();
	virtual void OnSceneSizeChanged(int width, int height);
public:
	seProgram* mProgram;
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;
	ID3D11Buffer* mCB;
};

#endif
