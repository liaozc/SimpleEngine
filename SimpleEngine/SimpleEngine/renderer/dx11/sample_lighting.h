#ifndef SAMPLE_LIGHTING_H
#define SAMPLE_LIGHTING_H

#include "sample_public.h"

class seSample_Lighting : public seSample
{
public:
	virtual void Init(ID3D11Device* device, ID3D11DeviceContext* context);
	virtual void Render();
	virtual void UnInit();
	virtual void OnSceneSizeChanged(int width, int height);
protected:
	seProgram* mProgram;
	seProgram* mProgramLight;
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;
	ID3D11Buffer* mCB;
	ID3D11Buffer* mCBLight;
};

#endif
