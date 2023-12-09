#include <fstream>

#include <Main/Utils/Utils.h>


namespace y_2023
{
	namespace d_01
	{
		struct NumberStr
		{
			std::string m_str{ "" };
			uint32_t	m_value{ 0 };
		};

		auto g_string_values = std::vector< NumberStr >{ { "0", 0 }, { "1", 1 }, { "2", 2 }, { "3", 3 }, { "4", 4 }, { "5", 5 }, { "6", 6 }, { "7", 7 }, { "8", 8 }, { "9", 9 },
															{ "zero", 0 }, { "one", 1 }, { "two", 2 }, { "three", 3 }, { "four", 4 }, { "five", 5 }, { "six", 6 }, { "seven", 7 }, { "eight", 8 }, { "nine", 9 } };

		int get_number_in_string( const std::string& _string )
		{
			auto first_number{ 0 };
			auto last_number{ 0 };

			LOG_NEW_LINE();
			LOG( "input string: %s", _string.c_str() );

			for( const char character : _string )
			{
				auto number = atoi( &character );

				if( number == 0 )
					continue;

				LOG( " - number found: %d", number );

				if( first_number <= 0 )
					first_number += number * 10;

				last_number = number;
			}

			return first_number + last_number;
		}

		int get_number_in_string_02( const std::string& _string )
		{
			auto first_number{ 0 };
			auto last_number{ 0 };

			LOG_NEW_LINE();
			LOG( "input string: %s", _string.c_str() );

			auto leftest_number = std::pair< uint32_t, uint32_t >{ UINT32_MAX, 0 };
			auto rightest_number = std::pair< uint32_t, uint32_t >{ 0, 0 };

			for( auto number_str : g_string_values )
			{
				auto ret_first = _string.find( number_str.m_str );
				auto ret_last = _string.rfind( number_str.m_str );

				if( ret_first != std::string::npos && ret_first < leftest_number.first )
				{
					leftest_number.first = static_cast<uint32_t>( ret_first );
					leftest_number.second = number_str.m_value;

					LOG( " - left number found: %u (%u)", number_str.m_value, ret_first );
				}

				if( ret_last != std::string::npos && ret_last >= rightest_number.first )
				{
					rightest_number.first = static_cast<uint32_t>( ret_last );
					rightest_number.second = number_str.m_value;

					LOG( " - right number found: %u (%u)", number_str.m_value, ret_last );
				}
			}

			return leftest_number.second * 10 + rightest_number.second;
		}


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void part_01()
		{
			auto inputFile = open_input_file( 2023, 01, FileType::PuzzleInput );

			if( inputFile.is_open() == false )
				return;

			auto final_number{ 0 };
			auto line = std::string{};

			while( std::getline( inputFile, line ) )
			{
				auto number = get_number_in_string( line );

				if( number > 0 )
				{
					final_number += number;

					LOG( "new number: %d", number );
					LOG( "current sum: %d", final_number );
				}
			}

			LOG_PRIO( LogColor::green, "Calibration value: %u", final_number );
		}

		void part_02()
		{
			auto inputFile = open_input_file( 2023, 01, FileType::PuzzleInput );

			if( inputFile.is_open() == false )
				return;

			auto final_number{ 0 };
			auto line = std::string{};

			while( std::getline( inputFile, line ) )
			{
				auto number = get_number_in_string_02( line );

				if( number > 0 )
				{
					final_number += number;

					LOG( "new number: %d", number );
					LOG( "current sum: %d", final_number );
				}
			}

			LOG_PRIO( LogColor::green, "Calibration value: %u", final_number );
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void day_01( const std::string& _title )
	{
		LOG_PRIO( LogColor::red, "2023 - Day 01 - %s\n", _title.c_str() );
		LOG_PRIO( LogColor::yellow, "Part 1" );

		d_01::part_01();

		LOG_NEW_LINE();
		LOG_PRIO( LogColor::yellow, "Part 2" );

		d_01::part_02();
	}
};
