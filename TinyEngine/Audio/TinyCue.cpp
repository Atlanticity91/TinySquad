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
 * @creation : 04/01/2024
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
TinyCue::TinyCue( )
	: _format{ },
    _context{ },
	_storage{ } 
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyCueFormat& TinyCue::GetFormat( ) { return _format; }

TinyCueContext& TinyCue::GetContext( ) { return _context; }

tiny_storage& TinyCue::GetStorage( ) { return _storage; }

TinyCueBuffer TinyCue::GetBuffer( ) {
    auto* address = _storage.GetAddress( );

    return { 
        XAUDIO2_END_OF_STREAM,
        tiny_cast( _storage.Capacity, tiny_uint ), tiny_cast( address, const BYTE* ),
        0, 0,
        0, 0,
        1,
        tiny_cast( tiny_rvalue( _context ), c_ptr )
    };
}
