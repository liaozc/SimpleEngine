#ifndef SAMPLE_SIMPLE_3D_H
#define SAMPLE_SIMPLE_3D_H

#include "sample_public.h"

class seSample_Simple3D :public seSample
{
public:
	virtual void Init(ID3D11Device* device, ID3D11DeviceContext* context);
	virtual void Render();
	virtual void UnInit();
	void OnSceneSizeChanged(int width, int height);

protected:
	seProgram* mProgram;
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;
	ID3D11Buffer* mCB;
};

#endif
