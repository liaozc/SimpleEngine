#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <math.h>

namespace SimpleEngine {

	class Vector3
	{
	public:
		float _x;
		float _y;
		float _z;

		Vector3() :_x(0), _y(0), _z(0)
		{}

		Vector3(float __x, float __y, float __z) :_x(__x), _y(__y), _z(__z)
		{}

		Vector3 operator + (const Vector3& _other)
		{
			Vector3 result;
			result._x = _x + _other._x;
			result._y = _y + _other._y;
			result._z = _z + _other._z;
			return result;
		}

		Vector3& operator += (const Vector3& _other)
		{
			_x = _x + _other._x;
			_y = _y + _other._y;
			_z = _z + _other._z;
			return *this;
		}

		Vector3 operator - (const Vector3& _other) const
		{
			Vector3 result;
			result._x = _x - _other._x;
			result._y = _y - _other._y;
			result._z = _z - _other._z;
			return result;
		}

		Vector3& operator -= (const Vector3& _other)
		{
			_x = _x - _other._x;
			_y = _y - _other._y;
			_z = _z - _other._z;
			return *this;
		}

		float operator * (const Vector3& _other)
		{
			Vector3 result;
			result._x = _x * _other._x;
			result._y = _y * _other._y;
			result._z = _z * _other._z;
			return result._x + result._y + result._z;
		}

		Vector3 operator * (float _s)
		{
			Vector3 result;
			result._x = _x * _s;
			result._y = _y * _s;
			result._z = _z * _s;
			return result;
		}

		Vector3& operator *= (float _s)
		{
			_x = _x * _s;
			_y = _y * _s;
			_z = _z * _s;
			return *this;
		}

		Vector3 cross(const Vector3& _other)
		{
			Vector3 result;
			result._x = _y * _other._z - _z * _other._y;
			result._y = _z * _other._x - _x * _other._z;
			result._z = _x * _other._y - _y * _other._x;
			return result;
		}

		float Length() const
		{
			return sqrt(_x * _x + _y * _y + _z * _z);
		}

		float LengthSqr() const
		{
			return _x * _x + _y * _y + _z * _z;
		}

		bool IsZero() const
		{
			return (_x == 0 && _y == 0 && _z == 0);
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