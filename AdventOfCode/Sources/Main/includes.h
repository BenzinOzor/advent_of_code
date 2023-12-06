#pragma once

#include <stdint.h>
#include <string>

class base_day
{
public:
	base_day(uint32_t _year, uint32_t _day) :
		m_year(_year),
		m_day(_day)
	{}

	virtual void step_01() { printf( "YEAR: %u\nDAY: %02u\nSTEP: 01\n\n", m_year, m_day ); }
	virtual void step_02() { printf( "YEAR: %u\nDAY: %02u\nSTEP: 02\n\n", m_year, m_day ); }

private:
	uint32_t m_year;
	uint32_t m_day;
};
