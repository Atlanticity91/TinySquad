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
TinyImGuiContext::TinyImGuiContext( ) 
	: m_is_visible{ true },
	m_context{ nullptr }
{ }

bool TinyImGuiContext::Create( TinyGraphicManager& graphics ) {
	IMGUI_CHECKVERSION( );

	m_context = ImGui::CreateContext( );

	auto& io = ImGui::GetIO( );

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	return m_context != nullptr;
}

void TinyImGuiContext::Show( ) { m_is_visible = true; }

void TinyImGuiContext::Hide( ) { m_is_visible = false; }

void TinyImGuiContext::Toggle( ) { m_is_visible = !m_is_visible; }

void TinyImGuiContext::Prepare( ) { ImGui::NewFrame( ); }

void TinyImGuiContext::Terminate( ) {
	if ( m_context != nullptr ) 
		ImGui::DestroyContext( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyImGuiContext::GetIsVisible( ) const { return  m_is_visible; }

ImGuiContext* TinyImGuiContext::Get( ) const { return m_context; }

TinyImGuiContext::operator ImGuiContext* ( ) const { return Get( ); }
