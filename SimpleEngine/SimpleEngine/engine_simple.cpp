#include "precompiled.h"
#pragma hdrstop

#include "engine_simple.h"
#include "inuptEventSystem.h"
#include "sys/sys_wnd_public.h"
#include "renderer/render_public.h"

seEngine_Simple * gEngine = nullptr;
DLL_INTERFACE seEngine* GetSimpleEngine()
{
	if (!gEngine) {
		gEngine = new seEngine_Simple();
		gEngine->init();
	}
	return gEngine;
}

seEngine_Simple::seEngine_Simple()
{
	mInuptEventSys = nullptr;
	mSysWnd = nullptr;
	mRenderer = nullptr;
}

seEngine_Simple::~seEngine_Simple()
{

}

void seEngine_Simple::init()
{
	//create systems.
	//1.input event system
	mInuptEventSys = new seInputEventSystem(this);
	//2.window system
	mSysWnd = CreateSysWnd(mInuptEventSys);
	//3.renderer
	mRenderer = CreateRenderer();
}

void seEngine_Simple::Close()
{
	mRenderer->UnInit();
	DelOBJ(mSysWnd);
	DelOBJ(mRenderer);
}

void seEngine_Simple::InitConfig(const seConfig& config)
{
	mSysWnd->CreateWnd(config);
	mRenderer->Init(mSysWnd);
}

void seEngine_Simple::Run()
{
	bool exit = false;
	do {
		mSysWnd->Run(exit);
		mRenderer->DoRender();
		BreakIf(exit);
	} while (true);
}

seRenderer* seEngine_Simple::GetRenderer() const
{
	return mRenderer;
}

bool seEngine_Simple::OnSize(int width, int height)
{
	mRenderer->OnSize(width, height);
	return true;
}