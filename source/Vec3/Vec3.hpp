#ifndef __VEC3_HPP__
#define __VEC3_HPP__

/*
   Vector3クラス
NOTE: (x,y,z)と(r,g,b)併用
*/

#include <iostream>
#include <cmath>

template<class TYPE>
class Vec3
{
	public:
		TYPE e[3];

		Vec3(): e{} {}
		Vec3(const TYPE &x, const TYPE &y, const TYPE &z): e{x, y, z} {}
		~Vec3() {}

		// Operator
		// Base
		inline const Vec3<TYPE>& operator+() const { return *this; }
		inline Vec3<TYPE> operator-() const { return Vec3<TYPE>(-e[0], -e[1], -e[2]); }
		inline TYPE  operator[](const int &i) const { return e[i]; }
		inline TYPE& operator[](const int &i) { return e[i]; }
		// Vector	
		inline Vec3<TYPE>& operator+=(const Vec3 &rhs)
		{
			e[0] += rhs.e[0];
			e[1] += rhs.e[1];
			e[2] += rhs.e[2];
			return *this;
		}
		inline Vec3<TYPE>& operator-=(const Vec3 &rhs)
		{
			e[0] -= rhs.e[0];
			e[1] -= rhs.e[1];
			e[2] -= rhs.e[2];
			return *this;
		}
		inline Vec3<TYPE>& operator*=(const Vec3 &rhs)
		{
			e[0] *= rhs.e[0];
			e[1] *= rhs.e[1];
			e[2] *= rhs.e[2];
			return *this;
		}
		inline Vec3<TYPE>& operator/=(const Vec3 &rhs)
		{
			e[0] /= rhs.e[0];
			e[1] /= rhs.e[1];
			e[2] /= rhs.e[2];
			return *this;
		}
		// Scalar
		inline Vec3<TYPE>& operator+=(const TYPE &rhs)
		{
			e[0] += rhs;
			e[1] += rhs;
			e[2] += rhs;
			return *this;
		}
		inline Vec3<TYPE>& operator-=(const TYPE &rhs)
		{
			e[0] -= rhs;
			e[1] -= rhs;
			e[2] -= rhs;
			return *this;
		}
		inline Vec3<TYPE>& operator*=(const TYPE &rhs)
		{
			e[0] *= rhs;
			e[1] *= rhs;
			e[2] *= rhs;
			return *this;
		}
		inline Vec3<TYPE>& operator/=(const TYPE &rhs)
		{
			const TYPE k = static_cast<TYPE>(1.0) / rhs;
			e[0] *= k;
			e[1] *= k;
			e[2] *= k;
			return *this;
		}

		// function
		inline TYPE Length() const { return static_cast<TYPE>(std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2])); }
		inline TYPE SquaredLength() const { return (e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
		inline void Normalize()
		{
			TYPE k = static_cast<TYPE>(1.0) / Length();
			*this *= k;
		}

		// Getter
		// Coordinate
		inline TYPE x() const { return e[0]; }
		inline TYPE y() const { return e[1]; }
		inline TYPE z() const { return e[2]; }
		// Color
		inline TYPE r() const { return e[0]; }
		inline TYPE g() const { return e[1]; }
		inline TYPE b() const { return e[2]; }
};

// Stream
template<class TYPE> std::istream& operator>>(std::istream &is, const Vec3<TYPE> &t) { is >> t.e[0] >> t.e[1] >> t.e[2]; return is; }
template<class TYPE> std::ostream& operator<<(std::ostream &os, const Vec3<TYPE> &t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}
// Conditional
template<class TYPE> Vec3<TYPE> operator+(const Vec3<TYPE> &lhs, const Vec3<TYPE> &rhs) { return Vec3<TYPE>(lhs.e[0] + rhs.e[0], lhs.e[1] + rhs.e[1], lhs.e[2] + rhs.e[2]); }
template<class TYPE> Vec3<TYPE> operator+(const Vec3<TYPE> &lhs, const TYPE &rhs) { return Vec3<TYPE>(lhs.e[0] + rhs, lhs.e[1] + rhs, lhs.e[2] + rhs); }
template<class TYPE> Vec3<TYPE> operator-(const Vec3<TYPE> &lhs, const Vec3<TYPE> &rhs) { return Vec3<TYPE>(lhs.e[0] - rhs.e[0], lhs.e[1] - rhs.e[1], lhs.e[2] - rhs.e[2]); }
template<class TYPE> Vec3<TYPE> operator*(const Vec3<TYPE> &lhs, const Vec3<TYPE> &rhs) { return Vec3<TYPE>(lhs.e[0] * rhs.e[0], lhs.e[1] * rhs.e[1], lhs.e[2] * rhs.e[2]); }
template<class TYPE> Vec3<TYPE> operator*(const Vec3<TYPE> &lhs, const TYPE &rhs) { return Vec3<TYPE>(lhs.e[0] * rhs, lhs.e[1] * rhs, lhs.e[2] * rhs); }
template<class TYPE> Vec3<TYPE> operator*(const TYPE &lhs,const Vec3<TYPE> &rhs) { return Vec3<TYPE>(rhs.e[0] * lhs, rhs.e[1] * lhs, rhs.e[2] * lhs); }
template<class TYPE> Vec3<TYPE> operator/(const Vec3<TYPE> &lhs, const Vec3<TYPE> &rhs) { return Vec3<TYPE>(lhs.e[0] / rhs.e[0], lhs.e[1] / rhs.e[1], lhs.e[2] / rhs.e[2]); }
template<class TYPE> Vec3<TYPE> operator/(const Vec3<TYPE> &lhs, const TYPE &rhs) { return Vec3<TYPE>(lhs.e[0] / rhs, lhs.e[1] / rhs, lhs.e[2] / rhs); }

// Function
namespace MyVec
{
	template<class TYPE> TYPE Dot(const Vec3<TYPE> &lhs, const Vec3<TYPE> &rhs)
	{
		return lhs.e[0] * rhs.e[0] + lhs.e[1] * rhs.e[1] + lhs.e[2] * rhs.e[2];
	}
	template<class TYPE> Vec3<TYPE> Cross(const Vec3<TYPE> &lhs, const Vec3<TYPE> &rhs)
	{
		return Vec3<TYPE>
			(
			 (lhs.e[1]*rhs.e[2]-lhs.e[2]*rhs.e[1]),
			 (lhs.e[2]*rhs.e[0]-lhs.e[0]*rhs.e[2]),
			 (lhs.e[0]*rhs.e[1]-lhs.e[1]*rhs.e[0])
			);
	}
	template<class TYPE> Vec3<TYPE> UnitVector(const Vec3<TYPE> &vec) { return vec / vec.Length(); }
};
#endif
