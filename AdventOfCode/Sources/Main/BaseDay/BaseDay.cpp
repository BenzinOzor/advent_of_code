#include <Main/includes.h>

#include "BaseDay.h"


void BaseDay::step_01()
{
	LOG_NEW_LINE();
	LOG_C( LogColor::yellow, "YEAR: %u", m_year );
	LOG_C( LogColor::yellow, "DAY: %02u", m_day );
	LOG_C( LogColor::yellow, "STEP: 01" );
	LOG_NEW_LINE();
}

void BaseDay::step_02()
{
	LOG_NEW_LINE();
	LOG_C( LogColor::yellow, "YEAR: %u", m_year );
	LOG_C( LogColor::yellow, "DAY: %02u", m_day );
	LOG_C( LogColor::yellow, "STEP: 02" );
	LOG_NEW_LINE();
}

std::string BaseDay::_get_file_path( FileType _file_type )
{
	std::string root = sprintf( "../../../AdventOfCode/Sources/%d/%02d/", m_year, m_day );

	switch( _file_type )
	{
		case FileType::PuzzleInput:
			return root + "input.txt";
		case FileType::Example01:
			return root + "example_input_01.txt";
		case FileType::Example02:
			return root + "example_input_02.txt";
	};

	return "";
}

std::ifstream BaseDay::_open_input_file( FileType _file_type )
{
	return std::ifstream( _get_file_path( _file_type ) );
}
