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

#pragma once

#include <TinyMicro/Audio/Utils/TinyAudioDevice.h>

typedef WAVEFORMATEX TinyCueFormat;
typedef XAUDIO2_BUFFER TinyCueBuffer;

tm_class TinyAudioVoice final {

private:
	IXAudio2SourceVoice* m_voice;

public:
	TinyAudioVoice( );

	~TinyAudioVoice( ) = default;

	bool Acquire( TinyAudioDevice& device, const TinyCueFormat& format );

	void SetVolume( float volume );

	bool Submit( const XAUDIO2_BUFFER& autio_buffer );

	bool Start( );

	void Stop( );

	void Release( );

public:
	bool GetIsEmpty( ) const;

public:
	IXAudio2SourceVoice* operator->( );

};
