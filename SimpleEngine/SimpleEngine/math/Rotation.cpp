#include "../precompiled.h"
#pragma hdrstop


/*
============
seRotation::ToAngles
============
*/
seAngles seRotation::ToAngles( void ) const {
	return ToMat3().ToAngles();
}

/*
============
seRotation::ToQuat
============
*/
seQuat seRotation::ToQuat( void ) const {
	float a, s, c;

	a = angle * ( seMath::M_DEG2RAD * 0.5f );
	seMath::SinCos( a, s, c );
	return seQuat( vec.x * s, vec.y * s, vec.z * s, c );
}

/*
============
seRotation::toMat3
============
*/
const seMat3 &seRotation::ToMat3( void ) const {
	float wx, wy, wz;
	float xx, yy, yz;
	float xy, xz, zz;
	float x2, y2, z2;
	float a, c, s, x, y, z;

	if ( axisValid ) {
		return axis;
	}

	a = angle * ( seMath::M_DEG2RAD * 0.5f );
	seMath::SinCos( a, s, c );

	x = vec[0] * s;
	y = vec[1] * s;
	z = vec[2] * s;

	x2 = x + x;
	y2 = y + y;
	z2 = z + z;

	xx = x * x2;
	xy = x * y2;
	xz = x * z2;

	yy = y * y2;
	yz = y * z2;
	zz = z * z2;

	wx = c * x2;
	wy = c * y2;
	wz = c * z2;

	axis[ 0 ][ 0 ] = 1.0f - ( yy + zz );
	axis[ 0 ][ 1 ] = xy - wz;
	axis[ 0 ][ 2 ] = xz + wy;

	axis[ 1 ][ 0 ] = xy + wz;
	axis[ 1 ][ 1 ] = 1.0f - ( xx + zz );
	axis[ 1 ][ 2 ] = yz - wx;

	axis[ 2 ][ 0 ] = xz - wy;
	axis[ 2 ][ 1 ] = yz + wx;
	axis[ 2 ][ 2 ] = 1.0f - ( xx + yy );

	axisValid = true;

	return axis;
}

/*
============
seRotation::ToMat4
============
*/
seMat4 seRotation::ToMat4( void ) const {
	return ToMat3().ToMat4();
}

/*
============
seRotation::ToAngularVelocity
============
*/
seVec3 seRotation::ToAngularVelocity( void ) const {
	return vec * DEG2RAD( angle );
}

/*
============
seRotation::Normalize180
============
*/
void seRotation::Normalize180( void ) {
	angle -= floor( angle / 360.0f ) * 360.0f;
	if ( angle > 180.0f ) {
		angle -= 360.0f;
	}
	else if ( angle < -180.0f ) {
		angle += 360.0f;
	}
}

/*
============
seRotation::Normalize360
============
*/
void seRotation::Normalize360( void ) {
	angle -= floor( angle / 360.0f ) * 360.0f;
	if ( angle > 360.0f ) {
		angle -= 360.0f;
	}
	else if ( angle < 0.0f ) {
		angle += 360.0f;
	}
}
