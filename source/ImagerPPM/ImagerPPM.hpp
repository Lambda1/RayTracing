#ifndef __IMAGER_PPM_HPP__
#define __IMAGER_PPM_HPP__

#include <iostream>
#include <string>

template<class TYPE>
class ImagerPPM
{
	// Image Setting
	static inline constexpr unsigned int MAX_COLOR_VALUE = 255;
	const unsigned int m_width, m_height;
	const std::string m_format;
	public:
		ImagerPPM():
			m_width(200), m_height(100), m_format("P3")
		{
		}
		ImagerPPM(const unsigned int &width, const unsigned int &height, const std::string &format):
			m_width(width), m_height(height), m_format(format)
		{
		}
		~ImagerPPM()
		{
		}
		void OutputTest()
		{
			std::cout << m_format << std::endl;
			std::cout << m_width << " " << m_height << std::endl;
			std::cout << MAX_COLOR_VALUE << std::endl;
		}
};

#endif
