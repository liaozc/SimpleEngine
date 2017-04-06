#ifndef SAMPLE_TEXTURE_H
#define SAMPLE_TEXTURE_H

#include "sample_public.h"

class seSample_Texture : public seSample
{
public:
	virtual void Init(ID3D11Device* device, ID3D11DeviceContext* context);
	virtual void Render();
	virtual void UnInit();
	virtual void OnSceneSizeChanged(int width, int height);
protected:
	seProgram* mProgram;
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;
	ID3D11Buffer* mCBNeverChange;
	ID3D11Buffer* mCBOnSize;
	ID3D11Buffer* mCBPerFrame;
	ID3D11ShaderResourceView* mSRV;
	ID3D11SamplerState* mSS;
};

#endif // !SAMPLE_TEXTURE_H

