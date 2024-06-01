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
 * @creation : 21/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolAssetEditor::TinyToolAssetEditor( const tiny_string& name )
	: TinyToolAssetEditor{ name, { .0f, .0f } }
{ }

TinyToolAssetEditor::TinyToolAssetEditor( const tiny_string& name, const ImVec2& min_size )
	: m_in_use{ false },
	m_min_size{ min_size },
	m_name{ name },
	m_asset{ },
	m_asset_name{ "" }
{ }

bool TinyToolAssetEditor::Open( TinyGame* game, const tiny_string& name, TinyAssetHandle& asset ) {
	auto& assets = game->GetAssets( );

	if ( m_in_use ) {
		Close( game );
		OnClose( game, assets );
	}

	auto state = asset.GetIsValid( );

	if ( state ) {
		m_in_use	 = true;
		m_asset		 = asset;
		m_asset_name = name;

		auto* m_asset = assets.GetAsset( asset );

		state = m_asset && OnOpen( game, name, m_asset );
	}

	return state;
}

void TinyToolAssetEditor::Tick( TinyGame* game, TinyAssetManager& assets ) {
	if ( m_in_use ) {
		auto* name_str = m_name.get( );
		auto win_size  = TinyImGui::ScopeVars{ ImGuiStyleVar_WindowMinSize, m_min_size };

		if ( ImGui::Begin( name_str, tiny_rvalue( m_in_use ), ImGuiWindowFlags_AlwaysVerticalScrollbar ) )
			OnTick( game, assets );

		if ( !m_in_use )
			Close( game );

		ImGui::End( );
	} else if ( m_asset )
		OnClose( game, assets );
}

void TinyToolAssetEditor::Close( TinyGame* game ) {
	Save( game );

	m_in_use = false;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolAssetEditor::OnClose( TinyGame* game, TinyAssetManager& assets ) {
	assets.Release( game, m_asset );
}
