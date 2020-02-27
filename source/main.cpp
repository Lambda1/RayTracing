#include "./ImagerPPM/ImagerPPM.hpp"
#include "./Vec3/Vec3.hpp"
#include "./Ray/Ray.hpp"

using type = float;

Vec3<type> color(const Ray<type> &r)
{
	const Vec3<type> unit_direction = MyVec::UnitVector(r.Direction());
	type t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f-t)*Vec3<type>(1.0f, 1.0f, 1.0f) + t*Vec3<type>(0.5f, 0.7f, 1.0f);
}

int main(int argc, char *argv[])
{
	// Image
	const unsigned int width = 200, height = 100;
	ImagerPPM<type> imager(width, height, "P3");
	// Camera
	Vec3<type> lower_left_corner(-2.0f, -1.0f, -1.0f);
	Vec3<type> horizontal(4.0f, 0.0f, 0.0f);
	Vec3<type> vertical(0.0f, 2.0f, 0.0f);
	Vec3<type> origin(0.0f, 0.0f, 0.0f);
	
	// Calc
	for (int i = height-1;i >= 0;--i)
	{
		for (int j = 0;j < width;++j)
		{
			type u = static_cast<type>(j) / static_cast<type>(width);
			type v = static_cast<type>(i) / static_cast<type>(height);
			Ray<type> r(origin, lower_left_corner + u*horizontal + v*vertical);
			imager.Set(i,j,color(r));
		}
	}

	// Output Image
	imager.OutputHeader();
	imager.OutputImageReverse();

	return 0;
}
