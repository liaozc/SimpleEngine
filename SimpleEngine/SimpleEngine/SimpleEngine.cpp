#include "precompiled.h"
#pragma hdrstop

#include "SimpleEngine.h"
#include "sys/sys_wnd_public.h"
#include "renderer/render_public.h"

seEngine * gEngine = nullptr;
DLL_INTERFACE seIEngine* GetSimpleEngine()
{
	if (!gEngine) {
		gEngine = new seEngine();
		gEngine->init();
	}
	return gEngine;
}

seEngine::seEngine()
{
	mSysWnd = nullptr;
	mRenderer = nullptr;
}

seEngine::~seEngine()
{

}

void seEngine::init()
{
	//create systems.
	//1.window system
	mSysWnd = CreateWndSystem();
	//2.renderer
	mRenderer = CreateRenderer();
}

void seEngine::Close()
{
	mRenderer->UnInit();
	DelOBJ(mSysWnd);
	DelOBJ(mRenderer);
}

void seEngine::InitConfig(const seConfig& config)
{
	mSysWnd->CreateWnd(config);
	mRenderer->Init(mSysWnd);
}

void seEngine::Run()
{
	bool exit = false;
	do {
		mSysWnd->Run(exit);
		mRenderer->DoRender();
		BreakIf(exit);
	} while (true);
}

seRenderer* seEngine::GetRenderer() const
{
	return mRenderer;
}