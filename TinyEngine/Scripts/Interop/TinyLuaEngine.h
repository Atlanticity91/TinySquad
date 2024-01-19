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
 * @creation : 13/01/2024
 * @version  : 2024.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyLuaColor.h"

namespace TinyLua::Engine { 

	tiny_dll tli_prototypefn( CreateEntity );

	tiny_dll tli_prototypefn( GetEntity );

	tiny_dll tli_prototypefn( GetEntities );

	tiny_dll tli_prototypefn( GetEntitiesFlags );
	
	tiny_dll tli_prototypefn( GetEntitiesComps );
	
	tiny_dll tli_prototypefn( KillEntity );

	tiny_dll tli_prototypefn( KillEntities );

	tiny_dll tli_prototypefn( KillEntitiesFlags );

	tiny_dll tli_prototypefn( KillEntitiesComps );

	tiny_dll tli_prototypefn( LoadAsset );

	tiny_dll tli_prototypefn( HasAsset );

	tiny_dll void Register( TinyLuaContext& context );

};
