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
 * @creation : 16/01/2024
 * @version  : 2024.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyLua::Anim2D::Convert( lua_State* context, TinyComponent* component ) {
	auto* tmp = tiny_cast( component, c_pointer );

	tli_create_new(
		TINY_ANIM2D_NAME,
		tli_create_field( "value", tmp );
	);
}

tli_implementfn( TinyLua::Anim2D::Create ) {
	return Component::Create( context, TINY_ANIM2D_NAME );
}

tli_implementfn( TinyLua::Anim2D::Destroy ) {
	return 0;
}

tli_implementfn( TinyLua::Anim2D::ToString ) { 
	return Component::ToString( context, TINY_ANIM2D_NAME );
}
