#pragma once

#include <Main/includes.h>


namespace y_2023
{
	class Day_01 : public BaseDay
	{
	public:
		struct NumberStr
		{
			std::string m_str{ "" };
			uint32_t	m_value{ 0 };
		};

		Day_01() : BaseDay( 2023, 01 ) {}

		void step_01();
		void step_02();
	};
};
