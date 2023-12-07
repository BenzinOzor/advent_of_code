#pragma once

#include <Main/includes.h>


namespace y_2023
{
	class Day_07 : public BaseDay
	{
	public:
		enum class HandType
		{
			high_card,
			one_pair,
			two_pair,
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
			HandType	m_type{ HandType::COUNT };

			uint32_t	m_cards_score{ 0 };
			uint32_t	m_hand_score{ 0 };
		};

		Day_07() : BaseDay( 2023, 07 ) {}

		void step_01();
		void step_02();
	};
};