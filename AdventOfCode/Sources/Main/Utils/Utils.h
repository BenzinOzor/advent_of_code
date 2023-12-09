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

std::string					sprintf( const char* pFormat, ... );
std::ifstream				open_input_file( uint32_t _year, uint32_t _day, FileType _file_type );
void						parse_input( uint32_t _year, uint32_t _day, FileType _file_type, std::function<void(std::string)> _day_function );
bool						is_number( const std::string& _string );
std::vector< std::string >	split( const std::string& _line, char _delimiter );
std::vector< int >			extract_numbers( const std::string _line, char _delimiter );
std::vector< std::string >	extract_words( const std::string& _line, char _delimiter );
