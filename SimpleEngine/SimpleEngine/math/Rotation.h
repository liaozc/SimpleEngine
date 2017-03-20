
#ifndef __MATH_ROTATION_H__
#define __MATH_ROTATION_H__

/*
===============================================================================
	Describes a complete rotation in degrees about an abritray axis.
	A local rotation matrix is stored for fast rotation of multiple points.
===============================================================================
*/


class seAngles;
class seQuat;
class seMat3;

class DLL_INTERFACE seRotation {

	friend class seAngles;
	friend class seQuat;
	friend class seMat3;

public:
						seRotation( void );
						seRotation( const seVec3 &rotationOrigin, const seVec3 &rotationVec, const float rotationAngle );

	void				Set( const seVec3 &rotationOrigin, const seVec3 &rotationVec, const float rotationAngle );
	void				SetOrigin( const seVec3 &rotationOrigin );
	void				SetVec( const seVec3 &rotationVec );					// has to be normalized
	void				SetVec( const float x, const float y, const float z );	// has to be normalized
	void				SetAngle( const float rotationAngle );
	void				Scale( const float s );
	void				ReCalculateMatrix( void );
	const seVec3 &		GetOrigin( void ) const;
	const seVec3 &		GetVec( void ) const;
	float				GetAngle( void ) const;

	seRotation			operator-() const;										// flips rotation
	seRotation			operator*( const float s ) const;						// scale rotation
	seRotation			operator/( const float s ) const;						// scale rotation
	seRotation &		operator*=( const float s );							// scale rotation
	seRotation &		operator/=( const float s );							// scale rotation
	seVec3				operator*( const seVec3 &v ) const;						// rotate vector

	friend seRotation	operator*( const float s, const seRotation &r );		// scale rotation
	friend seVec3		operator*( const seVec3 &v, const seRotation &r );		// rotate vector
	friend seVec3 &		operator*=( seVec3 &v, const seRotation &r );			// rotate vector

	seAngles			ToAngles( void ) const;
	seQuat				ToQuat( void ) const;
	const seMat3 &		ToMat3( void ) const;
	seMat4				ToMat4( void ) const;
	seVec3				ToAngularVelocity( void ) const;

	void				RotatePoint( seVec3 &point ) const;

	void				Normalize180( void );
	void				Normalize360( void );

private:
	seVec3				origin;			// origin of rotation
	seVec3				vec;			// normalized vector to rotate around
	float				angle;			// angle of rotation in degrees
	mutable seMat3		axis;			// rotation axis
	mutable bool		axisValid;		// true if rotation axis is valid
};


SE_INLINE seRotation::seRotation( void ) {
}

SE_INLINE seRotation::seRotation( const seVec3 &rotationOrigin, const seVec3 &rotationVec, const float rotationAngle ) {
	origin = rotationOrigin;
	vec = rotationVec;
	angle = rotationAngle;
	axisValid = false;
}

SE_INLINE void seRotation::Set( const seVec3 &rotationOrigin, const seVec3 &rotationVec, const float rotationAngle ) {
	origin = rotationOrigin;
	vec = rotationVec;
	angle = rotationAngle;
	axisValid = false;
}

SE_INLINE void seRotation::SetOrigin( const seVec3 &rotationOrigin ) {
	origin = rotationOrigin;
}

SE_INLINE void seRotation::SetVec( const seVec3 &rotationVec ) {
	vec = rotationVec;
	axisValid = false;
}

SE_INLINE void seRotation::SetVec( float x, float y, float z ) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	axisValid = false;
}

SE_INLINE void seRotation::SetAngle( const float rotationAngle ) {
	angle = rotationAngle;
	axisValid = false;
}

SE_INLINE void seRotation::Scale( const float s ) {
	angle *= s;
	axisValid = false;
}

SE_INLINE void seRotation::ReCalculateMatrix( void ) {
	axisValid = false;
	ToMat3();
}

SE_INLINE const seVec3 &seRotation::GetOrigin( void ) const {
	return origin;
}

SE_INLINE const seVec3 &seRotation::GetVec( void ) const  {
	return vec;
}

SE_INLINE float seRotation::GetAngle( void ) const  {
	return angle;
}

SE_INLINE seRotation seRotation::operator-() const {
	return seRotation( origin, vec, -angle );
}

SE_INLINE seRotation seRotation::operator*( const float s ) const {
	return seRotation( origin, vec, angle * s );
}

SE_INLINE seRotation seRotation::operator/( const float s ) const {
	assert( s != 0.0f );
	return seRotation( origin, vec, angle / s );
}

SE_INLINE seRotation &seRotation::operator*=( const float s ) {
	angle *= s;
	axisValid = false;
	return *this;
}

SE_INLINE seRotation &seRotation::operator/=( const float s ) {
	assert( s != 0.0f );
	angle /= s;
	axisValid = false;
	return *this;
}

SE_INLINE seVec3 seRotation::operator*( const seVec3 &v ) const {
	if ( !axisValid ) {
		ToMat3();
	}
	return ((v - origin) * axis + origin);
}

SE_INLINE seRotation operator*( const float s, const seRotation &r ) {
	return r * s;
}

SE_INLINE seVec3 operator*( const seVec3 &v, const seRotation &r ) {
	return r * v;
}

SE_INLINE seVec3 &operator*=( seVec3 &v, const seRotation &r ) {
	v = r * v;
	return v;
}

SE_INLINE void seRotation::RotatePoint( seVec3 &point ) const {
	if ( !axisValid ) {
		ToMat3();
	}
	point = ((point - origin) * axis + origin);
}

#endif /* !__MATH_ROTATION_H__ */
