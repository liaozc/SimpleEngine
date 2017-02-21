#ifndef MATRIX_H
#define MATRIX_H

#include<string>

namespace SimpleEngine {

	class Mat2
	{
	public:
		union
		{
			struct {
				float m11;
				float m12;
				float m21;
				float m22;
			};
			float c[4];
		};

		Mat2()
		{
			memset(&c, 0, sizeof(c));
		}

		Mat2(float _m11, float _m12, float _m21, float _m22) :m11(_m11), m12(_m12), m21(_m21), m22(_m22)
		{}

		Mat2 operator + (const Mat2& _other)
		{
			Mat2 r;
			r.m11 = m11 + _other.m11;
			r.m12 = m12 + _other.m12;
			r.m21 = m21 + _other.m21;
			r.m22 = m22 + _other.m22;
			return r;
		}

		void operator += (const Mat2& _other)
		{
			m11 = m11 + _other.m11;
			m12 = m12 + _other.m12;
			m21 = m21 + _other.m21;
			m22 = m22 + _other.m22;
		}

		Mat2 operator - (const Mat2& _other)
		{
			Mat2 r;
			r.m11 = m11 - _other.m11;
			r.m12 = m12 - _other.m12;
			r.m21 = m21 - _other.m21;
			r.m22 = m22 - _other.m22;
			return r;
		}

		void operator -= (const Mat2& _other)
		{
			m11 = m11 - _other.m11;
			m12 = m12 - _other.m12;
			m21 = m21 - _other.m21;
			m22 = m22 - _other.m22;
		}

		Mat2 operator * (float _s)
		{
			Mat2 r;
			r.m11 = m11 * _s;
			r.m12 = m12 * _s;
			r.m21 = m21 * _s;
			r.m22 = m22 * _s;
			return r;
		}

		Mat2& operator *= (float _s)
		{
			m11 *= _s;
			m12 *= _s;
			m21 *= _s;
			m22 *= _s;
			return *this;
		}

		Mat2 operator * (const Mat2& _other)
		{
			Mat2 r;
			r.m11 = m11 * _other.m11 + m12 * _other.m21;
			r.m12 = m11 * _other.m12 + m12 * _other.m22;
			r.m21 = m21 * _other.m11 + m22 * _other.m21;
			r.m22 = m21 * _other.m12 + m22 * _other.m22;
			return r;
		}

		void operator *= (const Mat2& _other)
		{
			m11 = m11 * _other.m11 + m12 * _other.m21;
			m12 = m11 * _other.m12 + m12 * _other.m22;
			m21 = m21 * _other.m11 + m22 * _other.m21;
			m22 = m21 * _other.m12 + m22 * _other.m22;
		}

		float determinant() const
		{
			return m11 * m22 - m12 * m21;
		}

		Mat2 getInverses() const
		{
			Mat2 m;
			float det = determinant();
			if (det != 0) {
				float idet = 1.0f / det;
				m.m11 = idet * m22;
				m.m12 = -idet * m12;
				m.m21 = -idet * m21;
				m.m22 = idet * m11;
			}
			return m;
		}
	};

	class Mat3
	{
	public:
		union
		{
			struct {
				float m11;
				float m12;
				float m13;
				float m21;
				float m22;
				float m23;
				float m31;
				float m32;
				float m33;
			};
			float c[9];
		};

		Mat3()
		{
			memset(&c, 0, sizeof(c));
		}

		Mat3(float _m11, float _m12, float _m13, float _m21, float _m22, float _m23, float _m31, float _m32, float _m33) :
			m11(_m11), m12(_m12), m13(_m13),
			m21(_m21), m22(_m22), m23(_m23),
			m31(_m31), m32(_m32), m33(_m33)
		{}

		Mat3 operator + (const Mat3& _other)
		{
			Mat3 r;
			r.m11 = m11 + _other.m11;
			r.m12 = m12 + _other.m12;
			r.m13 = m13 + _other.m13;
			r.m21 = m21 + _other.m21;
			r.m22 = m22 + _other.m22;
			r.m23 = m23 + _other.m23;
			r.m31 = m31 + _other.m31;
			r.m32 = m32 + _other.m32;
			r.m33 = m33 + _other.m33;
			return r;
		}

		void operator += (const Mat3& _other)
		{
			m11 = m11 + _other.m11;
			m12 = m12 + _other.m12;
			m13 = m13 + _other.m13;
			m21 = m21 + _other.m21;
			m22 = m22 + _other.m22;
			m23 = m23 + _other.m23;
			m31 = m31 + _other.m31;
			m32 = m32 + _other.m32;
			m33 = m33 + _other.m33;
		}

		Mat3 operator - (const Mat3& _other)
		{
			Mat3 r;
			r.m11 = m11 - _other.m11;
			r.m12 = m12 - _other.m12;
			r.m13 = m13 - _other.m13;
			r.m21 = m21 - _other.m21;
			r.m22 = m22 - _other.m22;
			r.m23 = m23 - _other.m23;
			r.m31 = m31 - _other.m31;
			r.m32 = m32 - _other.m32;
			r.m33 = m33 - _other.m33;
			return r;
		}

		void operator -= (const Mat3& _other)
		{
			m11 = m11 - _other.m11;
			m12 = m12 - _other.m12;
			m13 = m13 - _other.m13;
			m21 = m21 - _other.m21;
			m22 = m22 - _other.m22;
			m23 = m23 - _other.m23;
			m31 = m31 - _other.m31;
			m32 = m32 - _other.m32;
			m33 = m33 - _other.m33;
		}

		Mat3 operator * (float _s)
		{
			Mat3 r;
			r.m11 = m11 * _s;
			r.m12 = m12 * _s;
			r.m13 = m13 * _s;
			r.m21 = m21 * _s;
			r.m22 = m22 * _s;
			r.m23 = m23 * _s;
			r.m31 = m31 * _s;
			r.m32 = m32 * _s;
			r.m33 = m33 * _s;
			return r;
		}

		void operator *= (float _s)
		{
			m11 = m11 * _s;
			m12 = m12 * _s;
			m13 = m13 * _s;
			m21 = m21 * _s;
			m22 = m22 * _s;
			m23 = m23 * _s;
			m31 = m31 * _s;
			m32 = m32 * _s;
			m33 = m33 * _s;
		}

		Mat3 operator * (const Mat3& _other)
		{
			Mat3 r;
			r.m11 = m11 * _other.m11 + m12 * _other.m21 + m13 * _other.m31;
			r.m12 = m11 * _other.m12 + m12 * _other.m22 + m13 * _other.m32;
			r.m13 = m11 * _other.m13 + m12 * _other.m23 + m13 * _other.m33;

			r.m21 = m21 * _other.m11 + m22 * _other.m21 + m23 * _other.m31;
			r.m22 = m21 * _other.m12 + m22 * _other.m22 + m23 * _other.m32;
			r.m23 = m21 * _other.m13 + m22 * _other.m23 + m23 * _other.m33;

			r.m31 = m31 * _other.m11 + m32 * _other.m21 + m33 * _other.m31;
			r.m32 = m31 * _other.m12 + m32 * _other.m22 + m33 * _other.m32;
			r.m33 = m31 * _other.m13 + m32 * _other.m23 + m33 * _other.m33;
			return r;
		}

		void operator *= (const Mat3& _other)
		{
			m11 = m11 * _other.m11 + m12 * _other.m21 + m13 * _other.m31;
			m12 = m11 * _other.m12 + m12 * _other.m22 + m13 * _other.m32;
			m13 = m11 * _other.m13 + m12 * _other.m23 + m13 * _other.m33;

			m21 = m21 * _other.m11 + m22 * _other.m21 + m23 * _other.m31;
			m22 = m21 * _other.m12 + m22 * _other.m22 + m23 * _other.m32;
			m23 = m21 * _other.m13 + m22 * _other.m23 + m23 * _other.m33;

			m31 = m31 * _other.m11 + m32 * _other.m21 + m33 * _other.m31;
			m32 = m31 * _other.m12 + m32 * _other.m22 + m33 * _other.m32;
			m33 = m31 * _other.m13 + m32 * _other.m23 + m33 * _other.m33;
		}

		float determinant() const
		{
			return m11*(m22 * m33 - m32*m23) - m12*(m21*m33 - m31*m23) + m13*(m21*m32 - m31*m22);
		}

		Mat3 getInverses() const
		{
			Mat3 m;
			float det = determinant();
			if (det != 0) {
				float idet = 1.0f / det;
				m.m11 = Mat2(m22, m23, m32, m33).determinant() * idet;
				m.m12 = -Mat2(m12, m13, m32, m33).determinant() * idet;
				m.m13 = Mat2(m12, m13, m22, m23).determinant() * idet;
				m.m21 = -Mat2(m21, m23, m31, m33).determinant() * idet;
				m.m22 = Mat2(m11, m13, m31, m33).determinant() * idet;
				m.m23 = -Mat2(m11, m13, m21, m23).determinant() * idet;
				m.m31 = Mat2(m21, m22, m31, m32).determinant() * idet;
				m.m32 = -Mat2(m11, m12, m31, m32).determinant() * idet;
				m.m33 = Mat2(m11, m12, m21, m22).determinant() * idet;
			}
			return m;
		}
	};

	class Mat4
	{
	public:
		union
		{
			struct {
				float m11;
				float m12;
				float m13;
				float m14;
				float m21;
				float m22;
				float m23;
				float m24;
				float m31;
				float m32;
				float m33;
				float m34;
				float m41;
				float m42;
				float m43;
				float m44;
			};
			float c[16];
		};

		Mat4()
		{
			memset(&c, 0, sizeof(c));
		}

		Mat4(float _m11, float _m12, float _m13, float _m14,
			float _m21, float _m22, float _m23, float _m24,
			float _m31, float _m32, float _m33, float _m34,
			float _m41, float _m42, float _m43, float _m44) :
			m11(_m11), m12(_m12), m13(_m13), m14(_m14),
			m21(_m21), m22(_m22), m23(_m23), m24(_m24),
			m31(_m31), m32(_m32), m33(_m33), m34(_m34),
			m41(_m41), m42(_m42), m43(_m43), m44(_m44)
		{}

		Mat4 operator + (const Mat4& _other)
		{
			Mat4 r;
			r.m11 = m11 + _other.m11;
			r.m12 = m12 + _other.m12;
			r.m13 = m13 + _other.m13;
			r.m14 = m14 + _other.m14;

			r.m21 = m21 + _other.m21;
			r.m22 = m22 + _other.m22;
			r.m23 = m23 + _other.m23;
			r.m24 = m24 + _other.m24;

			r.m31 = m31 + _other.m31;
			r.m32 = m32 + _other.m32;
			r.m33 = m33 + _other.m33;
			r.m34 = m34 + _other.m34;


			r.m41 = m41 + _other.m41;
			r.m42 = m42 + _other.m42;
			r.m43 = m43 + _other.m43;
			r.m44 = m44 + _other.m44;

			return r;
		}

		void operator += (const Mat4& _other)
		{
			m11 = m11 + _other.m11;
			m12 = m12 + _other.m12;
			m13 = m13 + _other.m13;
			m14 = m14 + _other.m14;

			m21 = m21 + _other.m21;
			m22 = m22 + _other.m22;
			m23 = m23 + _other.m23;
			m24 = m24 + _other.m24;

			m31 = m31 + _other.m31;
			m32 = m32 + _other.m32;
			m33 = m33 + _other.m33;
			m34 = m34 + _other.m34;


			m41 = m41 + _other.m41;
			m42 = m42 + _other.m42;
			m43 = m43 + _other.m43;
			m44 = m44 + _other.m44;
		}

		Mat4 operator - (const Mat4& _other)
		{
			Mat4 r;
			r.m11 = m11 - _other.m11;
			r.m12 = m12 - _other.m12;
			r.m13 = m13 - _other.m13;
			r.m14 = m14 - _other.m14;

			r.m21 = m21 - _other.m21;
			r.m22 = m22 - _other.m22;
			r.m23 = m23 - _other.m23;
			r.m24 = m24 - _other.m24;

			r.m31 = m31 - _other.m31;
			r.m32 = m32 - _other.m32;
			r.m33 = m33 - _other.m33;
			r.m34 = m34 - _other.m34;


			r.m41 = m41 - _other.m41;
			r.m42 = m42 - _other.m42;
			r.m43 = m43 - _other.m43;
			r.m44 = m44 - _other.m44;

			return r;
		}

		void operator -= (const Mat4& _other)
		{
			m11 = m11 - _other.m11;
			m12 = m12 - _other.m12;
			m13 = m13 - _other.m13;
			m14 = m14 - _other.m14;

			m21 = m21 - _other.m21;
			m22 = m22 - _other.m22;
			m23 = m23 - _other.m23;
			m24 = m24 - _other.m24;

			m31 = m31 - _other.m31;
			m32 = m32 - _other.m32;
			m33 = m33 - _other.m33;
			m34 = m34 - _other.m34;


			m41 = m41 - _other.m41;
			m42 = m42 - _other.m42;
			m43 = m43 - _other.m43;
			m44 = m44 - _other.m44;
		}

		Mat4 operator * (float _s)
		{
			Mat4 r;
			r.m11 = m11 * _s;
			r.m12 = m12 * _s;
			r.m13 = m13 * _s;
			r.m14 = m14 * _s;

			r.m21 = m21 * _s;
			r.m22 = m22 * _s;
			r.m23 = m23 * _s;
			r.m24 = m24 * _s;

			r.m31 = m31 * _s;
			r.m32 = m32 * _s;
			r.m33 = m33 * _s;
			r.m34 = m34 * _s;

			r.m41 = m41 * _s;
			r.m42 = m42 * _s;
			r.m43 = m43 * _s;
			r.m44 = m44 * _s;

			return r;
		}

		void operator *= (float _s)
		{
			m11 = m11 * _s;
			m12 = m12 * _s;
			m13 = m13 * _s;
			m14 = m14 * _s;

			m21 = m21 * _s;
			m22 = m22 * _s;
			m23 = m23 * _s;
			m24 = m24 * _s;

			m31 = m31 * _s;
			m32 = m32 * _s;
			m33 = m33 * _s;
			m34 = m34 * _s;

			m41 = m41 * _s;
			m42 = m42 * _s;
			m43 = m43 * _s;
			m44 = m44 * _s;
		}

		Mat4 operator * (const Mat4& _other)
		{
			Mat4 r;
			r.m11 = m11 * _other.m11 + m12 * _other.m21 + m13 * _other.m31 + m14 * _other.m41;
			r.m12 = m11 * _other.m12 + m12 * _other.m22 + m13 * _other.m32 + m14 * _other.m42;
			r.m13 = m11 * _other.m13 + m12 * _other.m23 + m13 * _other.m33 + m14 * _other.m43;
			r.m14 = m11 * _other.m14 + m12 * _other.m24 + m13 * _other.m34 + m14 * _other.m44;

			r.m21 = m21 * _other.m11 + m22 * _other.m21 + m23 * _other.m31 + m24 * _other.m41;
			r.m22 = m21 * _other.m12 + m22 * _other.m22 + m23 * _other.m32 + m24 * _other.m42;
			r.m23 = m21 * _other.m13 + m22 * _other.m23 + m23 * _other.m33 + m24 * _other.m43;
			r.m24 = m21 * _other.m14 + m22 * _other.m24 + m23 * _other.m34 + m24 * _other.m44;

			r.m31 = m31 * _other.m11 + m32 * _other.m21 + m33 * _other.m31 + m34 * _other.m41;
			r.m32 = m31 * _other.m12 + m32 * _other.m22 + m33 * _other.m32 + m34 * _other.m42;
			r.m33 = m31 * _other.m13 + m32 * _other.m23 + m33 * _other.m33 + m34 * _other.m43;
			r.m34 = m31 * _other.m14 + m32 * _other.m24 + m33 * _other.m34 + m34 * _other.m44;

			r.m41 = m41 * _other.m11 + m42 * _other.m21 + m43 * _other.m31 + m44 * _other.m41;
			r.m42 = m41 * _other.m12 + m42 * _other.m22 + m43 * _other.m32 + m44 * _other.m42;
			r.m43 = m41 * _other.m13 + m42 * _other.m23 + m43 * _other.m33 + m44 * _other.m43;
			r.m44 = m41 * _other.m14 + m42 * _other.m24 + m43 * _other.m34 + m44 * _other.m44;

			return r;
		}

		void operator *= (const Mat4& _other)
		{
			m11 = m11 * _other.m11 + m12 * _other.m21 + m13 * _other.m31 + m14 * _other.m41;
			m12 = m11 * _other.m12 + m12 * _other.m22 + m13 * _other.m32 + m14 * _other.m42;
			m13 = m11 * _other.m13 + m12 * _other.m23 + m13 * _other.m33 + m14 * _other.m43;
			m14 = m11 * _other.m14 + m12 * _other.m24 + m13 * _other.m34 + m14 * _other.m44;

			m21 = m21 * _other.m11 + m22 * _other.m21 + m23 * _other.m31 + m24 * _other.m41;
			m22 = m21 * _other.m12 + m22 * _other.m22 + m23 * _other.m32 + m24 * _other.m42;
			m23 = m21 * _other.m13 + m22 * _other.m23 + m23 * _other.m33 + m24 * _other.m43;
			m24 = m21 * _other.m14 + m22 * _other.m24 + m23 * _other.m34 + m24 * _other.m44;

			m31 = m31 * _other.m11 + m32 * _other.m21 + m33 * _other.m31 + m34 * _other.m41;
			m32 = m31 * _other.m12 + m32 * _other.m22 + m33 * _other.m32 + m34 * _other.m42;
			m33 = m31 * _other.m13 + m32 * _other.m23 + m33 * _other.m33 + m34 * _other.m43;
			m34 = m31 * _other.m14 + m32 * _other.m24 + m33 * _other.m34 + m34 * _other.m44;

			m41 = m41 * _other.m11 + m42 * _other.m21 + m43 * _other.m31 + m44 * _other.m41;
			m42 = m41 * _other.m12 + m42 * _other.m22 + m43 * _other.m32 + m44 * _other.m42;
			m43 = m41 * _other.m13 + m42 * _other.m23 + m43 * _other.m33 + m44 * _other.m43;
			m44 = m41 * _other.m14 + m42 * _other.m24 + m43 * _other.m34 + m44 * _other.m44;
		}

		operator Mat3()
		{
			Mat3 m(m11, m12, m13,
				m21, m22, m23,
				m31, m32, m33);
			return m;
		}

		float determinant() const
		{
			float det = 0;
			det += m11 * Mat3(m22, m23, m24, m32, m33, m34, m42, m43, m44).determinant(); // 1+1
			det -= m12 * Mat3(m21, m23, m24, m31, m33, m34, m41, m43, m44).determinant(); // 1+2
			det += m13 * Mat3(m21, m22, m24, m31, m32, m34, m41, m42, m44).determinant(); // 1+3
			det -= m14 * Mat3(m21, m22, m23, m31, m32, m33, m41, m42, m43).determinant(); // 1+4
			return det;
		}

		Mat4 getInverses() const
		{
			Mat4 m;
			float det = determinant();
			if (det != 0) {
				float idet = 1.0f / det;
				m.m11 = Mat3(m22, m23, m24, m32, m33, m34, m42, m43, m44).determinant() * idet;
				m.m12 = -Mat3(m12, m13, m14, m32, m33, m34, m42, m43, m44).determinant() * idet;
				m.m13 = Mat3(m12, m13, m14, m22, m23, m24, m42, m43, m44).determinant() * idet;
				m.m14 = -Mat3(m12, m13, m14, m22, m23, m24, m32, m33, m34).determinant() * idet;

				m.m21 = -Mat3(m21, m23, m24, m31, m33, m34, m41, m43, m44).determinant() * idet;
				m.m22 = Mat3(m11, m13, m14, m31, m33, m34, m41, m43, m44).determinant() * idet;
				m.m23 = -Mat3(m11, m13, m14, m21, m23, m24, m41, m43, m44).determinant() * idet;
				m.m24 = Mat3(m11, m13, m14, m21, m23, m24, m31, m33, m34).determinant() * idet;

				m.m31 = Mat3(m21, m22, m24, m31, m32, m34, m41, m42, m44).determinant() * idet;
				m.m32 = -Mat3(m11, m12, m14, m31, m32, m34, m41, m42, m44).determinant() * idet;
				m.m33 = Mat3(m11, m12, m14, m21, m22, m24, m41, m42, m44).determinant() * idet;
				m.m34 = -Mat3(m11, m12, m14, m21, m22, m24, m31, m32, m34).determinant() * idet;

				m.m41 = -Mat3(m21, m22, m23, m31, m32, m33, m41, m42, m43).determinant() * idet;
				m.m42 = Mat3(m11, m12, m13, m31, m32, m33, m41, m42, m43).determinant() * idet;
				m.m43 = -Mat3(m11, m12, m13, m21, m22, m23, m41, m42, m43).determinant() * idet;
				m.m44 = Mat3(m11, m12, m13, m21, m22, m23, m31, m32, m33).determinant() * idet;
			}
			return m;
		}
	};
}

#endif