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
TinyAnim2D::TinyAnim2D( )
	: TinyAnim2D{ TINY_NO_ENTITY }
{ }

TinyAnim2D::TinyAnim2D( const tiny_hash entity_hash )
	: TinyComponent{ entity_hash },
	_animation{ TA_TYPE_ANIMATION_2D },
	_flags{ tiny_cast( 0, tiny_uint ) },
	_frame_id{ tiny_cast( 0, tiny_uint ) },
	_frame_time{ .0f }
{ }

bool TinyAnim2D::Create( TinyGame* game, TinyEngine& engine ) {
	auto& ecs  = engine.GetECS( );
	auto state = ecs.GetHasComponent( _owner, "TinySkin2D" );

	if ( !state )
		state = ecs.Append( game, engine, _owner, "TinySkin2D" ) != nullptr;

	return state;
}

void TinyAnim2D::Delete( TinyGame* game, TinyEngine& engine ) {
}

void TinyAnim2D::DisplayWidget(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) {
	TinyComponent::DisplayWidget( game, engine, toolbox );

	toolbox.DisplayAsset( game, "Animation", _animation );

	auto state = tiny_cast( _flags & TA_FLAG_PLAYING, bool );
	if ( TinyImGui::Checkbox( "Playing", state ) )
		_flags ^= TA_FLAG_PLAYING;

	state = _flags & TA_FLAG_LOOPING;
	if ( TinyImGui::Checkbox( "Looping", state ) )
		_flags ^= TA_FLAG_LOOPING;

	state = _flags & TA_FLAG_REVERSE;
	if ( TinyImGui::Checkbox( "Reverse", state ) )
		_flags ^= TA_FLAG_REVERSE;

	TinyImGui::InputScalar( "Frame", _frame_id );
	TinyImGui::InputScalar( "Time", _frame_time );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAsset& TinyAnim2D::GetAnimation( ) { return _animation; }

tiny_uint TinyAnim2D::GetFlags( ) const { return _flags; }

tiny_uint TinyAnim2D::GetFrameID( ) const { return _frame_id; }

float TinyAnim2D::GetFrameTime( ) const { return _frame_time; }
