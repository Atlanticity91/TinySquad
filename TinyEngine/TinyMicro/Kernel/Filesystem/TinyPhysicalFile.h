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
 * @creation : 23/05/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyVirtualFile.h"

tm_class TinyPhysicalFile final : tiny_inherit( TinyFile ) {

private:
	tiny_file m_handle;

public:
	TinyPhysicalFile( );

	~TinyPhysicalFile( );

	tiny_implement( bool Seek( const TinyFileOrigin origin, const tiny_ulong offset ) );

	tiny_implement( tiny_uint Read( const tiny_uint length, native_pointer data ) );

	tiny_implement( tiny_uint Write( const tiny_uint length, const native_pointer data ) );

	tiny_implement( bool ReadAll( const tiny_ulong length, native_pointer& storage ) );

public:
	tiny_implement( bool GetIsValid( ) const );

	tiny_implement( TinyFileAccesses GetAccess( ) const );

	tiny_implement( bool GetCan( TinyFileAccesses access ) const );

	tiny_implement( tiny_ulong GetSize( ) const );

public:
	TinyPhysicalFile& operator=( const tiny_file& file );

};
