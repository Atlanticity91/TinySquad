/******************************************************************************************
 *
 *   _______ _             __  __ _
 *  |__   __(_)           |  \/  (_)
 *     | |   _ _ __  _   _| \  / |_  ___ _ __ ___
 *     | |  | | '_ \| | | | |\/| | |/ __| '__/ _ \
 *     | |  | | | | | |_| | |  | | | (__| | | (_) |
 *     |_|  |_|_| |_|\__, |_|  |_|_|\___|_|  \___/
 *                    __/ |
 *	                 |___/
 *
 * @author   : ALVES Quentin
 * @creation : 29/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyImGuiWindowManager::TinyImGuiWindowManager( )
	: m_show_exemples{ false },
	m_windows{ }
{ }

void TinyImGuiWindowManager::ShowExemples( ) { m_show_exemples = true; }

void TinyImGuiWindowManager::HideExemples( ) { m_show_exemples = false; }

void TinyImGuiWindowManager::Show( const tiny_string& alias, native_pointer user_data ) {
	auto* window = Get( alias );

	if ( window )
		window->Show( user_data );
}

void TinyImGuiWindowManager::Hide( const tiny_string& alias, native_pointer user_data ) {
	auto* window = Get( alias );

	if ( window )
		window->Hide( user_data );
}

void TinyImGuiWindowManager::Toggle( const tiny_string& alias, native_pointer user_data ) {
	auto* window = Get( alias );

	if ( window )
		window->Toggle( user_data );
}

void TinyImGuiWindowManager::Delete( const tiny_string& alias, native_pointer user_data ) {
	auto window_id = tiny_cast( 0, tiny_uint );
	auto* window   = tiny_cast( nullptr, TinyImGuiWindow* );

	if ( m_windows.find( alias, window_id ) ) {
		window = m_windows.at( window_id );

		window->Delete( user_data );

		delete window;

		m_windows.erase( window_id );
	}
}

void TinyImGuiWindowManager::Tick(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	native_pointer user_data
) {
	ImGui::ShowDemoWindow( tiny_rvalue( m_show_exemples ) );

	for ( auto& pair : m_windows ) {
		auto* window = pair.Data;

		if ( window->GetIsVisible( ) )
			window->Tick( graphics, inputs, user_data );
	}
}

void TinyImGuiWindowManager::Terminate( native_pointer user_data ) {
	for ( auto& pair : m_windows ) {
		auto* window = pair.Data;

		window->Delete( user_data );

		delete window;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyImGuiWindowManager::GetIsExemplesVisivle( ) const { return m_show_exemples; }

bool TinyImGuiWindowManager::GetHas( const tiny_string& alias ) const {
	return m_windows.find( alias );
}

bool TinyImGuiWindowManager::GetExist( const tiny_uint window_id ) const { 
	return window_id < m_windows.size( ) && m_windows[ window_id ] != nullptr;
}

TinyImGuiWindow* TinyImGuiWindowManager::Get( const tiny_string& alias ) const {
	auto window_id = tiny_cast( 0, tiny_uint );
	auto* window   = tiny_cast( nullptr, TinyImGuiWindow* );

	if ( m_windows.find( alias, window_id ) )
		window = tiny_cast( tiny_rvalue( m_windows.at( window_id ) ), TinyImGuiWindow* );

	return window;
}

TinyImGuiWindow* TinyImGuiWindowManager::At( const tiny_uint window_id ) const {
	auto* window = tiny_cast( nullptr, TinyImGuiWindow* );

	if ( window_id < m_windows.size( ) )
		window = m_windows[ window_id ];

	return window;
}
