#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include "../Ray/Ray.hpp"

using TYPE = float;

class Material
{
	public:
		virtual ~Material(){}
		virtual bool Scatter(const Ray<TYPE> &r_in, const HitRecord &rec, Vec3<TYPE> &attenuation, Ray<TYPE> &scattered) const = 0;
};

#endif
