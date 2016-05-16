#include "VFTHook.hpp"

std::unique_ptr<VFTHook> g_pPanelHook;

VFTHook::VFTHook ( void*** class_ )
{
	if ( !class_ )
		Dispose ( );

	m_class = class_;

	if ( !*m_class )
		Dispose ( );

	m_originalTable = *m_class;
	m_functionNumber = GetFunctionNumber ( );

	if ( m_functionNumber <= 0 )
		Dispose ( );

	m_replaceTable = new void* [ m_functionNumber ];

	if ( !m_replaceTable )
		Dispose ( );

	memcpy_s ( m_replaceTable, sizeof ( void* ) * m_functionNumber, m_originalTable, sizeof ( void* ) * m_functionNumber );

	printf_s ( "m_class = %p\n", m_class );
	printf_s ( "m_originalTable = %p\n", m_originalTable );
	printf_s ( "m_functionNumber = %d\n", m_functionNumber );
	printf_s ( "m_replaceTable: %p\n", m_replaceTable );

	*m_class = m_replaceTable;
}

VFTHook::~VFTHook ( )
{
	if ( *m_class == m_replaceTable )
		*m_class = m_originalTable;

	if ( m_replaceTable )
	{
		delete m_replaceTable;
		m_replaceTable = nullptr;
	}
}

size_t VFTHook::GetFunctionNumber ( ) const
{
	size_t counter = 0;
	while ( m_originalTable [ counter ] )
		counter++;

	return counter;
}

void VFTHook::Dispose ( ) const
{
	if ( *m_class == m_replaceTable )
		*m_class = m_originalTable;

	if ( m_replaceTable )
	{
		delete m_replaceTable;
		m_replaceTable;
	}

	delete this;
}
