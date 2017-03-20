
#ifndef __MATH_QUAT_H__
#define __MATH_QUAT_H__

/*
===============================================================================

	Quaternion

===============================================================================
*/


class seVec3;
class seAngles;
class seRotation;
class seMat3;
class seMat4;
class seCQuat;

class DLL_INTERFACE seQuat {
public:
	float			x;
	float			y;
	float			z;
	float			w;

					seQuat( void );
					seQuat( float x, float y, float z, float w );

	void 			Set( float x, float y, float z, float w );

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	seQuat			operator-() const;
	seQuat &		operator=( const seQuat &a );
	seQuat			operator+( const seQuat &a ) const;
	seQuat &		operator+=( const seQuat &a );
	seQuat			operator-( const seQuat &a ) const;
	seQuat &		operator-=( const seQuat &a );
	seQuat			operator*( const seQuat &a ) const;
	seVec3			operator*( const seVec3 &a ) const;
	seQuat			operator*( float a ) const;
	seQuat &		operator*=( const seQuat &a );
	seQuat &		operator*=( float a );

	friend seQuat	operator*( const float a, const seQuat &b );
	friend seVec3	operator*( const seVec3 &a, const seQuat &b );

	bool			Compare( const seQuat &a ) const;						// exact compare, no epsilon
	bool			Compare( const seQuat &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const seQuat &a ) const;					// exact compare, no epsilon
	bool			operator!=(	const seQuat &a ) const;					// exact compare, no epsilon

	seQuat			Inverse( void ) const;
	float			Length( void ) const;
	seQuat &		Normalize( void );

	float			CalcW( void ) const;
	int				GetDimension( void ) const;

	seAngles		ToAngles( void ) const;
	seRotation		ToRotation( void ) const;
	seMat3			ToMat3( void ) const;
	seMat4			ToMat4( void ) const;
	seCQuat			ToCQuat( void ) const;
	seVec3			ToAngularVelocity( void ) const;
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	const char *	ToString( int precision = 2 ) const;

	seQuat &		Slerp( const seQuat &from, const seQuat &to, float t );
};

SE_INLINE seQuat::seQuat( void ) {
}

SE_INLINE seQuat::seQuat( float x, float y, float z, float w ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

SE_INLINE float seQuat::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < 4 ) );
	return ( &x )[ index ];
}

SE_INLINE float& seQuat::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < 4 ) );
	return ( &x )[ index ];
}

SE_INLINE seQuat seQuat::operator-() const {
	return seQuat( -x, -y, -z, -w );
}

SE_INLINE seQuat &seQuat::operator=( const seQuat &a ) {
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;

	return *this;
}

SE_INLINE seQuat seQuat::operator+( const seQuat &a ) const {
	return seQuat( x + a.x, y + a.y, z + a.z, w + a.w );
}

SE_INLINE seQuat& seQuat::operator+=( const seQuat &a ) {
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
}

SE_INLINE seQuat seQuat::operator-( const seQuat &a ) const {
	return seQuat( x - a.x, y - a.y, z - a.z, w - a.w );
}

SE_INLINE seQuat& seQuat::operator-=( const seQuat &a ) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
}

SE_INLINE seQuat seQuat::operator*( const seQuat &a ) const {
	return seQuat(	w*a.x + x*a.w + y*a.z - z*a.y,
					w*a.y + y*a.w + z*a.x - x*a.z,
					w*a.z + z*a.w + x*a.y - y*a.x,
					w*a.w - x*a.x - y*a.y - z*a.z );
}

SE_INLINE seVec3 seQuat::operator*( const seVec3 &a ) const {
#if 0
	// it's faster to do the conversion to a 3x3 matrix and multiply the vector by this 3x3 matrix
	return ( ToMat3() * a );
#else
	// result = this->Inverse() * seQuat( a.x, a.y, a.z, 0.0f ) * (*this)
	float xxzz = x*x - z*z;
	float wwyy = w*w - y*y;

	float xw2 = x*w*2.0f;
	float xy2 = x*y*2.0f;
	float xz2 = x*z*2.0f;
	float yw2 = y*w*2.0f;
	float yz2 = y*z*2.0f;
	float zw2 = z*w*2.0f;

	return seVec3(
		(xxzz + wwyy)*a.x		+ (xy2 + zw2)*a.y		+ (xz2 - yw2)*a.z,
		(xy2 - zw2)*a.x			+ (y*y+w*w-x*x-z*z)*a.y	+ (yz2 + xw2)*a.z,
		(xz2 + yw2)*a.x			+ (yz2 - xw2)*a.y		+ (wwyy - xxzz)*a.z
	);
#endif
}

SE_INLINE seQuat seQuat::operator*( float a ) const {
	return seQuat( x * a, y * a, z * a, w * a );
}

SE_INLINE seQuat operator*( const float a, const seQuat &b ) {
	return b * a;
}

SE_INLINE seVec3 operator*( const seVec3 &a, const seQuat &b ) {
	return b * a;
}

SE_INLINE seQuat& seQuat::operator*=( const seQuat &a ) {
	*this = *this * a;

	return *this;
}

SE_INLINE seQuat& seQuat::operator*=( float a ) {
	x *= a;
	y *= a;
	z *= a;
	w *= a;

	return *this;
}

SE_INLINE bool seQuat::Compare( const seQuat &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) && ( w == a.w ) );
}

SE_INLINE bool seQuat::Compare( const seQuat &a, const float epsilon ) const {
	if ( seMath::Fabs( x - a.x ) > epsilon ) {
		return false;
	}
	if ( seMath::Fabs( y - a.y ) > epsilon ) {
		return false;
	}
	if ( seMath::Fabs( z - a.z ) > epsilon ) {
		return false;
	}
	if ( seMath::Fabs( w - a.w ) > epsilon ) {
		return false;
	}
	return true;
}

SE_INLINE bool seQuat::operator==( const seQuat &a ) const {
	return Compare( a );
}

SE_INLINE bool seQuat::operator!=( const seQuat &a ) const {
	return !Compare( a );
}

SE_INLINE void seQuat::Set( float x, float y, float z, float w ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

SE_INLINE seQuat seQuat::Inverse( void ) const {
	return seQuat( -x, -y, -z, w );
}

SE_INLINE float seQuat::Length( void ) const {
	float len;

	len = x * x + y * y + z * z + w * w;
	return seMath::Sqrt( len );
}

SE_INLINE seQuat& seQuat::Normalize( void ) {
	float len;
	float ilength;

	len = this->Length();
	if ( len ) {
		ilength = 1 / len;
		x *= ilength;
		y *= ilength;
		z *= ilength;
		w *= ilength;
	}
	return *this;
}

SE_INLINE float seQuat::CalcW( void ) const {
	// take the absolute value because floating point rounding may cause the dot of x,y,z to be larger than 1
	return sqrt( fabs( 1.0f - ( x * x + y * y + z * z ) ) );
}

SE_INLINE int seQuat::GetDimension( void ) const {
	return 4;
}

SE_INLINE const float *seQuat::ToFloatPtr( void ) const {
	return &x;
}

SE_INLINE float *seQuat::ToFloatPtr( void ) {
	return &x;
}


/*
===============================================================================

	Compressed quaternion

===============================================================================
*/

class DLL_INTERFACE seCQuat {
public:
	float			x;
	float			y;
	float			z;

					seCQuat( void );
					seCQuat( float x, float y, float z );

	void 			Set( float x, float y, float z );

	float			operator[]( int index ) const;
	float &			operator[]( int index );

	bool			Compare( const seCQuat &a ) const;						// exact compare, no epsilon
	bool			Compare( const seCQuat &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const seCQuat &a ) const;					// exact compare, no epsilon
	bool			operator!=(	const seCQuat &a ) const;					// exact compare, no epsilon

	int				GetDimension( void ) const;

	seAngles		ToAngles( void ) const;
	seRotation		ToRotation( void ) const;
	seMat3			ToMat3( void ) const;
	seMat4			ToMat4( void ) const;
	seQuat			ToQuat( void ) const;
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	const char *	ToString( int precision = 2 ) const;
};

SE_INLINE seCQuat::seCQuat( void ) {
}

SE_INLINE seCQuat::seCQuat( float x, float y, float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

SE_INLINE void seCQuat::Set( float x, float y, float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

SE_INLINE float seCQuat::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &x )[ index ];
}

SE_INLINE float& seCQuat::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &x )[ index ];
}

SE_INLINE bool seCQuat::Compare( const seCQuat &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) );
}

SE_INLINE bool seCQuat::Compare( const seCQuat &a, const float epsilon ) const {
	if ( seMath::Fabs( x - a.x ) > epsilon ) {
		return false;
	}
	if ( seMath::Fabs( y - a.y ) > epsilon ) {
		return false;
	}
	if ( seMath::Fabs( z - a.z ) > epsilon ) {
		return false;
	}
	return true;
}

SE_INLINE bool seCQuat::operator==( const seCQuat &a ) const {
	return Compare( a );
}

SE_INLINE bool seCQuat::operator!=( const seCQuat &a ) const {
	return !Compare( a );
}

SE_INLINE int seCQuat::GetDimension( void ) const {
	return 3;
}

SE_INLINE seQuat seCQuat::ToQuat( void ) const {
	// take the absolute value because floating point rounding may cause the dot of x,y,z to be larger than 1
	return seQuat( x, y, z, sqrt( fabs( 1.0f - ( x * x + y * y + z * z ) ) ) );
}

SE_INLINE const float *seCQuat::ToFloatPtr( void ) const {
	return &x;
}

SE_INLINE float *seCQuat::ToFloatPtr( void ) {
	return &x;
}

#endif /* !__MATH_QUAT_H__ */
