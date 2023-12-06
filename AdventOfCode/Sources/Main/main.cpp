#include <Main/years.h>

int main()
{
	auto today = y_2023::day_01{};

	today.step_01();
	today.step_02();

	system( "pause" );

	return 0;
}