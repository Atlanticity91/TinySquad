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
#define TINY_VEC2_NAME "TinyVec2"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
tli_implementfn( TinyLua::Vec2::New ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Delete ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::SetX ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::SetY ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Set ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::TranslateX ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::TranslateY ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Translate ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Add ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Sub ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Scale ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Magnitude ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::sqrtMagnitude ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Normalize ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Angle ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Distance ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Min ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Max ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Dot ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Reflect ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Perpendicular ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Lerp ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Interpolate ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::ToPoint ) {
	if ( lua_istable( context, tli_self ) ) {
		auto x = lua_Number{ };
		auto y = lua_Number{ };

		tli_get_field( tli_self, "x", x );
		tli_get_field( tli_self, "y", y );

		TinyLua::Point::Create( 
			context, 
			tiny_cast( x, lua_Integer ), 
			tiny_cast( y, lua_Integer )
		);
	}

	return 0;
}

tli_implementfn( TinyLua::Vec2::ToVec3 ) {
	if ( lua_istable( context, tli_self ) ) {
		auto x = lua_Number{ };
		auto y = lua_Number{ };

		tli_get_field( tli_self, "x", x );
		tli_get_field( tli_self, "y", y );

		TinyLua::Vec3::Create( context, x, y, 0.0 );
	}

	return 0;
}

tli_implementfn( TinyLua::Vec2::ToString ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Equal ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::Less ) {
	return 0;
}

tli_implementfn( TinyLua::Vec2::LessEqual ) {
	return 0;
}

void TinyLua::Vec2::Create( lua_State* context, const tiny_vec2& vector ) {
	Create( context, vector.x, vector.y );
}

void TinyLua::Vec2::Create( lua_State* context, lua_Number x, lua_Number y ) {
	tli_create_new(
		TINY_VEC2_NAME,
		tli_create_field( "x", x );
		tli_create_field( "y", y );
	);
}

/*
void TinyLua::Vec2::Register( TinyLuaContext& context ) {
	tli_create( TINY_VEC2_NAME );

	tli_createfn( "new", New );
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
	tli_createfn( "to_point", ToPoint );
	tli_createfn( "to_vec3", ToVec3 );
	tli_createfn( "to_string", ToString );
	tli_createfn( "equal", Equal );
	tli_createfn( "less", Less );
	tli_createfn( "less_equal", LessEqual );

	if ( tli_createmeta( TINY_VEC2_NAME ) ) {
		tli_createop( "__gc", Delete );
		tli_createop( "__add", Add );
		tli_createop( "__sub", Sub );
		tli_createop( "__mul", Scale );
		tli_createop( "__div", Divide );
		tli_createop( "__unm", Negate );
		tli_createop( "__len", Magnitude );
		tli_createop( "__idiv", Angle );
		tli_createop( "__concat", Dot );
		//tli_createop( "__pow ", Cross );
		tli_createop( "__tostring", ToString );

		tli_createop( "__eq", Equal );
		tli_createop( "__lt", Less );
		tli_createop( "__le", LessEqual );
	}
}
*/
