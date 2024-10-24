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
TinyImGuiManager::TinyImGuiManager( )
	: m_context{ },
	m_backend{ },
	m_font_manager{ },
	m_theme_manager{ }, 
	m_window_manager{ }
{ }

bool TinyImGuiManager::Initialize(
	TinyWindow& window,
	TinyGraphicManager& graphics,
	const TinyImGuiSpecification& specification,
	native_pointer user_data
) {
	auto state = m_context.Create( graphics ) &&
				 m_backend.Create( window, graphics, specification );
	
	if ( state ) {
		m_font_manager.Initialize( );
		m_theme_manager.Initialize( );
	}

	return state;
}

void TinyImGuiManager::Show( ) { m_context.Show( ); }

void TinyImGuiManager::Hide( ) { m_context.Hide( ); }

void TinyImGuiManager::Toggle( ) { m_context.Toggle( ); }

void TinyImGuiManager::ShowExemples( ) { m_window_manager.ShowExemples( ); }

void TinyImGuiManager::HideExemples( ) { m_window_manager.HideExemples( ); }

bool TinyImGuiManager::LoadFont(
	TinyFilesystem& filesystem,
	TinyGraphicManager& graphics,
	const TinyImGuiFont& font
) {
	return m_font_manager.LoadFont( filesystem, graphics, font );
}

bool TinyImGuiManager::LoadFonts(
	TinyFilesystem& filesystem,
	TinyGraphicManager& graphics,
	tiny_init<TinyImGuiFont> fonts
) {
	return m_font_manager.LoadFonts( filesystem, graphics, fonts );
}

bool TinyImGuiManager::AddFont(
	const tiny_string& alias,
	tiny_int length,
	const tiny_uint* data,
	float size
) {
	return m_font_manager.AddFont( alias, length, data, size );
}

bool TinyImGuiManager::CreateFont(
	const tiny_string& name,
	float size,
	tiny_init<TinyImGuiFontEmbedded> fonts
) {
	return m_font_manager.CreateFont( name, size, fonts );
}

void TinyImGuiManager::SetFont( const tiny_string& name ) {
	m_font_manager.SetFont( name );
}

void TinyImGuiManager::ShowWindow( const tiny_string& alias, native_pointer user_data ) {
	m_window_manager.Show( alias, user_data );
}

void TinyImGuiManager::HideWindow( const tiny_string& alias, native_pointer user_data ) {
	m_window_manager.Hide( alias, user_data );
}

void TinyImGuiManager::ToggleWindow( const tiny_string& alias, native_pointer user_data ) {
	m_window_manager.Toggle( alias, user_data );
}

void TinyImGuiManager::DeleteWindow( const tiny_string& alias, native_pointer user_data ) {
	m_window_manager.Delete( alias, user_data );
}

void TinyImGuiManager::DockSpace( const tiny_string& name ) {
	auto* dockspace_name = name.as_string( );
	auto dockspace_id    = ImGui::GetID( dockspace_name );

	ImGui::DockSpace( dockspace_id );
}

void TinyImGuiManager::Tick(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	native_pointer user_data
) {
	if ( m_context.GetIsVisible( ) ) {
		ImGui::SetCurrentContext( m_context );

		m_backend.Prepare( );
		m_context.Prepare( );
		m_window_manager.Tick( graphics, inputs, user_data );
		m_backend.Flush( graphics );
	}
}

void TinyImGuiManager::Terminate(
	TinyGraphicManager& graphics,
	native_pointer user_data
) {
	ImGui::SetCurrentContext( m_context );

	m_window_manager.Terminate( user_data );
	m_backend.Terminate( graphics );
	m_context.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyImGuiManager::GetIsVisible( ) const { return m_context.GetIsVisible( ); }

bool TinyImGuiManager::GetIsExemplesVisivle( ) const { 
	return m_window_manager.GetIsExemplesVisivle( ); 
}

TinyImGuiContext& TinyImGuiManager::GetContext( ) { return m_context; }

TinyImGuiBackend& TinyImGuiManager::GetBackend( ) { return m_backend; }

TinyImGuiFontManager& TinyImGuiManager::GetFontManager( ) { return m_font_manager; }

TinyImGuiTheme& TinyImGuiManager::GetTheme( ) { return m_theme_manager; }

TinyImGuiWindowManager& TinyImGuiManager::GetWindowManager( ) { return m_window_manager; }

bool TinyImGuiManager::GetHasWindow( const tiny_string& alias ) const {
	return m_window_manager.GetHas( alias );
}

bool TinyImGuiManager::GetWindowExist( const tiny_uint window_id ) const {
	return m_window_manager.GetExist( window_id );
}

TinyImGuiWindow* TinyImGuiManager::GetWindow( const tiny_string& alias ) const {
	return m_window_manager.Get( alias );
}

TinyImGuiWindow* TinyImGuiManager::GetWindow( const tiny_uint window_id ) const {
	return m_window_manager.At( window_id );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyImGuiManager::operator ImGuiContext* ( ) const { return m_context.Get( ); }
