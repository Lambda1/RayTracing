#ifndef __IMAGER_PPM_HPP__
#define __IMAGER_PPM_HPP__

#include <iostream>
#include <string>

template<class TYPE>
class ImagerPPM
{
	// Image Setting
	using TYPE_OUT = unsigned int;
	static inline constexpr unsigned int MAX_COLOR_VALUE = 255;
	static inline constexpr float BIAS = 255.99;
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
			for (int i = 0;i < m_height;++i)
			{
				for (int j = 0;j < m_width;++j)
				{
					TYPE r = static_cast<TYPE>(j)/m_width;
					TYPE g = static_cast<TYPE>(i)/m_height;
					TYPE b = static_cast<TYPE>(0.2f);
					std::cout << static_cast<TYPE_OUT>(r*BIAS) << " " << static_cast<TYPE_OUT>(g*BIAS) << " " << static_cast<TYPE_OUT>(b*BIAS) << std::endl;
				}
			}
		}
};

#endif
