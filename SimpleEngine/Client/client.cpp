
#include<cstdlib>
#include<cstdio>

#include "precompiled.h"

int waitForInput()
{
	printf("engine has quit.!\n");
//	system("pause");
	return 0;
}

int main()
{
	{//test math lib
		seRotation rot(seVec3(0, 0, 0), seVec3(0, 1, 0), seMath::ONEFOURTH_PI);
		seQuat quat = rot.ToQuat();
		seMat3 rMat3 = rot.ToMat3();
		seMat3 qMat3 = quat.ToMat3();
		bool equal = rMat3 == qMat3;
	}

	seEngine* gEngine = nullptr;
	{//test simple renderer
		//1.get the engine
		gEngine = GetSimpleEngine();
		//2.config and init.
		seConfig config;
		config.screenHeight = 480;
		config.screenWidth = 640;
		config.fullScreen = false;
		gEngine->InitConfig(config);
		//3.update the msg loop
		gEngine->Run();
	}
	
	waitForInput();
	//clear
	gEngine->Close();
	delete gEngine;
}

