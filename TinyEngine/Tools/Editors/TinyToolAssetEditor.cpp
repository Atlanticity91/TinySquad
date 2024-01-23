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
	: _in_use{ false },
	_asset{ nullptr },
	_asset_name{ "" },
	_name{ name }
{ }

bool TinyToolAssetEditor::Open( TinyGame* game, const tiny_string& name, c_ptr asset ) {
	if ( asset ) {
		_in_use		= true;
		_asset		= asset;
		_asset_name = name;
	}

	return _asset && OnOpen( game, name, asset );
}

void TinyToolAssetEditor::Tick( TinyGame* game, TinyAssetManager& assets ) {
	if ( _in_use ) {
		auto* name_str = _name.as_chars( );

		if ( ImGui::Begin( name_str, tiny_rvalue( _in_use ), ImGuiWindowFlags_AlwaysVerticalScrollbar ) )
			OnTick( game, assets );

		if ( !_in_use )
			Close( game );

		ImGui::End( );
	}
}

void TinyToolAssetEditor::Close( TinyGame* game ) {
	auto& assets = game->GetAssets( );
	
	OnClose( game, assets );

	_in_use = false;
	_asset  = nullptr;
}
