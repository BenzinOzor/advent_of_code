#pragma once

#include <Main/includes.h>
#include <fstream>


enum class FileType
{
	PuzzleInput,
	Example01,
	Example02,
	COUNT
};

std::ifstream	open_input_file( uint32_t _year, uint32_t _day, FileType _file_type );
