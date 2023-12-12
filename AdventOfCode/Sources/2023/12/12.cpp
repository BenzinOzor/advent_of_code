#include <Main/Utils/Utils.h>

namespace y_2023
{
	namespace d_12
	{
		struct PuzzleVariables
		{
			
		};
		auto g_pv = PuzzleVariables{};

		void parse_line( const std::string& _line )
		{
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void part_01( uint32_t _year, uint32_t _day )
		{
			g_pv = PuzzleVariables{};
			parse_input( _year, _day, FileType::PuzzleInput, parse_line );
			//LOG_PRIO( LogColor::green, "Total length: %llu", g_pv.m_total_length );
		}

		void part_02( uint32_t _year, uint32_t _day )
		{
			g_pv = PuzzleVariables{};
			parse_input( _year, _day, FileType::PuzzleInput, parse_line );
			//LOG_PRIO( LogColor::green, "Total length: %llu", g_pv.m_total_length );
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void day_12( const std::string& _title )
	{
		auto year{ 2023 };
		auto day{ 12 };

		LOG_PRIO( LogColor::red, "%d - Day %02d - %s\n", year, day, _title.c_str() );
		LOG_PRIO( LogColor::yellow, "Part 1" );

		d_12::part_01( year, day );

		LOG_NEW_LINE();
		LOG_PRIO( LogColor::yellow, "Part 2" );

		d_12::part_02( year, day );
	}
}