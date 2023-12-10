#include <Main/Utils/Utils.h>

namespace y_2023
{
	namespace d_10
	{
		enum class PipeType
		{
			vertical,
			horizontal,
			up_right,
			up_left,
			down_right,
			down_left,
			COUNT
		};

		enum class Direction
		{
			up,
			down,
			left,
			right,
			COUNT
		};

		struct Position
		{
			uint32_t m_row{ 0 };
			uint32_t m_col{ 0 };
		};

		struct Pipe
		{
			char		m_pipe{ '.' };
			PipeType	m_type{ PipeType::COUNT };

			Position	m_pos{};

			bool		m_in_loop{ false };
			bool		m_start{ false };
			bool		m_far_point{ false };
			bool		m_inside_loop{ false };
			bool		m_out_of_bounds{ false };
		};
		using Pipes = std::vector< Pipe >;
		using PipesPtr = std::vector< Pipe* >;

		struct PuzzleVariables
		{
			std::vector< Pipes >	m_map;
			Position				m_start_position{};
			uint32_t				m_steps{ 0 };
			uint32_t				m_inside_tiles{ 0 };
		};
		auto g_pv = PuzzleVariables{};

		PipeType get_type_from_char( const char _pipe )
		{
			switch( _pipe )
			{
			case '|':
				return PipeType::vertical;
			case '-':
				return PipeType::horizontal;
			case 'L':
				return PipeType::up_right;
			case 'J':
				return PipeType::up_left;
			case 'F':
				return PipeType::down_right;
			case '7':
				return PipeType::down_left;
			default:
				return PipeType::COUNT;
			}
		}

		void print_pipes()
		{
			auto pipe_color{ LogColor::white };
			auto pipe_char = std::string{};

			for( auto& pipes_row : g_pv.m_map )
			{
				for( auto& pipe : pipes_row )
				{
					pipe_char = pipe.m_pipe;

					if( pipe.m_start )
						pipe_color = LogColor::pink;
					else if( pipe.m_far_point )
						pipe_color = LogColor::purple;
					else if( pipe.m_in_loop )
						pipe_color = LogColor::green;
					else if( pipe.m_inside_loop )
					{
						pipe_color = LogColor::white;
						pipe_char = "I";
					}
					else if( pipe.m_out_of_bounds )
					{
						//pipe_char = " ";
						pipe_color = LogColor::black;
					}
					else
					{
						pipe_color = LogColor::gray;
						pipe_char = "O";
					}

					Logger::colored_print( pipe_color, pipe_char.c_str() );
				}
				printf( "\n" );
			}
		}

		Pipe get_pipe_from_char( const char _pipe )
		{
			auto pipe = Pipe{};

			pipe.m_pipe = _pipe;
			pipe.m_type = get_type_from_char( pipe.m_pipe );

			if( pipe.m_pipe == 'S' )
			{
				pipe.m_start = true;
				pipe.m_in_loop = true;
			}

			return pipe;
		}

		Direction get_opposite( Direction _direction )
		{
			switch( _direction )
			{
			case y_2023::d_10::Direction::up:
			{
				return Direction::down;
			}
			case y_2023::d_10::Direction::down:
			{
				return Direction::up;
			}
			case y_2023::d_10::Direction::left:
			{
				return Direction::right;
			}
			case y_2023::d_10::Direction::right:
			{
				return Direction::left;
			}
			default:
				return Direction::COUNT;
			}
		}

		bool can_connect_to_pipe( Direction _source, PipeType _pipe )
		{
			switch( _source )
			{
			case y_2023::d_10::Direction::up:
			{
				switch( _pipe )
				{
				case y_2023::d_10::PipeType::vertical:
				case y_2023::d_10::PipeType::up_right:
				case y_2023::d_10::PipeType::up_left:
					return true;
				case y_2023::d_10::PipeType::horizontal:
				case y_2023::d_10::PipeType::down_right:
				case y_2023::d_10::PipeType::down_left:
				default:
					return false;
				}
			}
			case y_2023::d_10::Direction::down:
			{
				switch( _pipe )
				{
				case y_2023::d_10::PipeType::vertical:
				case y_2023::d_10::PipeType::down_right:
				case y_2023::d_10::PipeType::down_left:
					return true;
				case y_2023::d_10::PipeType::horizontal:
				case y_2023::d_10::PipeType::up_right:
				case y_2023::d_10::PipeType::up_left:
				default:
					return false;
				}
			}
			case y_2023::d_10::Direction::left:
			{
				switch( _pipe )
				{
				case y_2023::d_10::PipeType::horizontal:
				case y_2023::d_10::PipeType::up_left:
				case y_2023::d_10::PipeType::down_left:
					return true;
				case y_2023::d_10::PipeType::vertical:
				case y_2023::d_10::PipeType::up_right:
				case y_2023::d_10::PipeType::down_right:
				default:
					return false;
				}
			}
			case y_2023::d_10::Direction::right:
			{
				switch( _pipe )
				{
				case y_2023::d_10::PipeType::horizontal:
				case y_2023::d_10::PipeType::up_right:
				case y_2023::d_10::PipeType::down_right:
					return true;
				case y_2023::d_10::PipeType::vertical:
				case y_2023::d_10::PipeType::up_left:
				case y_2023::d_10::PipeType::down_left:
				default:
					return false;
				}
			}
			default:
				return false;
			}
		}

		void determine_start_type()
		{
			if( g_pv.m_start_position.m_row >= g_pv.m_map.size() )
			{
				LOG_ERROR( "START ROW HIGHER THAN MAP ROW COUNT (%u vs %d)", g_pv.m_start_position.m_row, g_pv.m_map.size() );
				return;
			}

			auto& start_row{ g_pv.m_start_position.m_row };

			if( g_pv.m_start_position.m_col >= g_pv.m_map[ start_row ].size() )
			{
				LOG_ERROR( "START COLUMN HIGHER THAN MAP COLUMN COUNT (%u vs %d)", g_pv.m_start_position.m_col, g_pv.m_map[ start_row ].size() );
				return;
			}

			auto& start_col{ g_pv.m_start_position.m_col };
			auto& start_pipe{ g_pv.m_map[ start_row ][ start_col ] };

			auto can_connect_up{ false };
			auto can_connect_down{ false };
			auto can_connect_left{ false };
			auto can_connect_right{ false };

			// checking above - source: down
			if( start_row > 0 )
				can_connect_up = can_connect_to_pipe( Direction::down, g_pv.m_map[ start_row - 1 ][ start_col ].m_type );

			// check under - source: up
			if( start_row < g_pv.m_map.size() - 1 )
				can_connect_down = can_connect_to_pipe( Direction::up, g_pv.m_map[ start_row + 1 ][ start_col ].m_type );

			// checking right - source: left
			if( start_col < g_pv.m_map[ start_row ].size() - 1 )
				can_connect_right = can_connect_to_pipe( Direction::left, g_pv.m_map[ start_row ][ start_col + 1 ].m_type );

			// check left - source: right
			if( start_col > 0 )
				can_connect_left = can_connect_to_pipe( Direction::right, g_pv.m_map[ start_row ][ start_col - 1 ].m_type );

			if( can_connect_up )
			{
				if( can_connect_right )
					start_pipe.m_type = PipeType::up_right;
				else if( can_connect_left )
					start_pipe.m_type = PipeType::up_left;
				else if( can_connect_down )
					start_pipe.m_type = PipeType::vertical;
			}
			else if( can_connect_down )
			{
				if( can_connect_right )
					start_pipe.m_type = PipeType::down_right;
				else if( can_connect_left )
					start_pipe.m_type = PipeType::down_left;
				else if( can_connect_up )
					start_pipe.m_type = PipeType::vertical;
			}
			else if( can_connect_right && can_connect_left )
			{
				start_pipe.m_type = PipeType::horizontal;
			}

			if( start_pipe.m_type == PipeType::COUNT )
				LOG_ERROR( "COULDN'T DETERMINE START PIPE TYPE!" );
		}

		std::pair<Pipe*,Direction> add_next_pipe_to_loop( Pipe* _pipe, Direction _previous_pipe )
		{
			if( _pipe == nullptr )
				return {};

			Pipe* next_pipe{ nullptr };
			auto previous_pipe{ Direction::COUNT };

			switch( _pipe->m_type )
			{
			case PipeType::vertical:
			{
				if( _previous_pipe == Direction::up )
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row + 1 ][ _pipe->m_pos.m_col ];
					previous_pipe = Direction::up;
				}
				else
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row - 1 ][ _pipe->m_pos.m_col ];
					previous_pipe = Direction::down;
				}

				break;
			}
			case PipeType::horizontal:
			{
				if( _previous_pipe == Direction::left )
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row ][ _pipe->m_pos.m_col + 1 ];
					previous_pipe = Direction::left;
				}
				else
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row ][ _pipe->m_pos.m_col - 1 ];
					previous_pipe = Direction::right;
				}

				break;
			}
			case PipeType::up_right:
			{
				if( _previous_pipe == Direction::up )
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row ][ _pipe->m_pos.m_col + 1 ];
					previous_pipe = Direction::left;
				}
				else
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row - 1 ][ _pipe->m_pos.m_col ];
					previous_pipe = Direction::down;
				}

				break;
			}
			case PipeType::up_left:
			{
				if( _previous_pipe == Direction::up )
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row ][ _pipe->m_pos.m_col - 1 ];
					previous_pipe = Direction::right;
				}
				else
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row - 1 ][ _pipe->m_pos.m_col ];
					previous_pipe = Direction::down;
				}

				break;
			}
			case PipeType::down_right:
			{
				if( _previous_pipe == Direction::down )
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row ][ _pipe->m_pos.m_col + 1 ];
					previous_pipe = Direction::left;
				}
				else
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row + 1 ][ _pipe->m_pos.m_col ];
					previous_pipe = Direction::up;
				}

				break;
			}
			case PipeType::down_left:
			{
				if( _previous_pipe == Direction::down )
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row ][ _pipe->m_pos.m_col - 1 ];
					previous_pipe = Direction::right;
				}
				else
				{
					next_pipe = &g_pv.m_map[ _pipe->m_pos.m_row + 1 ][ _pipe->m_pos.m_col ];
					previous_pipe = Direction::up;
				}

				break;
			}
			default:
				LOG_ERROR( "COULDN'T FIND NEXT PIPE!" );
				break;
			}

			if( next_pipe == nullptr || next_pipe->m_start )
				return {};

			next_pipe->m_in_loop = true;
			++g_pv.m_steps;
			return { next_pipe, previous_pipe };
		}

		void compute_loop()
		{
			++g_pv.m_steps;

			auto* next_pipe = &g_pv.m_map[ g_pv.m_start_position.m_row ][ g_pv.m_start_position.m_col ];
			auto previous_pipe{ Direction::COUNT };

			while( next_pipe != nullptr )
			{
				auto [ret_pipe, prev_pipe] = add_next_pipe_to_loop( next_pipe, previous_pipe );
				next_pipe = ret_pipe;
				previous_pipe = prev_pipe;
			}
		}

		void clean_grid()
		{
			auto first_loop_pipe_found{ false };
			auto last_loop_index{ -1 };
			auto pipe_index{ 0 };

			for( auto& pipes_row : g_pv.m_map )
			{
				first_loop_pipe_found = false;
				last_loop_index = -1;
				pipe_index = 0;

				for( auto& pipe : pipes_row )
				{
					if( first_loop_pipe_found == false )
					{
						if( pipe.m_in_loop == false )
							pipe.m_out_of_bounds = true;
						else
							first_loop_pipe_found = true;
					}

					if( pipe.m_in_loop )
						last_loop_index = pipe_index;

					++pipe_index;
				}

				for( auto index{ last_loop_index + 1 }; index < pipes_row.size(); ++index )
					pipes_row[ index ].m_out_of_bounds = true;
			}
		}

		void compute_inside_tiles()
		{
			auto last_tile{'\0'};

			for( auto& pipes_row : g_pv.m_map )
			{
				auto wall_count{ 0 };
				
				for( auto& pipe : pipes_row )
				{
					if( pipe.m_out_of_bounds )
						continue;

					if( pipe.m_in_loop )
					{
						switch( pipe.m_pipe )
						{
						case '|':
						{
							++wall_count;
							break;
						}
						case 'L':
						{
							last_tile = 'L';
							break;
						}
						case 'F':
						{
							last_tile = 'F';
							break;
						}
						case '7':
						{
							if( last_tile == 'L' )
								++wall_count;

							last_tile = '\0';
							break;
						}
						case 'J':
						{
							if( last_tile == 'F' )
								++wall_count;

							last_tile = '\0';
							break;
						}
						};
					}
					else
					{
						if( wall_count % 2 == 1 )
						{
							pipe.m_inside_loop = true;
							++g_pv.m_inside_tiles;
						}
						else
							pipe.m_inside_loop = false;
					}
				}
			}
		}

		void parse_pipes( const std::string& _line )
		{
			g_pv.m_map.push_back( {} );

			auto& pipe_row = g_pv.m_map.back();
			pipe_row.reserve( _line.size() );

			for( auto pipe : _line )
			{
				pipe_row.push_back( get_pipe_from_char( pipe ) );

				pipe_row.back().m_pos.m_row = static_cast<uint32_t>( g_pv.m_map.size() - 1 );
				pipe_row.back().m_pos.m_col = static_cast<uint32_t>( pipe_row.size() - 1 );

				if( pipe_row.back().m_start )
					g_pv.m_start_position = pipe_row.back().m_pos;
			}
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void part_01( uint32_t _year, uint32_t _day )
		{
			g_pv = PuzzleVariables{};
			parse_input( _year, _day, FileType::Example01, parse_pipes );
			determine_start_type();
			compute_loop();
			print_pipes();
			LOG_PRIO( LogColor::green, "Steps: %u", g_pv.m_steps / 2 );
		}

		void part_02( uint32_t _year, uint32_t _day )
		{
			g_pv = PuzzleVariables{};
			parse_input( _year, _day, FileType::PuzzleInput, parse_pipes );
			determine_start_type();
			compute_loop();
			clean_grid();

			compute_inside_tiles();

			print_pipes();
			LOG_PRIO( LogColor::green, "Inside tiles: %u", g_pv.m_inside_tiles );
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void day_10( const std::string& _title )
	{
		auto year{ 2023 };
		auto day{ 10 };

		LOG_PRIO( LogColor::red, "%d - Day %02d - %s\n", year, day, _title.c_str() );
		LOG_PRIO( LogColor::yellow, "Part 1" );

		d_10::part_01( year, day );

		LOG_NEW_LINE();
		LOG_PRIO( LogColor::yellow, "Part 2" );

		d_10::part_02( year, day );
	}
}