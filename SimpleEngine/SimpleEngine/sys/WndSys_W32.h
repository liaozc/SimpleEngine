#ifndef WND_SYS_W32
#define WND_SYS_W32

#include "IWndSys.h"
#include "windows.h"

class seWndSys_W32 : public seIWndSys
{
	friend seIWndSys* CreateWndSystem();
	seWndSys_W32();
	virtual ~seWndSys_W32();
public:
	virtual void Init();
	virtual void Run(bool& exit);
	virtual void CreateWnd(const seConfig& config);
protected:
	HWND mHwnd;
};

#endif