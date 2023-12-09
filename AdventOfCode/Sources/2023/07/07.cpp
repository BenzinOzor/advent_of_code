#include <Main/Utils/Utils.h>

namespace y_2023
{
	namespace d_07
	{
		enum class HandType
		{
			high_card,
			one_pair,
			two_pairs,
			three_of_a_kind,
			full_house,
			four_of_a_kind,
			five_of_a_kind,
			COUNT
		};

		struct Hand
		{
			std::string m_hand{ "" };
			uint32_t	m_bid{ 0 };
			uint32_t	m_rank{ 0 };
			HandType	m_type{ HandType::COUNT };

			uint32_t	m_hand_score{ 0 };
		};

		std::unordered_map< char, uint32_t > s_cards_value = std::unordered_map< char, uint32_t >();

		void fill_cards_info( const std::string& _cards, Hand& _hand, bool _enable_jokers )
		{
			struct cards_number
			{
				char m_card{ '\0' };
				uint32_t m_count{ 0 };
			};

			auto cards_map = std::unordered_map< char, uint32_t >();
			auto cards_vector = std::vector< cards_number >();

			_hand.m_hand = _cards;

			for( auto card : _cards )
				++cards_map[ card ];

			auto J_count = cards_map[ 'J' ];

			if( J_count == 5 )
			{
				_hand.m_type = HandType::five_of_a_kind;
				return;
			}

			for( auto it = cards_map.begin(); it != cards_map.end(); ++it )
			{
				if( _enable_jokers && it->first == 'J' )
					continue;

				cards_vector.push_back( { it->first, it->second } );
			}

			std::sort( cards_vector.begin(), cards_vector.end(), []( const cards_number& _cardsA, const cards_number& _cardsB )
				{
					return _cardsA.m_count > _cardsB.m_count;
				} );

			auto pair_found{ false };
			auto three_of_a_kind_found{ false };
			auto type_found{ false };

			for( auto cards : cards_vector )
			{
				switch( cards.m_count )
				{
				case 5:
				{
					_hand.m_type = HandType::five_of_a_kind;
					return;
				}
				case 4:
				{
					_hand.m_type = HandType::four_of_a_kind;
					type_found = true;
					break;
				}
				case 3:
				{
					three_of_a_kind_found = true;
					break;
				}
				case 2:
				{
					if( three_of_a_kind_found )
					{
						_hand.m_type = HandType::full_house;
						return;
					}

					if( pair_found )
					{
						_hand.m_type = HandType::two_pairs;
						type_found = true;
						break;
					}

					pair_found = true;
					break;
				}
				case 1:
				{
					if( three_of_a_kind_found || pair_found )
						continue;

					_hand.m_type = HandType::high_card;
					type_found = true;
					break;
				}
				};

				if( type_found )
					break;
			}

			if( _hand.m_type == HandType::COUNT )
			{
				if( three_of_a_kind_found )
					_hand.m_type = HandType::three_of_a_kind;

				if( pair_found )
					_hand.m_type = HandType::one_pair;
			}

			if( _enable_jokers == false || J_count <= 0 )
				return;

			/*
			* conversion table (from hand without Js)
			*
			* 4 of a kind
			* - 1J: 5 of a kind
			*
			* 3 of a kind
			* - 2J: 5 of a kind
			* - 1J: 4 of a kind
			*
			* 2 pairs
			* - 1J: Full House
			*
			* 1 pair
			* - 3J: 5 of a kind
			* - 2J: 4 of a kind
			* - 1J: 3 of a kind
			*
			* high card
			* - 4J: 5 of a kind
			* - 3J: 4 of a kind
			* - 2J: 3 of a kind
			* - 1J: one pair
			*/

			switch( _hand.m_type )
			{
			case HandType::four_of_a_kind:
			{
				_hand.m_type = HandType::five_of_a_kind;
				return;
			}
			case HandType::three_of_a_kind:
			{
				if( J_count == 2 )
					_hand.m_type = HandType::five_of_a_kind;
				else
					_hand.m_type = HandType::four_of_a_kind;

				return;
			}
			case HandType::two_pairs:
			{
				_hand.m_type = HandType::full_house;
				return;
			}
			case HandType::one_pair:
			{
				switch( J_count )
				{
				case 3:
				{
					_hand.m_type = HandType::five_of_a_kind;
					return;
				}
				case 2:
				{
					_hand.m_type = HandType::four_of_a_kind;
					return;
				}
				case 1:
				{
					_hand.m_type = HandType::three_of_a_kind;
					return;
				}
				};
			}
			case HandType::high_card:
			{
				switch( J_count )
				{
				case 4:
				{
					_hand.m_type = HandType::five_of_a_kind;
					return;
				}
				case 3:
				{
					_hand.m_type = HandType::four_of_a_kind;
					return;
				}
				case 2:
				{
					_hand.m_type = HandType::three_of_a_kind;
					return;
				}
				case 1:
				{
					_hand.m_type = HandType::one_pair;
					return;
				}
				};
			}
			};
		}

		std::string get_hand_type_string( HandType _type )
		{
			switch( _type )
			{
			case HandType::high_card:
				return "High Card";
			case HandType::one_pair:
				return "One pair";
			case HandType::two_pairs:
				return "Two pairs";
			case HandType::three_of_a_kind:
				return "Three of a kind";
			case HandType::full_house:
				return "Full House";
			case HandType::four_of_a_kind:
				return "Four of a kind";
			case HandType::five_of_a_kind:
				return "Five of a kind";
			}
			return "";
		};

		template< typename fn >
		uint32_t sort_and_rank_hands( std::vector< Hand >& _hands, fn&& _sort_fct )
		{
			std::ranges::sort( _hands, _sort_fct );

			auto rank{ 1 };
			auto total_score{ 0 };

			for( auto& hand : _hands )
			{
				hand.m_rank = rank;
				hand.m_hand_score = hand.m_rank * hand.m_bid;

				total_score += hand.m_hand_score;

				LOG( "hand %s (%s): %u x %u = %u // %u", hand.m_hand.c_str(), get_hand_type_string( hand.m_type ).c_str(), hand.m_rank, hand.m_bid, hand.m_hand_score, total_score );

				++rank;
			}

			return total_score;
		}

		Hand get_hand_from_line( const std::string& _line, bool _enable_jokers )
		{
			auto hand = Hand{};

			auto space_index = _line.find_first_of( " " );

			auto cards = _line.substr( 0, space_index );
			auto bid = _line.substr( space_index + 1 );

			fill_cards_info( cards, hand, _enable_jokers );

			hand.m_bid = atoi( bid.c_str() );

			return hand;
		}

		bool _compare_hands( const Hand& _handA, const Hand& _handB )
		{
			if( _handA.m_type != _handB.m_type )
				return _handA.m_type < _handB.m_type;

			for( auto card{ 0 }; card < 5; ++card )
			{
				if( _handA.m_hand[ card ] == _handB.m_hand[ card ] )
					continue;

				return s_cards_value[ _handA.m_hand[ card ] ] < s_cards_value[ _handB.m_hand[ card ] ];
			}

			return true;
		}


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void part_01()
		{
			s_cards_value['2'] = 2;
			s_cards_value['3'] = 3;
			s_cards_value['4'] = 4;
			s_cards_value['5'] = 5;
			s_cards_value['6'] = 6;
			s_cards_value['7'] = 7;
			s_cards_value['8'] = 8;
			s_cards_value['9'] = 9;
			s_cards_value['T'] = 10;
			s_cards_value['J'] = 11;
			s_cards_value['Q'] = 12;
			s_cards_value['K'] = 13;
			s_cards_value['A'] = 14;

			auto inputFile = open_input_file( 2023, 07, FileType::PuzzleInput );

			if( inputFile.is_open() == false )
				return;

			auto line = std::string{};
			auto hands = std::vector< Hand >{};

			while( std::getline( inputFile, line ) )
				hands.push_back( get_hand_from_line( line, false ) );

			LOG_PRIO( LogColor::green, "Total score: %u", sort_and_rank_hands( hands, _compare_hands ) );
		}

		void part_02()
		{
			s_cards_value['J'] = 1;
			s_cards_value['2'] = 2;
			s_cards_value['3'] = 3;
			s_cards_value['4'] = 4;
			s_cards_value['5'] = 5;
			s_cards_value['6'] = 6;
			s_cards_value['7'] = 7;
			s_cards_value['8'] = 8;
			s_cards_value['9'] = 9;
			s_cards_value['T'] = 10;
			s_cards_value['Q'] = 11;
			s_cards_value['K'] = 12;
			s_cards_value['A'] = 13;

			auto inputFile = open_input_file( 2023, 07, FileType::PuzzleInput);

			if (inputFile.is_open() == false)
				return;

			auto line = std::string{};
			auto hands = std::vector< Hand >{};

			while (std::getline(inputFile, line))
				hands.push_back(get_hand_from_line( line, true ));

			LOG_PRIO( LogColor::green, "Total score: %u", sort_and_rank_hands( hands, _compare_hands ) );
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void day_07( const std::string& _title )
	{
		LOG_PRIO( LogColor::red, "2023 - Day 07 - %s\n", _title.c_str() );
		LOG_PRIO( LogColor::yellow, "Part 1" );

		d_07::part_01();

		LOG_NEW_LINE();
		LOG_PRIO( LogColor::yellow, "Part 2" );

		d_07::part_02();
	}
};
