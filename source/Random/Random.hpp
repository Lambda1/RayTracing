#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

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
};

#endif
