#include <Windows.h>
#include "Utilities.hpp"
#include "VFTHook.hpp"
#include "InterfaceManager.hpp"
#include "SDK.hpp"
#include "Drawing.hpp"

void __stdcall hkPaintTraverse( unsigned int panel_, bool forceRepaint, bool allowForce )
{
	oPaintTraverse( Panel, panel_, forceRepaint, allowForce );

	static unsigned int panel = 0;
	if ( !panel )
	{
		const char* panelName = Panel->GetName( panel_ );
		if ( strcmp( panelName, "FocusOverlayPanel" ) == 0 )
			panel = panel_;
	}

	if ( panel && panel_ == panel )
	{
		g_pDrawing->DrawString( 50, 50, Color( 255, 0, 0, 255 ), L"dont know" );
	}
}

DWORD WINAPI Init( LPVOID lpThreadParameter )
{
	Utilities::CreateConsole( "Log console" );

	Client = InterfaceManager::Grab<IBaseClientDLL>( "client.dll", "VClient017" );
	Panel = InterfaceManager::Grab<IPanel>( "vgui2.dll", "VGUI_Panel009" );
	Surface = InterfaceManager::Grab<ISurface>( "vguimatsurface.dll", "VGUI_Surface031" );
	 
	g_pPanelHook = std::make_unique<VFTHook>( ( void*** ) Panel );
	g_pDrawing = std::make_unique<Drawing>( );
	
	oPaintTraverse = g_pPanelHook->Hook<tPaintTraverse>( 41, hkPaintTraverse );

	return TRUE;
}

BOOL WINAPI DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls( hModule );
		CreateThread( nullptr, 0, static_cast< LPTHREAD_START_ROUTINE >( Init ), nullptr, 0, nullptr );
		break;

		case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
