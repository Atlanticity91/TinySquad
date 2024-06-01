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

#define _RegisterTool( TYPE, ID )\
	Register< TYPE, ID >( game, toolbox );

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolManager::TinyToolManager( ) 
	: m_current{ 0 },
	m_categories{ }
{ }

bool TinyToolManager::Initialize( TinyGame* game, TinyToolbox& toolbox ) {
	_RegisterTool( TinyToolCommon, TT_CATEGORY_COMMON );
	_RegisterTool( TinyToolInputs, TT_CATEGORY_INPUTS );
	_RegisterTool( TinyToolRender, TT_CATEGORY_RENDER );
	_RegisterTool( TinyToolContent, TT_CATEGORY_CONTENT );
	_RegisterTool( TinyToolScene, TT_CATEGORY_SCENE );
	_RegisterTool( TinyToolWorld, TT_CATEGORY_WORLD );

	return true; 
}

void TinyToolManager::Clear( ) { m_categories.clear( ); }

void TinyToolManager::Tick( TinyGame* game, TinyToolbox& toolbox ) {
	if ( m_categories.size( ) > 0 ) {
		if ( ImGui::Begin( "Tiny Editor", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar ) ) {
			auto tab_id = tiny_cast( 0, tiny_uint );

			if ( ImGui::BeginTabBar( "__tiny_editor_tabs__", ImGuiTabBarFlags_None ) ) {
				for ( auto& category : m_categories ) {
					if ( !category->Tick( game, toolbox ) )
						tab_id += 1;
					else
						m_current = tab_id;
				}

				ImGui::EndTabBar( );
			}
		}

		ImGui::End( );
	}
}

void TinyToolManager::Terminate( TinyGame* game ) {
	for ( auto& category : m_categories ) {
		category->Terminate( game );

		delete category;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolCategory* TinyToolManager::GetCurrent( ) { return GetCategory( m_current ); }

TinyToolCategory* TinyToolManager::GetCategory( tiny_uint category ) {
	auto* value = tiny_cast( nullptr, TinyToolCategory* );

	if ( category < m_categories.size( ) )
		value = m_categories[ category ];

	return value;
}
