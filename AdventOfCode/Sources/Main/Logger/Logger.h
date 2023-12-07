#pragma once

#include <string>

enum class LogColor
{
	black,
	dark_blue,
	dark_green,
	dark_cyan,
	dark_red,
	purple,
	dark_yellow,
	light_gray,
	gray,
	blue,
	green,
	cyan,
	red,
	pink,
	yellow,
	white,
	COUNT
};

void log_message( LogColor _color, const char* _message, ... );
void log_message( const char* _message, ... );

class Logger
{
public:
	static void log_message( const char* _file, int _line, const char* _message, ... );
	static void log_message( const std::string& _file, int _line, LogColor _color, const char* _message, ... );

	static bool s_enable_logging;

protected:
	static void _log_to_console( const std::string& _file, int _line, const char* _message );
};
