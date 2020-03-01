#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "../Ray/Ray.hpp"

using TYPE = float;

class Camera
{
	Vec3<TYPE> m_lower_left_corner, m_horizontal, m_vertical, m_origin;
	static inline constexpr TYPE MY_PI = 3.14159265f;
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
	Camera(const Vec3<TYPE> &lookfrom, const Vec3<TYPE> &lookat, const Vec3<TYPE> vup, const TYPE &v_fov,const TYPE &aspect)
	{
		Vec3<TYPE> u, v, w;
		
		TYPE theta = v_fov * MY_PI/180.0f;
		// h = tan(theta/2)
		TYPE half_height = std::tan(theta/2.0f);
		TYPE half_width = aspect * half_height;
		
		m_origin = lookfrom;
		w = MyVec::UnitVector(lookfrom - lookat);
		u = MyVec::UnitVector(MyVec::Cross(vup, w));
		v = MyVec::Cross(w, u);

		m_lower_left_corner = m_origin - half_width*u - half_height*v - w;
		m_horizontal = 2.0f * half_width * u;
		m_vertical = 2.0f * half_height * v;
	}
	~Camera()
	{
	}

	// Function
	inline Ray<TYPE> GetRay(const TYPE &u, const TYPE &v)
	{
		return Ray<TYPE>(m_origin, m_lower_left_corner+u*m_horizontal + v*m_vertical - m_origin);
	}

	// Getter
};

#endif
