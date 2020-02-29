#ifndef __METAL_HPP__
#define __METAL_HPP__

#include "../Ray/Ray.hpp"
#include "../Hittable/Hittable.hpp"
#include "./Material.hpp"

using TYPE = float;

class Metal : public Material
{
	Vec3<TYPE> m_albedo;
	TYPE m_fuzz;
	/*
	 * 反射ベクトル: R = v+2*B
	 * B = -dot(v,n)*n : 正射影ベクトル
	 * R = v - 2 * dot(v,n)*n
	 */
	inline Vec3<TYPE> Reflect(const Vec3<TYPE> &v, const Vec3<TYPE> &n) const { return v - 2.0f * MyVec::Dot(v,n) * n; }

	public:
	Metal(): m_albedo() {}
	Metal(const Vec3<TYPE> &albedo,const TYPE &fuzz): m_albedo(albedo), m_fuzz(fuzz)
	{
		if (m_fuzz > 1.0f){ m_fuzz = 1.0f; }
	}
	~Metal(){}
	virtual bool Scatter(const Ray<TYPE> &r_in, const HitRecord<TYPE> &rec, Vec3<TYPE> &attenuation, Ray<TYPE> &scattered) const
	{
		Vec3<TYPE> reflected = Reflect(MyVec::UnitVector(r_in.Direction()), rec.normal);
		scattered = Ray<TYPE>(rec.p, reflected);
		attenuation = m_albedo;
		return (MyVec::Dot(scattered.Direction(), rec.normal) > 0.0f);
	}

};

#endif
