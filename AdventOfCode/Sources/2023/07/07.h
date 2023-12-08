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

		Day_07() : BaseDay( 2023, 07 ) {}

		void step_01();
		void step_02();
	private:
		static bool _compare_hands(const Day_07::Hand& _handA, const Day_07::Hand& _handB);

		static std::unordered_map< char, uint32_t > s_cards_value;
	};
};