
#include<cstdlib>
#include<cstdio>

#include "precompiled.h"

int waitForInput()
{
	system("pause");
	return 0;
}

int main()
{
	seRotation rot(seVec3(0, 0, 0), seVec3(0, 1, 0), seMath::ONEFOURTH_PI);
	seQuat quat = rot.ToQuat();
	seMat3 rMat3 = rot.ToMat3();
	seMat3 qMat3 = quat.ToMat3();
	bool equal = rMat3 == qMat3;
	return waitForInput();
}

