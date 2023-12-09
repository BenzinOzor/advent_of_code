#include "Utils.h"

std::string get_file_path( uint32_t _year, uint32_t _day, FileType _file_type )
{
	std::string root = sprintf( "../../../AdventOfCode/Sources/%u/%02u/", _year, _day );

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

std::ifstream open_input_file( uint32_t _year, uint32_t _day, FileType _file_type )
{
	return std::ifstream( get_file_path( _year, _day, _file_type ) );
}

