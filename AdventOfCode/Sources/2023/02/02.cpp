#include <Main/Utils/Utils.h>
#include <ranges>

namespace y_2023
{
	namespace d_02
	{
		struct Set
		{
			uint32_t m_red{ 0 };
			uint32_t m_green{ 0 };
			uint32_t m_blue{ 0 };
		};

		using Sets = std::vector< Set >;
		

		struct PuzzleVariables
		{
			std::vector< Sets > m_games{};
			Set					m_inventory{ 12, 13, 14 };
			uint32_t			m_sum{ 0 };
		};

		auto g_puzzle_variables = PuzzleVariables{};

		Set get_cube_set( const std::vector< int >& _numbers, const std::vector< std::string >& _colors )
		{
			auto set = Set{};

			for( auto [ number, color ] : std::views::zip( _numbers, _colors ) )
			{
				switch( color[ 0 ] )
				{
				case 'r':
				{
					set.m_red = number;
					break;
				}
				case 'g':
				{
					set.m_green = number;
					break;
				}
				case 'b':
				{
					set.m_blue = number;
					break;
				}
				};
			}

			return set;
		}

		bool is_set_possible( const Set& _set )
		{
			return !(_set.m_red > g_puzzle_variables.m_inventory.m_red || _set.m_green > g_puzzle_variables.m_inventory.m_green || _set.m_blue > g_puzzle_variables.m_inventory.m_blue );
		}

		void parse_game( const std::string& _line )
		{
			g_puzzle_variables.m_games.push_back( {} );
			auto& sets_vector = g_puzzle_variables.m_games.back();

			auto game = _line.substr( _line.find_first_of( ':' ) + 1 );
			auto sets = split( game, ';' );
			auto valid_game{ true };

			for( auto set : sets )
			{
				sets_vector.push_back( get_cube_set( extract_numbers( set, ' ' ), extract_words( set, ' ' ) ) );

				valid_game &= is_set_possible( sets_vector.back() );
			}

			if( valid_game )
			{
				g_puzzle_variables.m_sum += static_cast< uint32_t >( g_puzzle_variables.m_games.size() );
				LOG_C( LogColor::dark_green, "%s // sum: %d", _line.c_str(), g_puzzle_variables.m_sum );
			}
			else
			{
				LOG_C( LogColor::dark_red, _line.c_str() );
			}
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void part_01( uint32_t _year, uint32_t _day )
		{
			g_puzzle_variables = PuzzleVariables{};
			parse_input( _year, _day, FileType::PuzzleInput, parse_game );
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void day_02( const std::string& _title )
	{
		auto year{ 2023 };
		auto day{ 2 };

		LOG_PRIO( LogColor::red, "%d - Day %02d - %s\n", year, day, _title.c_str() );
		LOG_PRIO( LogColor::yellow, "Part 1" );

		d_02::part_01( year, day );

		LOG_NEW_LINE();
		LOG_PRIO( LogColor::yellow, "Part 2" );

	}
}