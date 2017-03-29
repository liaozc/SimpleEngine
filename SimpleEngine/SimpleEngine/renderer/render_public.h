#ifndef I_RENDERER_H
#define I_RENDERER_H

#include"../sys/sys_wnd_public.h"

class seDrawVert;
class seSysWnd;

class seRenderer
{
public:
	virtual void DrawPrimitive(seDrawVert* vertList,unsigned short* indices) = 0;
	virtual void Init(seSysWnd* sysWnd) = 0;
	virtual void UnInit() = 0;
	virtual void DoRender() = 0;
};

seRenderer* CreateRenderer();

#endif // !I_RENDERER_H

