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

	/*
	 * 判別式で球の交点を調べる(球の当たり判定).
	 * NOTE: 0(なし), 1(接点), 2(貫通)
	 * NOTE: 最小のtを返す.(手前にあるから)

	 * ray: p(t) = A + t*B
	 * center: C = (Cx,Cy,Cz)
	 * sphere: (x-Cx)^2 + (y-Cy)^2 + (z-Cz)^2 = R^2
	 * -> dot((p(t)-C),(p(t)-C)) = R^2
	 * -> t^2*dot(B,B) + 2t*dot(B,A-C) + dot(A-C,A-C) - R^2 = 0
	 * -> t^2*a + 2t*b + c - R^2 = 0
	 * -> t^2*(a) + t*(2b) + (c-R^2) = 0
	 */
	bool Hit(const Ray<TYPE> &r, const TYPE &t_min, const TYPE &t_max, HitRecord<TYPE> &rec) const override
	{
		Vec3<TYPE> oc = r.Origin() - m_center;
		const TYPE a = MyVec::Dot<TYPE>(r.Direction(), r.Direction());
		const TYPE b = MyVec::Dot<TYPE>(oc, r.Direction());
		const TYPE c = MyVec::Dot<TYPE>(oc, oc) - m_radius*m_radius;
		const TYPE discriminant = b*b - a*c;

		// 接点 or 貫通
		if (discriminant > 0)
		{
			// 解の公式(偶数版)
			TYPE solution = (-b - std::sqrt(discriminant))/a;
			// 最小解が範囲内(tmin < t < tmax)
			if (solution < t_max && solution > t_min)
			{
				rec.t = solution;
				rec.p = r.PointAtParameter(rec.t);
				rec.normal = (rec.p - m_center) / m_radius;
				return true;
			}
			// もう一つ解を調査(tmin < t < tmax)
			solution = (-b + std::sqrt(discriminant))/a;
			if (solution < t_max && solution > t_min)
			{
				rec.t = solution;
				rec.p = r.PointAtParameter(rec.t);
				rec.normal = (rec.p - m_center) / m_radius;
				return true;
			}
		}
		// 解なし
		return false;
	}

};

#endif
