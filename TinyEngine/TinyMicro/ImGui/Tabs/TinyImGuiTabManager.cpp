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
TinyImGuiTabManager::TinyImGuiTabManager( )
	: TinyImGuiTabManager{  "", false, "_", IMGUI_NO_FLAGS }
{ }

TinyImGuiTabManager::TinyImGuiTabManager( 
	const tiny_string& name,
	const tiny_string& tab_alias,
	ImGuiTabBarFlags tab_flags
)
	: TinyImGuiTabManager{ name, true, tab_alias, tab_flags }
{ }

TinyImGuiTabManager::TinyImGuiTabManager(
	const tiny_string& name,
	bool is_visible,
	const tiny_string& tab_alias,
	ImGuiTabBarFlags tab_flags
)
	: TinyImGuiWindow{ name, is_visible },
	m_tab_alias{ tab_alias },
	m_tab_flags{ tab_flags },
	m_current{ 0 },
	m_tabs{ }
{ }

void TinyImGuiTabManager::RemoveTab( const tiny_string& name ) {
	auto tab_id = tiny_cast( 0, tiny_uint );
	auto* tab   = tiny_cast( nullptr, TinyImGuiTab* );

	if ( m_tabs.find( name, tab_id ) ) {
		delete tab;

		m_tabs.erase( tab_id );
	}
}

void TinyImGuiTabManager::Delete( native_pointer user_data ) {
	for ( auto& tab : m_tabs )
		delete tab.Data;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyImGuiTabManager::OnTick(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	native_pointer user_data
) {
	auto* tab_name = m_tab_alias.as_string( );

	if ( ImGui::BeginTabBar( tab_name, m_tab_flags ) ) {
		auto tab_id = tiny_cast( 0, tiny_uint );

		for ( auto& pair : m_tabs ) {
			if ( !pair.Data->Tick( graphics, inputs, user_data ) )
				tab_id += 1;
			else
				m_current = tab_id;
		}

		ImGui::EndTabBar( );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyImGuiTabManager::GetCurrentTabID( ) const { return m_current; }

bool TinyImGuiTabManager::GetHasTab( const tiny_string& name ) const {
	return m_tabs.find( name );
}

TinyImGuiTab* TinyImGuiTabManager::GetTab( const tiny_string& name ) {
	auto tab_id = tiny_cast( 0, tiny_uint );
	auto* tab   = tiny_cast( nullptr, TinyImGuiTab* );

	if ( m_tabs.find( name, tab_id ) )
		tab = tiny_cast( tiny_rvalue( m_tabs.at( tab_id ) ), TinyImGuiTab* );

	return tab;
}
