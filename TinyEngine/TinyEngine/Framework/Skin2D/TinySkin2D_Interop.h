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

#include "TinySkin2D_Compoment.h"

#define TINY_SKIN2D_NAME "TinySkin2D"

namespace TinyLua::Skin2D { 

	tiny_dll void Convert( lua_State* context, TinyComponent* component );

	tiny_dll tli_prototypefn( Create );
	tiny_dll tli_prototypefn( Destroy );

	tiny_dll tli_prototypefn( SetColor );

	tiny_dll tli_prototypefn( GetColor );

	tiny_dll tli_prototypefn( ToString );

};
