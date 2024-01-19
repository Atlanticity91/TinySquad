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
 * @creation : 16/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolManager::TinyToolManager( ) 
	: _current{ 0 },
	_categories{ }
{ }

bool TinyToolManager::Initialize( TinyGame* game, TinyToolbox& toolbox ) {
	auto& engine = game->GetEngine( );

	Register<TinyToolCommon, TT_CATEGORY_COMMON>( game, engine, toolbox );
	Register<TinyToolRender, TT_CATEGORY_RENDER>( game, engine, toolbox );
	Register<TinyToolContent, TT_CATEGORY_CONTENT>( game, engine, toolbox );
	Register<TinyToolWorld, TT_CATEGORY_WORLD>( game, engine, toolbox );
	Register<TinyToolTerrain, TT_CATEGORY_TERRAIN>( game, engine, toolbox );

	return true; 
}

void TinyToolManager::Tick( TinyGame* game, TinyEngine& engine, TinyToolbox& toolbox ) {
	if ( ImGui::Begin( "Tiny Editor" ) ) {
		auto tab_id = tiny_cast( 0, tiny_uint );
		if ( ImGui::BeginTabBar( "__tiny_editor_tabs__", ImGuiTabBarFlags_None ) ) {
			for ( auto& category : _categories ) {
				if ( !category->Tick( game, engine, toolbox ) )
					tab_id += 1;
				else
					_current = tab_id;
			}

			ImGui::EndTabBar( );
		}
	}

	ImGui::End( );
}

void TinyToolManager::Terminate( TinyGame* game ) {
	auto& engine = game->GetEngine( );
	
	for ( auto& category : _categories ) {
		category->Terminate( game, engine );

		delete category;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolCategory* TinyToolManager::GetCurrent( ) { return GetCategory( _current ); }

TinyToolCategory* TinyToolManager::GetCategory( tiny_uint category ) {
	auto* value = tiny_cast( nullptr, TinyToolCategory* );

	if ( category < _categories.size( ) )
		value = _categories[ category ];

	return value;
}
