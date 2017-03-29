#ifndef WND_SYS_W32
#define WND_SYS_W32

#include "sys_wnd_public.h"

class seSysWnd_W32 : public seSysWnd
{
	friend seSysWnd* CreateWndSystem();
	seSysWnd_W32();
	virtual ~seSysWnd_W32();
public:
	virtual void Init();
	virtual void Run(bool& exit);
	virtual void CreateWnd(const seConfig& config);
	virtual WindowHandle GetHandle() const { return mHwnd; }
	virtual int GetWidth() const { return mWidth; }
	virtual int GetHeight() const { return mHeight; }
protected:
	WindowHandle mHwnd;
	int mWidth;
	int mHeight;
};

#endif