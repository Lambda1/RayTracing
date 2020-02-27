#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "../Ray/Ray.hpp"
#include "../Hittable/Hittable.hpp"

template<class TYPE>
class Sphere : public Hittable<TYPE>
{
	Vec3<TYPE> m_center;
	TYPE m_radius;
	public:
		Sphere(): m_center(), m_radius(1.0f) {};
		Sphere(const Vec3<TYPE> &center, const TYPE &radius): m_center(center), m_radius(radius) {};
		~Sphere(){}
		bool Hit(const Ray<TYPE> &r, const TYPE &t_min, const float &t_max, HitRecord<TYPE> &rec) const override
		{
			return true;
		}

};

#endif
