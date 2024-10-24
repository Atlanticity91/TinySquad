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
TinyImGuiWindow::TinyImGuiWindow( )
	: TinyImGuiWindow{ "", false, ImGuiWindowFlags_None } 
{ }

TinyImGuiWindow::TinyImGuiWindow( const tiny_string& name )
	: TinyImGuiWindow{ name, true, ImGuiWindowFlags_None }
{ }


TinyImGuiWindow::TinyImGuiWindow( const tiny_string& name, ImGuiWindowFlags flags )
	: TinyImGuiWindow{ name, true, flags }
{ }

TinyImGuiWindow::TinyImGuiWindow( const tiny_string& name, bool is_visible )
	: TinyImGuiWindow{ name, is_visible, ImGuiWindowFlags_None }
{ }

TinyImGuiWindow::TinyImGuiWindow( const tiny_string& name, bool is_visible, ImGuiWindowFlags flags )
	: m_is_visible{ is_visible },
	m_name{ name },
	m_flags{ flags }
{ }

void TinyImGuiWindow::AddFlag( ImGuiWindowFlags flag ) {
	if ( flag > ImGuiWindowFlags_None )
		m_flags |= flag;
}

void TinyImGuiWindow::DeleteFlag( ImGuiWindowFlags flag ) {
	if ( flag > ImGuiWindowFlags_None )
		m_flags ^= flag;
}

void TinyImGuiWindow::SetFlags( ImGuiWindowFlags flag ) { m_flags = flag; }

void TinyImGuiWindow::Show( native_pointer user_data ) { 
	m_is_visible = true;

	OnShow( user_data );
}

void TinyImGuiWindow::Hide( native_pointer user_data ) {
	m_is_visible = false; 
	
	OnHide( user_data );
}

void TinyImGuiWindow::Toggle( native_pointer user_data ) {
	m_is_visible = !m_is_visible;

	if ( m_is_visible )
		OnShow( user_data );
	else
		OnHide( user_data );
}

void TinyImGuiWindow::Tick(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	native_pointer user_data
) {
	auto* name = m_name.as_string( );

	if ( ImGui::Begin( name, tiny_rvalue( m_is_visible ), m_flags ) )
		OnTick( graphics, inputs, user_data );

	ImGui::End( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyImGuiWindow::GetIsVisible( ) const { return m_is_visible; }

const tiny_string TinyImGuiWindow::GetName( ) const { return m_name; }

bool TinyImGuiWindow::GetHasFlag( ImGuiWindowFlags flags ) const {
	return ( m_flags & flags ) == flags; 
}

ImGuiWindowFlags TinyImGuiWindow::GetFlags( ) const { return m_flags; }
