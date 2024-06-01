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
	: TinyAsset{ TA_TYPE_CUE },
    m_format{ },
    m_context{ },
	m_storage{ } 
{ }

bool TinyCue::Create( const TinyCueBuilder& builder ) {
    return true;
}

void TinyCue::Terminate( TinyGame* game ) { tiny_deallocate( m_storage ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const TinyCueFormat& TinyCue::GetFormat( ) const { return m_format; }

const TinyCueContext& TinyCue::GetContext( ) const { return m_context; }

const tiny_storage& TinyCue::GetStorage( ) const { return m_storage; }

TinyCueBuffer TinyCue::GetBuffer( ) const {
    auto* audio_data = tiny_cast( m_storage.GetAddress( ), const BYTE* );

    return { 
        XAUDIO2_END_OF_STREAM,
        tiny_cast( m_storage.Capacity, tiny_uint ), audio_data,
        0, 0,
        0, 0,
        1,
        tiny_cast( tiny_rvalue( m_context ), native_pointer )
    };
}
