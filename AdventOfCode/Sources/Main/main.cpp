#include <functional>

#include <Main/years.h>
#include <Main/includes.h>
#include <Main/Utils/Utils.h>

#include <format>

int main()
{
	const static auto days = std::vector< std::function<void()> >
	{	
		[](){ y_2023::day_01( "Trebuchet?!" ); },
		[](){ y_2023::day_02( "Cube Conundrum" ); },
		[](){ y_2023::day_07( "Camel Cards" ); },
		[](){ y_2023::day_09( "Mirage Maintenance" ); },
		[](){ y_2023::day_10( "Pipe Maze" ); },
		[](){ y_2023::day_11( "Cosmic Expansion" ); },
		[](){ y_2023::day_12( "Hot Springs" ); }
	};

	//Logger::s_enable_logging = false;

	days[ 6 ]();

	//const char* test = "prout {}";
	//auto lol = std::vformat(std::string_view{ test }, days.size());

	system( "pause" );

	return 0;
}