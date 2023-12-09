#include <Main/Utils/Utils.h>

namespace y_2023
{
	namespace d_09
	{
		using Values = std::vector< int >;
		auto g_OASIS_report = std::vector< Values >{};
		auto g_total_value{ 0 };
		auto g_last_value{ 0 };

		void fill_differences( uint32_t _line_to_process )
		{
			if( _line_to_process >= g_OASIS_report.size() || g_OASIS_report[ _line_to_process ].size() < 1 )
				return;

			g_OASIS_report.push_back( Values{} );

			auto& values = g_OASIS_report[ _line_to_process ];
			auto& differences = g_OASIS_report.back();

			for( auto value_index{ 1 }; value_index < values.size(); ++value_index )
			{
				differences.push_back( values[ value_index ] - values[ value_index - 1 ] );
			}

			auto value_to_check = differences.front();

			if( std::ranges::find_if_not( differences, [value_to_check]( int i ) { return i == value_to_check; } ) != differences.end() )
				fill_differences( _line_to_process + 1 );
		}

		void determine_new_value( uint32_t _line_to_process )
		{
			if( _line_to_process >= g_OASIS_report.size() || g_OASIS_report[ _line_to_process ].size() < 1 )
				return;

			auto& values = g_OASIS_report[ _line_to_process ];

			// We're on the last line, we only have to copy the previous value
			if( _line_to_process == g_OASIS_report.size() - 1 )
				values.push_back( values.back() );
			else
			{
				auto& previous_values = g_OASIS_report[ _line_to_process + 1 ];
				values.push_back( values.back() + previous_values.back() );
			}

			if( _line_to_process > 0 )
				determine_new_value( _line_to_process - 1 );
			else
			{
				g_last_value = values.back();
				g_total_value += g_last_value;
			}
		}

		void fill_base_values( std::string _line )
		{
			auto space_index = _line.find_first_of( " " );
			g_OASIS_report.push_back( Values{} );

			while( space_index != std::string::npos )
			{
				g_OASIS_report[ 0 ].push_back( std::stoi( _line.substr( 0, space_index ) ) );
				_line = _line.substr( space_index + 1 );
				space_index = _line.find_first_of( " " );
			}

			g_OASIS_report[ 0 ].push_back( std::stoi( _line ) );
		}

		void print_OASIS_report()
		{
			auto line_values = std::string{};

			for( auto values : g_OASIS_report )
			{
				line_values.clear();
				for( auto value : values )
				{
					line_values += sprintf( "%d ", value );
				}

				LOG( line_values.c_str() );
			}

			LOG_PRIO( LogColor::green, "Last value: %d // Total: %d", g_last_value, g_total_value );
			LOG_NEW_LINE();
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void part_01( const std::string& _line )
		{
			g_OASIS_report.clear();
			fill_base_values( _line );
			fill_differences( 0 );
			determine_new_value( static_cast< uint32_t >( g_OASIS_report.size() - 1 ) );

			print_OASIS_report();
		}

		void part_02( const std::string& _line )
		{
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void day_09( const std::string& _title )
	{
		auto year{ 2023 };
		auto day{ 9 };

		LOG_PRIO( LogColor::red, "%d - Day %02d - %s\n", year, day, _title.c_str() );
		LOG_PRIO( LogColor::yellow, "Part 1" );

		d_09::g_total_value = 0;
		parse_input( year, day, FileType::PuzzleInput, d_09::part_01 );

		LOG_NEW_LINE();
		LOG_PRIO( LogColor::yellow, "Part 2" );

		d_09::g_total_value = 0;
		parse_input( year, day, FileType::Example02, d_09::part_02 );
	}
}