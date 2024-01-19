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
 * @creation : 20/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyTransform2DSystem::TinyTransform2DSystem( ) 
	: TinySystem{ false, true }
{ }

void TinyTransform2DSystem::RegisterInterop( TinyGame* game ) {
	tli_make_lua_context( context );

	tli_create( TINY_TRANSFORM2D_NAME );

	tli_createfn( "create", TinyLua::Transform2D::Create );
	tli_createfn( "destroy", TinyLua::Transform2D::Destroy );
	tli_createfn( "set_location_x", TinyLua::Transform2D::SetLocationX );
	tli_createfn( "set_location_y", TinyLua::Transform2D::SetLocationY );
	tli_createfn( "set_location", TinyLua::Transform2D::SetLocation );
	tli_createfn( "set_rotation", TinyLua::Transform2D::SetRotation );
	tli_createfn( "set_scale_x", TinyLua::Transform2D::SetScaleX );
	tli_createfn( "set_scale_y", TinyLua::Transform2D::SetScaleY );
	tli_createfn( "set_scale", TinyLua::Transform2D::SetScale );
	tli_createfn( "set", TinyLua::Transform2D::Set );
	tli_createfn( "move_x", TinyLua::Transform2D::MoveX );
	tli_createfn( "move_y", TinyLua::Transform2D::MoveY );
	tli_createfn( "move", TinyLua::Transform2D::Move );
	tli_createfn( "rotate", TinyLua::Transform2D::Rotate );
	tli_createfn( "scale_x", TinyLua::Transform2D::ScaleX );
	tli_createfn( "scale_y", TinyLua::Transform2D::ScaleY );
	tli_createfn( "scale", TinyLua::Transform2D::Scale );
	tli_createfn( "get_location", TinyLua::Transform2D::GetLocation );
	tli_createfn( "get_rotation", TinyLua::Transform2D::GetRotation );
	tli_createfn( "get_scale", TinyLua::Transform2D::GetScale );
	tli_createfn( "get_center", TinyLua::Transform2D::GetCenter );
	tli_createfn( "get_world_location", TinyLua::Transform2D::GetWorldLocation );
	tli_createfn( "get_world_rotation", TinyLua::Transform2D::GetWorldRotation );
	tli_createfn( "get_world_scale", TinyLua::Transform2D::GetWorldScale );
	tli_createfn( "get_world_center", TinyLua::Transform2D::GetWorldCenter );
	tli_createfn( "to_string", TinyLua::Transform2D::ToString );

	if ( tli_createmeta( TINY_TRANSFORM2D_NAME ) )
		tli_createop( "__tostring", TinyLua::Transform2D::ToString );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyTransform2DSystem::PostTick( TinyGame* game, TinyEngine& engine ) {
	for ( auto& comp : _components )
		comp.ReCalculate( );
}
