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
 * @creation : 18/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyFont::TinyFont( )
	: TinyAsset{ TA_TYPE_FONT },
	m_range{ 2.f },
	m_miter{ 1.f },
	m_texture{ },
	m_geometry{ }
{ }

void TinyFont::Terminate( TinyGame* game ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const tiny_vec2& TinyFont::GetRange( ) const { return m_range; }

const tiny_vec2& TinyFont::GetMiter( ) const { return m_miter; }

const TinyCharGeometry& TinyFont::GetGeometry( char character ) const {
	return m_geometry[ 0 ]; 
}

const VkDescriptorImageInfo& TinyFont::GetTexure( ) const { 
	return tiny_lvalue( m_texture.GetDescriptor( ) );
}
