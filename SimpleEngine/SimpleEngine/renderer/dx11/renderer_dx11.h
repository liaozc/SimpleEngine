#ifndef DX11_RENDERER_H
#define DX11_RENDERER_H

#include "dx_header.h"

#include "../render_public.h"

class seRenderer_Dx11:public seRenderer
{
public:
	virtual void DrawPrimitive(seDrawVert* vertList, unsigned short* indices);
	virtual void Init(seSysWnd* sysWnd);
	virtual void UnInit();
	virtual void DoRender();

protected:
	ID3D11Device*				mDevice;
	ID3D11DeviceContext*		mContext;
	IDXGISwapChain*				mSwapChain;
	ID3D11RenderTargetView*		mRenderTargetView;
};

#endif // !DX11_RENDERER_H
