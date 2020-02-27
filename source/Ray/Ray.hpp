#ifndef __RAY_HPP__
#define __RAY_HPP__

/*
	p(t) = A + t*B
*/

#include "../Vec3/Vec3.hpp"

template<class TYPE>
class Ray
{
	Vec3<TYPE> A, B;
	public:
		Ray(){}
		Ray(const Vec3<TYPE> &a, const Vec3<TYPE> &b) : A(a), B(b) {}
		~Ray(){}

		Vec3<TYPE> Origin() const { return A; }
		Vec3<TYPE> Direction() const { return B; }
		Vec3<TYPE> PointAtParameter(const float &t) const { return A + t*B; }
};

#endif
