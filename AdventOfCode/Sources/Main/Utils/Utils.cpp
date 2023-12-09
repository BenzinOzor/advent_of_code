#include <sstream>

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

std::string sprintf( const char* pFormat, ... )
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

std::ifstream open_input_file( uint32_t _year, uint32_t _day, FileType _file_type )
{
	return std::ifstream( get_file_path( _year, _day, _file_type ) );
}

void parse_input( uint32_t _year, uint32_t _day, FileType _file_type, std::function<void( std::string )> _day_function )
{
	auto inputFile = open_input_file( _year, _day, _file_type );

	if( inputFile.is_open() == false )
		return;

	auto line = std::string{};

	while( std::getline( inputFile, line ) )
		_day_function( line );
}

bool is_number( const std::string& _string )
{
	return _string.empty() == false && std::ranges::find_if_not( _string, []( unsigned char _char ){ return std::isdigit( _char ); } ) == _string.end();
}

std::vector< std::string > split( const std::string& _line, char _delimiter )
{
	auto line_stream = std::stringstream( _line );
	auto item = std::string{};
	auto items = std::vector< std::string >{};

	while( std::getline( line_stream, item, _delimiter ) )
		items.push_back( item );

	return items;
}

std::vector< int > extract_numbers( const std::string _line, char _delimiter )
{
	auto line_stream = std::stringstream( _line );
	auto item = std::string{};
	auto items = std::vector< int >{};

	while( std::getline( line_stream, item, _delimiter ) )
	{
		if( item.empty() || is_number( item ) == false )
			continue;

		items.push_back( std::stoi( item ) );
	}

	return items;
}

std::vector< std::string > extract_words( const std::string& _line, char _delimiter )
{
	auto line_stream = std::stringstream( _line );
	auto item = std::string{};
	auto items = std::vector< std::string >{};

	while( std::getline( line_stream, item, _delimiter ) )
	{
		if( item.empty() || is_number( item ) )
			continue;
		
		items.push_back( item );
	}

	return items;
}

