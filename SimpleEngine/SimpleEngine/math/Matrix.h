#ifndef __MATH_MATRIX_H__
#define __MATH_MATRIX_H__

/*
===============================================================================

  Matrix classes, all matrices are row-major except seMat3

===============================================================================
*/

#define MATRIX_INVERSE_EPSILON		1e-14
#define MATRIX_EPSILON				1e-6

class seAngles;
class seQuat;
class seCQuat;
class seRotation;
class seMat4;

//===============================================================
//
//	seMat2 - 2x2 matrix
//
//===============================================================

class DLL_INTERFACE seMat2 {
public:
					seMat2( void );
					explicit seMat2( const seVec2 &x, const seVec2 &y );
					explicit seMat2( const float xx, const float xy, const float yx, const float yy );
					explicit seMat2( const float src[ 2 ][ 2 ] );

	const seVec2 &	operator[]( int index ) const;
	seVec2 &		operator[]( int index );
	seMat2			operator-() const;
	seMat2			operator*( const float a ) const;
	seVec2			operator*( const seVec2 &vec ) const;
	seMat2			operator*( const seMat2 &a ) const;
	seMat2			operator+( const seMat2 &a ) const;
	seMat2			operator-( const seMat2 &a ) const;
	seMat2 &		operator*=( const float a );
	seMat2 &		operator*=( const seMat2 &a );
	seMat2 &		operator+=( const seMat2 &a );
	seMat2 &		operator-=( const seMat2 &a );

	friend seMat2	operator*( const float a, const seMat2 &mat );
	friend seVec2	operator*( const seVec2 &vec, const seMat2 &mat );
	friend seVec2 &	operator*=( seVec2 &vec, const seMat2 &mat );

	bool			Compare( const seMat2 &a ) const;						// exact compare, no epsilon
	bool			Compare( const seMat2 &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const seMat2 &a ) const;					// exact compare, no epsilon
	bool			operator!=( const seMat2 &a ) const;					// exact compare, no epsilon

	void			Zero( void );
	void			Identity( void );
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;

	float			Trace( void ) const;
	float			Determinant( void ) const;
	seMat2			Transpose( void ) const;	// returns transpose
	seMat2 &		TransposeSelf( void );
	seMat2			Inverse( void ) const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf( void );		// returns false if determinant is zero
	seMat2			InverseFast( void ) const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf( void );	// returns false if determinant is zero

	int				GetDimension( void ) const;

	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	const char *	ToString( int precision = 2 ) const;

private:
	seVec2			mat[ 2 ];
};

extern seMat2 mat2_zero;
extern seMat2 mat2_identity;
#define mat2_default	mat2_identity

SE_INLINE seMat2::seMat2( void ) {
}

SE_INLINE seMat2::seMat2( const seVec2 &x, const seVec2 &y ) {
	mat[ 0 ].x = x.x; mat[ 0 ].y = x.y;
	mat[ 1 ].x = y.x; mat[ 1 ].y = y.y;
}

SE_INLINE seMat2::seMat2( const float xx, const float xy, const float yx, const float yy ) {
	mat[ 0 ].x = xx; mat[ 0 ].y = xy;
	mat[ 1 ].x = yx; mat[ 1 ].y = yy;
}

SE_INLINE seMat2::seMat2( const float src[ 2 ][ 2 ] ) {
	memcpy( mat, src, 2 * 2 * sizeof( float ) );
}

SE_INLINE const seVec2 &seMat2::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 2 ) );
	return mat[ index ];
}

SE_INLINE seVec2 &seMat2::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 2 ) );
	return mat[ index ];
}

SE_INLINE seMat2 seMat2::operator-() const {
	return seMat2(	-mat[0][0], -mat[0][1],
					-mat[1][0], -mat[1][1] );
}

SE_INLINE seVec2 seMat2::operator*( const seVec2 &vec ) const {
	return seVec2(
		mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y,
		mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y );
}

SE_INLINE seMat2 seMat2::operator*( const seMat2 &a ) const {
	return seMat2(
		mat[0].x * a[0].x + mat[0].y * a[1].x,
		mat[0].x * a[0].y + mat[0].y * a[1].y,
		mat[1].x * a[0].x + mat[1].y * a[1].x,
		mat[1].x * a[0].y + mat[1].y * a[1].y );
}

SE_INLINE seMat2 seMat2::operator*( const float a ) const {
	return seMat2(
		mat[0].x * a, mat[0].y * a, 
		mat[1].x * a, mat[1].y * a );
}

SE_INLINE seMat2 seMat2::operator+( const seMat2 &a ) const {
	return seMat2(
		mat[0].x + a[0].x, mat[0].y + a[0].y, 
		mat[1].x + a[1].x, mat[1].y + a[1].y );
}
    
SE_INLINE seMat2 seMat2::operator-( const seMat2 &a ) const {
	return seMat2(
		mat[0].x - a[0].x, mat[0].y - a[0].y,
		mat[1].x - a[1].x, mat[1].y - a[1].y );
}

SE_INLINE seMat2 &seMat2::operator*=( const float a ) {
	mat[0].x *= a; mat[0].y *= a;
	mat[1].x *= a; mat[1].y *= a;

    return *this;
}

SE_INLINE seMat2 &seMat2::operator*=( const seMat2 &a ) {
	float x, y;
	x = mat[0].x; y = mat[0].y;
	mat[0].x = x * a[0].x + y * a[1].x;
	mat[0].y = x * a[0].y + y * a[1].y;
	x = mat[1].x; y = mat[1].y;
	mat[1].x = x * a[0].x + y * a[1].x;
	mat[1].y = x * a[0].y + y * a[1].y;
	return *this;
}

SE_INLINE seMat2 &seMat2::operator+=( const seMat2 &a ) {
	mat[0].x += a[0].x; mat[0].y += a[0].y;
	mat[1].x += a[1].x; mat[1].y += a[1].y;

    return *this;
}

SE_INLINE seMat2 &seMat2::operator-=( const seMat2 &a ) {
	mat[0].x -= a[0].x; mat[0].y -= a[0].y;
	mat[1].x -= a[1].x; mat[1].y -= a[1].y;

    return *this;
}

SE_INLINE seVec2 operator*( const seVec2 &vec, const seMat2 &mat ) {
	return mat * vec;
}

SE_INLINE seMat2 operator*( const float a, seMat2 const &mat ) {
	return mat * a;
}

SE_INLINE seVec2 &operator*=( seVec2 &vec, const seMat2 &mat ) {
	vec = mat * vec;
	return vec;
}

SE_INLINE bool seMat2::Compare( const seMat2 &a ) const {
	if ( mat[0].Compare( a[0] ) &&
		mat[1].Compare( a[1] ) ) {
		return true;
	}
	return false;
}

SE_INLINE bool seMat2::Compare( const seMat2 &a, const float epsilon ) const {
	if ( mat[0].Compare( a[0], epsilon ) &&
		mat[1].Compare( a[1], epsilon ) ) {
		return true;
	}
	return false;
}

SE_INLINE bool seMat2::operator==( const seMat2 &a ) const {
	return Compare( a );
}

SE_INLINE bool seMat2::operator!=( const seMat2 &a ) const {
	return !Compare( a );
}

SE_INLINE void seMat2::Zero( void ) {
	mat[0].Zero();
	mat[1].Zero();
}

SE_INLINE void seMat2::Identity( void ) {
	*this = mat2_identity;
}

SE_INLINE bool seMat2::IsIdentity( const float epsilon ) const {
	return Compare( mat2_identity, epsilon );
}

SE_INLINE bool seMat2::IsSymmetric( const float epsilon ) const {
	return ( seMath::Fabs( mat[0][1] - mat[1][0] ) < epsilon );
}

SE_INLINE bool seMat2::IsDiagonal( const float epsilon ) const {
	if ( seMath::Fabs( mat[0][1] ) > epsilon ||
		seMath::Fabs( mat[1][0] ) > epsilon ) {
		return false;
	}
	return true;
}

SE_INLINE float seMat2::Trace( void ) const {
	return ( mat[0][0] + mat[1][1] );
}

SE_INLINE float seMat2::Determinant( void ) const {
	return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

SE_INLINE seMat2 seMat2::Transpose( void ) const {
	return seMat2(	mat[0][0], mat[1][0],
					mat[0][1], mat[1][1] );
}

SE_INLINE seMat2 &seMat2::TransposeSelf( void ) {
	float tmp;

	tmp = mat[0][1];
	mat[0][1] = mat[1][0];
	mat[1][0] = tmp;

	return *this;
}

SE_INLINE seMat2 seMat2::Inverse( void ) const {
	seMat2 invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

SE_INLINE seMat2 seMat2::InverseFast( void ) const {
	seMat2 invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

SE_INLINE int seMat2::GetDimension( void ) const {
	return 4;
}

SE_INLINE const float *seMat2::ToFloatPtr( void ) const {
	return mat[0].ToFloatPtr();
}

SE_INLINE float *seMat2::ToFloatPtr( void ) {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	seMat3 - 3x3 matrix
//
//	NOTE:	matrix is column-major
//
//===============================================================

class DLL_INTERFACE seMat3 {
public:
					seMat3( void );
					explicit seMat3( const seVec3 &x, const seVec3 &y, const seVec3 &z );
					explicit seMat3( const float xx, const float xy, const float xz, const float yx, const float yy, const float yz, const float zx, const float zy, const float zz );
					explicit seMat3( const float src[ 3 ][ 3 ] );

	const seVec3 &	operator[]( int index ) const;
	seVec3 &		operator[]( int index );
	seMat3			operator-() const;
	seMat3			operator*( const float a ) const;
	seVec3			operator*( const seVec3 &vec ) const;
	seMat3			operator*( const seMat3 &a ) const;
	seMat3			operator+( const seMat3 &a ) const;
	seMat3			operator-( const seMat3 &a ) const;
	seMat3 &		operator*=( const float a );
	seMat3 &		operator*=( const seMat3 &a );
	seMat3 &		operator+=( const seMat3 &a );
	seMat3 &		operator-=( const seMat3 &a );

	friend seMat3	operator*( const float a, const seMat3 &mat );
	friend seVec3	operator*( const seVec3 &vec, const seMat3 &mat );
	friend seVec3 &	operator*=( seVec3 &vec, const seMat3 &mat );

	bool			Compare( const seMat3 &a ) const;						// exact compare, no epsilon
	bool			Compare( const seMat3 &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const seMat3 &a ) const;					// exact compare, no epsilon
	bool			operator!=( const seMat3 &a ) const;					// exact compare, no epsilon

	void			Zero( void );
	void			Identity( void );
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsRotated( void ) const;

	void			ProjectVector( const seVec3 &src, seVec3 &dst ) const;
	void			UnprojectVector( const seVec3 &src, seVec3 &dst ) const;

	bool			FixDegeneracies( void );	// fix degenerate axial cases
	bool			FixDenormals( void );		// change tiny numbers to zero

	float			Trace( void ) const;
	float			Determinant( void ) const;
	seMat3			OrthoNormalize( void ) const;
	seMat3 &		OrthoNormalizeSelf( void );
	seMat3			Transpose( void ) const;	// returns transpose
	seMat3 &		TransposeSelf( void );
	seMat3			Inverse( void ) const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf( void );		// returns false if determinant is zero
	seMat3			InverseFast( void ) const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf( void );	// returns false if determinant is zero
	seMat3			TransposeMultiply( const seMat3 &b ) const;

	seMat3			InertiaTranslate( const float mass, const seVec3 &centerOfMass, const seVec3 &translation ) const;
	seMat3 &		InertiaTranslateSelf( const float mass, const seVec3 &centerOfMass, const seVec3 &translation );
	seMat3			InertiaRotate( const seMat3 &rotation ) const;
	seMat3 &		InertiaRotateSelf( const seMat3 &rotation );

	int				GetDimension( void ) const;

	seAngles		ToAngles( void ) const;
	seQuat			ToQuat( void ) const;
	seCQuat			ToCQuat( void ) const;
	seRotation		ToRotation( void ) const;
	seMat4			ToMat4( void ) const;
	seVec3			ToAngularVelocity( void ) const;
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	const char *	ToString( int precision = 2 ) const;

	friend void		TransposeMultiply( const seMat3 &inv, const seMat3 &b, seMat3 &dst );
	friend seMat3	SkewSymmetric( seVec3 const &src );

private:
	seVec3			mat[ 3 ];
};

extern seMat3 mat3_zero;
extern seMat3 mat3_identity;
#define mat3_default	mat3_identity

SE_INLINE seMat3::seMat3( void ) {
}

SE_INLINE seMat3::seMat3( const seVec3 &x, const seVec3 &y, const seVec3 &z ) {
	mat[ 0 ].x = x.x; mat[ 0 ].y = x.y; mat[ 0 ].z = x.z;
	mat[ 1 ].x = y.x; mat[ 1 ].y = y.y; mat[ 1 ].z = y.z;
	mat[ 2 ].x = z.x; mat[ 2 ].y = z.y; mat[ 2 ].z = z.z;
}

SE_INLINE seMat3::seMat3( const float xx, const float xy, const float xz, const float yx, const float yy, const float yz, const float zx, const float zy, const float zz ) {
	mat[ 0 ].x = xx; mat[ 0 ].y = xy; mat[ 0 ].z = xz;
	mat[ 1 ].x = yx; mat[ 1 ].y = yy; mat[ 1 ].z = yz;
	mat[ 2 ].x = zx; mat[ 2 ].y = zy; mat[ 2 ].z = zz;
}

SE_INLINE seMat3::seMat3( const float src[ 3 ][ 3 ] ) {
	memcpy( mat, src, 3 * 3 * sizeof( float ) );
}

SE_INLINE const seVec3 &seMat3::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 3 ) );
	return mat[ index ];
}

SE_INLINE seVec3 &seMat3::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 3 ) );
	return mat[ index ];
}

SE_INLINE seMat3 seMat3::operator-() const {
	return seMat3(	-mat[0][0], -mat[0][1], -mat[0][2],
					-mat[1][0], -mat[1][1], -mat[1][2],
					-mat[2][0], -mat[2][1], -mat[2][2] );
}

SE_INLINE seVec3 seMat3::operator*( const seVec3 &vec ) const {
	return seVec3(
		mat[ 0 ].x * vec.x + mat[ 1 ].x * vec.y + mat[ 2 ].x * vec.z,
		mat[ 0 ].y * vec.x + mat[ 1 ].y * vec.y + mat[ 2 ].y * vec.z,
		mat[ 0 ].z * vec.x + mat[ 1 ].z * vec.y + mat[ 2 ].z * vec.z );
}

SE_INLINE seMat3 seMat3::operator*( const seMat3 &a ) const {
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	seMat3 dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 3 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 3 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 3 + j ];
			dstPtr++;
		}
		m1Ptr += 3;
	}
	return dst;
}

SE_INLINE seMat3 seMat3::operator*( const float a ) const {
	return seMat3(
		mat[0].x * a, mat[0].y * a, mat[0].z * a,
		mat[1].x * a, mat[1].y * a, mat[1].z * a,
		mat[2].x * a, mat[2].y * a, mat[2].z * a );
}

SE_INLINE seMat3 seMat3::operator+( const seMat3 &a ) const {
	return seMat3(
		mat[0].x + a[0].x, mat[0].y + a[0].y, mat[0].z + a[0].z,
		mat[1].x + a[1].x, mat[1].y + a[1].y, mat[1].z + a[1].z,
		mat[2].x + a[2].x, mat[2].y + a[2].y, mat[2].z + a[2].z );
}
    
SE_INLINE seMat3 seMat3::operator-( const seMat3 &a ) const {
	return seMat3(
		mat[0].x - a[0].x, mat[0].y - a[0].y, mat[0].z - a[0].z,
		mat[1].x - a[1].x, mat[1].y - a[1].y, mat[1].z - a[1].z,
		mat[2].x - a[2].x, mat[2].y - a[2].y, mat[2].z - a[2].z );
}

SE_INLINE seMat3 &seMat3::operator*=( const float a ) {
	mat[0].x *= a; mat[0].y *= a; mat[0].z *= a;
	mat[1].x *= a; mat[1].y *= a; mat[1].z *= a; 
	mat[2].x *= a; mat[2].y *= a; mat[2].z *= a;

    return *this;
}

SE_INLINE seMat3 &seMat3::operator*=( const seMat3 &a ) {
	int i, j;
	const float *m2Ptr;
	float *m1Ptr, dst[3];

	m1Ptr = reinterpret_cast<float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);

	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			dst[j]  = m1Ptr[0] * m2Ptr[ 0 * 3 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 3 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 3 + j ];
		}
		m1Ptr[0] = dst[0]; m1Ptr[1] = dst[1]; m1Ptr[2] = dst[2];
		m1Ptr += 3;
	}
	return *this;
}

SE_INLINE seMat3 &seMat3::operator+=( const seMat3 &a ) {
	mat[0].x += a[0].x; mat[0].y += a[0].y; mat[0].z += a[0].z;
	mat[1].x += a[1].x; mat[1].y += a[1].y; mat[1].z += a[1].z;
	mat[2].x += a[2].x; mat[2].y += a[2].y; mat[2].z += a[2].z;

    return *this;
}

SE_INLINE seMat3 &seMat3::operator-=( const seMat3 &a ) {
	mat[0].x -= a[0].x; mat[0].y -= a[0].y; mat[0].z -= a[0].z;
	mat[1].x -= a[1].x; mat[1].y -= a[1].y; mat[1].z -= a[1].z;
	mat[2].x -= a[2].x; mat[2].y -= a[2].y; mat[2].z -= a[2].z;

    return *this;
}

SE_INLINE seVec3 operator*( const seVec3 &vec, const seMat3 &mat ) {
	return mat * vec;
}

SE_INLINE seMat3 operator*( const float a, const seMat3 &mat ) {
	return mat * a;
}

SE_INLINE seVec3 &operator*=( seVec3 &vec, const seMat3 &mat ) {
	float x = mat[ 0 ].x * vec.x + mat[ 1 ].x * vec.y + mat[ 2 ].x * vec.z;
	float y = mat[ 0 ].y * vec.x + mat[ 1 ].y * vec.y + mat[ 2 ].y * vec.z;
	vec.z = mat[ 0 ].z * vec.x + mat[ 1 ].z * vec.y + mat[ 2 ].z * vec.z;
	vec.x = x;
	vec.y = y;
	return vec;
}

SE_INLINE bool seMat3::Compare( const seMat3 &a ) const {
	if ( mat[0].Compare( a[0] ) &&
		mat[1].Compare( a[1] ) &&
		mat[2].Compare( a[2] ) ) {
		return true;
	}
	return false;
}

SE_INLINE bool seMat3::Compare( const seMat3 &a, const float epsilon ) const {
	if ( mat[0].Compare( a[0], epsilon ) &&
		mat[1].Compare( a[1], epsilon ) &&
		mat[2].Compare( a[2], epsilon ) ) {
		return true;
	}
	return false;
}

SE_INLINE bool seMat3::operator==( const seMat3 &a ) const {
	return Compare( a );
}

SE_INLINE bool seMat3::operator!=( const seMat3 &a ) const {
	return !Compare( a );
}

SE_INLINE void seMat3::Zero( void ) {
	memset( mat, 0, sizeof( seMat3 ) );
}

SE_INLINE void seMat3::Identity( void ) {
	*this = mat3_identity;
}

SE_INLINE bool seMat3::IsIdentity( const float epsilon ) const {
	return Compare( mat3_identity, epsilon );
}

SE_INLINE bool seMat3::IsSymmetric( const float epsilon ) const {
	if ( seMath::Fabs( mat[0][1] - mat[1][0] ) > epsilon ) {
		return false;
	}
	if ( seMath::Fabs( mat[0][2] - mat[2][0] ) > epsilon ) {
		return false;
	}
	if ( seMath::Fabs( mat[1][2] - mat[2][1] ) > epsilon ) {
		return false;
	}
	return true;
}

SE_INLINE bool seMat3::IsDiagonal( const float epsilon ) const {
	if ( seMath::Fabs( mat[0][1] ) > epsilon ||
		seMath::Fabs( mat[0][2] ) > epsilon ||
		seMath::Fabs( mat[1][0] ) > epsilon ||
		seMath::Fabs( mat[1][2] ) > epsilon ||
		seMath::Fabs( mat[2][0] ) > epsilon ||
		seMath::Fabs( mat[2][1] ) > epsilon ) {
		return false;
	}
	return true;
}

SE_INLINE bool seMat3::IsRotated( void ) const {
	return !Compare( mat3_identity );
}

SE_INLINE void seMat3::ProjectVector( const seVec3 &src, seVec3 &dst ) const {
	dst.x = src * mat[ 0 ];
	dst.y = src * mat[ 1 ];
	dst.z = src * mat[ 2 ];
}

SE_INLINE void seMat3::UnprojectVector( const seVec3 &src, seVec3 &dst ) const {
	dst = mat[ 0 ] * src.x + mat[ 1 ] * src.y + mat[ 2 ] * src.z;
}

SE_INLINE bool seMat3::FixDegeneracies( void ) {
	bool r = mat[0].FixDegenerateNormal();
	r |= mat[1].FixDegenerateNormal();
	r |= mat[2].FixDegenerateNormal();
	return r;
}

SE_INLINE bool seMat3::FixDenormals( void ) {
	bool r = mat[0].FixDenormals();
	r |= mat[1].FixDenormals();
	r |= mat[2].FixDenormals();
	return r;
}

SE_INLINE float seMat3::Trace( void ) const {
	return ( mat[0][0] + mat[1][1] + mat[2][2] );
}

SE_INLINE seMat3 seMat3::OrthoNormalize( void ) const {
	seMat3 ortho;

	ortho = *this;
	ortho[ 0 ].Normalize();
	ortho[ 2 ].Cross( mat[ 0 ], mat[ 1 ] );
	ortho[ 2 ].Normalize();
	ortho[ 1 ].Cross( mat[ 2 ], mat[ 0 ] );
	ortho[ 1 ].Normalize();
	return ortho;
}

SE_INLINE seMat3 &seMat3::OrthoNormalizeSelf( void ) {
	mat[ 0 ].Normalize();
	mat[ 2 ].Cross( mat[ 0 ], mat[ 1 ] );
	mat[ 2 ].Normalize();
	mat[ 1 ].Cross( mat[ 2 ], mat[ 0 ] );
	mat[ 1 ].Normalize();
	return *this;
}

SE_INLINE seMat3 seMat3::Transpose( void ) const {
	return seMat3(	mat[0][0], mat[1][0], mat[2][0],
					mat[0][1], mat[1][1], mat[2][1],
					mat[0][2], mat[1][2], mat[2][2] );
}

SE_INLINE seMat3 &seMat3::TransposeSelf( void ) {
	float tmp0, tmp1, tmp2;

	tmp0 = mat[0][1];
	mat[0][1] = mat[1][0];
	mat[1][0] = tmp0;
	tmp1 = mat[0][2];
	mat[0][2] = mat[2][0];
	mat[2][0] = tmp1;
	tmp2 = mat[1][2];
	mat[1][2] = mat[2][1];
	mat[2][1] = tmp2;

	return *this;
}

SE_INLINE seMat3 seMat3::Inverse( void ) const {
	seMat3 invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

SE_INLINE seMat3 seMat3::InverseFast( void ) const {
	seMat3 invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

SE_INLINE seMat3 seMat3::TransposeMultiply( const seMat3 &b ) const {
	return seMat3(	mat[0].x * b[0].x + mat[1].x * b[1].x + mat[2].x * b[2].x,
					mat[0].x * b[0].y + mat[1].x * b[1].y + mat[2].x * b[2].y,
					mat[0].x * b[0].z + mat[1].x * b[1].z + mat[2].x * b[2].z,
					mat[0].y * b[0].x + mat[1].y * b[1].x + mat[2].y * b[2].x,
					mat[0].y * b[0].y + mat[1].y * b[1].y + mat[2].y * b[2].y,
					mat[0].y * b[0].z + mat[1].y * b[1].z + mat[2].y * b[2].z,
					mat[0].z * b[0].x + mat[1].z * b[1].x + mat[2].z * b[2].x,
					mat[0].z * b[0].y + mat[1].z * b[1].y + mat[2].z * b[2].y,
					mat[0].z * b[0].z + mat[1].z * b[1].z + mat[2].z * b[2].z );
}

SE_INLINE void TransposeMultiply( const seMat3 &transpose, const seMat3 &b, seMat3 &dst ) {
	dst[0].x = transpose[0].x * b[0].x + transpose[1].x * b[1].x + transpose[2].x * b[2].x;
	dst[0].y = transpose[0].x * b[0].y + transpose[1].x * b[1].y + transpose[2].x * b[2].y;
	dst[0].z = transpose[0].x * b[0].z + transpose[1].x * b[1].z + transpose[2].x * b[2].z;
	dst[1].x = transpose[0].y * b[0].x + transpose[1].y * b[1].x + transpose[2].y * b[2].x;
	dst[1].y = transpose[0].y * b[0].y + transpose[1].y * b[1].y + transpose[2].y * b[2].y;
	dst[1].z = transpose[0].y * b[0].z + transpose[1].y * b[1].z + transpose[2].y * b[2].z;
	dst[2].x = transpose[0].z * b[0].x + transpose[1].z * b[1].x + transpose[2].z * b[2].x;
	dst[2].y = transpose[0].z * b[0].y + transpose[1].z * b[1].y + transpose[2].z * b[2].y;
	dst[2].z = transpose[0].z * b[0].z + transpose[1].z * b[1].z + transpose[2].z * b[2].z;
}

SE_INLINE seMat3 SkewSymmetric( seVec3 const &src ) {
	return seMat3( 0.0f, -src.z,  src.y, src.z,   0.0f, -src.x, -src.y,  src.x,   0.0f );
}

SE_INLINE int seMat3::GetDimension( void ) const {
	return 9;
}

SE_INLINE const float *seMat3::ToFloatPtr( void ) const {
	return mat[0].ToFloatPtr();
}

SE_INLINE float *seMat3::ToFloatPtr( void ) {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	seMat4 - 4x4 matrix
//
//===============================================================

class DLL_INTERFACE seMat4 {
public:
					seMat4( void );
					explicit seMat4( const seVec4 &x, const seVec4 &y, const seVec4 &z, const seVec4 &w );
					explicit seMat4(const float xx, const float xy, const float xz, const float xw,
									const float yx, const float yy, const float yz, const float yw,
									const float zx, const float zy, const float zz, const float zw,
									const float wx, const float wy, const float wz, const float ww );
					explicit seMat4( const seMat3 &rotation, const seVec3 &translation );
					explicit seMat4( const float src[ 4 ][ 4 ] );

	const seVec4 &	operator[]( int index ) const;
	seVec4 &		operator[]( int index );
	seMat4			operator*( const float a ) const;
	seVec4			operator*( const seVec4 &vec ) const;
	seVec3			operator*( const seVec3 &vec ) const;
	seMat4			operator*( const seMat4 &a ) const;
	seMat4			operator+( const seMat4 &a ) const;
	seMat4			operator-( const seMat4 &a ) const;
	seMat4 &		operator*=( const float a );
	seMat4 &		operator*=( const seMat4 &a );
	seMat4 &		operator+=( const seMat4 &a );
	seMat4 &		operator-=( const seMat4 &a );

	friend seMat4	operator*( const float a, const seMat4 &mat );
	friend seVec4	operator*( const seVec4 &vec, const seMat4 &mat );
	friend seVec3	operator*( const seVec3 &vec, const seMat4 &mat );
	friend seVec4 &	operator*=( seVec4 &vec, const seMat4 &mat );
	friend seVec3 &	operator*=( seVec3 &vec, const seMat4 &mat );

	bool			Compare( const seMat4 &a ) const;						// exact compare, no epsilon
	bool			Compare( const seMat4 &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const seMat4 &a ) const;					// exact compare, no epsilon
	bool			operator!=( const seMat4 &a ) const;					// exact compare, no epsilon

	void			Zero( void );
	void			Identity( void );
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsRotated( void ) const;

	void			ProjectVector( const seVec4 &src, seVec4 &dst ) const;
	void			UnprojectVector( const seVec4 &src, seVec4 &dst ) const;

	float			Trace( void ) const;
	float			Determinant( void ) const;
	seMat4			Transpose( void ) const;	// returns transpose
	seMat4 &		TransposeSelf( void );
	seMat4			Inverse( void ) const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf( void );		// returns false if determinant is zero
	seMat4			InverseFast( void ) const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf( void );	// returns false if determinant is zero
	//seMat4			TransposeMultiply( const seMat4 &b ) const;

	int				GetDimension( void ) const;

	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	const char *	ToString( int precision = 2 ) const;

private:
	seVec4			mat[ 4 ];
};

extern seMat4 mat4_zero;
extern seMat4 mat4_identity;
#define mat4_default	mat4_identity

SE_INLINE seMat4::seMat4( void ) {
}

SE_INLINE seMat4::seMat4( const seVec4 &x, const seVec4 &y, const seVec4 &z, const seVec4 &w ) {
	mat[ 0 ] = x;
	mat[ 1 ] = y;
	mat[ 2 ] = z;
	mat[ 3 ] = w;
}

SE_INLINE seMat4::seMat4( const float xx, const float xy, const float xz, const float xw,
							const float yx, const float yy, const float yz, const float yw,
							const float zx, const float zy, const float zz, const float zw,
							const float wx, const float wy, const float wz, const float ww ) {
	mat[0][0] = xx; mat[0][1] = xy; mat[0][2] = xz; mat[0][3] = xw;
	mat[1][0] = yx; mat[1][1] = yy; mat[1][2] = yz; mat[1][3] = yw;
	mat[2][0] = zx; mat[2][1] = zy; mat[2][2] = zz; mat[2][3] = zw;
	mat[3][0] = wx; mat[3][1] = wy; mat[3][2] = wz; mat[3][3] = ww;
}

SE_INLINE seMat4::seMat4( const seMat3 &rotation, const seVec3 &translation ) {
	// NOTE: seMat3 is transposed because it is column-major
	mat[ 0 ][ 0 ] = rotation[0][0];
	mat[ 0 ][ 1 ] = rotation[1][0];
	mat[ 0 ][ 2 ] = rotation[2][0];
	mat[ 0 ][ 3 ] = translation[0];
	mat[ 1 ][ 0 ] = rotation[0][1];
	mat[ 1 ][ 1 ] = rotation[1][1];
	mat[ 1 ][ 2 ] = rotation[2][1];
	mat[ 1 ][ 3 ] = translation[1];
	mat[ 2 ][ 0 ] = rotation[0][2];
	mat[ 2 ][ 1 ] = rotation[1][2];
	mat[ 2 ][ 2 ] = rotation[2][2];
	mat[ 2 ][ 3 ] = translation[2];
	mat[ 3 ][ 0 ] = 0.0f;
	mat[ 3 ][ 1 ] = 0.0f;
	mat[ 3 ][ 2 ] = 0.0f;
	mat[ 3 ][ 3 ] = 1.0f;
}

SE_INLINE seMat4::seMat4( const float src[ 4 ][ 4 ] ) {
	memcpy( mat, src, 4 * 4 * sizeof( float ) );
}

SE_INLINE const seVec4 &seMat4::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 4 ) );
	return mat[ index ];
}

SE_INLINE seVec4 &seMat4::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 4 ) );
	return mat[ index ];
}

SE_INLINE seMat4 seMat4::operator*( const float a ) const {
	return seMat4(
		mat[0].x * a, mat[0].y * a, mat[0].z * a, mat[0].w * a,
		mat[1].x * a, mat[1].y * a, mat[1].z * a, mat[1].w * a,
		mat[2].x * a, mat[2].y * a, mat[2].z * a, mat[2].w * a,
		mat[3].x * a, mat[3].y * a, mat[3].z * a, mat[3].w * a );
}

SE_INLINE seVec4 seMat4::operator*( const seVec4 &vec ) const {
	return seVec4(
		mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w * vec.w,
		mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w * vec.w,
		mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w * vec.w,
		mat[ 3 ].x * vec.x + mat[ 3 ].y * vec.y + mat[ 3 ].z * vec.z + mat[ 3 ].w * vec.w );
}

SE_INLINE seVec3 seMat4::operator*( const seVec3 &vec ) const {
	float s = mat[ 3 ].x * vec.x + mat[ 3 ].y * vec.y + mat[ 3 ].z * vec.z + mat[ 3 ].w;
	if ( s == 0.0f ) {
		return seVec3( 0.0f, 0.0f, 0.0f );
	}
	if ( s == 1.0f ) {
		return seVec3(
			mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w,
			mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w,
			mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w );
	}
	else {
		float invS = 1.0f / s;
		return seVec3(
			(mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w) * invS,
			(mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w) * invS,
			(mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w) * invS );
	}
}

SE_INLINE seMat4 seMat4::operator*( const seMat4 &a ) const {
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	seMat4 dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 4; i++ ) {
		for ( j = 0; j < 4; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 4 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 4 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 4 + j ]
					+ m1Ptr[3] * m2Ptr[ 3 * 4 + j ];
			dstPtr++;
		}
		m1Ptr += 4;
	}
	return dst;
}

SE_INLINE seMat4 seMat4::operator+( const seMat4 &a ) const {
	return seMat4( 
		mat[0].x + a[0].x, mat[0].y + a[0].y, mat[0].z + a[0].z, mat[0].w + a[0].w,
		mat[1].x + a[1].x, mat[1].y + a[1].y, mat[1].z + a[1].z, mat[1].w + a[1].w,
		mat[2].x + a[2].x, mat[2].y + a[2].y, mat[2].z + a[2].z, mat[2].w + a[2].w,
		mat[3].x + a[3].x, mat[3].y + a[3].y, mat[3].z + a[3].z, mat[3].w + a[3].w );
}
    
SE_INLINE seMat4 seMat4::operator-( const seMat4 &a ) const {
	return seMat4( 
		mat[0].x - a[0].x, mat[0].y - a[0].y, mat[0].z - a[0].z, mat[0].w - a[0].w,
		mat[1].x - a[1].x, mat[1].y - a[1].y, mat[1].z - a[1].z, mat[1].w - a[1].w,
		mat[2].x - a[2].x, mat[2].y - a[2].y, mat[2].z - a[2].z, mat[2].w - a[2].w,
		mat[3].x - a[3].x, mat[3].y - a[3].y, mat[3].z - a[3].z, mat[3].w - a[3].w );
}

SE_INLINE seMat4 &seMat4::operator*=( const float a ) {
	mat[0].x *= a; mat[0].y *= a; mat[0].z *= a; mat[0].w *= a;
	mat[1].x *= a; mat[1].y *= a; mat[1].z *= a; mat[1].w *= a;
	mat[2].x *= a; mat[2].y *= a; mat[2].z *= a; mat[2].w *= a;
	mat[3].x *= a; mat[3].y *= a; mat[3].z *= a; mat[3].w *= a;
    return *this;
}

SE_INLINE seMat4 &seMat4::operator*=( const seMat4 &a ) {
	*this = (*this) * a;
	return *this;
}

SE_INLINE seMat4 &seMat4::operator+=( const seMat4 &a ) {
	mat[0].x += a[0].x; mat[0].y += a[0].y; mat[0].z += a[0].z; mat[0].w += a[0].w;
	mat[1].x += a[1].x; mat[1].y += a[1].y; mat[1].z += a[1].z; mat[1].w += a[1].w;
	mat[2].x += a[2].x; mat[2].y += a[2].y; mat[2].z += a[2].z; mat[2].w += a[2].w;
	mat[3].x += a[3].x; mat[3].y += a[3].y; mat[3].z += a[3].z; mat[3].w += a[3].w;
    return *this;
}

SE_INLINE seMat4 &seMat4::operator-=( const seMat4 &a ) {
	mat[0].x -= a[0].x; mat[0].y -= a[0].y; mat[0].z -= a[0].z; mat[0].w -= a[0].w;
	mat[1].x -= a[1].x; mat[1].y -= a[1].y; mat[1].z -= a[1].z; mat[1].w -= a[1].w;
	mat[2].x -= a[2].x; mat[2].y -= a[2].y; mat[2].z -= a[2].z; mat[2].w -= a[2].w;
	mat[3].x -= a[3].x; mat[3].y -= a[3].y; mat[3].z -= a[3].z; mat[3].w -= a[3].w;
    return *this;
}

SE_INLINE seMat4 operator*( const float a, const seMat4 &mat ) {
	return mat * a;
}

SE_INLINE seVec4 operator*( const seVec4 &vec, const seMat4 &mat ) {
	return mat * vec;
}

SE_INLINE seVec3 operator*( const seVec3 &vec, const seMat4 &mat ) {
	return mat * vec;
}

SE_INLINE seVec4 &operator*=( seVec4 &vec, const seMat4 &mat ) {
	vec = mat * vec;
	return vec;
}

SE_INLINE seVec3 &operator*=( seVec3 &vec, const seMat4 &mat ) {
	vec = mat * vec;
	return vec;
}

SE_INLINE bool seMat4::Compare( const seMat4 &a ) const {
	dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 4*4; i++ ) {
		if ( ptr1[i] != ptr2[i] ) {
			return false;
		}
	}
	return true;
}

SE_INLINE bool seMat4::Compare( const seMat4 &a, const float epsilon ) const {
	dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 4*4; i++ ) {
		if ( seMath::Fabs( ptr1[i] - ptr2[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

SE_INLINE bool seMat4::operator==( const seMat4 &a ) const {
	return Compare( a );
}

SE_INLINE bool seMat4::operator!=( const seMat4 &a ) const {
	return !Compare( a );
}

SE_INLINE void seMat4::Zero( void ) {
	memset( mat, 0, sizeof( seMat4 ) );
}

SE_INLINE void seMat4::Identity( void ) {
	*this = mat4_identity;
}

SE_INLINE bool seMat4::IsIdentity( const float epsilon ) const {
	return Compare( mat4_identity, epsilon );
}

SE_INLINE bool seMat4::IsSymmetric( const float epsilon ) const {
	for ( int i = 1; i < 4; i++ ) {
		for ( int j = 0; j < i; j++ ) {
			if ( seMath::Fabs( mat[i][j] - mat[j][i] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SE_INLINE bool seMat4::IsDiagonal( const float epsilon ) const {
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i != j && seMath::Fabs( mat[i][j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

SE_INLINE bool seMat4::IsRotated( void ) const {
	if ( !mat[ 0 ][ 1 ] && !mat[ 0 ][ 2 ] &&
		!mat[ 1 ][ 0 ] && !mat[ 1 ][ 2 ] &&
		!mat[ 2 ][ 0 ] && !mat[ 2 ][ 1 ] ) {
		return false;
	}
	return true;
}

SE_INLINE void seMat4::ProjectVector( const seVec4 &src, seVec4 &dst ) const {
	dst.x = src * mat[ 0 ];
	dst.y = src * mat[ 1 ];
	dst.z = src * mat[ 2 ];
	dst.w = src * mat[ 3 ];
}

SE_INLINE void seMat4::UnprojectVector( const seVec4 &src, seVec4 &dst ) const {
	dst = mat[ 0 ] * src.x + mat[ 1 ] * src.y + mat[ 2 ] * src.z + mat[ 3 ] * src.w;
}

SE_INLINE float seMat4::Trace( void ) const {
	return ( mat[0][0] + mat[1][1] + mat[2][2] + mat[3][3] );
}

SE_INLINE seMat4 seMat4::Inverse( void ) const {
	seMat4 invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

SE_INLINE seMat4 seMat4::InverseFast( void ) const {
	seMat4 invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

SE_INLINE seMat4 seMat3::ToMat4( void ) const {
	// NOTE: seMat3 is transposed because it is column-major
	return seMat4(	mat[0][0],	mat[1][0],	mat[2][0],	0.0f,
					mat[0][1],	mat[1][1],	mat[2][1],	0.0f,
					mat[0][2],	mat[1][2],	mat[2][2],	0.0f,
					0.0f,		0.0f,		0.0f,		1.0f );
}

SE_INLINE int seMat4::GetDimension( void ) const {
	return 16;
}

SE_INLINE const float *seMat4::ToFloatPtr( void ) const {
	return mat[0].ToFloatPtr();
}

SE_INLINE float *seMat4::ToFloatPtr( void ) {
	return mat[0].ToFloatPtr();
}


#endif /* !__MATH_MATRIX_H__ */
