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

#include "TinyLuaVec4.h"

namespace TinyLua::Color {

	tiny_dll tli_prototypefn( New );
	tiny_dll tli_prototypefn( Delete );
	tiny_dll tli_prototypefn( Clone );
	tiny_dll tli_prototypefn( SetR );
	tiny_dll tli_prototypefn( SetG );
	tiny_dll tli_prototypefn( SetB );
	tiny_dll tli_prototypefn( SetA );
	tiny_dll tli_prototypefn( Set );
	tiny_dll tli_prototypefn( Add );
	tiny_dll tli_prototypefn( Sub );

	tiny_dll tli_prototypefn( Lerp );
	tiny_dll tli_prototypefn( Interpolate );

	tiny_dll tli_prototypefn( ToVec3 );
	tiny_dll tli_prototypefn( ToVec4 );
	tiny_dll tli_prototypefn( ToString );

	tiny_dll tli_prototypefn( Equal );
	tiny_dll tli_prototypefn( Less );
	tiny_dll tli_prototypefn( LessEqual );

	tiny_dll void Create( TinyLuaContext& context, const tiny_color& color );

	tiny_dll void Create(
		lua_State* context,
		lua_Number r, 
		lua_Number g, 
		lua_Number b, 
		lua_Number a
	);

	tiny_dll void Register( TinyLuaContext& context );

};
