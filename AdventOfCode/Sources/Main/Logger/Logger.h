#pragma once

#include <string>
#include <stdarg.h>
#include <source_location>

#define LOG( ... ) { const std::source_location location = std::source_location::current(); Logger::log_message( location.file_name(), location.line(), LogColor::white, __VA_ARGS__ ); }
#define LOG_C( color, ... ) { const std::source_location location = std::source_location::current(); Logger::log_message( location.file_name(), location.line(), color, __VA_ARGS__ ); }
#define LOG_PRIO( color,... ) { const std::source_location location = std::source_location::current(); Logger::log_prio_message( location.file_name(), location.line(), color, __VA_ARGS__ ); }
#define LOG_NEW_LINE() { Logger::log_new_line(); }


inline std::string sprintf( const char* pFormat, ... )
{
	std::string sOut;
	va_list oArgs;
	va_start( oArgs, pFormat );
	int iLen;
	static char sTmp[16384];

	iLen = _vsnprintf_s( sTmp, 16384, pFormat, oArgs );

	sOut.assign( sTmp, iLen );

	return sOut;
}


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

class Logger
{
public:
	static void log_new_line();
	static void log_message( const char* _file, int _line, const char* _message, ... );
	static void log_message( const std::string& _file, int _line, LogColor _color, const char* _message, ... );
	static void log_prio_message( const std::string& _file, int _line, LogColor _color, const char* _message, ... );

	static bool s_enable_logging;

protected:
	static void _log_to_console( const std::string& _file, int _line, const char* _message );
};
