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
	: m_voice{ nullptr } 
{ }

bool TinyAudioVoice::Acquire( TinyAudioDevice& device, const TinyCueFormat& format ) {
	auto master = XAUDIO2_SEND_DESCRIPTOR{ XAUDIO2_NO_FLAG, device };
	auto sends  = XAUDIO2_VOICE_SENDS{ 1, tiny_rvalue( master ) };

	return !FAILED( device->CreateSourceVoice( tiny_rvalue( m_voice ), tiny_rvalue( format ), 0, 2.0f, nullptr, tiny_rvalue( sends ) ) );
}

void TinyAudioVoice::SetVolume( float volume ) { m_voice->SetVolume( volume ); }

bool TinyAudioVoice::Submit( const XAUDIO2_BUFFER& autio_buffer ) {
	return !FAILED( m_voice->SubmitSourceBuffer( tiny_rvalue( autio_buffer ), nullptr ) );
}

bool TinyAudioVoice::Start( ) { 
	//_voice->SetVolume( 1.f );

	return !FAILED( m_voice->Start( ) ); 
}

void TinyAudioVoice::Stop( ) {
	m_voice->Stop( );
	m_voice->FlushSourceBuffers( );
}

void TinyAudioVoice::Release( ) {
	if ( m_voice ) {
		Stop( );

		m_voice->DestroyVoice( );

		m_voice = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAudioVoice::GetIsEmpty( ) const { return m_voice == nullptr; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
IXAudio2SourceVoice* TinyAudioVoice::operator->( ) { return m_voice; }
