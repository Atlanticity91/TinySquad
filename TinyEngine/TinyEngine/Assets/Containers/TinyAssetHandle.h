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
 * @creation : 03/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyAssetTypes.h"

te_struct TinyAssetHandle {

	tiny_uint Type;
	tiny_hash Hash;

	TinyAssetHandle( );

	TinyAssetHandle( TinyAssetTypes type );

	TinyAssetHandle( tiny_uint type );

	TinyAssetHandle( tiny_uint type, const tiny_string& asset );

	bool GetIsValid( ) const;

	bool GetEqual( const TinyAssetHandle& other ) const;

	bool GetNotEqual( const TinyAssetHandle& other ) const;

	operator bool( ) const;

	operator tiny_hash ( ) const;

	TinyAssetHandle& operator=( const TinyAssetHandle& other );

	bool operator==( const TinyAssetHandle& other ) const;

	bool operator!=( const TinyAssetHandle& other ) const;

};
