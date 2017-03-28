#include "precompiled.h"
#pragma hdrstop

#include "SimpleEngine.h"
#include "sys/IWndSys.h"

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
	mWndSys = nullptr;
}

seEngine::~seEngine()
{

}

void seEngine::init()
{
	//create systems.
	//1.window system
	mWndSys = CreateWndSystem();

}

void seEngine::Close()
{
}

void seEngine::InitConfig(const seConfig& config)
{
	mWndSys->CreateWnd(config);
}

void seEngine::Run()
{
	bool exit = false;
	while (true) {
		mWndSys->Run(exit);
		if (exit)
			break;
	}
}
