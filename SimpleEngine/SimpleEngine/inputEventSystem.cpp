#include "precompiled.h"
#pragma hdrstop

#include "inuptEventSystem.h"

seInputEventSystem::seInputEventSystem(seEngine* engine)
{
	mEngine = engine;
}

bool seInputEventSystem::OnMsg(seInputPackage& iEvent)
{
	ReturnValIf(iEvent.msg >= EventType_Count, false);
	if (iEvent.msg == EventType_Size){
		mEngine->OnSize(iEvent.param[0], iEvent.param[1]);
		return true;
	}
	return false;
}

