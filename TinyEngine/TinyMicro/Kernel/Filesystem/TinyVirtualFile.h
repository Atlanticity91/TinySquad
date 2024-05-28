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
 * @creation : 05/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyFile.h"

tm_class TinyVirtualFile final : tiny_inherit( TinyFile ) { 

private:
	TinyFileAccesses _access;

	tiny_pointer  _memory;
	tiny_ulong _offset;
	tiny_ulong _size;

public:
	TinyVirtualFile( );

	TinyVirtualFile( TinyFileAccesses access, const tiny_storage& storage );

	~TinyVirtualFile( ) = default;

	tiny_implement( bool Seek( TinyFileOrigin origin, tiny_ulong offset ) );

	tiny_implement( tiny_uint Read( tiny_uint length, native_pointer data ) );

	tiny_implement( tiny_uint Write( tiny_uint length, const native_pointer data ) );

	tiny_implement( bool ReadAll( const tiny_ulong length, native_pointer& storage ) );

private:
	TinyVirtualFile( TinyFileAccesses access, const tiny_ulong size );

public:
	tiny_implement( bool GetIsValid( ) const );

	tiny_implement( TinyFileAccesses GetAccess( ) const );

	tiny_implement( bool GetCan( TinyFileAccesses access ) const );

	tiny_implement( tiny_ulong GetSize( ) const );

};
