#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

#include "../Vec3/Vec3.hpp"

#include <functional>
#include <random>

namespace MyRand
{
	template<class T> T Random()
	{
		static std::uniform_real_distribution<T> distribution(static_cast<T>(0.0), static_cast<T>(1.0));
		static std::mt19937 generator;
		static std::function<T()> rand_generator = std::bind(distribution, generator);
		return rand_generator();
	}
	template<class T> Vec3<T> RandomInUnitSphere()
	{
		Vec3<T> p;
		do
		{
			p = 2.0f * Vec3<T>(MyRand::Random<T>(), MyRand::Random<T>(), MyRand::Random<T>()) - Vec3<T>(1.0f, 1.0f, 1.0f);
		}while(p.SquaredLength() >= 1.0f);
		return p;
	}

};

#endif
