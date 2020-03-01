#ifndef __LAMBERTIAN_HPP__
#define __LAMBERTIAN_HPP__

#include "../Vec3/Vec3.hpp"
#include "../Random/Random.hpp"
#include "../Hittable/Hittable.hpp"
#include "./Material.hpp"

using TYPE = float;

class Lambertian : public Material
{
	Vec3<TYPE> m_albedo;
	public:
	Lambertian(): m_albedo(){}
	Lambertian(const Vec3<TYPE> &albedo): m_albedo(albedo){}
	~Lambertian(){}
	virtual bool Scatter(const Ray<TYPE> &r_in, const HitRecord<TYPE> &rec, Vec3<TYPE> &attenuation, Ray<TYPE> &scattered) const
	{
		Vec3<TYPE> target = (rec.p+rec.normal) + MyRand::RandomInUnitSphere<TYPE>();
		scattered = Ray<TYPE>(rec.p, target-rec.p);
		attenuation = m_albedo;
		return (MyVec::Dot(scattered.Direction(), rec.normal) > 0.0f);
	}
};

#endif
