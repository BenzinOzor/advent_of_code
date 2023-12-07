#include <fstream>

#include <Main/includes.h>

#include "01.h"


namespace y_2023
{
	int get_number_in_string( const std::string& _string )
	{
		auto string_number = std::string{ "" };
		auto last_character{ '\0' };

		LOG_NEW_LINE();
		LOG( "input string: %s", _string.c_str() );

		for( const char character : _string )
		{
			auto number = atoi( &character );

			if( number == 0 )
				continue;

			LOG( " - number found: %d", number );

			if( string_number.empty() )
				string_number += character;
			
			last_character = character;
		}

		string_number += last_character;

		return atoi( string_number.c_str() );
	}

	int get_number_in_string_02( const std::string& _string )
	{
		auto string_number = std::string{ "" };
		auto last_character{ '\0' };

		LOG_NEW_LINE();
		LOG( "input string: %s", _string.c_str() );

		for( const char character : _string )
		{
			auto number = atoi( &character );

			if( number == 0 )
				continue;

			LOG( " - number found: %d", number );

			if( string_number.empty() )
				string_number += character;

			last_character = character;
		}

		string_number += last_character;

		return atoi( string_number.c_str() );
	}

	void Day_01::step_01()
	{
		BaseDay::step_01();

		auto inputFile = _open_input_file( FileType::PuzzleInput );

		if( inputFile.is_open() == false )
			return;

		char test[256]{};
		auto reading{ true };
		auto final_number{ 0 };

		while( reading )
		{
			inputFile.getline( test, sizeof( test ) );

			auto number = get_number_in_string( test );

			if( number > 0 )
			{
				final_number += number;

				LOG( "new number: %d", number );
				LOG( "current sum: %d", final_number );
			}
			else
				reading = false;
		}
	}

	void Day_01::step_02()
	{
		BaseDay::step_02();

		auto inputFile = _open_input_file( FileType::PuzzleInput );

		if( inputFile.is_open() == false )
			return;

		char test[256]{};
		auto reading{ true };
		auto final_number{ 0 };

		while( reading )
		{
			inputFile.getline( test, sizeof( test ) );

			auto number = get_number_in_string_02( test );

			if( number > 0 )
			{
				final_number += number;

				LOG( "new number: %d", number );
				LOG( "current sum: %d", final_number );
			}
			else
				reading = false;
		}
	}
};
