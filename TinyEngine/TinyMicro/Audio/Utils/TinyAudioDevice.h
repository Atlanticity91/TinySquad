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
 * @creation : 03/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Inputs/TinyInputManager.h>

#define XAUDIO2_NO_FLAG 0

tm_class TinyAudioDevice final {

private:
	IXAudio2*				_device;
	IXAudio2MasteringVoice* _master;

public:
	TinyAudioDevice( );

	~TinyAudioDevice( ) = default;

	bool Create( );

	void Terminate( );

public:
	operator IXAudio2* ( );

	operator IXAudio2MasteringVoice* ( );

	IXAudio2* operator->( );

};
