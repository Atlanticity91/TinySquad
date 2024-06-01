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
 * @creation : 11/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Voices/TinyAudioPool.h"

tm_class TinyAudioManager final : tiny_inherit( ITinyManager ) {

private:
	TinyAudioDevice m_device;
	TinyAudioPool m_pool;

public:
	TinyAudioManager( );

	~TinyAudioManager( ) = default;

	tiny_implement( bool Initialize( TinyFilesystem& file_system, TinyWindow& window ) );

	tiny_inline tiny_uint Acquire( const TinyCueFormat& format );

	bool SetVolume( tiny_uint voice_id, float volume );

	bool Submit( tiny_uint voice_id, const TinyCueBuffer& audio_buffer );

	bool Start( tiny_uint voice_id );

	void Stop( tiny_uint voice_id );

	void Release( tiny_uint& voice_id );

	tiny_inline void Tick( TinyInputManager& inputs );

	tiny_implement( void Terminate( TinyFilesystem& file_system, TinyWindow& window ) );

public:
	TinyAudioDevice& GetDevice( );

	TinyAudioPool& GetPool( );

	bool GetExist( tiny_uint voice_id );

};
