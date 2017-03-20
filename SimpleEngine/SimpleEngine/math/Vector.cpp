#include "../precompiled.h"
#pragma hdrstop


seVec2 vec2_origin(0.0f, 0.0f);
seVec3 vec3_origin(0.0f, 0.0f, 0.0f);
seVec4 vec4_origin(0.0f, 0.0f, 0.0f, 0.0f);

/*
=============
seVec2::ToString
=============
*/
const char *seVec2::ToString(int precision) const {
	return "not implented";
}

/*
=============
Lerp

Linearly inperpolates one vector to another.
=============
*/
void seVec2::Lerp(const seVec2 &v1, const seVec2 &v2, const float l) {
	if (l <= 0.0f) {
		(*this) = v1;
	}
	else if (l >= 1.0f) {
		(*this) = v2;
	}
	else {
		(*this) = v1 + l * (v2 - v1);
	}
}



//===============================================================
//
//	seVec3
//
//===============================================================

/*
=============
seVec3::ToYaw
=============
*/
float seVec3::ToYaw(void) const {
	float yaw;

	if ((y == 0.0f) && (x == 0.0f)) {
		yaw = 0.0f;
	}
	else {
		yaw = RAD2DEG(atan2f(y, x));
		if (yaw < 0.0f) {
			yaw += 360.0f;
		}
	}

	return yaw;
}

/*
=============
seVec3::ToPitch
=============
*/
float seVec3::ToPitch(void) const {
	float	forward;
	float	pitch;

	if ((x == 0.0f) && (y == 0.0f)) {
		if (z > 0.0f) {
			pitch = 90.0f;
		}
		else {
			pitch = 270.0f;
		}
	}
	else {
		forward = (float)seMath::Sqrt(x * x + y * y);
		pitch = RAD2DEG(atan2f(z, forward));
		if (pitch < 0.0f) {
			pitch += 360.0f;
		}
	}

	return pitch;
}

/*
=============
seVec3::ToAngles
=============
*/
seAngles seVec3::ToAngles(void) const {
	float forward;
	float yaw;
	float pitch;

	if ((x == 0.0f) && (y == 0.0f)) {
		yaw = 0.0f;
		if (z > 0.0f) {
			pitch = 90.0f;
		}
		else {
			pitch = 270.0f;
		}
	}
	else {
		yaw = RAD2DEG(atan2f(y, x));
		if (yaw < 0.0f) {
			yaw += 360.0f;
		}

		forward = (float)seMath::Sqrt(x * x + y * y);
		pitch = RAD2DEG(atan2f(z, forward));
		if (pitch < 0.0f) {
			pitch += 360.0f;
		}
	}

	return seAngles(-pitch, yaw, 0.0f);
}

/*
=============
seVec3::ToPolar
=============
*/
sePolar3 seVec3::ToPolar(void) const {
	float forward;
	float yaw;
	float pitch;

	if ((x == 0.0f) && (y == 0.0f)) {
		yaw = 0.0f;
		if (z > 0.0f) {
			pitch = 90.0f;
		}
		else {
			pitch = 270.0f;
		}
	}
	else {
		yaw = RAD2DEG(atan2f(y, x));
		if (yaw < 0.0f) {
			yaw += 360.0f;
		}

		forward = (float)seMath::Sqrt(x * x + y * y);
		pitch = RAD2DEG(atan2f(z, forward));
		if (pitch < 0.0f) {
			pitch += 360.0f;
		}
	}
	return sePolar3(seMath::Sqrt(x * x + y * y + z * z), yaw, -pitch);
}

/*
=============
seVec3::ToMat3
=============
*/

seMat3 seVec3::ToMat3(void) const {
	seMat3	mat;
	float	d;

	mat[0] = *this;
	d = x * x + y * y;
	if (!d) {
		mat[1][0] = 1.0f;
		mat[1][1] = 0.0f;
		mat[1][2] = 0.0f;
	}
	else {
		d = seMath::InvSqrt(d);
		mat[1][0] = -y * d;
		mat[1][1] = x * d;
		mat[1][2] = 0.0f;
	}
	mat[2] = Cross(mat[1]);

	return mat;
}


/*
=============
seVec3::ToString
=============
*/
const char *seVec3::ToString(int precision) const {
	return "not implented";
}

/*
=============
Lerp

Linearly inperpolates one vector to another.
=============
*/
void seVec3::Lerp(const seVec3 &v1, const seVec3 &v2, const float l) {
	if (l <= 0.0f) {
		(*this) = v1;
	}
	else if (l >= 1.0f) {
		(*this) = v2;
	}
	else {
		(*this) = v1 + l * (v2 - v1);
	}
}

/*
=============
SLerp

Spherical linear interpolation from v1 to v2.
Vectors are expected to be normalized.
=============
*/
#define LERP_DELTA 1e-6

void seVec3::SLerp(const seVec3 &v1, const seVec3 &v2, const float t) {
	float omega, cosom, sinom, scale0, scale1;

	if (t <= 0.0f) {
		(*this) = v1;
		return;
	}
	else if (t >= 1.0f) {
		(*this) = v2;
		return;
	}

	cosom = v1 * v2;
	if ((1.0f - cosom) > LERP_DELTA) {
		omega = acosf(cosom);
		sinom = sinf(omega);
		scale0 = sinf((1.0f - t) * omega) / sinom;
		scale1 = sinf(t * omega) / sinom;
	}
	else {
		scale0 = 1.0f - t;
		scale1 = t;
	}

	(*this) = (v1 * scale0 + v2 * scale1);
}

/*
=============
ProjectSelfOntoSphere

Projects the z component onto a sphere.
=============
*/
void seVec3::ProjectSelfOntoSphere(const float radius) {
	float rsqr = radius * radius;
	float len = Length();
	if (len  < rsqr * 0.5f) {
		z = sqrtf(rsqr - len);
	}
	else {
		z = rsqr / (2.0f * sqrtf(len));
	}
}


//===============================================================
//
//	seVec4
//
//===============================================================

/*
=============
seVec4::ToString
=============
*/
const char *seVec4::ToString(int precision) const {
	return "not implented";
}

/*
=============
Lerp

Linearly inperpolates one vector to another.
=============
*/
void seVec4::Lerp(const seVec4 &v1, const seVec4 &v2, const float l) {
	if (l <= 0.0f) {
		(*this) = v1;
	}
	else if (l >= 1.0f) {
		(*this) = v2;
	}
	else {
		(*this) = v1 + l * (v2 - v1);
	}
}
