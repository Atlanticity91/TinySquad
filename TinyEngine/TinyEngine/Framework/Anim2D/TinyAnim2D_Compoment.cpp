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
	m_collection{ TA_TYPE_ANIMATION_2D },
	m_animation{ "" },
	m_flags{ 0 },
	m_frame_id{ 0 },
	m_frame_time{ .0f },
	m_frame_duration{ .0f }
{ }

bool TinyAnim2D::Create( TinyGame* game ) {
	auto& ecs  = game->GetECS( );
	auto state = ecs.GetHasComponent( m_owner, "TinySkin2D" );

	if ( !state )
		state = ecs.Append( game, m_owner, "TinySkin2D" ) != nullptr;

	return state;
}

TinyAnim2D& TinyAnim2D::SetCollection( TinyGame* game, const tiny_string& collection ) {
	auto& assets = game->GetAssets( );
	auto hash	 = tiny_hash{ collection };

	if ( assets.GetExist( TA_TYPE_ANIMATION_2D, hash ) ) {
		assets.Release( game, m_collection );

		m_collection.Hash = hash;

		assets.Acquire( game, m_collection );
	}

	return tiny_self;
}

TinyAnim2D& TinyAnim2D::SetAnimation( TinyGame* game, const tiny_string& animation ) {
	m_animation		= animation;
	m_animation_hash = tiny_hash{ animation };

	return SetFrame( game, 0 );
}

TinyAnim2D& TinyAnim2D::SetFrame( TinyGame* game, tiny_uint frame_id ) {
	auto& assets	 = game->GetAssets( );
	auto* collection = assets.GetAssetAs<TinyAnimation2D>( m_collection );

	if ( collection ) {
		auto* frames = collection->Get( m_animation );

		if ( frames && frame_id < frames->size( ) )
			SetFrame( game, frame_id, frames );
	}

	return tiny_self;
}

TinyAnim2D& TinyAnim2D::Play( ) {
	m_flags |= TA_FLAG_PLAYING;

	return tiny_self;
}

TinyAnim2D& TinyAnim2D::Pause( ) {
	m_flags ^= TA_FLAG_PLAYING;

	return tiny_self;
}

void TinyAnim2D::Tick(
	TinyAnimation2DManager* animations, 
	TinyInputManager& inputs, 
	TinyECS& ecs 
) {
	m_frame_time += inputs.GetTimestep( ).GetElapsed( );

	if ( m_frame_duration - m_frame_time > 0.f )
		return;

	auto* animation = tiny_cast( animations->GetAsset( m_collection ), TinyAnimation2D* );
	auto* frame		= animation->Next( m_animation_hash, m_frame_id, m_flags & TA_FLAG_REVERSE, m_flags & TA_FLAG_LOOPING );

	if ( frame ) {
		auto* skin = ecs.GetComponentAs<TinySkin2D>( m_owner );

		m_frame_time		= .0f;
		m_frame_duration = frame->Duration;

		skin->SetSprite( frame->Column, frame->Row );
	} else
		m_flags ^= TA_FLAG_PLAYING;
}

void TinyAnim2D::Delete( TinyGame* game ) { }

void TinyAnim2D::DisplayWidget( TinyGame* game, TinyToolbox& toolbox ) {
	TinyComponent::DisplayWidget( game, toolbox );

	toolbox.DisplayAsset( game, "Collection", m_collection );

	auto& assets	 = game->GetAssets( );
	auto* collection = assets.GetAssetAs<TinyAnimation2D>( m_collection );
	auto animations  = tiny_list<tiny_string>{ "Undefined" };

	if ( collection )
		collection->GetAnimations( animations );

	ImGui::BeginDisabled( !collection );
	
	auto context = TinyImGui::DropdownContext{ animations, m_animation };

	if ( TinyImGui::Dropdown( "Animation", context ) )
		m_animation = context.Values[ context.Index ];
	
	ImGui::EndDisabled( );

	auto state = tiny_cast( m_flags & TA_FLAG_PLAYING, bool );
	if ( TinyImGui::Checkbox( "Playing", state ) )
		m_flags ^= TA_FLAG_PLAYING;

	state = m_flags & TA_FLAG_LOOPING;
	if ( TinyImGui::Checkbox( "Looping", state ) )
		m_flags ^= TA_FLAG_LOOPING;

	state = m_flags & TA_FLAG_REVERSE;
	if ( TinyImGui::Checkbox( "Reverse", state ) )
		m_flags ^= TA_FLAG_REVERSE;

	if ( TinyImGui::InputScalar( "Frame", m_frame_id ) )
		m_frame_time = 0.f;

	ImGui::BeginDisabled( );
	TinyImGui::InputScalar( "Time", m_frame_time );
	TinyImGui::InputScalar( "Duration", m_frame_duration );
	ImGui::EndDisabled( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyAnim2D::SetFrame(
	TinyGame* game,
	tiny_uint frame_id,
	const TinyAnimation2D::FrameCollection* frames
) {
	auto& ecs   = game->GetECS( );
	auto& frame = frames->at( frame_id );

	m_frame_id		= frame_id;
	m_frame_time		= .0f;
	m_frame_duration = frame.Duration;

	auto* skin = ecs.GetComponentAs<TinySkin2D>( m_owner );

	skin->SetSprite( frame.Column, frame.Row );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAnim2D::GetIsActive( ) const { 
	return TinyComponent::GetIsActive( ) && GetIsPlaying( ); 
}

TinyAssetHandle& TinyAnim2D::GetCollection( ) { return m_collection; }

const tiny_string& TinyAnim2D::GetAnimation( ) const { return m_animation; }

tiny_uint TinyAnim2D::GetFlags( ) const { return m_flags; }

bool TinyAnim2D::GetIsPlaying( ) const { return m_flags & TA_FLAG_PLAYING; }

bool TinyAnim2D::GetLoop( ) const { return m_flags & TA_FLAG_LOOPING; }

bool TinyAnim2D::GetReverse( ) const { return m_flags & TA_FLAG_REVERSE; }

tiny_uint TinyAnim2D::GetFrameID( ) const { return m_frame_id; }

float TinyAnim2D::GetFrameTime( ) const { return m_frame_time; }

float TinyAnim2D::GetFrameDuration( ) const { return m_frame_duration; }
