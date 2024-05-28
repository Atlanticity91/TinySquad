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
 * @creation : 13/10/2023
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyHash.h"

tm_class tiny_uuid final {

private:
	tiny_ulong _uuid;

public:
	tiny_uuid( );

	tiny_uuid( const tiny_ulong uuid );

	tiny_uuid( const tiny_uuid& other );

	~tiny_uuid( ) = default;

	tiny_uuid& asign( const tiny_ulong uuid );

	tiny_inline tiny_uuid& asign( const tiny_uuid& other );

	bool equal( const tiny_ulong uuid ) const;

	tiny_inline bool equal( const tiny_uuid& other ) const;

	bool not_equal( const tiny_ulong uuid ) const;

	tiny_inline bool not_equal( const tiny_uuid& other ) const;

public:
	operator tiny_ulong ( ) const;

	tiny_uuid& operator=( const tiny_ulong uuid );

	tiny_uuid& operator=( const tiny_uuid& other );

	bool operator==( const tiny_ulong uuid ) const;

	bool operator==( const tiny_uuid& other ) const;

	bool operator!=( const tiny_ulong uuid ) const;

	bool operator!=( const tiny_uuid& other ) const;

};
