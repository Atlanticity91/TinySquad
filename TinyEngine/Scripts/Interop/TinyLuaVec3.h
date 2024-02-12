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

#pragma once

#include "TinyLuaVec2.h"

namespace TinyLua::Vec3 {

	tiny_dll tli_prototypefn( New );
	tiny_dll tli_prototypefn( Delete );
	tiny_dll tli_prototypefn( Negate );
	tiny_dll tli_prototypefn( SetX );
	tiny_dll tli_prototypefn( SetY );
	tiny_dll tli_prototypefn( SetZ );
	tiny_dll tli_prototypefn( Set );
	tiny_dll tli_prototypefn( TranslateX );
	tiny_dll tli_prototypefn( TranslateY );
	tiny_dll tli_prototypefn( TranslateZ );
	tiny_dll tli_prototypefn( Translate );
	tiny_dll tli_prototypefn( Add );
	tiny_dll tli_prototypefn( Sub );
	tiny_dll tli_prototypefn( Scale );
	tiny_dll tli_prototypefn( Divide );
	tiny_dll tli_prototypefn( Magnitude );
	tiny_dll tli_prototypefn( sqrtMagnitude );
	tiny_dll tli_prototypefn( Normalize );
	tiny_dll tli_prototypefn( Angle );
	tiny_dll tli_prototypefn( Distance );
	tiny_dll tli_prototypefn( Dot );
	tiny_dll tli_prototypefn( Min );
	tiny_dll tli_prototypefn( Max );
	tiny_dll tli_prototypefn( Dot );
	tiny_dll tli_prototypefn( Cross );
	tiny_dll tli_prototypefn( Reflect );
	tiny_dll tli_prototypefn( Perpendicular );

	tiny_dll tli_prototypefn( Lerp );
	tiny_dll tli_prototypefn( Interpolate );

	tiny_dll tli_prototypefn( ToPoint );
	tiny_dll tli_prototypefn( ToVec2 );
	tiny_dll tli_prototypefn( ToVec4 );
	tiny_dll tli_prototypefn( ToString );

	tiny_dll tli_prototypefn( Equal );
	tiny_dll tli_prototypefn( Less );
	tiny_dll tli_prototypefn( LessEqual );

	tiny_dll void Create( TinyLuaContext& context, const tiny_vec3& vector );

	tiny_dll void Create( 
		lua_State* context,
		lua_Number x, 
		lua_Number y, 
		lua_Number z
	);

	tiny_dll void Register( TinyLuaContext& context );

};
