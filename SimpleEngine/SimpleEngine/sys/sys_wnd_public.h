#ifndef I_WINDOW_SYSTEM_H
#define I_WINDOW_SYSTEM_H


#ifdef _WIN32
#include "windows.h"
#define	WindowHandle	HWND

#endif // _WIN32

class seSysWnd
{
public:
	virtual ~seSysWnd() {}
	virtual void Init() = 0;
	virtual void CreateWnd(const seConfig& config) = 0;
	virtual void Run(bool& exit) = 0;
	virtual WindowHandle GetHandle() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};

seSysWnd* CreateWndSystem();


#endif
