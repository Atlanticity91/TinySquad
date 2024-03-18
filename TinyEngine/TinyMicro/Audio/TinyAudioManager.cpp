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
 * @creation : 12/10/2023
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
TinyAudioManager::TinyAudioManager( ) 
	: ITinyManager{ },
	_device{ },
    _pool{ }
{ }

bool TinyAudioManager::Initialize( TinyFilesystem& file_system, TinyWindow& window ) {
	return _device.Create( );
}

tiny_uint TinyAudioManager::Acquire( const TinyCueFormat& format ) {
    return _pool.Acquire( _device, format );
}

bool TinyAudioManager::SetVolume( tiny_uint voice_id, float volume ) {
    auto* voice = _pool.GetVoice( voice_id );

    if ( voice )
        voice->SetVolume( volume );

    return voice;
}

bool TinyAudioManager::Submit( tiny_uint voice_id, const TinyCueBuffer& audio_buffer ) {
    auto* voice = _pool.GetVoice( voice_id );

    return voice && voice->Submit( audio_buffer );
}

bool TinyAudioManager::Start( tiny_uint voice_id ) {
    auto* voice = _pool.GetVoice( voice_id );

    return voice && voice->Start( );
}

void TinyAudioManager::Stop( tiny_uint voice_id ) {
    auto* voice = _pool.GetVoice( voice_id );

    if ( voice ) 
        voice->Stop( );
}

void TinyAudioManager::Release( tiny_uint& voice_id ) {
    if ( voice_id < _pool.GetCapacity( ) )
        _pool.Release( voice_id );

    voice_id = TINY_UINT_MAX;
}

void TinyAudioManager::Tick( TinyInputManager& inputs ) { _pool.Tick( inputs ); }

void TinyAudioManager::Terminate( TinyFilesystem& file_system, TinyWindow& window ) {
    _pool.Terminate( );
    _device.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAudioDevice& TinyAudioManager::GetDevice( ) { return _device; }

TinyAudioPool& TinyAudioManager::GetPool( ) { return _pool; }

bool TinyAudioManager::GetExist( tiny_uint voice_id ) { 
    return _pool.GetVoice( voice_id ) != nullptr; 
} 
