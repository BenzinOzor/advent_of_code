#pragma once

#include <stdint.h>
#include <stdarg.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


inline std::string sprintf( const char* pFormat, ... )
{
	std::string sOut;
	va_list oArgs;
	va_start( oArgs, pFormat );
	int iLen;
	static char sTmp[ 16384 ];

	iLen = _vsnprintf_s( sTmp, 16384, pFormat, oArgs );

	sOut.assign( sTmp, iLen );

	return sOut;
}

class base_day
{
public:
	base_day(uint32_t _year, uint32_t _day) :
		m_year(_year),
		m_day(_day)
	{}

	virtual void step_01() { printf( "YEAR: %u\nDAY: %02u\nSTEP: 01\n\n", m_year, m_day ); }
	virtual void step_02() { printf( "\nYEAR: %u\nDAY: %02u\nSTEP: 02\n\n", m_year, m_day ); }

protected:
	enum class FileType
	{
		PuzzleInput,
		Example01,
		Example02,
		COUNT
	};
	
	std::string get_file_path( FileType _file_type )
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

	std::ifstream _open_input_file( FileType _file_type )
	{
		auto inputFile = std::ifstream( get_file_path( _file_type ) );
	}

private:
	uint32_t m_year;
	uint32_t m_day;
};
