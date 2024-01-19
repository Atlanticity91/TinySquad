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
TinySound::TinySound( )
	: TinySound{ TINY_NO_ENTITY } 
{ }

TinySound::TinySound( const tiny_hash entity_hash )
	: TinyComponent{ entity_hash },
	_cue{ TA_TYPE_CUE },
	_handle{ TINY_UINT_MAX },
	_volume{ 1.f }
{ }

bool TinySound::Create( TinyGame* game, TinyEngine& engine ) {
	return true;
}

void TinySound::Delete( TinyGame* game, TinyEngine& engine ) {
	auto& audio = engine.GetAudio( );

	audio.Release( _handle );
}

bool TinySound::SetCue( TinyGame* game, const tiny_string& cue_name ) {
	auto& assets = game->GetAssets( );
	auto state   = false;

	if ( assets.GetExist( cue_name ) ) {
		assets.Release( game, _cue );

		_cue.Hash = tiny_hash{ cue_name };

		state = assets.Acquire( game, _cue );

		if ( !state )
			_cue.Hash = 0;
	}

	return state;
}

bool TinySound::Play( TinyGame* game ) { return Play( game, true ); }

bool TinySound::Play( TinyGame* game, bool imediate ) {
	auto& assets = game->GetAssets( );
	auto& audio  = game->GetAudio( );
	auto state   = false;
	auto* cue	 = assets.GetAssetAs<TinyCue>( _cue );

	if ( cue ) {
		if ( !audio.GetExist( _handle ) )
			_handle = audio.Acquire( cue->GetFormat( ) );

		state = audio.Submit( _handle, cue->GetBuffer( ) );

		if ( state && imediate )
			state = audio.Start( _handle );
	}

	return state;
}

void TinySound::Stop( TinyGame* game ) {
	auto& audio = game->GetAudio( );

	audio.Stop( _handle );
	audio.Release( _handle );
}

void TinySound::DisplayWidget(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) { 
	auto& audio = engine.GetAudio( );

	TinyComponent::DisplayWidget( game, engine, toolbox );

	toolbox.DisplayAsset( game, "Cue", _cue );

	if ( TinyImGui::InputSlider( "Volume", _volume, .0f, 224.f ) )
		audio.SetVolume( _handle, _volume );

	if ( _cue.GetIsValid( ) && ImGui::Button( "Play" ) ) {
		
		auto* c = engine.GetAssets( ).GetAssetAs<TinyCue>( _cue );
		auto v = audio.Acquire( c->GetFormat( ) );
		
		audio.Submit( v, c->GetBuffer( ) );
		audio.Start( v );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAsset& TinySound::GetCue( ) { return _cue; }

float TinySound::GetVolume( ) const { return _volume; }
