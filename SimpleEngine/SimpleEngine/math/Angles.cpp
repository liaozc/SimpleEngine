#include "../precompiled.h"
#pragma hdrstop

#include <float.h>

seAngles ang_zero( 0.0f, 0.0f, 0.0f );


/*
=================
seAngles::Normalize360

returns angles normalized to the range [0 <= angle < 360]
=================
*/
seAngles& seAngles::Normalize360( void ) {
	int i;

	for ( i = 0; i < 3; i++ ) {
		if ( ( (*this)[i] >= 360.0f ) || ( (*this)[i] < 0.0f ) ) {
			(*this)[i] -= floorf( (*this)[i] / 360.0f ) * 360.0f;

			if ( (*this)[i] >= 360.0f ) {
				(*this)[i] -= 360.0f;
			}
			if ( (*this)[i] < 0.0f ) {
				(*this)[i] += 360.0f;
			}
		}
	}

	return *this;
}

/*
=================
seAngles::Normalize180

returns angles normalized to the range [-180 < angle <= 180]
=================
*/
seAngles& seAngles::Normalize180( void ) {
	Normalize360();

	if ( pitch > 180.0f ) {
		pitch -= 360.0f;
	}
	
	if ( yaw > 180.0f ) {
		yaw -= 360.0f;
	}

	if ( roll > 180.0f ) {
		roll -= 360.0f;
	}
	return *this;
}

/*
=================
seAngles::ToVectors
=================
*/
void seAngles::ToVectors( seVec3 *forward, seVec3 *right, seVec3 *up ) const {
	float sr, sp, sy, cr, cp, cy;
	
	seMath::SinCos( DEG2RAD( yaw ), sy, cy );
	seMath::SinCos( DEG2RAD( pitch ), sp, cp );
	seMath::SinCos( DEG2RAD( roll ), sr, cr );

	if ( forward ) {
		forward->Set( cp * cy, cp * sy, -sp );
	}

	if ( right ) {
		right->Set( -sr * sp * cy + cr * sy, -sr * sp * sy + -cr * cy, -sr * cp );
	}

	if ( up ) {
		up->Set( cr * sp * cy + -sr * -sy, cr * sp * sy + -sr * cy, cr * cp );
	}
}

/*
=================
seAngles::ToForward
=================
*/
seVec3 seAngles::ToForward( void ) const {
	float sp, sy, cp, cy;
	
	seMath::SinCos( DEG2RAD( yaw ), sy, cy );
	seMath::SinCos( DEG2RAD( pitch ), sp, cp );

	return seVec3( cp * cy, cp * sy, -sp );
}

/*
=================
seAngles::ToQuat
=================
*/

seQuat seAngles::ToQuat( void ) const {
	float sx, cx, sy, cy, sz, cz;
	float sxcy, cxcy, sxsy, cxsy;

	seMath::SinCos( DEG2RAD( yaw ) * 0.5f, sz, cz );
	seMath::SinCos( DEG2RAD( pitch ) * 0.5f, sy, cy );
	seMath::SinCos( DEG2RAD( roll ) * 0.5f, sx, cx );

	sxcy = sx * cy;
	cxcy = cx * cy;
	sxsy = sx * sy;
	cxsy = cx * sy;

	return seQuat( cxsy*sz - sxcy*cz, -cxsy*cz - sxcy*sz, sxsy*cz - cxcy*sz, cxcy*cz + sxsy*sz );
}


/*
=================
seAngles::ToRotation
=================
*/

seRotation seAngles::ToRotation( void ) const {
	seVec3 vec;
	float angle, w;
	float sx, cx, sy, cy, sz, cz;
	float sxcy, cxcy, sxsy, cxsy;

	if ( pitch == 0.0f ) {
		if ( yaw == 0.0f ) {
			return seRotation( vec3_origin, seVec3( -1.0f, 0.0f, 0.0f ), roll );
		}
		if ( roll == 0.0f ) {
			return seRotation( vec3_origin, seVec3( 0.0f, 0.0f, -1.0f ), yaw );
		}
	} else if ( yaw == 0.0f && roll == 0.0f ) {
		return seRotation( vec3_origin, seVec3( 0.0f, -1.0f, 0.0f ), pitch );
	}

	seMath::SinCos( DEG2RAD( yaw ) * 0.5f, sz, cz );
	seMath::SinCos( DEG2RAD( pitch ) * 0.5f, sy, cy );
	seMath::SinCos( DEG2RAD( roll ) * 0.5f, sx, cx );

	sxcy = sx * cy;
	cxcy = cx * cy;
	sxsy = sx * sy;
	cxsy = cx * sy;

	vec.x =  cxsy * sz - sxcy * cz;
	vec.y = -cxsy * cz - sxcy * sz;
	vec.z =  sxsy * cz - cxcy * sz;
	w =		 cxcy * cz + sxsy * sz;
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
=================
seAngles::ToMat3
=================
*/

seMat3 seAngles::ToMat3( void ) const {
	seMat3 mat;
	float sr, sp, sy, cr, cp, cy;

	seMath::SinCos( DEG2RAD( yaw ), sy, cy );
	seMath::SinCos( DEG2RAD( pitch ), sp, cp );
	seMath::SinCos( DEG2RAD( roll ), sr, cr );

	mat[ 0 ].Set( cp * cy, cp * sy, -sp );
	mat[ 1 ].Set( sr * sp * cy + cr * -sy, sr * sp * sy + cr * cy, sr * cp );
	mat[ 2 ].Set( cr * sp * cy + -sr * -sy, cr * sp * sy + -sr * cy, cr * cp );

	return mat;
}


/*
=================
seAngles::ToMat4
=================
*/

seMat4 seAngles::ToMat4( void ) const {
	return ToMat3().ToMat4();
}


/*
=================
seAngles::ToAngularVelocity
=================
*/

seVec3 seAngles::ToAngularVelocity( void ) const {
	seRotation rotation = seAngles::ToRotation();
	return rotation.GetVec() * DEG2RAD( rotation.GetAngle() );
}


/*
=============
seAngles::ToString
=============
*/
const char *seAngles::ToString( int precision ) const {
	return "not implented";
}
