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
	_collection{ TA_TYPE_ANIMATION_2D },
	_animation{ "" },
	_flags{ 0 },
	_frame_id{ 0 },
	_frame_time{ .0f },
	_frame_duration{ .0f }
{ }

bool TinyAnim2D::Create( TinyGame* game, TinyEngine& engine ) {
	auto& ecs  = engine.GetECS( );
	auto state = ecs.GetHasComponent( _owner, "TinySkin2D" );

	if ( !state )
		state = ecs.Append( game, engine, _owner, "TinySkin2D" ) != nullptr;

	return state;
}

TinyAnim2D& TinyAnim2D::SetCollection( TinyGame* game, const tiny_string& collection ) {
	auto& assets = game->GetAssets( );

	assets.Acquire( game, _collection, collection );

	return tiny_self;
}

TinyAnim2D& TinyAnim2D::SetAnimation( TinyGame* game, const tiny_string& animation ) {
	_animation		= animation;
	_animation_hash = tiny_hash{ animation };

	return SetFrame( game, 0 );
}

TinyAnim2D& TinyAnim2D::SetFrame( TinyGame* game, tiny_uint frame_id ) {
	auto& assets	 = game->GetAssets( );
	auto* collection = assets.GetAssetAs<TinyAnimation2D>( _collection );

	if ( collection ) {
		auto* frames = collection->Get( _animation );

		if ( frames && frame_id < frames->size( ) )
			SetFrame( game, frame_id, frames );
	}

	return tiny_self;
}

TinyAnim2D& TinyAnim2D::Play( ) {
	_flags |= TA_FLAG_PLAYING;

	return tiny_self;
}

TinyAnim2D& TinyAnim2D::Pause( ) {
	_flags ^= TA_FLAG_PLAYING;

	return tiny_self;
}

void TinyAnim2D::Tick(
	TinyAnimation2DManager* animations, 
	TinyInputManager& inputs, 
	TinyECS& ecs 
) {
	_frame_time += inputs.GetTimestep( ).GetElapsed( );

	if ( _frame_duration - _frame_time > 0.f )
		return;

	auto* animation = tiny_cast( animations->GetAsset( _collection ), TinyAnimation2D* );
	auto* frame		= animation->Next( _animation_hash, _frame_id, _flags & TA_FLAG_REVERSE, _flags & TA_FLAG_LOOPING );

	if ( frame ) {
		auto* skin = ecs.GetComponentAs<TinySkin2D>( _owner );

		_frame_time		= .0f;
		_frame_duration = frame->Duration;

		skin->SetSprite( frame->Column, frame->Row );
	} else
		_flags ^= TA_FLAG_PLAYING;
}

void TinyAnim2D::Delete( TinyGame* game, TinyEngine& engine ) { }

void TinyAnim2D::DisplayWidget(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) {
	TinyComponent::DisplayWidget( game, engine, toolbox );

	toolbox.DisplayAsset( game, "Collection", _collection );

	auto& assets	 = game->GetAssets( );
	auto* collection = assets.GetAssetAs<TinyAnimation2D>( _collection );
	auto animations  = tiny_list<tiny_string>{ "Undefined" };

	if ( collection )
		collection->GetAnimations( animations );

	ImGui::BeginDisabled( !collection );
	
	auto context = TinyImGui::DropdownContext{ animations, _animation };

	if ( TinyImGui::Dropdown( "Animation", context ) )
		_animation = context.Values[ context.Index ];
	
	ImGui::EndDisabled( );

	auto state = tiny_cast( _flags & TA_FLAG_PLAYING, bool );
	if ( TinyImGui::Checkbox( "Playing", state ) )
		_flags ^= TA_FLAG_PLAYING;

	state = _flags & TA_FLAG_LOOPING;
	if ( TinyImGui::Checkbox( "Looping", state ) )
		_flags ^= TA_FLAG_LOOPING;

	state = _flags & TA_FLAG_REVERSE;
	if ( TinyImGui::Checkbox( "Reverse", state ) )
		_flags ^= TA_FLAG_REVERSE;

	if ( TinyImGui::InputScalar( "Frame", _frame_id ) )
		_frame_time = 0.f;

	ImGui::BeginDisabled( );
	TinyImGui::InputScalar( "Time", _frame_time );
	TinyImGui::InputScalar( "Duration", _frame_duration );
	ImGui::EndDisabled( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyAnim2D::SetFrame(
	TinyGame* game,
	tiny_uint frame_id,
	TinyAnimation2D::FrameCollection* frames
) {
	auto& ecs   = game->GetECS( );
	auto& frame = frames->at( frame_id );

	_frame_id		= frame_id;
	_frame_time		= .0f;
	_frame_duration = frame.Duration;

	auto* skin = ecs.GetComponentAs<TinySkin2D>( _owner );

	skin->SetSprite( frame.Column, frame.Row );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAnim2D::GetIsActive( ) const { 
	return TinyComponent::GetIsActive( ) && GetIsPlaying( ); 
}

TinyAsset& TinyAnim2D::GetCollection( ) { return _collection; }

const tiny_string& TinyAnim2D::GetAnimation( ) const { return _animation; }

tiny_uint TinyAnim2D::GetFlags( ) const { return _flags; }

bool TinyAnim2D::GetIsPlaying( ) const { return _flags & TA_FLAG_PLAYING; }

bool TinyAnim2D::GetLoop( ) const { return _flags & TA_FLAG_LOOPING; }

bool TinyAnim2D::GetReverse( ) const { return _flags & TA_FLAG_REVERSE; }

tiny_uint TinyAnim2D::GetFrameID( ) const { return _frame_id; }

float TinyAnim2D::GetFrameTime( ) const { return _frame_time; }

float TinyAnim2D::GetFrameDuration( ) const { return _frame_duration; }
