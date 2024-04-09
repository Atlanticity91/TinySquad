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
 * @creation : 06/04/2024
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
TinyAssetHeader::TinyAssetHeader( )
	: TinyAssetHeader{ tiny_cast( TA_TYPE_UNDEFINED, tiny_uint ) }
{ }

TinyAssetHeader::TinyAssetHeader( tiny_uint type )
	: Magic{ },
	Version{ TINY_ENGINE_VERSION },
	Type{ type },
	Padding{ 0xffffffff } 
{
	Tiny::Memcpy( TinyAssetMagic, Magic, 4 );
	Date = Tiny::GetDate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAssetHeader::GetIsAsset( ) const {
	auto tiny_magic = tiny_lvalue( tiny_cast( TinyAssetMagic, tiny_uint* ) );
	auto file_magic = tiny_lvalue( tiny_cast( Magic, tiny_uint* ) );

	return tiny_magic == file_magic && Type < TA_TYPE_COUNT;
}

bool TinyAssetHeader::GetIsAsset( const TinyAssetTypes type ) const {
	return GetIsAsset( tiny_cast( type, tiny_uint ) );
}

bool TinyAssetHeader::GetIsAsset( const tiny_uint type ) const {
	auto tiny_magic = tiny_lvalue( tiny_cast( TinyAssetMagic, tiny_uint* ) );
	auto file_magic = tiny_lvalue( tiny_cast( Magic, tiny_uint* ) );

	return tiny_magic == file_magic && Type == type;
}
