#include <functional>

#include <Main/years.h>
#include <Main/includes.h>
#include <Main/Utils/Utils.h>

int main()
{
	const static auto days = std::vector< std::function<void()> >
	{	
		[](){ y_2023::day_01( "Trebuchet?!" ); },
		[](){ y_2023::day_02( "Cube Conundrum" ); },
		[](){ y_2023::day_07( "Camel Cards" ); },
		[](){ y_2023::day_09( "Mirage Maintenance" ); },
		[](){ y_2023::day_10( "Pipe Maze" ); },
		[](){ y_2023::day_11( "Cosmic Expansion" ); }
	};

	//Logger::s_enable_logging = false;

	days[ 5 ]();

	system( "pause" );

	return 0;
}