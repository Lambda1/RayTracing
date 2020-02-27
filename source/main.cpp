#include "./ImagerPPM/ImagerPPM.hpp"
#include "./Vec3/Vec3.hpp"
#include "./Ray/Ray.hpp"

using type = float;

/*
	判別式で球の交点を調べる(球の当たり判定).
	NOTE: 0(なし), 1(接点), 2(貫通)
	NOTE: 最小のtを返す.(手前にあるから)
ray: p(t) = A + t*B
center: C = (Cx,Cy,Cz)
sphere: (x-Cx)^2 + (y-Cy)^2 + (z-Cz)^2 = R^2
	-> dot((p(t)-C),(p(t)-C)) = R^2
	-> t^2*dot(B,B) + 2t*dot(B,A-C) + dot(A-C,A-C) - R^2 = 0
	-> t^2*a + 2t*b + c - R^2 = 0
	-> t^2*(a) + t*(2b) + (c-R^2) = 0
*/
type hit_sphere(const Vec3<type> &center, const float &radius, const Ray<type> &r)
{
	Vec3<type> oc = r.Origin() - center;
	const type a = MyVec::Dot<type>(r.Direction(), r.Direction());
	const type b = 2.0f * MyVec::Dot<type>(oc, r.Direction());
	const type c = MyVec::Dot<type>(oc, oc) - radius*radius;
	const type discriminant = b*b - 4.0f*a*c;

	// 解なし
	if (discriminant < 0) { return -1.0f; }
	// 接点 or 貫通
	else { return (-b - std::sqrt(discriminant)) / (2.0f*a); }
}

Vec3<type> color(const Ray<type> &r)
{
	// 中心(0,0,-1), 半径0.5の球体に光線が当たる時, 赤色を返却
	type t = hit_sphere(Vec3<type>(0.0f, 0.0f, -1.0f), 0.5f, r);
	// 法線計算(正規化)
	if (t > 0.0f)
	{
		Vec3<type> N = MyVec::UnitVector(r.PointAtParameter(t) - Vec3<type>(0.0f, 0.0f, -1.0f));
		return 0.5f * Vec3<type>(N.x()+1.0f, N.y()+1.0f, N.z()+1.0f);
	}

	const Vec3<type> unit_direction = MyVec::UnitVector(r.Direction());
	t = 0.5f * (unit_direction.y() + 1.0f);
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
