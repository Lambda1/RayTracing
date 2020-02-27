#ifndef __RAY_HPP__
#define __RAY_HPP__

/*
	p(t) = A + t*B
*/

#include "../Vec3/Vec3.hpp"

template<class TYPE>
class Ray
{
	Vec3 A, B;
	public:
		Ray(){}
		Ray(const Vec3 &a, const Vec3 &b) : A(a), B(b) {}
		~Ray(){}

		Vec3 Origin() const { return A; }
		Vec3 Direction() const { return B; }
		Vec3 PointAtParameter(const float &t) const { return A + t*B; }
};

#endif
