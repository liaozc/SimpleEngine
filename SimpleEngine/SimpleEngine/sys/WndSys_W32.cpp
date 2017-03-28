#include "../precompiled.h"
#pragma hdrstop

#include "WndSys_W32.h"
#define IDI_ICON1 101
#include <cstdio>

LONG WINAPI MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
#if 1
	switch (uMsg) {
		case WM_DESTROY: {
			PostMessage(0, WM_QUIT, 0, 0);
			break;
		}
		case WM_WINDOWPOSCHANGED:
		case WM_CREATE:
		case WM_CLOSE:
		case WM_ACTIVATE:
		case WM_MOVE: 
		case WM_TIMER: 
		case WM_SYSCOMMAND:
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYUP:
		case WM_CHAR:
		case WM_NCLBUTTONDOWN:
		case WM_ENTERSIZEMOVE:
		case WM_EXITSIZEMOVE:
		case WM_SIZING:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEMOVE: 
		case WM_MOUSEWHEEL: 
				break;
	}
#endif
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


seIWndSys* gWndSys = nullptr;
seIWndSys* CreateWndSystem()
{
	if (!gWndSys) {
		gWndSys = new seWndSys_W32();
		gWndSys->Init();
	}
	return gWndSys;
}

seWndSys_W32::seWndSys_W32()
{
	mHwnd = 0;
}

seWndSys_W32::~seWndSys_W32()
{
}

void seWndSys_W32::Init()
{
	//register window
	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (struct HBRUSH__ *)COLOR_GRAYTEXT;
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"SimpleWnd";

	if (!RegisterClass(&wc)) {
		printf("registe window fail");
		return;
	}
	printf("...registered window class\n");
}

void seWndSys_W32::CreateWnd(const seConfig& config)
{
	int				stylebits;
	int				x, y, w, h;
	int				exstyle;
	//
	// compute width and height
	//
	if (config.fullScreen) {
		exstyle = WS_EX_TOPMOST;
		stylebits = WS_POPUP | WS_VISIBLE | WS_SYSMENU;

		x = 0;
		y = 0;
		w = config.screenWidth;
		h = config.screenHeight;
	}
	else {
		RECT	r;
		// adjust width and height for window border
		r.bottom = config.screenHeight;;
		r.left = 0;
		r.top = 0;
		r.right = config.screenWidth;

		exstyle = 0;
		stylebits = WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_VISIBLE | WS_THICKFRAME | WS_SYSMENU;
		AdjustWindowRect(&r, stylebits, FALSE);

		w = r.right - r.left;
		h = r.bottom - r.top;
		x = y = 0;
	}

	mHwnd = CreateWindowEx(
		exstyle,
		L"SimpleWnd",
		L"SimpleEngineV0.01",
		stylebits,
		x, y, w, h,
		NULL,
		NULL,
		GetModuleHandle(0),
		NULL);

	if (!mHwnd) {
		printf("^3GLW_CreateWindow() - Couldn't create window^0\n");
	}

	//::SetTimer(mHwnd, 0, 100, NULL);
	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);
	printf("...created window @ %d,%d (%dx%d)\n", x, y, w, h);
//	SetForegroundWindow(mHwnd);
//	SetFocus(mHwnd);
}

void seWndSys_W32::Run(bool& exit)
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			exit = true;
			continue;
		}
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}
