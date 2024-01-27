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

#pragma once

#include "TinyComponent.h"

namespace TinyLua::Component {

	template<typename Type>
		requires tiny_is_child_of( Type, TinyComponent )
	Type* Get( lua_State* context, tiny_int param_id ) {
		auto* comp = tiny_cast( nullptr, c_pointer );

		if ( lua_istable( context, param_id ) )
			tli_get_field( param_id, "value", comp );

		return tiny_cast( comp, Type* );
	};

	tiny_dll tiny_int Create( lua_State* context, const tiny_string& name );

	tiny_dll tiny_hash GetHash( lua_State* context, tiny_int param_id );

	tiny_dll tiny_int ToString( lua_State* context, const tiny_string& name );

};
