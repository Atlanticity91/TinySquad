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
 * @creation : 14/01/2024
 * @version  : 2024.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyLua::Transform2D::Convert( lua_State* context, TinyComponent* component ) {
	auto* tmp = tiny_cast( component, c_pointer );
	
	tli_create_new(
		TINY_TRANSFORM2D_NAME,
		tli_create_field( "value", tmp );
	);
}

tli_implementfn( TinyLua::Transform2D::Create ) {
	return Component::Create( context, TINY_TRANSFORM2D_NAME );
}

tli_implementfn( TinyLua::Transform2D::Destroy ) {
	auto* comp = Component::Get<TinyTransform2D>( context, tli_param_one );
	auto* game = tli_get_game( tli_param_two );

	if ( comp && game ) 
		game->GetECS( ).Remove( game, comp );

	return 0;
}

tli_implementfn( TinyLua::Transform2D::SetLocationX ) {
	return 0;
}

tli_implementfn( TinyLua::Transform2D::SetLocationY ) {
	return 0;
}

tli_implementfn( TinyLua::Transform2D::SetLocation ) {
	auto param_count = lua_gettop( context );
	auto* comp		 = Component::Get<TinyTransform2D>( context, tli_param_one );
	
	if ( comp ) {
		auto x = lua_Number{ };
		auto y = lua_Number{ };

		if (
			param_count == 2					  &&
			lua_istable( context, tli_param_one ) &&
			lua_istable( context, tli_param_two )
		) {
			tli_get_field( tli_param_two, "x", x );
			tli_get_field( tli_param_two, "y", y );
		} else if (
			param_count == 3					   &&
			lua_istable( context, tli_param_one )  &&
			lua_isnumber( context, tli_param_two ) &&
			lua_isnumber( context, tli_param_three )
		) {
			x = lua_tonumber( context, tli_param_two );
			y = lua_tonumber( context, tli_param_three );
		}

		comp->SetLocation( tiny_cast( x, float ), tiny_cast( y, float ) );
	}

	return 0;
}

tli_implementfn( TinyLua::Transform2D::SetRotation ) {
	auto* comp = Component::Get<TinyTransform2D>( context, tli_param_one );

	if ( comp && lua_isnumber( context, tli_param_two ) ) {
		auto value = lua_tonumber( context, tli_param_two );

		comp->SetRotation( tiny_cast( value, float ) );
	}

	return 0;
}

tli_implementfn( TinyLua::Transform2D::SetScaleX ) {
	return 0;
}

tli_implementfn( TinyLua::Transform2D::SetScaleY ) {
	return 0;
}

tli_implementfn( TinyLua::Transform2D::SetScale ) {
	return 0;
}

tli_implementfn( TinyLua::Transform2D::Set ) {
	auto param_count = lua_gettop( context );
	auto* comp = Component::Get<TinyTransform2D>( context, tli_param_one );

	if ( 
		comp									 &&
		lua_istable( context, tli_param_two )	 &&
		lua_isnumber( context, tli_param_three ) &&
		lua_istable( context, tli_param_four )
	) {
		auto x = lua_Number{ };
		auto y = lua_Number{ };
		
		tli_get_field( tli_param_two, "x", x );
		tli_get_field( tli_param_two, "y", y );

		comp->SetLocation( tiny_cast( x, float ), tiny_cast( y, float ) );
		
		x = lua_tonumber( context, tli_param_three );

		comp->SetRotation( tiny_cast( x, float ) );

		tli_get_field( tli_param_four, "x", x );
		tli_get_field( tli_param_four, "y", y );

		comp->SetScale( tiny_cast( x, float ), tiny_cast( y, float ) );
	}

	return 0;
}

tli_implementfn( TinyLua::Transform2D::MoveX ) {
	return 0;
}

tli_implementfn( TinyLua::Transform2D::MoveY ) {
	return 0;
}

tli_implementfn( TinyLua::Transform2D::Move ) {
	auto param_count = lua_gettop( context );
	auto* comp = Component::Get<TinyTransform2D>( context, tli_param_one );

	if ( comp ) {
		auto x = lua_Number{ };
		auto y = lua_Number{ };

		if ( param_count == 2 && lua_istable( context, tli_param_two ) ) {
			tli_get_field( tli_param_two, "x", x );
			tli_get_field( tli_param_two, "y", y );
		} else if (
			param_count == 3 &&
			lua_isnumber( context, tli_param_two ) &&
			lua_isnumber( context, tli_param_three )
		) {
			x = lua_tonumber( context, tli_param_two );
			y = lua_tonumber( context, tli_param_three );
		}

		comp->Move( tiny_cast( x, float ), tiny_cast( y, float ) );
	}

	return 0;
}

tli_implementfn( TinyLua::Transform2D::Rotate ) {
	auto* comp = Component::Get<TinyTransform2D>( context, tli_param_one );

	if ( comp && lua_isnumber( context, tli_param_two ) ) {
		auto value = lua_tonumber( context, tli_param_two );

		comp->Rotate( tiny_cast( value, float ) );
	}

	return 0;
}

tli_implementfn( TinyLua::Transform2D::ScaleX ) {
	return 0;
}

tli_implementfn( TinyLua::Transform2D::ScaleY ) {
	return 0;
}

tli_implementfn( TinyLua::Transform2D::Scale ) {
	auto param_count = lua_gettop( context );
	auto* comp		 = Component::Get<TinyTransform2D>( context, tli_param_one );

	if ( comp ) {
		auto x = lua_Number{ };
		auto y = lua_Number{ };

		if ( param_count == 2 && lua_isnumber( context, tli_param_two ) ) {
			x = lua_tonumber( context, tli_param_two );
			y = x;
		} else if ( param_count == 2 && lua_istable( context, tli_param_two ) ) {
			tli_get_field( tli_param_two, "x", x );
			tli_get_field( tli_param_two, "y", y );
		} else if (
			param_count == 3					   &&
			lua_isnumber( context, tli_param_two ) &&
			lua_isnumber( context, tli_param_three )
		) {
			x = lua_tonumber( context, tli_param_two );
			y = lua_tonumber( context, tli_param_three );
		}

		comp->Scale( tiny_cast( x, float ), tiny_cast( y, float ) );
	}

	return 0;
}

tli_implementfn( TinyLua::Transform2D::GetLocation ) {
	auto* comp = Component::Get<TinyTransform2D>( context, tli_self );
	auto value = tiny_vec2{ };

	if ( comp )
		value = comp->GetLocation( );

	TinyLua::Vec2::Create( context, value );

	return 1;
}

tli_implementfn( TinyLua::Transform2D::GetRotation ) {
	auto* comp = Component::Get<TinyTransform2D>( context, tli_self );
	auto value = 0.f;

	if ( comp )
		value = comp->GetRotation( );

	lua_pushnumber( context, value );

	return 1;
}

tli_implementfn( TinyLua::Transform2D::GetScale ) {
	auto* comp = Component::Get<TinyTransform2D>( context, tli_self );
	auto value = tiny_vec2{ };

	if ( comp )
		value = comp->GetScale( );

	TinyLua::Vec2::Create( context, value );

	return 1;
}

tli_implementfn( TinyLua::Transform2D::GetHalfScale ) {
	auto* comp = Component::Get<TinyTransform2D>( context, tli_self );
	auto value = tiny_vec2{ };

	if ( comp )
		value = comp->GetHalfScale( );

	TinyLua::Vec2::Create( context, value );

	return 1;
}

tli_implementfn( TinyLua::Transform2D::GetWorldLocation ) {
	lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Transform2D::GetWorldRotation ) {
	lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Transform2D::GetWorldScale ) {
	lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Transform2D::GetWorldCenter ) {
	lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Transform2D::ToString ) {
	return Component::ToString( context, TINY_TRANSFORM2D_NAME );
}
