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
TinyAudioVoice::TinyAudioVoice( )
	: _voice{ nullptr } 
{ }

bool TinyAudioVoice::Acquire( TinyAudioDevice& device, const TinyCueFormat& format ) {
	auto master = XAUDIO2_SEND_DESCRIPTOR{ XAUDIO2_NO_FLAG, device };
	auto sends  = XAUDIO2_VOICE_SENDS{ 1, tiny_rvalue( master ) };

	return !FAILED( device->CreateSourceVoice( tiny_rvalue( _voice ), tiny_rvalue( format ), 0, 2.0f, nullptr, &sends ) );
}

void TinyAudioVoice::SetVolume( float volume ) { _voice->SetVolume( volume ); }

bool TinyAudioVoice::Submit( const XAUDIO2_BUFFER& autio_buffer ) {
	return !FAILED( _voice->SubmitSourceBuffer( tiny_rvalue( autio_buffer ), nullptr ) );
}

bool TinyAudioVoice::Start( ) { 
	//_voice->SetVolume( 1.f );

	return !FAILED( _voice->Start( ) ); 
}

void TinyAudioVoice::Stop( ) {
	_voice->Stop( );
	_voice->FlushSourceBuffers( );
}

void TinyAudioVoice::Release( ) {
	if ( _voice ) {
		Stop( );

		_voice->DestroyVoice( );

		_voice = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAudioVoice::GetIsEmpty( ) const { return _voice == nullptr; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
IXAudio2SourceVoice* TinyAudioVoice::operator->( ) { return _voice; }
