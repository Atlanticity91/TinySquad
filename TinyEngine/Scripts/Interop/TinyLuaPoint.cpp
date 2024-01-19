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
 * @creation : 11/01/2024
 * @version  : 2024.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		=== INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
#define TINY_POINT_NAME "TinyPoint"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
tli_implementfn( TinyLua::Point::New ) {
	auto param_count = lua_gettop( context );
	auto x = lua_Integer{ 0 };
	auto y = lua_Integer{ 0 };

	if ( param_count == 1 && lua_istable( context, tli_param_one ) ) {
		tli_get_field( tli_param_one, "x", x );
		tli_get_field( tli_param_two, "y", y );
	} else if ( param_count == 1 && lua_isinteger( context, tli_param_one ) ) {
		x = lua_tointeger( context, tli_param_one );
		y = x;
	} else if ( 
		param_count == 2						&& 
		lua_isinteger( context, tli_param_one ) &&
		lua_isinteger( context, tli_param_two ) 
	) {
		x = lua_tointeger( context, tli_param_one );
		y = lua_tointeger( context, tli_param_two );
	}

	Create( context, x, y );

	return 0;
}

tli_implementfn( TinyLua::Point::Delete ) { return 0; }

tli_implementfn( TinyLua::Point::Clone ) { 
	if ( lua_istable( context, tli_self ) ) {
	} else
		lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Point::Negate ) {
	if ( lua_istable( context, tli_self ) ) {
		auto x = lua_Integer{ };
		auto y = lua_Integer{ };

		tli_get_field( tli_self, "x", x );
		tli_get_field( tli_self, "y", y );

		tli_set_field( "x", -x );
		tli_set_field( "y", -y );
	}

	return 0;
}

tli_implementfn( TinyLua::Point::SetX ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_isinteger( context, tli_param_two )
	)
		tli_set_field( "x", lua_tointeger( context, tli_param_two ) );

	return 0;
}

tli_implementfn( TinyLua::Point::SetY ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_isinteger( context, tli_param_two )
	)
		tli_set_field( "y", lua_tointeger( context, tli_param_two ) );

	return 0;
}

tli_implementfn( TinyLua::Point::Set ) {
	auto param_count = lua_gettop( context );
	auto x = lua_Integer{ 0 };
	auto y = lua_Integer{ 0 };

	if ( 
		param_count == 2					  && 
		lua_istable( context, tli_param_one ) && 
		lua_istable( context, tli_param_two )
	) {
		tli_get_field( tli_param_two, "x", x );
		tli_get_field( tli_param_two, "x", y );
	} else if ( 
		param_count == 2					  &&
		lua_istable( context, tli_param_one ) &&
		lua_isinteger( context, tli_param_two )
	) {
		x = lua_tointeger( context, tli_param_two );
		y = x;
	} else if ( 
		param_count == 3						&&
		lua_istable( context, tli_param_one )   &&
		lua_isinteger( context, tli_param_two ) &&
		lua_isinteger( context, tli_param_three )
	) {
		x = lua_tointeger( context, tli_param_two );
		y = lua_tointeger( context, tli_param_three );
	}

	tli_set_field( "x", x );
	tli_set_field( "y", y );

	return 0;
}

tli_implementfn( TinyLua::Point::TranslateX ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_isinteger( context, tli_param_two )
	) {
		auto value = lua_Integer{ };

		tli_get_field( tli_param_one, "x", value );
		tli_set_field( "x", value + lua_tointeger( context, tli_param_two ) );
	}

	return 0;
}

tli_implementfn( TinyLua::Point::TranslateY ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_isinteger( context, tli_param_two )
	) {
		auto value = lua_Integer{ };

		tli_get_field( tli_param_one, "y", value );
		tli_set_field( "y", value + lua_tointeger( context, tli_param_two ) );
	}

	return 0;
}

tli_implementfn( TinyLua::Point::Translate ) {
	auto param_count = lua_gettop( context );

	if ( param_count == 2 ) {
	} else if ( param_count == 2 ) {
	} else if ( param_count == 3 ) {
	}

	return 0;
}

tli_implementfn( TinyLua::Point::Add ) {
	return 0;
}

tli_implementfn( TinyLua::Point::Sub ) {
	return 0;
}

tli_implementfn( TinyLua::Point::Scale ) {
	return 0;
}

tli_implementfn( TinyLua::Point::Divide ) {
	return 0;
}

tli_implementfn( TinyLua::Point::Lerp ) {
	if ( 
		lua_istable( context, tli_param_one ) &&
		lua_istable( context, tli_param_two ) &&
		lua_isnumber( context, tli_param_three )
	) {
		auto scalar   = lua_tonumber( context, tli_param_three );
		auto scalar_n = 1.0 - scalar;
		auto x_1 = lua_Integer{ };
		auto x_2 = lua_Integer{ };
		auto y_1 = lua_Integer{ };
		auto y_2 = lua_Integer{ };

		tli_get_field( tli_param_one, "x", x_1 );
		tli_get_field( tli_param_one, "y", y_1 );
		tli_get_field( tli_param_two, "x", x_2 );
		tli_get_field( tli_param_two, "y", y_2 );

		Create(
			context,
			tiny_cast( floor( x_1 * scalar_n + scalar * x_2 ), lua_Integer ),
			tiny_cast( floor( y_1 * scalar_n + scalar * y_2 ), lua_Integer )
		);
	}

	return 1;
}

tli_implementfn( TinyLua::Point::Interpolate ) {
	return 0;
}

tli_implementfn( TinyLua::Point::Magnitude ) {
	auto value = lua_Number{ 0.0 };

	if ( lua_istable( context, tli_self ) ) {
		auto x = lua_Integer{ };
		auto y = lua_Integer{ };

		tli_get_field( tli_self, "x", x );
		tli_get_field( tli_self, "y", y );

		value = tiny_cast( x * x + y * y, lua_Number );
	}

	lua_pushnumber( context, value );

	return 1;
}

tli_implementfn( TinyLua::Point::SqrtMagnitude ) {
	auto value = lua_Number{ 0.0 };

	if ( lua_istable( context, tli_self ) ) {
		auto x = lua_Integer{ };
		auto y = lua_Integer{ };

		tli_get_field( tli_self, "x", x );
		tli_get_field( tli_self, "y", y );

		value = sqrt( x * x + y * y );
	}

	lua_pushnumber( context, value );

	return 1;
}

tli_implementfn( TinyLua::Point::ToVec2 ) {
	if ( lua_istable( context, tli_self ) ) {
		auto x = lua_Integer{ };
		auto y = lua_Integer{ };

		tli_get_field( tli_self, "x", x );
		tli_get_field( tli_self, "y", y );

		TinyLua::Vec2::Create( context, tiny_cast( x, float ), tiny_cast( y, float ) );
	} else
		lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Point::ToString ) {
	if ( lua_istable( context, tli_self ) ) {
		auto x = lua_Number{ };
		auto y = lua_Number{ };

		tli_get_field( tli_self, "x", x );
		tli_get_field( tli_self, "y", y );

		lua_pushfstring(
			context, "[ %d, %d ]",
			tiny_cast( x, tiny_int ),
			tiny_cast( y, tiny_int )
		);
	} else
		lua_pushfstring( context, "" );

	return 1;
}

tli_implementfn( TinyLua::Point::Equal ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_istable( context, tli_param_two )
	) {
		c_str channels[ 2 ] = { "x", "y" };

		auto state = true;
		auto val_0 = lua_Number{ };
		auto val_1 = lua_Number{ };

		for ( auto channel : channels ) {
			tli_get_field( tli_param_one, channel, val_0 );
			tli_get_field( tli_param_two, channel, val_1 );

			state = val_0 == val_1;

			if ( !state ) break;
		}

		lua_pushboolean( context, state );
	} else
		lua_pushboolean( context, false );

	return 1;
}

tli_implementfn( TinyLua::Point::Less ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_istable( context, tli_param_two )
	) {
		c_str channels[ 2 ] = { "x", "y" };

		auto state = true;
		auto val_0 = lua_Number{ };
		auto val_1 = lua_Number{ };

		for ( auto channel : channels ) {
			tli_get_field( tli_param_one, channel, val_0 );
			tli_get_field( tli_param_two, channel, val_1 );

			state = val_0 < val_1;

			if ( !state ) break;
		}

		lua_pushboolean( context, state );
	} else
		lua_pushboolean( context, false );

	return 1;;
}

tli_implementfn( TinyLua::Point::LessEqual ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_istable( context, tli_param_two )
	) {
		c_str channels[ 2 ] = { "x", "y" };

		auto state = true;
		auto val_0 = lua_Number{ };
		auto val_1 = lua_Number{ };

		for ( auto channel : channels ) {
			tli_get_field( tli_param_one, channel, val_0 );
			tli_get_field( tli_param_two, channel, val_1 );

			state = val_0 <= val_1;

			if ( !state ) break;
		}

		lua_pushboolean( context, state );
	} else
		lua_pushboolean( context, false );

	return 1;
}

void TinyLua::Point::Create( TinyLuaContext& context, const tiny_point& point ) {
	Create( 
		context,
		tiny_cast( point.x, lua_Integer ),
		tiny_cast( point.y, lua_Integer )
	);
}

void TinyLua::Point::Create( lua_State* context, lua_Integer x, lua_Integer y ) {
	tli_create_new(
		TINY_POINT_NAME,
		tli_create_field( "x", x );
		tli_create_field( "y", y );
	);
}

void TinyLua::Point::Register( TinyLuaContext& context ) {
	tli_create( TINY_POINT_NAME );

	tli_createfn( "new", New );
	tli_createfn( "clone", Clone );
	tli_createfn( "negate", Negate );
	tli_createfn( "set_x", SetX );
	tli_createfn( "set_y", SetY );
	tli_createfn( "set", Set );
	tli_createfn( "translate_x", TranslateX );
	tli_createfn( "translate_y", TranslateY );
	tli_createfn( "translate", Translate );
	tli_createfn( "add", Add );
	tli_createfn( "sub", Sub );
	tli_createfn( "scale", Scale );
	tli_createfn( "divide", Divide );
	tli_createfn( "lerp", Lerp );
	tli_createfn( "interpolate", Interpolate );
	tli_createfn( "magnitude", Magnitude );
	tli_createfn( "sqrt_magnitude", SqrtMagnitude );
	tli_createfn( "to_vec2", ToVec2 );
	tli_createfn( "to_string", ToString );
	tli_createfn( "equal", Equal );
	tli_createfn( "less", Less );
	tli_createfn( "less_equal", LessEqual );

	if ( tli_createmeta( TINY_POINT_NAME ) ) {
		tli_createop( "__gc", Delete );
		tli_createop( "__add", Add );
		tli_createop( "__sub", Sub );
		tli_createop( "__mul", Scale );
		tli_createop( "__div", Divide );
		tli_createop( "__unm", Negate );
		tli_createop( "__len", SqrtMagnitude );
		tli_createop( "__tostring", ToString );

		tli_createop( "__eq", Equal );
		tli_createop( "__lt", Less );
		tli_createop( "__le", LessEqual );
	}
}
