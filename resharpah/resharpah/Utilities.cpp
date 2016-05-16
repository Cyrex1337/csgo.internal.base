#include "Utilities.hpp"

void Utilities::CreateConsole( const std::string& conTitle )
{
	AllocConsole( );
	FILE *conin, *conout;
	freopen_s( &conin, "conin$", "r", stdin );
	freopen_s( &conout, "conout$", "w", stderr );
	freopen_s( &conout, "conout$", "w", stdout );

	if ( !conTitle.empty( ) && conTitle != "" )
		SetConsoleTitle( conTitle.c_str( ) );
}
