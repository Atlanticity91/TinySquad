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
 * @creation : 13/01/2024
 * @version  : 2024.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
#define TINY_ENGINE_NAME "TinyEngine"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
tli_implementfn( TinyLua::Engine::CreateEntity ) {
	return 0;
}

tli_implementfn( TinyLua::Engine::GetEntity ) {
	if ( 
		lua_islightuserdata( context, tli_param_one ) &&
		lua_isstring( context, tli_param_two )
	) {
		auto* game = tli_get_game( tli_param_one );
		auto name  = tiny_string{ lua_tostring( context, tli_param_two ) };

		if ( game && game->GetECS( ).FindEntity( name ) ) 
			Entity::Create( context, tiny_hash{ name } );
	} else
		lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Engine::GetEntities ) {
	return 0;
}

tli_implementfn( TinyLua::Engine::GetEntitiesFlags ) {
	return 0;
}

tli_implementfn( TinyLua::Engine::GetEntitiesComps ) {
	return 0;
}

tli_implementfn( TinyLua::Engine::KillEntity ) { 
	return 0; 
}

tli_implementfn( TinyLua::Engine::KillEntities ) {
	return 0;
}

tli_implementfn( TinyLua::Engine::KillEntitiesFlags ) {
	return 0;
}

tli_implementfn( TinyLua::Engine::KillEntitiesComps ) {
	return 0;
}

tli_implementfn( TinyLua::Engine::LoadAsset ) {
	auto state = false;

	if (
		lua_islightuserdata( context, tli_param_one ) &&
		lua_isstring( context, tli_param_two )
	) {
		auto* game = tli_get_game( tli_param_one );
		auto name = tiny_string{ lua_tostring( context, tli_param_two ) };

		if ( game )
			state = game->GetAssets( ).Load( game, name );
	}

	lua_pushboolean( context, state );

	return 1;
}

tli_implementfn( TinyLua::Engine::HasAsset ) {
	return 0;
}

void TinyLua::Engine::Register( TinyLuaContext& context ) {
	tli_create( TINY_ENGINE_NAME );

	tli_createfn( "create_entity", CreateEntity );
	tli_createfn( "get_entity", GetEntity );
	tli_createfn( "get_entities", GetEntities );
	tli_createfn( "get_entities_flags", GetEntitiesFlags );
	tli_createfn( "get_entities_comps", GetEntitiesComps );
	tli_createfn( "kill_entity", KillEntity );
	tli_createfn( "kill_entities", KillEntities ); 
	tli_createfn( "kill_entities_flags", KillEntitiesFlags );
	tli_createfn( "kill_entities_comps", KillEntitiesComps );
	tli_createfn( "load_asset", LoadAsset );
	tli_createfn( "has_asset", HasAsset );
}
