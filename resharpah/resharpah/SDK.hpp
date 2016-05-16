#pragma once

#include <Windows.h>
#include "dt_recv.h"

using tPaintTraverse = void( __thiscall* )( void*, unsigned int, bool, bool );
extern tPaintTraverse oPaintTraverse;

class IBaseClientDLL;
class IPanel;
class ISurface;

class Color
{
public:
	Color( ) : R( 0 ), G( 0 ), B( 0 ), A( 0 )
	{
	}

	Color( int r, int g, int b, int a ) : R( r ), G( g ), B( b ), A( a )
	{
	}

	Color( int r, int g, int b ) : R( r ), G( g ), B( b ), A( 255 )
	{
	}

	static Color White( ) { return Color( 255, 255, 255, 255 ); }
	static Color Black( ) { return Color( 0, 0, 0, 255 ); }
	static Color Red( ) { return Color( 255, 0, 0, 255 ); }
	static Color Green( ) { return Color( 0, 255, 0, 255 ); }
	static Color Blue( ) { return Color( 0, 0, 255, 255 ); }
	static Color Yellow( ) { return Color( 255, 255, 0, 255 ); }

	int r( ) { return R; }
	int g( ) { return G; }
	int b( ) { return B; }
	int a( ) { return A; }

	Color& operator = ( Color& c )
	{
		R = c.r( );
		G = c.g( );
		B = c.b( );
		A = c.a( );
		return *this;
	}

private:
	int R, G, B, A;
};
enum FontDrawType_t
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};
enum FontFlags_t
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

template <size_t index, typename ret>
ret GetVirtual( void* ecx )
{
	void** VFTable = *( void*** ) ecx;
	return ( ret ) VFTable [ index ];
}

class ClientClass
{
public:
	BYTE _chPadding [ 8 ];
	char* szName;
	RecvTable* rtTable;
	ClientClass* pNextClass;
	int iClassID;
};

class IBaseClientDLL
{
public:
	ClientClass* GetAllClasses( )
	{
		using tGetAllClasses = ClientClass*( __thiscall* )( void* );
		return GetVirtual<8, tGetAllClasses>( this )( this );
	}
};

class IPanel
{
public:
	const char* GetName( int panel )
	{
		using tGetName = const char*( __thiscall* )( void*, int );
		return GetVirtual<36, tGetName>( this )( this, panel );
	}
};

class ISurface
{
public:
	void DrawSetColor( const Color& col )
	{
		using tDrawSetColor = void( __thiscall* )( void*, Color );
		return GetVirtual<15, tDrawSetColor>( this )( this, col );
	}

	void DrawFilledRect( int x, int y, int w, int h )
	{
		using tDrawFilledRect = void( __thiscall* )( void*, int, int, int, int );
		return GetVirtual<16, tDrawFilledRect>( this )( this, x, y, w, h );
	}

	void DrawOutlinedRect( int x, int y, int w, int h )
	{
		using tDrawOutlinedRect = void( __thiscall* )( void*, int, int, int, int );
		return GetVirtual<18, tDrawOutlinedRect>( this )( this, x, y, w, h );
	}

	void DrawLine( int x, int y, int x2, int y2 )
	{
		using tDrawLine = void( __thiscall* )( void*, int, int, int, int );
		return GetVirtual<19, tDrawLine>( this )( this, x, y, x2, y2 );
	}

	void DrawSetTextFont( unsigned long index )
	{
		using tDrawSetTextFont = void( __thiscall* )( void*, unsigned long );
		return GetVirtual<23, tDrawSetTextFont>( this )( this, index );
	}

	void DrawSetTextColor( const Color& col )
	{
		using tDrawSetTextColor = void( __thiscall* )( void*, Color );
		return GetVirtual<25, tDrawSetTextColor>( this )( this, col );
	}

	void DrawSetTextPos( int x, int y )
	{
		using tDrawSetTextPos = void( __thiscall* )( void*, int, int );
		return GetVirtual<26, tDrawSetTextPos>( this )( this, x, y );
	}

	void DrawPrintText( wchar_t* text, int length, FontDrawType_t drawtype = FontDrawType_t::FONT_DRAW_DEFAULT )
	{
		using tDrawPrintText = void( __thiscall* )( void*, wchar_t*, int, FontDrawType_t );
		return GetVirtual<28, tDrawPrintText>( this )( this, text, length, drawtype );
	}

	unsigned long CreateCSFont( )
	{
		using tCreateCSFont = unsigned long( __thiscall* )( void* );
		return GetVirtual<71, tCreateCSFont>( this )( this );
	}

	bool SetFontGlyphSet( unsigned long font, const char* fontName, int tall, int weight, int blur, int scanlines, int flags, int rangeMin = 0, int rangeMax = 0 )
	{
		using tSetFontGlyphSet = bool( __thiscall* )( void*, unsigned long, const char*, int, int, int, int, int, int, int );
		return GetVirtual<72, tSetFontGlyphSet>( this )( this, font, fontName, tall, weight, blur, scanlines, flags, rangeMin, rangeMax );
	}

	bool AddCustomFontFile( const char* fontFileName )
	{
		using tAddCustomFontFile = bool( __thiscall* )( void*, const char* );
		return GetVirtual<73, tAddCustomFontFile>( this )( this, fontFileName );
	}

	bool GetTextSize( unsigned long font, const wchar_t* text, int& wide, int& tall )
	{
		using tGetTextSize = bool( __thiscall* )( void*, unsigned long, const wchar_t*, int&, int& );
		return GetVirtual<79, tGetTextSize>( this )( this, font, text, wide, tall );
	}

	void PlayCSSound( const char* fileName )
	{
		using tPlayCSSound = void( __thiscall* )( void*, const char* );
		return GetVirtual<82, tPlayCSSound>( this )( this, fileName );
	}
};