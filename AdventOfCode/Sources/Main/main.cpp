#include <Main/years.h>
#include <Main/Logger/Logger.h>

int main()
{
	//Logger::s_enable_logging = false;

	auto today = y_2023::Day_01{};

	today.step_01();
	today.step_02();

	system( "pause" );

	return 0;
}