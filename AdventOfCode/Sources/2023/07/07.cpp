#include <unordered_map>

#include <Main/includes.h>

#include "07.h"

namespace y_2023
{
	void fill_cards_info( const std::string& _cards, Day_07::Hand& _hand )
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

		for( auto it = cards_map.begin(); it != cards_map.end(); ++it )
			cards_vector.push_back( { it->first, it->second } );

		std::sort( cards_vector.begin(), cards_vector.end(), []( const cards_number& _cardsA, const cards_number& _cardsB )
			{
				return _cardsA.m_count > _cardsB.m_count;
			});

		auto pair_found{ false };
		auto three_of_a_kind_found{ false };

		for( auto cards : cards_vector )
		{
			switch( cards.m_count )
			{
				case 5:
				{
					_hand.m_type = Day_07::HandType::five_of_a_kind;
					return;
				}
				case 4:
				{
					_hand.m_type = Day_07::HandType::four_of_a_kind;
					return;
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
						_hand.m_type = Day_07::HandType::full_house;
						return;
					}
					
					if( pair_found )
					{
						_hand.m_type = Day_07::HandType::two_pair;
						return;
					}

					pair_found = true;
					break;
				}
				case 1:
				{
					if( three_of_a_kind_found || pair_found )
						continue;

					_hand.m_type = Day_07::HandType::high_card;
					return;
				}
			};
		}

		if( three_of_a_kind_found )
		{
			_hand.m_type = Day_07::HandType::three_of_a_kind;
			return;
		}

		if( pair_found )
		{
			_hand.m_type = Day_07::HandType::one_pair;
			return;
		}
	}

	Day_07::Hand get_hand_from_line( const std::string& _line )
	{
		auto hand = Day_07::Hand{};

		auto space_index = _line.find_first_of( " " );

		auto cards = _line.substr( 0, space_index );
		auto bid = _line.substr( space_index + 1 );

		fill_cards_info( cards, hand );

		hand.m_bid = atoi( bid.c_str() );

		return hand;
	}

	void Day_07::step_01()
	{
		BaseDay::step_01();

		auto inputFile = _open_input_file( FileType::Example01 );

		if( inputFile.is_open() == false )
			return;

		auto line = std::string{};
		auto final_number{ 0 };

		auto hands = std::vector< Hand >{};

		while( std::getline( inputFile, line ) )
			hands.push_back( get_hand_from_line( line ) );
	}

	void Day_07::step_02()
	{
	}
};
