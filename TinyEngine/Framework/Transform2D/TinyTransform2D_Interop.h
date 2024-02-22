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

#include "TinyTransform2D_Component.h"

#define TINY_TRANSFORM2D_NAME "TinyTransform2D"

namespace TinyLua::Transform2D {

	tiny_dll void Convert( lua_State* context, TinyComponent* component );

	tiny_dll tli_prototypefn( Create );
	tiny_dll tli_prototypefn( Destroy );

	tiny_dll tli_prototypefn( SetLocationX );
	tiny_dll tli_prototypefn( SetLocationY );
	tiny_dll tli_prototypefn( SetLocation );
	tiny_dll tli_prototypefn( SetLayer );
	tiny_dll tli_prototypefn( SetRotation );
	tiny_dll tli_prototypefn( SetScaleX );
	tiny_dll tli_prototypefn( SetScaleY );
	tiny_dll tli_prototypefn( SetScale );
	tiny_dll tli_prototypefn( Set );

	tiny_dll tli_prototypefn( MoveX );
	tiny_dll tli_prototypefn( MoveY );
	tiny_dll tli_prototypefn( Move );
	tiny_dll tli_prototypefn( Rotate );
	tiny_dll tli_prototypefn( ScaleX );
	tiny_dll tli_prototypefn( ScaleY );
	tiny_dll tli_prototypefn( Scale );

	tiny_dll tli_prototypefn( GetLocation );
	tiny_dll tli_prototypefn( GetRotation );
	tiny_dll tli_prototypefn( GetScale );	
	tiny_dll tli_prototypefn( GetHalfScale );

	tiny_dll tli_prototypefn( GetWorldLocation );
	tiny_dll tli_prototypefn( GetWorldRotation );
	tiny_dll tli_prototypefn( GetWorldScale );
	tiny_dll tli_prototypefn( GetWorldCenter );

	tiny_dll tli_prototypefn( ToString );

};
