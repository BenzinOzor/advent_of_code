#pragma once

#include <stdint.h>
#include <Main/Logger/Logger.h>

class BaseDay
{
public:
	BaseDay( uint32_t _year, uint32_t _day ) :
		m_year( _year ),
		m_day( _day )
	{}

	virtual void step_01();
	virtual void step_02();

protected:
	enum class FileType
	{
		PuzzleInput,
		Example01,
		Example02,
		COUNT
	};

	std::string		_get_file_path( FileType _file_type );
	std::ifstream	_open_input_file( FileType _file_type );

private:
	uint32_t m_year;
	uint32_t m_day;
};
