#ifndef SIMPLE_ENGINE_VECTOR_H
#define SIMPLE_ENGINE_VECTOR_H

#include <vector>
#include <math.h>

namespace SimpleEngine {

	class Vector3
	{
	public:
		float x;
		float y;
		float z;

		Vector3() :x(0), y(0), z(0)
		{}

		Vector3(float _x, float _y, float _z) :x(_x), y(_y), z(_z)
		{}

		Vector3 operator + (const Vector3& _other)
		{
			Vector3 result;
			result.x = x + _other.x;
			result.y = y + _other.y;
			result.z = z + _other.z;
			return result;
		}

		Vector3& operator += (const Vector3& _other)
		{
			x = x + _other.x;
			y = y + _other.y;
			z = z + _other.z;
			return *this;
		}

		Vector3 operator - (const Vector3& _other) const
		{
			Vector3 result;
			result.x = x - _other.x;
			result.y = y - _other.y;
			result.z = z - _other.z;
			return result;
		}

		Vector3& operator -= (const Vector3& _other)
		{
			x = x - _other.x;
			y = y - _other.y;
			z = z - _other.z;
			return *this;
		}

		float operator * (const Vector3& _other)
		{
			Vector3 result;
			result.x = x * _other.x;
			result.y = y * _other.y;
			result.z = z * _other.z;
			return result.x + result.y + result.z;
		}

		Vector3 operator * (float _s)
		{
			Vector3 result;
			result.x = x * _s;
			result.y = y * _s;
			result.z = z * _s;
			return result;
		}

		Vector3& operator *= (float _s)
		{
			x = x * _s;
			y = y * _s;
			z = z * _s;
			return *this;
		}

		Vector3 cross(const Vector3& _other)
		{
			Vector3 result;
			result.x = y * _other.z - z * _other.y;
			result.y = z * _other.x - x * _other.z;
			result.z = x * _other.y - y * _other.x;
			return result;
		}

		float Length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		float LengthSqr() const
		{
			return x * x + y * y + z * z;
		}

		bool IsZero() const
		{
			return abs(LengthSqr()) <= FLT_EPSILON;
		}

		void normalize()
		{
			do {
				if (IsZero())
					break;
				float lenSqr = LengthSqr();
				if (abs(lenSqr - 1) <= FLT_EPSILON)
					break;
				float len = sqrtf(lenSqr);
				x /= len;
				y /= len;
				z /= len;
			}while(0);
		}

		static void GramSchmidtOrthogonalization(std::vector<Vector3>& _basises)
		{
			unsigned int bNum = _basises.size();
			for (unsigned int i = 1; i < bNum; ++i) {
				Vector3 ei = _basises[i];
				Vector3 eSum;
				for (unsigned int j = 0; j <= i - 1; ++j) {
					Vector3 ej = _basises[j];
					eSum +=  ej * (ei * ej) * (1.0f / ej.LengthSqr());
				}
				ei = ei - eSum;
				_basises[i] = ei;
				if (ei.IsZero())
					break;
			}
		}

	};
}

#endif