#include "../precompiled.h"
#pragma hdrstop

/*
=====================
seQuat::ToAngles
=====================
*/
seAngles seQuat::ToAngles( void ) const {
	return ToMat3().ToAngles();
}

/*
=====================
seQuat::ToRotation
=====================
*/
seRotation seQuat::ToRotation( void ) const {
	seVec3 vec;
	float angle;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	angle = seMath::ACos( w );
	if ( angle == 0.0f ) {
		vec.Set( 0.0f, 0.0f, 1.0f );
	} else {
		//vec *= (1.0f / sin( angle ));
		vec.Normalize();
		vec.FixDegenerateNormal();
		angle *= 2.0f * seMath::M_RAD2DEG;
	}
	return seRotation( vec3_origin, vec, angle );
}

/*
=====================
seQuat::ToMat3
=====================
*/
seMat3 seQuat::ToMat3( void ) const {
	seMat3	mat;
	float	wx, wy, wz;
	float	xx, yy, yz;
	float	xy, xz, zz;
	float	x2, y2, z2;

	x2 = x + x;
	y2 = y + y;
	z2 = z + z;

	xx = x * x2;
	xy = x * y2;
	xz = x * z2;

	yy = y * y2;
	yz = y * z2;
	zz = z * z2;

	wx = w * x2;
	wy = w * y2;
	wz = w * z2;

	mat[ 0 ][ 0 ] = 1.0f - ( yy + zz );
	mat[ 0 ][ 1 ] = xy - wz;
	mat[ 0 ][ 2 ] = xz + wy;

	mat[ 1 ][ 0 ] = xy + wz;
	mat[ 1 ][ 1 ] = 1.0f - ( xx + zz );
	mat[ 1 ][ 2 ] = yz - wx;

	mat[ 2 ][ 0 ] = xz - wy;
	mat[ 2 ][ 1 ] = yz + wx;
	mat[ 2 ][ 2 ] = 1.0f - ( xx + yy );

	return mat;
}

/*
=====================
seQuat::ToMat4
=====================
*/
seMat4 seQuat::ToMat4( void ) const {
	return ToMat3().ToMat4();
}

/*
=====================
seQuat::ToCQuat
=====================
*/
seCQuat seQuat::ToCQuat( void ) const {
	if ( w < 0.0f ) {
		return seCQuat( -x, -y, -z );
	}
	return seCQuat( x, y, z );
}

/*
============
seQuat::ToAngularVelocity
============
*/
seVec3 seQuat::ToAngularVelocity( void ) const {
	seVec3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.Normalize();
	return vec * seMath::ACos( w );
}

/*
=============
seQuat::ToString
=============
*/
const char *seQuat::ToString( int precision ) const {
	return "not implented";
}

/*
=====================
seQuat::Slerp

Spherical linear interpolation between two quaternions.
=====================
*/
seQuat &seQuat::Slerp( const seQuat &from, const seQuat &to, float t ) {
	seQuat	temp;
	float	omega, cosom, sinom, scale0, scale1;

	if ( t <= 0.0f ) {
		*this = from;
		return *this;
	}

	if ( t >= 1.0f ) {
		*this = to;
		return *this;
	}

	if ( from == to ) {
		*this = to;
		return *this;
	}

	cosom = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;
	if ( cosom < 0.0f ) {
		temp = -to;
		cosom = -cosom;
	} else {
		temp = to;
	}

	if ( ( 1.0f - cosom ) > 1e-6f ) {
#if 0
		omega = acos( cosom );
		sinom = 1.0f / sin( omega );
		scale0 = sin( ( 1.0f - t ) * omega ) * sinom;
		scale1 = sin( t * omega ) * sinom;
#else
		scale0 = 1.0f - cosom * cosom;
		sinom = seMath::InvSqrt( scale0 );
		omega = seMath::ATan16( scale0 * sinom, cosom );
		scale0 = seMath::Sin16( ( 1.0f - t ) * omega ) * sinom;
		scale1 = seMath::Sin16( t * omega ) * sinom;
#endif
	} else {
		scale0 = 1.0f - t;
		scale1 = t;
	}

	*this = ( scale0 * from ) + ( scale1 * temp );
	return *this;
}

/*
=============
seCQuat::ToAngles
=============
*/
seAngles seCQuat::ToAngles( void ) const {
	return ToQuat().ToAngles();
}

/*
=============
seCQuat::ToRotation
=============
*/
seRotation seCQuat::ToRotation( void ) const {
	return ToQuat().ToRotation();
}

/*
=============
seCQuat::ToMat3
=============
*/
seMat3 seCQuat::ToMat3( void ) const {
	return ToQuat().ToMat3();
}

/*
=============
seCQuat::ToMat4
=============
*/
seMat4 seCQuat::ToMat4( void ) const {
	return ToQuat().ToMat4();
}

/*
=============
seCQuat::ToString
=============
*/
const char *seCQuat::ToString( int precision ) const {
	return "not implented";
}
