#pragma once

#include <Windows.h>
#include <memory>

class VFTHook
{
public:
	VFTHook ( void*** class_ );
	~VFTHook ( );

	template <typename T>
	T Hook ( size_t index, void* new_ );

private:
	size_t GetFunctionNumber ( ) const;
	void Dispose ( ) const;

	void*** m_class;
	void** m_originalTable;
	void** m_replaceTable;
	size_t m_functionNumber;
};

template <typename T>
T VFTHook::Hook ( size_t index, void* new_ )
{
	m_replaceTable [ index ] = new_;
	return ( T ) m_originalTable [ index ];
}

extern std::unique_ptr<VFTHook> g_pPanelHook;