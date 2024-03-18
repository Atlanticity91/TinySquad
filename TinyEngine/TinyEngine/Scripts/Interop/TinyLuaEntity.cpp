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
 * @creation : 12/01/2024
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
#define TINY_ENTITY_NAME "TinyEntity"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
tli_implementfn( TinyLua::Entity::New ) {
	Create( context, tiny_cast( 0, lua_Integer ) );

	return 0;
}

tli_implementfn( TinyLua::Entity::Delete ) { return 0; }

tli_implementfn( TinyLua::Entity::Kill ) {
	if ( 
		lua_istable( context, tli_param_one ) && 
		lua_islightuserdata( context, tli_param_two ) 
	) {
		auto hash  = Component::GetHash( context, tli_param_one );
		auto* game = tli_get_game( tli_param_two );

		if ( hash && game ) 
			game->GetECS( ).Kill( game, hash );
	}

	return 1;
}

tli_implementfn( TinyLua::Entity::AddComp ) {
	auto state = false;

	if ( 
		lua_istable( context, tli_param_one )		  &&
		lua_islightuserdata( context, tli_param_two ) &&
		lua_isstring( context, tli_param_three )
	) {
		auto hash  = Component::GetHash( context, tli_param_one );
		auto* game = tli_get_game( tli_param_two );
		
		if ( hash && game ) {
			auto comp_name = tiny_string{ lua_tostring( context, tli_param_three ) };

			state = game->GetECS( ).Append( game, hash, comp_name ) != nullptr;
		}
	}
	
	lua_pushboolean( context, state );

	return 1;
}

tli_implementfn( TinyLua::Entity::RemComp ) {
	if (
		lua_istable( context, tli_param_one )		  &&
		lua_islightuserdata( context, tli_param_two ) &&
		lua_isstring( context, tli_param_three )
	) {
		auto hash  = Component::GetHash( context, tli_param_one );
		auto* game = tli_get_game( tli_param_two );

		if ( hash && game ) {
			auto comp_name = tiny_string{ lua_tostring( context, tli_param_three ) };

			game->GetECS( ).Remove( game, hash, comp_name );
		}
	}

	return 0;
}

tli_implementfn( TinyLua::Entity::HasComp ) {
	auto state = false;

	if (
		lua_istable( context, tli_param_one ) &&
		lua_islightuserdata( context, tli_param_two ) &&
		lua_isstring( context, tli_param_three )
	) {
		auto hash  = Component::GetHash( context, tli_param_one );
		auto* game = tli_get_game( tli_param_two );

		if ( hash && game ) {
			auto comp_name = tiny_string{ lua_tostring( context, tli_param_three ) };

			state = game->GetECS( ).GetHasComponent( hash, comp_name );
		}
	}

	lua_pushboolean( context, state );

	return 1;
}

tli_implementfn( TinyLua::Entity::GetComp ) {
	lua_pushboolean( context, false );

	return 1;
}

tli_implementfn( TinyLua::Entity::AddFlag ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_islightuserdata( context, tli_param_two ) &&
		lua_isinteger( context, tli_param_three )
	) {
		auto hash  = Component::GetHash( context, tli_param_one );
		auto* game = tli_get_game( tli_param_two );

		if ( hash && game ) {
			auto flag = tiny_cast( lua_tointeger( context, tli_param_three ), tiny_uint );

			game->GetECS( ).AddFlag( hash, flag );
		}
	}

	return 0;
}

tli_implementfn( TinyLua::Entity::RemFlag ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_islightuserdata( context, tli_param_two ) &&
		lua_isinteger( context, tli_param_three )
	) {
		auto hash  = Component::GetHash( context, tli_param_one );
		auto* game = tli_get_game( tli_param_two );

		if ( hash && game ) {
			auto flag = tiny_cast( lua_tointeger( context, tli_param_three ), tiny_uint );

			game->GetECS( ).DeleteFlag( hash, flag );
		}
	}

	return 0;
}

tli_implementfn( TinyLua::Entity::HasFlag ) {
	auto state = false;

	if (
		lua_istable( context, tli_param_one ) &&
		lua_islightuserdata( context, tli_param_two ) &&
		lua_isinteger( context, tli_param_three )
	) {
		auto hash  = Component::GetHash( context, tli_param_one );
		auto* game = tli_get_game( tli_param_two );

		if ( hash && game ) {
			auto flag = tiny_cast( lua_tointeger( context, tli_param_three ), tiny_uint );

			state = game->GetECS( ).GetHasFlag( hash, flag );
		}
	}

	lua_pushboolean( context, state );

	return 1;
}

tli_implementfn( TinyLua::Entity::Attach ) {
	return 0;
}

tli_implementfn( TinyLua::Entity::Detach ) {
	return 0;
}

tli_implementfn( TinyLua::Entity::HasParent ) {
	auto state = false;

	if (
		lua_istable( context, tli_param_one ) &&
		lua_islightuserdata( context, tli_param_two )
	) {
		auto hash  = Component::GetHash( context, tli_param_one );
		auto* game = tli_get_game( tli_param_two );

		if ( hash && game )
			state = game->GetECS( ).GetHasParent( hash );
	}

	lua_pushboolean( context, state );

	return 1;
}

tli_implementfn( TinyLua::Entity::GetParent ) {
	return 0;
}

tli_implementfn( TinyLua::Entity::ToString ) {
	if ( lua_istable( context, tli_self ) ) {
		auto hash = lua_Integer{ };

		tli_get_field( tli_self, "hash", hash );

		lua_pushfstring( context, "[ %d ]", tiny_cast( hash, tiny_uint ) );
	}

	return 1;
}

void TinyLua::Entity::Create( TinyLuaContext& context, const tiny_hash entity_hash ) {
	Create( context, tiny_cast( entity_hash.get( ), lua_Integer ) );
}

void TinyLua::Entity::Create( lua_State* context, lua_Integer hash ) {
	tli_create_new(
		TINY_ENTITY_NAME,
		tli_create_field( "hash", hash );
	);
}

void TinyLua::Entity::Register( TinyLuaContext& context ) {
	tli_create( TINY_ENTITY_NAME );

	tli_createfn( "new", New );

	tli_createfn( "add_comp", AddComp );
	tli_createfn( "rem_comp", RemComp );
	tli_createfn( "has_comp", HasComp );
	tli_createfn( "get_comp", GetComp );

	tli_createfn( "add_flag", AddFlag );
	tli_createfn( "rem_flag", RemFlag );
	tli_createfn( "has_flag", HasFlag );

	tli_createfn( "attach", Attach );
	tli_createfn( "detach", Detach );
	tli_createfn( "has_parent", HasParent );
	tli_createfn( "get_parent", GetParent );

	tli_createfn( "to_string", ToString );

	if ( tli_createmeta( TINY_ENTITY_NAME ) ) {
		tli_createop( "__gc", Delete );

		tli_createop( "__tostring", ToString );
	}
}
