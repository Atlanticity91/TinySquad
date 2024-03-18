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

#include "TinyAudioVoice.h"

tm_class TinyAudioPool final {

	static const tiny_uint MAX_VOICES = 32;

private:
	tiny_array<TinyAudioVoice, MAX_VOICES> _voices;

public:
	TinyAudioPool( );

	~TinyAudioPool( ) = default;

	tiny_uint Acquire( TinyAudioDevice& device, const TinyCueFormat& format );

	void Release( tiny_uint voice_id );

	void Tick( TinyInputManager& inputs );

	void Terminate( );

public:
	tiny_uint GetCapacity( ) const;

	bool GetIsValid( tiny_uint voice_id ) const;

	TinyAudioVoice* GetVoice( tiny_uint voice_id );

};
