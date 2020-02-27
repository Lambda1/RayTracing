#include "./ImagerPPM/ImagerPPM.hpp"
#include "./Vec3/Vec3.hpp"

using type = float;

int main(int argc, char *argv[])
{
	ImagerPPM<type> imager;
	Vec3<type> v3(1,2,3);

	imager.OutputTest();

	return 0;
}
