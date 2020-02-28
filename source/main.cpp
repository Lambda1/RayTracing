#include "./ImagerPPM/ImagerPPM.hpp"
#include "./Vec3/Vec3.hpp"
#include "./Ray/Ray.hpp"
#include "./Sphere/Sphere.hpp"
#include "./Hittable/HittableList.hpp"
#include "./Random/Random.hpp"

#include <cfloat>

using type = float;
constexpr type MAX_TYPE = FLT_MAX;

Vec3<type> color(const Ray<type> &r,const Hittable<type> &world)
{
	HitRecord<type> rec;
	if (world.Hit(r, 0.0f, MAX_TYPE, rec))
	{
		return 0.5f * Vec3<type>(rec.normal.x()+1.0f, rec.normal.y()+1.0f, rec.normal.z()+1.0f);
	}
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
	// Object
	HittableList<type> object_list;
	object_list.GetList().push_back(std::unique_ptr<Sphere<type>>(new Sphere<type>(Vec3<type>(0.0f, 0.0f, -1.0f), 0.5f)));
	object_list.GetList().push_back(std::unique_ptr<Sphere<type>>(new Sphere<type>(Vec3<type>(0.0f, -100.5f, -1.0f), 100.0f)));

	// Calc
	for (int i = height-1;i >= 0;--i)
	{
		for (int j = 0;j < width;++j)
		{
			type u = static_cast<type>(j) / static_cast<type>(width);
			type v = static_cast<type>(i) / static_cast<type>(height);
			Ray<type> r(origin, lower_left_corner + u*horizontal + v*vertical);
			
			Vec3<type> p = r.PointAtParameter(2.0f);

			imager.Set(i,j,color(r, object_list));
		}
	}

	// Output Image
	imager.OutputHeader();
	imager.OutputImageReverse();

	return 0;
}
