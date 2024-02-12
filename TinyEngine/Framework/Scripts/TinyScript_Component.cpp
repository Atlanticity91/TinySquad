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
	_pre_tick{ },
	_post_tick{ }
{ }

TinyScript& TinyScript::SetPreTick(
	TinyScriptManager& scripts,
	const tiny_string& function
) {
	_pre_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPreTick(
	TinyScriptManager& scripts,
	const tiny_string& script,
	const tiny_string& function
) {
	_pre_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPreTick( const tiny_string& function ) {
	_pre_tick.Type	   = TS_TYPE_NATIVE;
	_pre_tick.Function = function;

	return tiny_self;
}

TinyScript& TinyScript::SetPostTick(
	TinyScriptManager& scripts,
	const tiny_string& function
) {
	_post_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPostTick(
	TinyScriptManager& scripts,
	const tiny_string& script,
	const tiny_string& function
) {
	_post_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPostTick( const tiny_string& function ) {
	_post_tick.Type     = TS_TYPE_NATIVE;
	_post_tick.Function = function;

	return tiny_self;
}

void TinyScript::DisplayWidget(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) {
	TinyComponent::DisplayWidget( game, engine, toolbox );

	TinyImGui::EndVars( );

	DisplayMeta( game, "Pre Tick", _pre_tick );
	DisplayMeta( game, "Post Tick", _post_tick );

	TinyImGui::BeginVars( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyScript::DisplayMeta( 
	TinyGame* game, 
	c_string label, 
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

				_is_active = _is_active && functions.Index > 0;
			}
		} else {
			auto& toolbox = game->GetToolbox( );
			auto& lua	  = game->GetScripts( );

			toolbox.DisplayAsset( game, "Module", metadata.Asset );

			auto asset_state = metadata.Asset.GetIsValid( );

			ImGui::BeginDisabled( !asset_state );

			auto* lua_module = tiny_cast( lua.GetAsset( metadata.Asset ), TinyScriptLua* );

			if ( lua_module ) {
				auto functions = TinyImGui::DropdownContext{ lua_module->GetFunctions( ), metadata.Function };

				if ( TinyImGui::Dropdown( "Function", functions ) ) {
					metadata.Function = functions.Values[ functions.Index ];

					_is_active = _is_active && functions.Index > 0;
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
	return GetIsActive( ) && _pre_tick.Function.is_valid( ); 
}

bool TinyScript::GetHasPostTick( ) const { 
	return GetIsActive( ) && _post_tick.Function.is_valid( );
}

TinyScriptMetadata& TinyScript::GetPreTick( ) { return _pre_tick; }

TinyScriptMetadata& TinyScript::GetPostTick( ) { return _post_tick; }
