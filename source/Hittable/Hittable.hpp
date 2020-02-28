#ifndef __HITTABLE_HPP__
#define __HITTABLE_HPP__

#include "../Ray/Ray.hpp"

class Material;

template<class TYPE>
struct HitRecord
{
	TYPE t;
	Vec3<TYPE> p;
	Vec3<TYPE> normal;
	Material *mat_ptr;
};

template<class TYPE>
class Hittable
{
	public:
		virtual ~Hittable(){}
		virtual bool Hit(const Ray<TYPE> &r, const TYPE &t_min, const float &t_max, HitRecord<TYPE> &rec) const = 0;
};

#endif
