#include <functional>

#include <Main/years.h>
#include <Main/includes.h>

int main()
{
	const static auto days = std::vector< std::function<void()> >{	[](){ y_2023::day_01( "Trebuchet?!" ); },
																	[](){ y_2023::day_07( "Camel Cards" ); } };

	//Logger::s_enable_logging = false;

	days[ 0 ]();

	system( "pause" );

	return 0;
}