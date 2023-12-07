#include <Windows.h>
#include <print>

#include <Main/includes.h>

static constexpr uint32_t LogLen{ 2048 };

bool Logger::s_enable_logging = true;


void Logger::log_new_line()
{
	OutputDebugStringA( "\n" );
	std::print( "\n" );
}

void Logger::log_message( const char* _file, int _line, const char* _message, ... )
{
	if( s_enable_logging == false )
		return;

	char sMessage[ LogLen ];
	va_list args;
	va_start( args, _message );

	vsprintf_s( sMessage, LogLen - 1, _message, args );

	OutputDebugStringA( sprintf( "%s (%i) : %s\n", _file, _line, sMessage ).c_str() );
}

void Logger::log_message( const std::string& _file, int _line, LogColor _color, const char* _message, ... )
{
	if( s_enable_logging == false )
		return;

	char sMessage[ LogLen ];
	LogColor log_color = LogColor::white;

	if( _color < LogColor::COUNT )
		log_color = _color;
	
	va_list args;
	va_start( args, _message );

	vsprintf_s( sMessage, LogLen - 1, _message, args );

	OutputDebugStringA( sprintf( "%s (%i) : %s\n", _file.c_str(), _line, sMessage ).c_str() );

	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), static_cast<WORD>( log_color ) );
	_log_to_console( _file, _line, sMessage );
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), static_cast<WORD>( LogColor::white ) );
}

void Logger::_log_to_console( const std::string& _file, int _line, const char* _message )
{
	std::string sTruncatedPath = _file.substr( _file.find_last_of( '\\' ) + 1 );
	std::print( "{} ({}) : {}\n", sTruncatedPath, _line, _message );
}
