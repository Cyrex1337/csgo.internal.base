#include "Drawing.hpp"
#include "InterfaceManager.hpp"

std::unique_ptr<Drawing> g_pDrawing;

Drawing::Drawing( )
{
	m_font = Surface->CreateCSFont( );
	if ( !m_font )
		return;

	Surface->SetFontGlyphSet( m_font, "Tahoma", 12, 400, 0, 0, FONTFLAG_OUTLINE );
}

void Drawing::DrawString( int x, int y, const Color& col, wchar_t* text ) const
{
	if ( !text )
		return;

	Surface->DrawSetTextPos( x, y );
	Surface->DrawSetTextFont( m_font );
	Surface->DrawSetTextColor( col );
	Surface->DrawPrintText( text, wcslen( text ) );
}
