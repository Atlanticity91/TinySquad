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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAudioDevice::TinyAudioDevice( )
	: _device{ nullptr },
	_master{ nullptr } 
{ }

bool TinyAudioDevice::Create( ) {
	auto state = !FAILED( XAudio2Create( &_device, XAUDIO2_NO_FLAG, XAUDIO2_DEFAULT_PROCESSOR ) );

	#	ifdef TINY_DEBUG
	if ( state ) {
		auto autio_debug = XAUDIO2_DEBUG_CONFIGURATION{ };

		autio_debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
		autio_debug.BreakMask = XAUDIO2_LOG_ERRORS;

		_device->SetDebugConfiguration( tiny_rvalue( autio_debug ), nullptr );
	}
	#	endif

	if ( state ) {
		state = !FAILED( _device->CreateMasteringVoice( tiny_rvalue( _master ) ) ) &&
				!FAILED( _device->StartEngine( ) );
	}

	return state;
}

void TinyAudioDevice::Terminate( ) { 
	if ( _master )
		_master->DestroyVoice( ); 
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAudioDevice::operator IXAudio2* ( ) { return _device; }

TinyAudioDevice::operator IXAudio2MasteringVoice* ( ) { return _master; }

IXAudio2* TinyAudioDevice::operator->( ) { return _device; }
