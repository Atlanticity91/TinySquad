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

#pragma once

#include "TinyLuaEngine.h"

namespace TinyLua::Entity {

	tiny_dll tli_prototypefn( New );
	tiny_dll tli_prototypefn( Delete );
	
	tiny_dll tli_prototypefn( Kill );

	tiny_dll tli_prototypefn( AddComp );
	tiny_dll tli_prototypefn( RemComp );
	tiny_dll tli_prototypefn( HasComp );
	tiny_dll tli_prototypefn( GetComp );

	tiny_dll tli_prototypefn( AddFlag );
	tiny_dll tli_prototypefn( RemFlag );
	tiny_dll tli_prototypefn( HasFlag );

	tiny_dll tli_prototypefn( Attach );
	tiny_dll tli_prototypefn( Detach );
	tiny_dll tli_prototypefn( HasParent );
	tiny_dll tli_prototypefn( GetParent );

	tiny_dll tli_prototypefn( ToString );

	tiny_dll void Create( TinyLuaContext& context, const tiny_hash entity_hash );

	tiny_dll void Create( lua_State* context, lua_Integer hash );

	tiny_dll void Register( TinyLuaContext& context );

};
