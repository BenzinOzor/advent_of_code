#include <fstream>

#include <Main/includes.h>

#include "01.h"


namespace y_2023
{
	int get_number_in_string( const std::string& _string )
	{
		auto string_number = std::string{ "" };
		auto last_character{ '\0' };

		printf( "\ninput string: %s\n", _string.c_str() );

		for( const char character : _string )
		{
			auto number = atoi( &character );

			if( number == 0 )
				continue;

			printf( " - number found: %d\n", number );

			if( string_number.empty() )
				string_number += character;
			
			last_character = character;
		}

		string_number += last_character;

		return atoi( string_number.c_str() );
	}

	void day_01::step_01()
	{
		base_day::step_01();

		auto inputFile = std::ifstream( get_file_path( FileType::PuzzleInput ) );

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

				printf( "new number: %d\n", number );
				printf( "current sum: %d\n", final_number );
			}
			else
				reading = false;
		}
	}

	void day_01::step_02()
	{
		base_day::step_02();
	}
};
