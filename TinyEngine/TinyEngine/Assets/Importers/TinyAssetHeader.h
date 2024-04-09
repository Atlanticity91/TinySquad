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

#pragma once

#include <TinyEngine/Utils/TinyNativeRegister.h>

static const char TinyAssetMagic[ 4 ] = "TMA";

te_struct TinyAssetHeader {

	char Magic[ 4 ];
	tiny_uint Version;
	tiny_uint Type;
	Tiny::Date Date;
	tiny_uint Padding;

	TinyAssetHeader( );

	TinyAssetHeader( tiny_uint type );

	bool GetIsAsset( ) const;

	tiny_inline bool GetIsAsset( const TinyAssetTypes type ) const;

	bool GetIsAsset( const tiny_uint type ) const;

};
