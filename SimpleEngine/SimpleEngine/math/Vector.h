#ifndef __MATH_VECTOR_H__
#define __MATH_VECTOR_H__

#define VECTOR_EPSILON		0.001f

class seAngles;
class sePolar3;
class seMat3;

//===============================================================
//	seVec2 - 2D vector
//===============================================================

class DLL_INTERFACE seVec2 {

public:
	float			x;
	float			y;

	seVec2(void);
	explicit seVec2(const float x, const float y);

	void 			Set(const float x, const float y);
	void			Zero(void);

	float			operator[](int index) const;
	float &			operator[](int index);
	seVec2			operator-() const;
	float			operator*(const seVec2 &a) const;
	seVec2			operator*(const float a) const;
	seVec2			operator/(const float a) const;
	seVec2			operator+(const seVec2 &a) const;
	seVec2			operator-(const seVec2 &a) const;
	seVec2 &		operator+=(const seVec2 &a);
	seVec2 &		operator-=(const seVec2 &a);
	seVec2 &		operator/=(const seVec2 &a);
	seVec2 &		operator/=(const float a);
	seVec2 &		operator*=(const float a);

	friend seVec2	operator*(const float a, const seVec2 b);

	bool			Compare(const seVec2 &a) const;							// exact compare, no epsilon
	bool			Compare(const seVec2 &a, const float epsilon) const;	// compare with epsilon
	bool			operator==(const seVec2 &a) const;						// exact compare, no epsilon
	bool			operator!=(const seVec2 &a) const;						// exact compare, no epsilon

	float			Length(void) const;
	float			LengthFast(void) const;
	float			LengthSqr(void) const;
	float			Normalize(void);			// returns length
	float			NormalizeFast(void);		// returns length
	seVec2 &		Truncate(float length);		// cap length
	void			Clamp(const seVec2 &min, const seVec2 &max);
	void			Snap(void);					// snap to closest integer value
	void			SnapInt(void);				// snap towards integer (floor)

	int				GetDimension(void) const;

	const float *	ToFloatPtr(void) const;
	float *			ToFloatPtr(void);
	const char *	ToString(int precision = 2) const;

	void			Lerp(const seVec2 &v1, const seVec2 &v2, const float l);
};

extern seVec2 vec2_origin;
#define vec2_zero vec2_origin


SE_INLINE seVec2::seVec2(void) {
}

SE_INLINE seVec2::seVec2(const float x, const float y) {
	this->x = x;
	this->y = y;
}

SE_INLINE void seVec2::Set(const float x, const float y) {
	this->x = x;
	this->y = y;
}

SE_INLINE void seVec2::Zero(void) {
	x = y = 0.0f;
}

SE_INLINE bool seVec2::Compare(const seVec2 &a) const {
	return ((x == a.x) && (y == a.y));
}

SE_INLINE bool seVec2::Compare(const seVec2 &a, const float epsilon) const {
	if (seMath::Fabs(x - a.x) > epsilon) {
		return false;
	}

	if (seMath::Fabs(y - a.y) > epsilon) {
		return false;
	}

	return true;
}

SE_INLINE bool seVec2::operator==(const seVec2 &a) const {
	return Compare(a);
}

SE_INLINE bool seVec2::operator!=(const seVec2 &a) const {
	return !Compare(a);
}

SE_INLINE float seVec2::operator[](int index) const {
	return (&x)[index];
}

SE_INLINE float& seVec2::operator[](int index) {
	return (&x)[index];
}

SE_INLINE float seVec2::Length(void) const {
	return (float)seMath::Sqrt(x * x + y * y);
}

SE_INLINE float seVec2::LengthFast(void) const {
	float sqrLength;

	sqrLength = x * x + y * y;
	return sqrLength * seMath::RSqrt(sqrLength);
}

SE_INLINE float seVec2::LengthSqr(void) const {
	return (x * x + y * y);
}

SE_INLINE float seVec2::Normalize(void) {
	float sqrLength, invLength;

	sqrLength = x * x + y * y;
	invLength = seMath::InvSqrt(sqrLength);
	x *= invLength;
	y *= invLength;
	return invLength * sqrLength;
}

SE_INLINE float seVec2::NormalizeFast(void) {
	float lengthSqr, invLength;

	lengthSqr = x * x + y * y;
	invLength = seMath::RSqrt(lengthSqr);
	x *= invLength;
	y *= invLength;
	return invLength * lengthSqr;
}

SE_INLINE seVec2 &seVec2::Truncate(float length) {
	float length2;
	float ilength;

	if (!length) {
		Zero();
	}
	else {
		length2 = LengthSqr();
		if (length2 > length * length) {
			ilength = length * seMath::InvSqrt(length2);
			x *= ilength;
			y *= ilength;
		}
	}

	return *this;
}

SE_INLINE void seVec2::Clamp(const seVec2 &min, const seVec2 &max) {
	if (x < min.x) {
		x = min.x;
	}
	else if (x > max.x) {
		x = max.x;
	}
	if (y < min.y) {
		y = min.y;
	}
	else if (y > max.y) {
		y = max.y;
	}
}

SE_INLINE void seVec2::Snap(void) {
	x = floorf(x + 0.5f);
	y = floorf(y + 0.5f);
}

SE_INLINE void seVec2::SnapInt(void) {
	x = float(int(x));
	y = float(int(y));
}

SE_INLINE seVec2 seVec2::operator-() const {
	return seVec2(-x, -y);
}

SE_INLINE seVec2 seVec2::operator-(const seVec2 &a) const {
	return seVec2(x - a.x, y - a.y);
}

SE_INLINE float seVec2::operator*(const seVec2 &a) const {
	return x * a.x + y * a.y;
}

SE_INLINE seVec2 seVec2::operator*(const float a) const {
	return seVec2(x * a, y * a);
}

SE_INLINE seVec2 seVec2::operator/(const float a) const {
	float inva = 1.0f / a;
	return seVec2(x * inva, y * inva);
}

SE_INLINE seVec2 operator*(const float a, const seVec2 b) {
	return seVec2(b.x * a, b.y * a);
}

SE_INLINE seVec2 seVec2::operator+(const seVec2 &a) const {
	return seVec2(x + a.x, y + a.y);
}

SE_INLINE seVec2 &seVec2::operator+=(const seVec2 &a) {
	x += a.x;
	y += a.y;

	return *this;
}

SE_INLINE seVec2 &seVec2::operator/=(const seVec2 &a) {
	x /= a.x;
	y /= a.y;

	return *this;
}

SE_INLINE seVec2 &seVec2::operator/=(const float a) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;

	return *this;
}

SE_INLINE seVec2 &seVec2::operator-=(const seVec2 &a) {
	x -= a.x;
	y -= a.y;

	return *this;
}

SE_INLINE seVec2 &seVec2::operator*=(const float a) {
	x *= a;
	y *= a;

	return *this;
}

SE_INLINE int seVec2::GetDimension(void) const {
	return 2;
}

SE_INLINE const float *seVec2::ToFloatPtr(void) const {
	return &x;
}

SE_INLINE float *seVec2::ToFloatPtr(void) {
	return &x;
}


//===============================================================
//
//	seVec3 - 3D vector
//
//===============================================================

class DLL_INTERFACE seVec3 {
public:
	float			x;
	float			y;
	float			z;

	seVec3(void);
	explicit seVec3(const float x, const float y, const float z);

	void 			Set(const float x, const float y, const float z);
	void			Zero(void);

	float			operator[](const int index) const;
	float &			operator[](const int index);
	seVec3			operator-() const;
	seVec3 &		operator=(const seVec3 &a);		// required because of a msvc 6 & 7 bug
	float			operator*(const seVec3 &a) const;
	seVec3			operator*(const float a) const;
	seVec3			operator/(const float a) const;
	seVec3			operator+(const seVec3 &a) const;
	seVec3			operator-(const seVec3 &a) const;
	seVec3 &		operator+=(const seVec3 &a);
	seVec3 &		operator-=(const seVec3 &a);
	seVec3 &		operator/=(const seVec3 &a);
	seVec3 &		operator/=(const float a);
	seVec3 &		operator*=(const float a);

	friend seVec3	operator*(const float a, const seVec3 b);

	bool			Compare(const seVec3 &a) const;							// exact compare, no epsilon
	bool			Compare(const seVec3 &a, const float epsilon) const;		// compare with epsilon
	bool			operator==(const seVec3 &a) const;						// exact compare, no epsilon
	bool			operator!=(const seVec3 &a) const;						// exact compare, no epsilon

	bool			FixDegenerateNormal(void);	// fix degenerate axial cases
	bool			FixDenormals(void);			// change tiny numbers to zero

	seVec3			Cross(const seVec3 &a) const;
	seVec3 &		Cross(const seVec3 &a, const seVec3 &b);
	float			Length(void) const;
	float			LengthSqr(void) const;
	float			LengthFast(void) const;
	float			Normalize(void);				// returns length
	float			NormalizeFast(void);			// returns length
	seVec3 &		Truncate(float length);		// cap length
	void			Clamp(const seVec3 &min, const seVec3 &max);
	void			Snap(void);					// snap to closest integer value
	void			SnapInt(void);				// snap towards integer (floor)

	int				GetDimension(void) const;

	float			ToYaw(void) const;
	float			ToPitch(void) const;
	seAngles		ToAngles(void) const;
	sePolar3		ToPolar(void) const;
	seMat3			ToMat3(void) const;		// vector should be normalized
	
	const seVec2 &	ToVec2(void) const;
	seVec2 &		ToVec2(void);
	const float *	ToFloatPtr(void) const;
	float *			ToFloatPtr(void);
	const char *	ToString(int precision = 2) const;

	void			NormalVectors(seVec3 &left, seVec3 &down) const;	// vector should be normalized
	void			OrthogonalBasis(seVec3 &left, seVec3 &up) const;

	void			ProjectOntoPlane(const seVec3 &normal, const float overBounce = 1.0f);
	bool			ProjectAlongPlane(const seVec3 &normal, const float epsilon, const float overBounce = 1.0f);
	void			ProjectSelfOntoSphere(const float radius);

	void			Lerp(const seVec3 &v1, const seVec3 &v2, const float l);
	void			SLerp(const seVec3 &v1, const seVec3 &v2, const float l);
};

extern seVec3 vec3_origin;
#define vec3_zero vec3_origin

SE_INLINE seVec3::seVec3(void) {
}

SE_INLINE seVec3::seVec3(const float x, const float y, const float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

SE_INLINE float seVec3::operator[](const int index) const {
	return (&x)[index];
}

SE_INLINE float &seVec3::operator[](const int index) {
	return (&x)[index];
}

SE_INLINE void seVec3::Set(const float x, const float y, const float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

SE_INLINE void seVec3::Zero(void) {
	x = y = z = 0.0f;
}

SE_INLINE seVec3 seVec3::operator-() const {
	return seVec3(-x, -y, -z);
}

SE_INLINE seVec3 &seVec3::operator=(const seVec3 &a) {
	x = a.x;
	y = a.y;
	z = a.z;
	return *this;
}

SE_INLINE seVec3 seVec3::operator-(const seVec3 &a) const {
	return seVec3(x - a.x, y - a.y, z - a.z);
}

SE_INLINE float seVec3::operator*(const seVec3 &a) const {
	return x * a.x + y * a.y + z * a.z;
}

SE_INLINE seVec3 seVec3::operator*(const float a) const {
	return seVec3(x * a, y * a, z * a);
}

SE_INLINE seVec3 seVec3::operator/(const float a) const {
	float inva = 1.0f / a;
	return seVec3(x * inva, y * inva, z * inva);
}

SE_INLINE seVec3 operator*(const float a, const seVec3 b) {
	return seVec3(b.x * a, b.y * a, b.z * a);
}

SE_INLINE seVec3 seVec3::operator+(const seVec3 &a) const {
	return seVec3(x + a.x, y + a.y, z + a.z);
}

SE_INLINE seVec3 &seVec3::operator+=(const seVec3 &a) {
	x += a.x;
	y += a.y;
	z += a.z;

	return *this;
}

SE_INLINE seVec3 &seVec3::operator/=(const seVec3 &a) {
	x /= a.x;
	y /= a.y;
	z /= a.z;

	return *this;
}

SE_INLINE seVec3 &seVec3::operator/=(const float a) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;
	z *= inva;

	return *this;
}

SE_INLINE seVec3 &seVec3::operator-=(const seVec3 &a) {
	x -= a.x;
	y -= a.y;
	z -= a.z;

	return *this;
}

SE_INLINE seVec3 &seVec3::operator*=(const float a) {
	x *= a;
	y *= a;
	z *= a;

	return *this;
}

SE_INLINE bool seVec3::Compare(const seVec3 &a) const {
	return ((x == a.x) && (y == a.y) && (z == a.z));
}

SE_INLINE bool seVec3::Compare(const seVec3 &a, const float epsilon) const {
	if (seMath::Fabs(x - a.x) > epsilon) {
		return false;
	}

	if (seMath::Fabs(y - a.y) > epsilon) {
		return false;
	}

	if (seMath::Fabs(z - a.z) > epsilon) {
		return false;
	}

	return true;
}

SE_INLINE bool seVec3::operator==(const seVec3 &a) const {
	return Compare(a);
}

SE_INLINE bool seVec3::operator!=(const seVec3 &a) const {
	return !Compare(a);
}

SE_INLINE float seVec3::NormalizeFast(void) {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z;
	invLength = seMath::RSqrt(sqrLength);
	x *= invLength;
	y *= invLength;
	z *= invLength;
	return invLength * sqrLength;
}

SE_INLINE bool seVec3::FixDegenerateNormal(void) {
	if (x == 0.0f) {
		if (y == 0.0f) {
			if (z > 0.0f) {
				if (z != 1.0f) {
					z = 1.0f;
					return true;
				}
			}
			else {
				if (z != -1.0f) {
					z = -1.0f;
					return true;
				}
			}
			return false;
		}
		else if (z == 0.0f) {
			if (y > 0.0f) {
				if (y != 1.0f) {
					y = 1.0f;
					return true;
				}
			}
			else {
				if (y != -1.0f) {
					y = -1.0f;
					return true;
				}
			}
			return false;
		}
	}
	else if (y == 0.0f) {
		if (z == 0.0f) {
			if (x > 0.0f) {
				if (x != 1.0f) {
					x = 1.0f;
					return true;
				}
			}
			else {
				if (x != -1.0f) {
					x = -1.0f;
					return true;
				}
			}
			return false;
		}
	}
	if (seMath::Fabs(x) == 1.0f) {
		if (y != 0.0f || z != 0.0f) {
			y = z = 0.0f;
			return true;
		}
		return false;
	}
	else if (seMath::Fabs(y) == 1.0f) {
		if (x != 0.0f || z != 0.0f) {
			x = z = 0.0f;
			return true;
		}
		return false;
	}
	else if (seMath::Fabs(z) == 1.0f) {
		if (x != 0.0f || y != 0.0f) {
			x = y = 0.0f;
			return true;
		}
		return false;
	}
	return false;
}

SE_INLINE bool seVec3::FixDenormals(void) {
	bool denormal = false;
	if (fabs(x) < 1e-30f) {
		x = 0.0f;
		denormal = true;
	}
	if (fabs(y) < 1e-30f) {
		y = 0.0f;
		denormal = true;
	}
	if (fabs(z) < 1e-30f) {
		z = 0.0f;
		denormal = true;
	}
	return denormal;
}

SE_INLINE seVec3 seVec3::Cross(const seVec3 &a) const {
	return seVec3(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
}

SE_INLINE seVec3 &seVec3::Cross(const seVec3 &a, const seVec3 &b) {
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;

	return *this;
}

SE_INLINE float seVec3::Length(void) const {
	return (float)seMath::Sqrt(x * x + y * y + z * z);
}

SE_INLINE float seVec3::LengthSqr(void) const {
	return (x * x + y * y + z * z);
}

SE_INLINE float seVec3::LengthFast(void) const {
	float sqrLength;

	sqrLength = x * x + y * y + z * z;
	return sqrLength * seMath::RSqrt(sqrLength);
}

SE_INLINE float seVec3::Normalize(void) {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z;
	invLength = seMath::InvSqrt(sqrLength);
	x *= invLength;
	y *= invLength;
	z *= invLength;
	return invLength * sqrLength;
}

SE_INLINE seVec3 &seVec3::Truncate(float length) {
	float length2;
	float ilength;

	if (!length) {
		Zero();
	}
	else {
		length2 = LengthSqr();
		if (length2 > length * length) {
			ilength = length * seMath::InvSqrt(length2);
			x *= ilength;
			y *= ilength;
			z *= ilength;
		}
	}

	return *this;
}

SE_INLINE void seVec3::Clamp(const seVec3 &min, const seVec3 &max) {
	if (x < min.x) {
		x = min.x;
	}
	else if (x > max.x) {
		x = max.x;
	}
	if (y < min.y) {
		y = min.y;
	}
	else if (y > max.y) {
		y = max.y;
	}
	if (z < min.z) {
		z = min.z;
	}
	else if (z > max.z) {
		z = max.z;
	}
}

SE_INLINE void seVec3::Snap(void) {
	x = floorf(x + 0.5f);
	y = floorf(y + 0.5f);
	z = floorf(z + 0.5f);
}

SE_INLINE void seVec3::SnapInt(void) {
	x = float(int(x));
	y = float(int(y));
	z = float(int(z));
}

SE_INLINE int seVec3::GetDimension(void) const {
	return 3;
}

SE_INLINE const seVec2 &seVec3::ToVec2(void) const {
	return *reinterpret_cast<const seVec2 *>(this);
}

SE_INLINE seVec2 &seVec3::ToVec2(void) {
	return *reinterpret_cast<seVec2 *>(this);
}

SE_INLINE const float *seVec3::ToFloatPtr(void) const {
	return &x;
}

SE_INLINE float *seVec3::ToFloatPtr(void) {
	return &x;
}

SE_INLINE void seVec3::NormalVectors(seVec3 &left, seVec3 &down) const {
	float d;

	d = x * x + y * y;
	if (!d) {
		left[0] = 1;
		left[1] = 0;
		left[2] = 0;
	}
	else {
		d = seMath::InvSqrt(d);
		left[0] = -y * d;
		left[1] = x * d;
		left[2] = 0;
	}
	down = left.Cross(*this);
}

SE_INLINE void seVec3::OrthogonalBasis(seVec3 &left, seVec3 &up) const {
	float l, s;

	if (seMath::Fabs(z) > 0.7f) {
		l = y * y + z * z;
		s = seMath::InvSqrt(l);
		up[0] = 0;
		up[1] = z * s;
		up[2] = -y * s;
		left[0] = l * s;
		left[1] = -x * up[2];
		left[2] = x * up[1];
	}
	else {
		l = x * x + y * y;
		s = seMath::InvSqrt(l);
		left[0] = -y * s;
		left[1] = x * s;
		left[2] = 0;
		up[0] = -z * left[1];
		up[1] = z * left[0];
		up[2] = l * s;
	}
}

SE_INLINE void seVec3::ProjectOntoPlane(const seVec3 &normal, const float overBounce) {
	float backoff;

	backoff = *this * normal;

	if (overBounce != 1.0) {
		if (backoff < 0) {
			backoff *= overBounce;
		}
		else {
			backoff /= overBounce;
		}
	}

	*this -= backoff * normal;
}

SE_INLINE bool seVec3::ProjectAlongPlane(const seVec3 &normal, const float epsilon, const float overBounce) {
	seVec3 cross;
	float len;

	cross = this->Cross(normal).Cross((*this));
	// normalize so a fixed epsilon can be used
	cross.Normalize();
	len = normal * cross;
	if (seMath::Fabs(len) < epsilon) {
		return false;
	}
	cross *= overBounce * (normal * (*this)) / len;
	(*this) -= cross;
	return true;
}

//===============================================================
//
//	idVec4 - 4D vector
//
//===============================================================

class DLL_INTERFACE seVec4 {
public:
	float			x;
	float			y;
	float			z;
	float			w;

	seVec4(void);
	explicit seVec4(const float x, const float y, const float z, const float w);

	void 			Set(const float x, const float y, const float z, const float w);
	void			Zero(void);

	float			operator[](const int index) const;
	float &			operator[](const int index);
	seVec4			operator-() const;
	float			operator*(const seVec4 &a) const;
	seVec4			operator*(const float a) const;
	seVec4			operator/(const float a) const;
	seVec4			operator+(const seVec4 &a) const;
	seVec4			operator-(const seVec4 &a) const;
	seVec4 &		operator+=(const seVec4 &a);
	seVec4 &		operator-=(const seVec4 &a);
	seVec4 &		operator/=(const seVec4 &a);
	seVec4 &		operator/=(const float a);
	seVec4 &		operator*=(const float a);

	friend seVec4	operator*(const float a, const seVec4 b);

	bool			Compare(const seVec4 &a) const;							// exact compare, no epsilon
	bool			Compare(const seVec4 &a, const float epsilon) const;		// compare with epsilon
	bool			operator==(const seVec4 &a) const;						// exact compare, no epsilon
	bool			operator!=(const seVec4 &a) const;						// exact compare, no epsilon

	float			Length(void) const;
	float			LengthSqr(void) const;
	float			Normalize(void);			// returns length
	float			NormalizeFast(void);		// returns length

	int				GetDimension(void) const;

	const seVec2 &	ToVec2(void) const;
	seVec2 &		ToVec2(void);
	const seVec3 &	ToVec3(void) const;
	seVec3 &		ToVec3(void);
	const float *	ToFloatPtr(void) const;
	float *			ToFloatPtr(void);
	const char *	ToString(int precision = 2) const;

	void			Lerp(const seVec4 &v1, const seVec4 &v2, const float l);
};

extern seVec4 vec4_origin;
#define vec4_zero vec4_origin

SE_INLINE seVec4::seVec4(void) {
}

SE_INLINE seVec4::seVec4(const float x, const float y, const float z, const float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

SE_INLINE void seVec4::Set(const float x, const float y, const float z, const float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

SE_INLINE void seVec4::Zero(void) {
	x = y = z = w = 0.0f;
}

SE_INLINE float seVec4::operator[](int index) const {
	return (&x)[index];
}

SE_INLINE float& seVec4::operator[](int index) {
	return (&x)[index];
}

SE_INLINE seVec4 seVec4::operator-() const {
	return seVec4(-x, -y, -z, -w);
}

SE_INLINE seVec4 seVec4::operator-(const seVec4 &a) const {
	return seVec4(x - a.x, y - a.y, z - a.z, w - a.w);
}

SE_INLINE float seVec4::operator*(const seVec4 &a) const {
	return x * a.x + y * a.y + z * a.z + w * a.w;
}

SE_INLINE seVec4 seVec4::operator*(const float a) const {
	return seVec4(x * a, y * a, z * a, w * a);
}

SE_INLINE seVec4 seVec4::operator/(const float a) const {
	float inva = 1.0f / a;
	return seVec4(x * inva, y * inva, z * inva, w * inva);
}

SE_INLINE seVec4 operator*(const float a, const seVec4 b) {
	return seVec4(b.x * a, b.y * a, b.z * a, b.w * a);
}

SE_INLINE seVec4 seVec4::operator+(const seVec4 &a) const {
	return seVec4(x + a.x, y + a.y, z + a.z, w + a.w);
}

SE_INLINE seVec4 &seVec4::operator+=(const seVec4 &a) {
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
}

SE_INLINE seVec4 &seVec4::operator/=(const seVec4 &a) {
	x /= a.x;
	y /= a.y;
	z /= a.z;
	w /= a.w;

	return *this;
}

SE_INLINE seVec4 &seVec4::operator/=(const float a) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;
	z *= inva;
	w *= inva;

	return *this;
}

SE_INLINE seVec4 &seVec4::operator-=(const seVec4 &a) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
}

SE_INLINE seVec4 &seVec4::operator*=(const float a) {
	x *= a;
	y *= a;
	z *= a;
	w *= a;

	return *this;
}

SE_INLINE bool seVec4::Compare(const seVec4 &a) const {
	return ((x == a.x) && (y == a.y) && (z == a.z) && w == a.w);
}

SE_INLINE bool seVec4::Compare(const seVec4 &a, const float epsilon) const {
	if (seMath::Fabs(x - a.x) > epsilon) {
		return false;
	}

	if (seMath::Fabs(y - a.y) > epsilon) {
		return false;
	}

	if (seMath::Fabs(z - a.z) > epsilon) {
		return false;
	}

	if (seMath::Fabs(w - a.w) > epsilon) {
		return false;
	}

	return true;
}

SE_INLINE bool seVec4::operator==(const seVec4 &a) const {
	return Compare(a);
}

SE_INLINE bool seVec4::operator!=(const seVec4 &a) const {
	return !Compare(a);
}

SE_INLINE float seVec4::Length(void) const {
	return (float)seMath::Sqrt(x * x + y * y + z * z + w * w);
}

SE_INLINE float seVec4::LengthSqr(void) const {
	return (x * x + y * y + z * z + w * w);
}

SE_INLINE float seVec4::Normalize(void) {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z + w * w;
	invLength = seMath::InvSqrt(sqrLength);
	x *= invLength;
	y *= invLength;
	z *= invLength;
	w *= invLength;
	return invLength * sqrLength;
}

SE_INLINE float seVec4::NormalizeFast(void) {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z + w * w;
	invLength = seMath::RSqrt(sqrLength);
	x *= invLength;
	y *= invLength;
	z *= invLength;
	w *= invLength;
	return invLength * sqrLength;
}

SE_INLINE int seVec4::GetDimension(void) const {
	return 4;
}

SE_INLINE const seVec2 &seVec4::ToVec2(void) const {
	return *reinterpret_cast<const seVec2 *>(this);
}

SE_INLINE seVec2 &seVec4::ToVec2(void) {
	return *reinterpret_cast<seVec2 *>(this);
}

SE_INLINE const seVec3 &seVec4::ToVec3(void) const {
	return *reinterpret_cast<const seVec3 *>(this);
}

SE_INLINE seVec3 &seVec4::ToVec3(void) {
	return *reinterpret_cast<seVec3 *>(this);
}

SE_INLINE const float *seVec4::ToFloatPtr(void) const {
	return &x;
}

SE_INLINE float *seVec4::ToFloatPtr(void) {
	return &x;
}


//===============================================================
//
//	idPolar3
//
//===============================================================

class sePolar3 {
public:
	float			radius, theta, phi;

	sePolar3(void);
	explicit sePolar3(const float radius, const float theta, const float phi);

	void 			Set(const float radius, const float theta, const float phi);

	float			operator[](const int index) const;
	float &			operator[](const int index);
	sePolar3		operator-() const;
	sePolar3 &		operator=(const sePolar3 &a);

	seVec3			ToVec3(void) const;
};

SE_INLINE sePolar3::sePolar3(void) {
}

SE_INLINE sePolar3::sePolar3(const float radius, const float theta, const float phi) {
	assert(radius > 0);
	this->radius = radius;
	this->theta = theta;
	this->phi = phi;
}

SE_INLINE void sePolar3::Set(const float radius, const float theta, const float phi) {
	assert(radius > 0);
	this->radius = radius;
	this->theta = theta;
	this->phi = phi;
}

SE_INLINE float sePolar3::operator[](const int index) const {
	return (&radius)[index];
}

SE_INLINE float &sePolar3::operator[](const int index) {
	return (&radius)[index];
}

SE_INLINE sePolar3 sePolar3::operator-() const {
	return sePolar3(radius, -theta, -phi);
}


SE_INLINE sePolar3 &sePolar3::operator=(const sePolar3 &a) {
	radius = a.radius;
	theta = a.theta;
	phi = a.phi;
	return *this;
}

SE_INLINE seVec3 sePolar3::ToVec3(void) const {
	float sp, cp, st, ct;
	seMath::SinCos(phi, sp, cp);
	seMath::SinCos(theta, st, ct);
	return seVec3(cp * radius * ct, cp * radius * st, radius * sp);
}


#endif