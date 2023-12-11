#include <numeric>

#include <Main/Utils/Utils.h>

namespace y_2023
{
	namespace d_11
	{
		struct Galaxy
		{
			int64_t operator-( const Galaxy& _galaxy )
			{
				return _abs64(m_scaled_col - _galaxy.m_scaled_col) + _abs64(m_scaled_row - _galaxy.m_scaled_row);
			}

			uint32_t m_id{ 0 };
			int m_row{ 0 };
			int m_col{ 0 };
			int64_t m_scaled_row{ 0 };
			int64_t m_scaled_col{ 0 };
		};

		struct PuzzleVariables
		{
			std::vector< uint32_t > m_empty_rows{};
			std::vector< uint32_t > m_empty_columns{};
			std::vector< Galaxy > m_galaxies{};
			int m_current_row{ 0 };
			uint32_t m_empty_space_value{ 0 };
			uint64_t m_total_length{ 0 };
		};
		auto g_pv = PuzzleVariables{};

		void parse_line( const std::string& _line )
		{
			if( g_pv.m_empty_columns.empty() )
			{
				g_pv.m_empty_columns.resize( _line.size() );
				std::ranges::iota( g_pv.m_empty_columns, 0 );
			}

			auto galaxy_index = _line.find( '#' );

			if( galaxy_index == std::string::npos )
				g_pv.m_empty_rows.push_back( g_pv.m_current_row );
			else
			{
				while( galaxy_index != std::string::npos )
				{
					g_pv.m_galaxies.push_back( { static_cast<uint32_t>( g_pv.m_galaxies.size() + 1 ), g_pv.m_current_row, static_cast< int >( galaxy_index ) } );

					if( auto it = std::ranges::find( g_pv.m_empty_columns, static_cast<uint32_t>( galaxy_index ) ); it != g_pv.m_empty_columns.end() )
						g_pv.m_empty_columns.erase( it );

					galaxy_index = _line.find( '#', galaxy_index + 1 );
				}
			}

			++g_pv.m_current_row;
		}

		void compute_scaled_coordinates()
		{
			for( auto& galaxy : g_pv.m_galaxies )
			{
				auto col_count = std::ranges::count_if( g_pv.m_empty_columns, [&]( uint32_t _col ) { return _col < galaxy.m_col; } );

				galaxy.m_scaled_col = galaxy.m_col - col_count + col_count * g_pv.m_empty_space_value;

				auto row_count = std::ranges::count_if( g_pv.m_empty_rows, [&]( uint32_t _row ) { return _row < galaxy.m_row; } );

				galaxy.m_scaled_row = galaxy.m_row - row_count + row_count * g_pv.m_empty_space_value;

				LOG( "Galaxy #%03u - [%03u ; %03u] [%03u ; %03u] || %d %d", galaxy.m_id, galaxy.m_col, galaxy.m_row, galaxy.m_scaled_col, galaxy.m_scaled_row, col_count, row_count );
			}
		}

		void compute_paths()
		{
			uint64_t length{ 0 };
			uint32_t pair{ 1 };

			for( auto& galaxy : g_pv.m_galaxies )
			{
				for( auto galaxy_index{ galaxy.m_id }; galaxy_index < g_pv.m_galaxies.size(); ++galaxy_index, ++pair )
				{
					length = g_pv.m_galaxies[ galaxy_index ] - galaxy;
					g_pv.m_total_length += length;

					LOG( "Galaxies %03u - %03u (%03u): %llu || total: %llu", g_pv.m_galaxies[ galaxy_index ].m_id, galaxy.m_id, pair, length, g_pv.m_total_length );
				}
			}
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void part_01( uint32_t _year, uint32_t _day )
		{
			g_pv = PuzzleVariables{};
			g_pv.m_empty_space_value = 2;
			parse_input( _year, _day, FileType::PuzzleInput, parse_line );
			compute_scaled_coordinates();
			compute_paths();
			LOG_PRIO( LogColor::green, "Total length: %llu", g_pv.m_total_length );
		}

		void part_02( uint32_t _year, uint32_t _day )
		{
			g_pv = PuzzleVariables{};
			g_pv.m_empty_space_value = 1000000;
			parse_input( _year, _day, FileType::PuzzleInput, parse_line );
			compute_scaled_coordinates();
			compute_paths();
			LOG_PRIO( LogColor::green, "Total length: %llu", g_pv.m_total_length);
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void day_11( const std::string& _title )
	{
		auto year{ 2023 };
		auto day{ 11 };

		LOG_PRIO( LogColor::red, "%d - Day %02d - %s\n", year, day, _title.c_str() );
		LOG_PRIO( LogColor::yellow, "Part 1" );

		//d_11::part_01( year, day );

		LOG_NEW_LINE();
		LOG_PRIO( LogColor::yellow, "Part 2" );

		d_11::part_02( year, day );
	}
}