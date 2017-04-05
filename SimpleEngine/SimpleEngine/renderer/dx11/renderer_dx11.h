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
	virtual void OnSize(int width, int height);
protected:
	ID3D11Device*				mDevice;
	ID3D11DeviceContext*		mContext;
	IDXGISwapChain*				mSwapChain;
	ID3D11RenderTargetView*		mRenderTargetView;
	ID3D11Texture2D*			mDepthStencil;
	ID3D11DepthStencilView*		mDepthStencilView;
};

#endif // !DX11_RENDERER_H
