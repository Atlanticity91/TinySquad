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
 * @creation : 28/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolWindow::TinyToolWindow( const tiny_string& name, bool is_visible )
	: m_is_visible{ is_visible },
	m_name{ name }
{ }

void TinyToolWindow::Show( ) { m_is_visible = true; }

void TinyToolWindow::Hide( ) { m_is_visible = false; }

void TinyToolWindow::Tick( TinyGame* game, TinyToolbox& toolbox ) {
	auto* name = m_name.as_string( );

	if ( ImGui::Begin( name, tiny_rvalue( m_is_visible ) ) ) {
		OnRender( game, toolbox );

		ImGui::End( );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyToolWindow::GetIsVisible( ) const { return m_is_visible; }

const tiny_string& TinyToolWindow::GetName( ) const { return m_name; }
