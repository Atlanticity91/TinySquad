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
 * @creation : 17/12/2023
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
TinyScript::TinyScript( ) 
	: TinyScript{ TINY_NO_ENTITY }
{ }

TinyScript::TinyScript( const tiny_hash entity_hash )
	: TinyComponent{ entity_hash },
	m_pre_tick{ },
	m_post_tick{ }
{ }

TinyScript& TinyScript::SetPreTick(
	TinyScriptManager& scripts,
	const tiny_string& function
) {
	m_pre_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPreTick(
	TinyScriptManager& scripts,
	const tiny_string& script,
	const tiny_string& function
) {
	m_pre_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPreTick( const tiny_string& function ) {
	m_pre_tick.Type	   = TS_TYPE_NATIVE;
	m_pre_tick.Function = function;

	return tiny_self;
}

TinyScript& TinyScript::SetPostTick(
	TinyScriptManager& scripts,
	const tiny_string& function
) {
	m_post_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPostTick(
	TinyScriptManager& scripts,
	const tiny_string& script,
	const tiny_string& function
) {
	m_post_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPostTick( const tiny_string& function ) {
	m_post_tick.Type     = TS_TYPE_NATIVE;
	m_post_tick.Function = function;

	return tiny_self;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void  TinyScript::OnTickWidget(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	TinyGame* game
) {
	TinyImGui::EndVars( );

	DisplayMeta( game, "Pre Tick", m_pre_tick );
	DisplayMeta( game, "Post Tick", m_post_tick );

	TinyImGui::BeginVars( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyScript::DisplayMeta( 
	TinyGame* game, 
	native_string label, 
	TinyScriptMetadata& metadata 
) {
	auto is_open = ImGui::TreeNode( label );

	if ( is_open ) {
		TinyImGui::BeginVars( );

		auto types = TinyImGui::DropdownContext{ metadata.Type, { "Native", "Lua" } };

		if ( TinyImGui::Dropdown( "Type", types ) ) {
			metadata.Type	  = tiny_cast( types.Index, TinyScriptTypes );
			metadata.Function = "";
		}

		if ( metadata.Type == TS_TYPE_NATIVE ) {
			auto& natives  = game->GetNatives( );
			auto functions = TinyImGui::DropdownContext{ natives.GetList( ), metadata.Function };

			if ( TinyImGui::Dropdown( "Function", functions ) ) {
				metadata.Function = functions.Values[ functions.Index ];

				m_is_active = m_is_active && functions.Index > 0;
			}
		} else {
			auto& lua = game->GetScripts( );

			TinyImGui::Asset( game, "Module", metadata.Asset );

			auto asset_state = metadata.Asset.GetIsValid( );

			ImGui::BeginDisabled( !asset_state );

			auto* lua_module = tiny_cast( lua.GetAsset( metadata.Asset.Hash ), TinyScriptLua* );

			if ( lua_module ) {
				auto functions = TinyImGui::DropdownContext{ lua_module->GetFunctions( ), metadata.Function };

				if ( TinyImGui::Dropdown( "Function", functions ) ) {
					metadata.Function = functions.Values[ functions.Index ];

					m_is_active = m_is_active && functions.Index > 0;
				}
			} else {
				auto functions = TinyImGui::DropdownContext{ };

				TinyImGui::Dropdown( "Function", functions );
			}

			ImGui::EndDisabled( );
		}

		TinyImGui::EndVars( );

		ImGui::TreePop( );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyScript::GetHasPreTick( ) const { 
	return GetIsActive( ) && m_pre_tick.Function.get_is_valid( ); 
}

bool TinyScript::GetHasPostTick( ) const { 
	return GetIsActive( ) && m_post_tick.Function.get_is_valid( );
}

TinyScriptMetadata& TinyScript::GetPreTick( ) { return m_pre_tick; }

TinyScriptMetadata& TinyScript::GetPostTick( ) { return m_post_tick; }
