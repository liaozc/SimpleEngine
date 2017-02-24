
#include<cstdlib>
#include<cstdio>

#include "math/Vector.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"

using namespace SimpleEngine;

void waitForInput()
{
	printf("\n");
	system("pause");
}

int main()
{
	Vector3 v(1, 0, 0);
	Quaternion q = Quaternion::FromRotatedAxis(Vector3(0, 1, 0), 0.785f);
	Vector3 v2 = q.RotVec3(v);
	printf("v : <%.2f,%.2f£¬%.2f> \n", v2.x, v2.y, v2.z);

	Mat3 m = q.ToMat();
	Vector3 v3 = m * v;
	printf("v : <%.2f,%.2f£¬%.2f> \n", v3.x, v3.y, v3.z);

	waitForInput();
	return 0;
}

