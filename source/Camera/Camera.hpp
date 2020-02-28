#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "../Ray/Ray.hpp"

using TYPE = float;

class Camera
{
	const Vec3<TYPE> m_lower_left_corner, m_horizontal, m_vertical, m_origin;
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
	~Camera()
	{
	}

	// Function
	inline Ray<TYPE> GetRay(const TYPE &u, const TYPE &v)
	{
		return Ray<TYPE>(m_origin, m_lower_left_corner+u*m_horizontal + v*m_vertical - m_origin);
	}
};

#endif
