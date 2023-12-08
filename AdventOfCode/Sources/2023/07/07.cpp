#include <Main/includes.h>

#include "07.h"

namespace y_2023
{
	std::unordered_map< char, uint32_t > Day_07::s_cards_value = std::unordered_map< char, uint32_t >();

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
						_hand.m_type = Day_07::HandType::two_pairs;
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

	std::string get_hand_type_string(Day_07::HandType _type)
	{
		switch (_type)
		{
			case y_2023::Day_07::HandType::high_card:
				return "High Card";
			case y_2023::Day_07::HandType::one_pair:
				return "One pair";
			case y_2023::Day_07::HandType::two_pairs:
				return "Two pairs";
			case y_2023::Day_07::HandType::three_of_a_kind:
				return "Three of a kind";
			case y_2023::Day_07::HandType::full_house:
				return "Full House";
			case y_2023::Day_07::HandType::four_of_a_kind:
				return "Four of a kind";
			case y_2023::Day_07::HandType::five_of_a_kind:
				return "Five of a kind";
		}
		return "";
	};

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

	bool Day_07::_compare_hands(const Day_07::Hand& _handA, const Day_07::Hand& _handB)
	{
		if (_handA.m_type != _handB.m_type)
			return _handA.m_type < _handB.m_type;

		for (auto card{ 0 }; card < 5; ++card)
		{
			if (_handA.m_hand[card] == _handB.m_hand[card])
				continue;

			return s_cards_value[_handA.m_hand[card]] < s_cards_value[_handB.m_hand[card]];
		}

		return true;
	}

	void Day_07::step_01()
	{
		BaseDay::step_01();

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

		auto inputFile = _open_input_file( FileType::PuzzleInput );

		if( inputFile.is_open() == false )
			return;

		auto line = std::string{};
		auto final_number{ 0 };

		auto hands = std::vector< Hand >{};

		while( std::getline( inputFile, line ) )
			hands.push_back( get_hand_from_line( line ) );

		std::ranges::sort(hands, _compare_hands);

		auto rank{ 1 };
		auto total_winnings{ 0 };

		for (auto& hand : hands)
		{
			hand.m_rank = rank;
			hand.m_hand_score = hand.m_rank * hand.m_bid;

			total_winnings += hand.m_hand_score;

			LOG( "hand %s (%s): %u x %u = %u // %u", hand.m_hand.c_str(), get_hand_type_string( hand.m_type ).c_str(), hand.m_rank, hand.m_bid, hand.m_hand_score, total_winnings );

			++rank;
		}
	}

	void Day_07::step_02()
	{
	}
};