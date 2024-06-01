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
 * @creation : 14/11/2023
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
TinySound2D::TinySound2D( )
	: TinySound2D{ TINY_NO_ENTITY }
{ }

TinySound2D::TinySound2D( const tiny_hash entity_hash )
	: TinyComponent{ entity_hash },
	m_cue{ TA_TYPE_CUE },
	m_handle{ TINY_UINT_MAX },
	m_volume{ 1.f }
{ }

bool TinySound2D::Create( TinyGame* game ) {
	return true;
}

void TinySound2D::Delete( TinyGame* game ) {
	auto& audio = game->GetAudio( );

	audio.Release( m_handle );
}

bool TinySound2D::SetCue( TinyGame* game, const tiny_string& cue_name ) {
	auto& assets = game->GetAssets( );
	auto state   = false;
	auto hash    = tiny_hash{ cue_name };

	if ( assets.GetExist( TA_TYPE_CUE, hash ) ) {
		assets.Release( game, m_cue );

		m_cue.Hash = hash;

		state = assets.Acquire( game, m_cue );

		if ( !state )
			m_cue.Hash.undefined( );
	}

	return state;
}

bool TinySound2D::Play( TinyGame* game ) { return Play( game, true ); }

bool TinySound2D::Play( TinyGame* game, bool imediate ) {
	auto& assets = game->GetAssets( );
	auto& audio  = game->GetAudio( );
	auto state   = false;
	auto* cue	 = assets.GetAssetAs<TinyCue>( m_cue );

	if ( cue ) {
		if ( !audio.GetExist( m_handle ) )
			m_handle = audio.Acquire( cue->GetFormat( ) );

		state = audio.Submit( m_handle, cue->GetBuffer( ) );

		if ( state && imediate )
			state = audio.Start( m_handle );
	}

	return state;
}

void TinySound2D::Stop( TinyGame* game ) {
	auto& audio = game->GetAudio( );

	audio.Stop( m_handle );
	audio.Release( m_handle );
}

void TinySound2D::DisplayWidget( TinyGame* game, TinyToolbox& toolbox ) { 
	auto& audio = game->GetAudio( );

	TinyComponent::DisplayWidget( game, toolbox );

	toolbox.DisplayAsset( game, "Cue", m_cue );

	if ( TinyImGui::InputSlider( "Volume", m_volume, .0f, 224.f ) )
		audio.SetVolume( m_handle, m_volume );

	if ( m_cue.GetIsValid( ) && ImGui::Button( "Play" ) ) {
		
		auto* c = game->GetAssets( ).GetAssetAs<TinyCue>( m_cue );
		auto v = audio.Acquire( c->GetFormat( ) );
		
		audio.Submit( v, c->GetBuffer( ) );
		audio.Start( v );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAssetHandle& TinySound2D::GetCue( ) { return m_cue; }

float TinySound2D::GetVolume( ) const { return m_volume; }
