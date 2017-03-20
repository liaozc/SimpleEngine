#ifndef __MATH_ANGLES_H__
#define __MATH_ANGLES_H__

/*
===============================================================================
	Euler angles
===============================================================================
*/

// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

class seVec3;
class seQuat;
class seRotation;
class seMat3;
class seMat4;

class DLL_INTERFACE seAngles {
public:
	float			pitch;
	float			yaw;
	float			roll;

					seAngles( void );
					seAngles( float pitch, float yaw, float roll );
					explicit seAngles( const seVec3 &v );

	void 			Set( float pitch, float yaw, float roll );
	seAngles &		Zero( void );

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	seAngles		operator-() const;			// negate angles, in general not the inverse rotation
	seAngles &		operator=( const seAngles &a );
	seAngles		operator+( const seAngles &a ) const;
	seAngles &		operator+=( const seAngles &a );
	seAngles		operator-( const seAngles &a ) const;
	seAngles &		operator-=( const seAngles &a );
	seAngles		operator*( const float a ) const;
	seAngles &		operator*=( const float a );
	seAngles		operator/( const float a ) const;
	seAngles &		operator/=( const float a );

	friend seAngles	operator*( const float a, const seAngles &b );

	bool			Compare( const seAngles &a ) const;							// exact compare, no epsilon
	bool			Compare( const seAngles &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const seAngles &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const seAngles &a ) const;						// exact compare, no epsilon

	seAngles &		Normalize360( void );	// normalizes 'this'
	seAngles &		Normalize180( void );	// normalizes 'this'

	void			Clamp( const seAngles &min, const seAngles &max );

	int				GetDimension( void ) const;

	void			ToVectors( seVec3 *forward, seVec3 *right = NULL, seVec3 *up = NULL ) const;
	seVec3			ToForward( void ) const;
	
	
	seQuat			ToQuat( void ) const;
	seRotation		ToRotation( void ) const;
	seMat3			ToMat3( void ) const;
	seMat4			ToMat4( void ) const;
	seVec3			ToAngularVelocity( void ) const;
	

	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	const char *	ToString( int precision = 2 ) const;
};

extern seAngles ang_zero;

SE_INLINE seAngles::seAngles( void ) {
}

SE_INLINE seAngles::seAngles( float pitch, float yaw, float roll ) {
	this->pitch = pitch;
	this->yaw	= yaw;
	this->roll	= roll;
}

SE_INLINE seAngles::seAngles( const seVec3 &v ) {
	this->pitch = v[0];
	this->yaw	= v[1];
	this->roll	= v[2];
}

SE_INLINE void seAngles::Set( float pitch, float yaw, float roll ) {
	this->pitch = pitch;
	this->yaw	= yaw;
	this->roll	= roll;
}

SE_INLINE seAngles &seAngles::Zero( void ) {
	pitch = yaw = roll = 0.0f;
	return *this;
}

SE_INLINE float seAngles::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &pitch )[ index ];
}

SE_INLINE float &seAngles::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &pitch )[ index ];
}

SE_INLINE seAngles seAngles::operator-() const {
	return seAngles( -pitch, -yaw, -roll );
}

SE_INLINE seAngles &seAngles::operator=( const seAngles &a ) {
	pitch	= a.pitch;
	yaw		= a.yaw;
	roll	= a.roll;
	return *this;
}

SE_INLINE seAngles seAngles::operator+( const seAngles &a ) const {
	return seAngles( pitch + a.pitch, yaw + a.yaw, roll + a.roll );
}

SE_INLINE seAngles& seAngles::operator+=( const seAngles &a ) {
	pitch	+= a.pitch;
	yaw		+= a.yaw;
	roll	+= a.roll;

	return *this;
}

SE_INLINE seAngles seAngles::operator-( const seAngles &a ) const {
	return seAngles( pitch - a.pitch, yaw - a.yaw, roll - a.roll );
}

SE_INLINE seAngles& seAngles::operator-=( const seAngles &a ) {
	pitch	-= a.pitch;
	yaw		-= a.yaw;
	roll	-= a.roll;

	return *this;
}

SE_INLINE seAngles seAngles::operator*( const float a ) const {
	return seAngles( pitch * a, yaw * a, roll * a );
}

SE_INLINE seAngles& seAngles::operator*=( float a ) {
	pitch	*= a;
	yaw		*= a;
	roll	*= a;
	return *this;
}

SE_INLINE seAngles seAngles::operator/( const float a ) const {
	float inva = 1.0f / a;
	return seAngles( pitch * inva, yaw * inva, roll * inva );
}

SE_INLINE seAngles& seAngles::operator/=( float a ) {
	float inva = 1.0f / a;
	pitch	*= inva;
	yaw		*= inva;
	roll	*= inva;
	return *this;
}

SE_INLINE seAngles operator*( const float a, const seAngles &b ) {
	return seAngles( a * b.pitch, a * b.yaw, a * b.roll );
}

SE_INLINE bool seAngles::Compare( const seAngles &a ) const {
	return ( ( a.pitch == pitch ) && ( a.yaw == yaw ) && ( a.roll == roll ) );
}

SE_INLINE bool seAngles::Compare( const seAngles &a, const float epsilon ) const {
	if ( seMath::Fabs( pitch - a.pitch ) > epsilon ) {
		return false;
	}
			
	if ( seMath::Fabs( yaw - a.yaw ) > epsilon ) {
		return false;
	}

	if ( seMath::Fabs( roll - a.roll ) > epsilon ) {
		return false;
	}

	return true;
}

SE_INLINE bool seAngles::operator==( const seAngles &a ) const {
	return Compare( a );
}

SE_INLINE bool seAngles::operator!=( const seAngles &a ) const {
	return !Compare( a );
}

SE_INLINE void seAngles::Clamp( const seAngles &min, const seAngles &max ) {
	if ( pitch < min.pitch ) {
		pitch = min.pitch;
	} else if ( pitch > max.pitch ) {
		pitch = max.pitch;
	}
	if ( yaw < min.yaw ) {
		yaw = min.yaw;
	} else if ( yaw > max.yaw ) {
		yaw = max.yaw;
	}
	if ( roll < min.roll ) {
		roll = min.roll;
	} else if ( roll > max.roll ) {
		roll = max.roll;
	}
}

SE_INLINE int seAngles::GetDimension( void ) const {
	return 3;
}

SE_INLINE const float *seAngles::ToFloatPtr( void ) const {
	return &pitch;
}

SE_INLINE float *seAngles::ToFloatPtr( void ) {
	return &pitch;
}

#endif /* !__MATH_ANGLES_H__ */
