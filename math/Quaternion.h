#ifndef SIMPLE_ENGINE_QUATERNION_H
#define SIMPLE_ENGINE_QUATERNION_H

#include "Vector.h"
#include "Matrix.h"

namespace SimpleEngine {
	
	class Quaternion
	{
	public:
		float x, y, z, w;
		
		Quaternion() :x(0), y(0), z(0), w(1.0f)
		{}
		
		Quaternion(float _x, float _y, float _z, float _w):x(_x),y(_y),z(_z),w(_w)
		{}

		Quaternion operator *(const Quaternion& _other)
		{
			Quaternion q;
			q.x = w * _other.x + x * _other.w + y * _other.z - z * _other.y;
			q.y = w * _other.y + y * _other.w + z * _other.x - x * _other.z;
			q.z = w * _other.z + z * _other.w + x * _other.y - y * _other.x;
			q.w = w * _other.w - x * _other.x - y * _other.y - z * _other.z;
			return q;
		}

		Quaternion& operator *= (const Quaternion& _other)
		{
			x = w * _other.x + x * _other.w + y * _other.z - z * _other.y;
			y = w * _other.y + y * _other.w + z * _other.x - x * _other.z;
			z = w * _other.z + z * _other.w + x * _other.y - y * _other.x;
			w = w * _other.w - x * _other.x - y * _other.y - z * _other.z;
			return *this;
		}

		float LengthSqr() const
		{
			return x*x + y*y + z*z + w*w;
		}

		float Length() const
		{
			return sqrt(x*x + y*y + z*z + w*w);
		}

		void Normalize()
		{
			float lenSqr = LengthSqr();
			if (abs(lenSqr - 1.0f) < FLT_EPSILON)
				return;
			if (abs(lenSqr) < FLT_EPSILON)
				return;
			float len = sqrt(lenSqr);
			x /= len;
			y /= len;
			z /= len;
			w /= len;
		}

		Quaternion GetInverses() const
		{//must normalize first. so they all unit quaternion.
			Quaternion q(-x, -y, -z, w);
			return q;
		}
		
		Mat3 ToMat() const
		{
			Mat3 m;
			float x2 = x * x;
			float y2 = y * y;
			float z2 = z * z;
			float wx = w * x;
			float wy = w * y;
			float wz = w * z;
			float xy = x * y;
			float xz = x * z;
			float yz = y * z;
			m.m11 = 1 - 2 * y2 - 2 * z2;
			m.m12 = 2 * xy - 2 * wz;
			m.m13 = 2 * xz + 2 * wy;
			m.m21 = 2 * xy + 2 * wz;
			m.m22 = 1 - 2 * x2 - 2 * z2;
			m.m23 = 2 * yz - 2 * wx;
			m.m31 = 2 * xz - 2 * wz;
			m.m32 = 2 * yz + 2 * wx;
			m.m33 = 1 - 2 * x2 - 2 * y2;
			return m;
		}

		Vector3 RotVec3_N(const Vector3& _v)
		{//normal method £¬but not the perfect one.
			Quaternion q;
			q.w = 0;
			q.x = _v.x;
			q.y = _v.y;
			q.z = _v.z;
			q = (*this) * q * (this->GetInverses());
			Vector3 rv;
			rv.x = q.x;
			rv.y = q.y;
			rv.z = q.z;
			return rv;
		}

		Vector3 RotVec3(const Vector3& _v)
		{
			
		}



		static Quaternion FromRotatedAxis(const Vector3& _axis, float _angle)
		{
			Quaternion q;
			_angle *= 0.5f;
			float sina = sinf(_angle);
			float cosa = cosf(_angle);
			q.x = sina * _axis.x;
			q.y = sina * _axis.y;
			q.z = sina * _axis.z;
			q.w = cosa;
			return q;
		}

	};

}

#endif