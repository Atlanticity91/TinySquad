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
#define TINY_VEC4_NAME "TinyVec4"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyLua::Vec4::Create( TinyLuaContext& context, const tiny_vec4& vector ) {
	Create( 
		context, 
		tiny_cast( vector.x, lua_Number ),
		tiny_cast( vector.y, lua_Number ),
		tiny_cast( vector.z, lua_Number ),
		tiny_cast( vector.w, lua_Number )
	);
}

void TinyLua::Vec4::Create(
	lua_State* context,
	lua_Number x,
	lua_Number y,
	lua_Number z,
	lua_Number w
) {
	tli_create_new(
		TINY_VEC4_NAME,
		tli_create_field( "x", x );
		tli_create_field( "y", y );
		tli_create_field( "z", z );
		tli_create_field( "w", w );
	);
}

/*
void TinyLua::Vec4::Register( TinyLuaContext& context ) {
	tli_create( TINY_VEC4_NAME );

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
	tli_createfn( "to_vec2", ToVec2 );
	tli_createfn( "to_vec3", ToVec3 );
	tli_createfn( "to_string", ToString );
	tli_createfn( "equal", Equal );
	tli_createfn( "less", Less );
	tli_createfn( "less_equal", LessEqual );

	if ( tli_createmeta( TINY_VEC4_NAME ) ) {
		tli_createop( "__gc", Delete );
		tli_createop( "__add", Add );
		tli_createop( "__sub", Sub );
		tli_createop( "__mul", Scale );
		tli_createop( "__div", Divide );
		tli_createop( "__unm", Negate );
		tli_createop( "__len", Magnitude );
		tli_createop( "__idiv", Angle );
		tli_createop( "__concat", Dot );
		tli_createop( "__pow", Cross );
		tli_createop( "__tostring", ToString );

		tli_createop( "__eq", Equal );
		tli_createop( "__lt", Less );
		tli_createop( "__le", LessEqual );
	}
}
*/
