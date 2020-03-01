#include "./ImagerPPM/ImagerPPM.hpp"
#include "./Vec3/Vec3.hpp"
#include "./Ray/Ray.hpp"
#include "./Sphere/Sphere.hpp"
#include "./Hittable/HittableList.hpp"
#include "./Random/Random.hpp"
#include "./Camera/Camera.hpp"
#include "./Material/Lambertian.hpp"
#include "./Material/Metal.hpp"
#include "./Material/Dielectric.hpp"

#include <cfloat>

using type = float;
constexpr type MAX_TYPE = FLT_MAX;

Vec3<type> reflect(const Vec3<type> &v, const Vec3<type> &n)
{
	return v - 2.0f * MyVec::Dot(v, n) * n;
}

Vec3<type> color(const Ray<type> &r,const Hittable<type> &world, const int &depth)
{
	HitRecord<type> rec;
	// Shadow Acne対策
	if (world.Hit(r, 0.001f, MAX_TYPE, rec))
	{
		Ray<type> scattered;
		Vec3<type> attenuation;
		if (depth < 50.0f && rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth+1.0f);
		}
		else
		{
			return Vec3(0.0f, 0.0f, 0.0f); 
		}
	}
	const Vec3<type> unit_direction = MyVec::UnitVector(r.Direction());
	type t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f-t)*Vec3<type>(1.0f, 1.0f, 1.0f) + t*Vec3<type>(0.5f, 0.7f, 1.0f);
}

void RandomScene(HittableList<TYPE> &object_list)
{
	const int n = 500;
	object_list.GetList().push_back(std::unique_ptr<Sphere<type>>(new Sphere<type>(Vec3<type>(0.0f, -1000.0f, 0.0f), 1000.0f, new Lambertian(Vec3<type>(0.5f, 0.5f, 0.5f)))));
	int i = i;

	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11;b < 11; ++b)
		{
			TYPE choose_mat = MyRand::Random<TYPE>();
			Vec3<TYPE> center(a+0.9f*MyRand::Random<TYPE>(), 0.2f, b+0.9f*MyRand::Random<TYPE>());
			if ((center-Vec3<TYPE>(4.0f, 0.2f, 0.0f)).Length() > 0.9f)
			{
				// diffuse
				if (choose_mat < 0.8f)
				{
					object_list.GetList().push_back(std::unique_ptr<Sphere<type>>(new Sphere<type>(center, 0.2f, new Lambertian(Vec3<type>(MyRand::Random<TYPE>(),MyRand::Random<TYPE>(),MyRand::Random<TYPE>())))));
				}
				// metal
				else if(choose_mat < 0.95f)
				{
					object_list.GetList().push_back(std::unique_ptr<Sphere<type>>(new Sphere<type>(center, 0.2f, new Metal(Vec3<type>(0.5f*(1.0f+MyRand::Random<TYPE>()),0.50f*(1.0f+MyRand::Random<TYPE>()),0.50f*(1.0f+MyRand::Random<TYPE>())),0.50f*MyRand::Random<TYPE>()))));
				}
				// glass
				else
				{
					object_list.GetList().push_back(std::unique_ptr<Sphere<type>>(new Sphere<type>(center, 0.2f, new Dielectric(1.5f))));
				}
				object_list.GetList().push_back(std::unique_ptr<Sphere<type>>(new Sphere<type>(Vec3<TYPE>(0.0f, 1.0f, 0.0f), 1.0f, new Dielectric(1.5f))));
				object_list.GetList().push_back(std::unique_ptr<Sphere<type>>(new Sphere<type>(Vec3<TYPE>(-4.0f, 1.0f, 0.0f), 1.0f, new Lambertian(Vec3<TYPE>(0.4f,0.2f,0.1f)))));
				object_list.GetList().push_back(std::unique_ptr<Sphere<type>>(new Sphere<type>(Vec3<TYPE>(4.0f, 1.0f, 0.0f), 1.0f, new Lambertian(Vec3<TYPE>(0.7f,0.6f,0.5f)))));
			}
		}
	}
}

int main(int argc, char *argv[])
{
	// Def
	constexpr TYPE MY_PI = 3.14159265f;
	// Image
	const unsigned int width = 1200, height = 800, iteration = 100;
	ImagerPPM<type> imager(width, height, "P3");
	// Camera
	Vec3<TYPE> lookfrom(15.0f, 2.0f, 5.0f);
	Vec3<TYPE> lookat(0.0f, 0.0f, 0.0f);
	TYPE dist_to_focus = 10.0f;
	TYPE aperture = 0.1f;
	Camera camera(lookfrom, lookat, Vec3<TYPE>(0.0f, 1.0f, 0.0f) , 20.0f, static_cast<TYPE>(width)/static_cast<TYPE>(height), aperture, dist_to_focus);
	TYPE R = std::cos(MY_PI/4.0f);
	// Object
	HittableList<type> object_list;
	RandomScene(object_list);

	// Calc
	for (int i = height-1;i >= 0;--i)
	{
		for (int j = 0;j < width;++j)
		{
			// Antialiasing
			Vec3<type> col(0.0f, 0.0f, 0.0f);
			for (int k = 0;k < iteration;++k)
			{
				type u = static_cast<type>(j + MyRand::Random<type>()) / static_cast<type>(width);
				type v = static_cast<type>(i + MyRand::Random<type>()) / static_cast<type>(height);
				Ray<type> r = camera.GetRay(u, v);
				col += color(r, object_list, 0.0f);
			}
			col /= static_cast<type>(iteration);
			// gamma補正(gamma-2)
			col = Vec3<type>(std::sqrt(col[0]), std::sqrt(col[1]), std::sqrt(col[2]));
			imager.Set(i, j, col);
		}
	}

	// Output Image
	imager.OutputHeader();
	imager.OutputImageReverse();


	return 0;
}
