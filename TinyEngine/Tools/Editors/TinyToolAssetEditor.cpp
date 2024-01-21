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
	_name{ name }
{ }

void TinyToolAssetEditor::Close( ) {
	_in_use = false;
	_asset  = nullptr;

	OnClose( );
}

void TinyToolAssetEditor::Tick( TinyGame* game ) {
	auto* name_str = _name.as_chars( );

	if ( _in_use && ImGui::Begin( name_str, tiny_rvalue( _in_use ) ) ) {
		OnTick( game );

		ImGui::End( );
	}
}
