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
 * @creation : 29/11/2023
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
TinyAnim2DSystem::TinyAnim2DSystem( ) 
	: TinySystem{ }
{ }

void TinyAnim2DSystem::RegisterInterop( TinyGame* game ) {
	tli_make_lua_context( context );

	tli_create( TINY_ANIM2D_NAME );

	tli_createfn( "create", TinyLua::Anim2D::Create );
	tli_createfn( "destroy", TinyLua::Anim2D::Destroy );
	tli_createfn( "play", nullptr );
	tli_createfn( "pause", nullptr );
	tli_createfn( "restart", nullptr );
	tli_createfn( "stop", nullptr );
	tli_createfn( "set_animation", nullptr );
	tli_createfn( "set_frame", nullptr );
	tli_createfn( "set", nullptr );
	tli_createfn( "get_animation", nullptr );
	tli_createfn( "get_frame", nullptr );
	tli_createfn( "get_is_playing", nullptr );
	tli_createfn( "to_string", TinyLua::Anim2D::ToString );

	if ( tli_createmeta( TINY_ANIM2D_NAME ) )
		tli_createop( "__tostring", TinyLua::Anim2D::ToString );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyAnim2DSystem::PostTick( TinyGame* game ) {
	auto& inputs	 = game->GetInputs( );
	auto& assets	 = game->GetAssets( );
	auto* animations = assets.GetContainerAs<TinyAnimation2DManager>( TA_TYPE_ANIMATION_2D );
	auto& ecs		 = game->GetECS( );

	for ( auto& comp : m_components ) {
		if ( comp.GetIsActive( ) )
			comp.Tick( animations, inputs, ecs );
	}
}
