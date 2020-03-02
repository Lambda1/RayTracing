#ifndef __DIELECTRIC_HPP__
#define __DIELECTRIC_HPP__

#include "../Hittable/Hittable.hpp"
#include "../Random/Random.hpp"
#include "./Material.hpp"

using TYPE = float;

class Dielectric : public Material
{
	// 屈折率
	TYPE m_ref_idx;

	inline Vec3<TYPE> Reflect(const Vec3<TYPE> &v, const Vec3<TYPE> &n) const { return v - 2.0f * MyVec::Dot(v,n) * n; }
	/*
	 *	スネルの法則
	 *	 -> cos1 = dot(-v, n) = -dot(v,n)
	 *	 -> cos2 = sqrt(1.0-(ni/nt)^2 * (1.0-cos1^2)) = sqrt(1.0 - ni_over_nt^2 * (1.0 - dt^2))
	 *	 -> f = (ni/nt)(uv-cos1*n) - n*sqrt(1-(ni/nt)^2 * (1-cos1^2))
	 */
	inline bool Refract(const Vec3<TYPE> &v, const Vec3<TYPE> &n, const TYPE &ni_over_nt, Vec3<TYPE> &refracted) const
	{
		Vec3<TYPE> uv = MyVec::UnitVector(v);
		TYPE dt = MyVec::Dot(uv, n);
		TYPE discriminant = 1.0f - ni_over_nt*ni_over_nt*(1.0f - dt*dt);
		if (discriminant > 0.0f)
		{
			refracted = ni_over_nt*(uv-n*dt) - n*std::sqrt(discriminant);
			return true;
		}
		return false;
	}
	/*
	 *	Schlickの近似式(フレネル反射)
	 */
	inline TYPE Schlick(const TYPE &cosine, const TYPE &ref_idx) const
	{
		TYPE r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
		r0 = r0 * r0;
		return r0 + (1.0f - r0)*std::pow((1.0f - cosine), 5.0f);
	}
	public:
	Dielectric(): m_ref_idx() {} 
	Dielectric(const TYPE &ri): m_ref_idx(ri) {}
	virtual bool Scatter(const Ray<TYPE> &r_in, const HitRecord<TYPE> &rec, Vec3<TYPE> &attenuation, Ray<TYPE> &scattered) const
	{
		Vec3<TYPE> outward_normal;
		Vec3<TYPE> reflected = Reflect(r_in.Direction(), rec.normal);
		TYPE ni_over_nt;
		// 減衰率
		// NOTE: ガラス表面は何も吸収しない
		attenuation = Vec3<TYPE>(1.0f, 1.0f, 1.0f);
		Vec3<TYPE> refracted;

		TYPE reflect_prob;
		TYPE cosine;

		// 入射光と衝突面法線の内積が0より大きい -> 空気から物体
		if (MyVec::Dot(r_in.Direction(), rec.normal) > 0.0f)
		{
			outward_normal = -rec.normal;
			ni_over_nt = m_ref_idx;
			cosine = m_ref_idx * MyVec::Dot(r_in.Direction(), rec.normal) / r_in.Direction().Length();
		}
		// 入射光と衝突面法線の内積が0以下 -> 物体から空気
		else
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0f / m_ref_idx;
			cosine = -MyVec::Dot(r_in.Direction(), rec.normal) / r_in.Direction().Length();
		}

		if (Refract(r_in.Direction(), outward_normal, ni_over_nt, refracted)){ reflect_prob = Schlick(cosine, m_ref_idx); }
		else{ reflect_prob = 1.0f; }

		if (MyRand::Random<TYPE>() < reflect_prob) { scattered = Ray<TYPE>(rec.p, reflected); }
		else { scattered = Ray<TYPE>(rec.p, refracted); }
		return true;
	}
};

#endif
