#pragma once

#include <Windows.h>
#include <iostream>
#include <memory>

class Color;

class Drawing
{
public:
	Drawing( );
	~Drawing( ) = default;

	void DrawString( int x, int y, const Color& col, wchar_t* text ) const;
	void DrawString( int x, int y, const Color& col, bool center, const char* text, ... );
	void DrawRect( int x, int y, int w, int h, const Color& col );
	void DrawOutlinedRect( int x, int y, int w, int h, const Color& col );
	void DrawLine( int x, int y, int x2, int y2, const Color& col );
	void DrawCornerBox( int x, int y, int w, int h, int cx, int cy, const Color& col );

private:
	unsigned long m_font;
};

extern std::unique_ptr<Drawing> g_pDrawing;