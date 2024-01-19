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
 * @creation : 04/01/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAudioPool::TinyAudioPool( )
	: _voices{ } 
{ }

tiny_uint TinyAudioPool::Acquire( TinyAudioDevice& device, const TinyCueFormat& format ) {
	auto voice_id = MAX_VOICES;

	while ( voice_id-- > 0 && !_voices[ voice_id ].GetIsEmpty( ) );

	if ( voice_id < MAX_VOICES && !_voices[ voice_id ].Acquire( device, format ) )
		voice_id = TINY_UINT_MAX;

	return voice_id;
}

void TinyAudioPool::Release( tiny_uint voice_id ) { _voices[ voice_id ].Release( ); }

void TinyAudioPool::Tick( TinyInputManager& inputs ) {
	auto voice_state = XAUDIO2_VOICE_STATE{ };
	auto voice_id    = MAX_VOICES;
     
    while ( voice_id-- > 0 ) {
        auto& voice = _voices[ voice_id ];

        if ( voice.GetIsEmpty( ) )
            continue;

        voice->GetState( tiny_rvalue( voice_state ) );
		
		if ( voice_state.BuffersQueued == 0 )
			voice.Release( );
    }
}

void TinyAudioPool::Terminate( ) {
	for ( auto& voice : _voices ) {
		if ( voice.GetIsEmpty( ) )
			continue;

		voice.Release( );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyAudioPool::GetCapacity( ) const { return MAX_VOICES; }

bool TinyAudioPool::GetIsValid( tiny_uint voice_id ) const {
	return voice_id < GetCapacity( ) && !_voices[ voice_id ].GetIsEmpty( );
}

TinyAudioVoice* TinyAudioPool::GetVoice( tiny_uint voice_id ) {
	auto voice = tiny_cast( nullptr, TinyAudioVoice* );

	if ( GetIsValid( voice_id ) )
		voice = tiny_rvalue( _voices[ voice_id ] );

	return voice;
}
