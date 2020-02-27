#ifndef __HITTABLE_HPP__
#define __HITTABLE_HPP__

#include "../Ray/Ray.hpp"

template<class TYPE>
struct HitRecord
{
	TYPE t;
	Vec3<TYPE> p;
	Vec3<TYPE> normal;
};

template<class TYPE>
class Hittable
{
	public:
		virtual bool Hit(const Ray<TYPE> &r, const TYPE &t_min, const float &t_max, HitRecord<TYPE> &rec) const = 0;
};

#endif
