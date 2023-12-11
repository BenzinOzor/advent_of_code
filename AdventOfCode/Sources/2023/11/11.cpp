#include <Main/Utils/Utils.h>

namespace y_2023
{
	namespace d_11
	{
		struct PuzzleVariables
		{
			std::vector< bool > m_column_states{ true };
		};
		auto g_pv = PuzzleVariables{};

		void parse_line( const std::string& _line )
		{
			g_pv.m_column_states.push_back( {} );
			//_line.find
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void part_01( uint32_t _year, uint32_t _day )
		{
			g_pv = PuzzleVariables{};
			parse_input( _year, _day, FileType::Example01, parse_line );
			//LOG_PRIO( LogColor::green, "Steps: %u", g_pv.m_steps / 2 );
		}

		void part_02( uint32_t _year, uint32_t _day )
		{
			g_pv = PuzzleVariables{};
			parse_input( _year, _day, FileType::PuzzleInput, parse_line );
			//LOG_PRIO( LogColor::green, "Inside tiles: %u", g_pv.m_inside_tiles );
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void day_11( const std::string& _title )
	{
		auto year{ 2023 };
		auto day{ 11 };

		LOG_PRIO( LogColor::red, "%d - Day %02d - %s\n", year, day, _title.c_str() );
		LOG_PRIO( LogColor::yellow, "Part 1" );

		d_11::part_01( year, day );

		LOG_NEW_LINE();
		LOG_PRIO( LogColor::yellow, "Part 2" );

		d_11::part_02( year, day );
	}
}