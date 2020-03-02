#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "../Random/Random.hpp"
#include "../Ray/Ray.hpp"

using TYPE = float;

class Camera
{
	Vec3<TYPE> m_lower_left_corner, m_horizontal, m_vertical, m_origin;
	Vec3<TYPE> m_u, m_v, m_w;
	TYPE m_lens_radius;
	static inline constexpr TYPE MY_PI = 3.14159265f;
	Vec3<TYPE> RandomInUnitDisk()
	{
		Vec3<TYPE> p;
		do
		{
			p = 2.0f * Vec3<TYPE>(MyRand::Random<TYPE>(), MyRand::Random<TYPE>(), 0.0f) - Vec3<TYPE>(1.0f, 1.0f, 0.0f);
		}while(MyVec::Dot(p,p) >= 1.0f);
		return p;
	}
	public:
	Camera():
		m_lower_left_corner(-2.0f, -1.0f, -1.0f),
		m_horizontal(4.0f, 0.0f, 0.0f), m_vertical(0.0f, 2.0f, 0.0f),
		m_origin(0.0f, 0.0f, 0.0f)
	{
	}
	Camera(const Vec3<TYPE> &origin,const Vec3<TYPE> &lower_left_corner, const Vec3<TYPE> &horizontal, const Vec3<TYPE> &vertical):
		m_lower_left_corner(lower_left_corner), m_horizontal(horizontal), m_vertical(vertical), m_origin(origin)
	{
	}
	// vfov is top to bottom in degrees.
	Camera(const Vec3<TYPE> &lookfrom, const Vec3<TYPE> &lookat, const Vec3<TYPE> vup, const TYPE &v_fov,const TYPE &aspect,const TYPE &aperture, const TYPE &focus_dist)
	{
		m_lens_radius = aperture / 2.0f;
		
		TYPE theta = v_fov * MY_PI/180.0f;
		// h = tan(theta/2)
		TYPE half_height = std::tan(theta/2.0f);
		TYPE half_width = aspect * half_height;
		
		m_origin = lookfrom;
		m_w = MyVec::UnitVector(lookfrom - lookat);
		m_u = MyVec::UnitVector(MyVec::Cross(vup, m_w));
		m_v = MyVec::Cross(m_w, m_u);

		m_lower_left_corner = m_origin - half_width*focus_dist*m_u - half_height*focus_dist*m_v - focus_dist*m_w;
		m_horizontal = 2.0f * half_width * focus_dist * m_u;
		m_vertical = 2.0f * half_height * focus_dist * m_v;
	}
	~Camera()
	{
	}

	// Function
	inline Ray<TYPE> GetRay(const TYPE &s, const TYPE &t)
	{
		Vec3<TYPE> rd = m_lens_radius * RandomInUnitDisk();
		Vec3<TYPE> offset = m_u * rd.x() + m_v * rd.y();
		return Ray<TYPE>(m_origin + offset, m_lower_left_corner+s*m_horizontal + t*m_vertical - m_origin - offset);
	}

	// Getter
};

#endif
