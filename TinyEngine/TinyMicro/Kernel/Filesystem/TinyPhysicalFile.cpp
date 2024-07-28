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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyPhysicalFile::TinyPhysicalFile( ) 
	: TinyFile{ },
	m_handle{ }
{ }

TinyPhysicalFile::~TinyPhysicalFile( ) {
	if ( Tiny::GetFileIsValid( m_handle ) )
		Tiny::FileClose( m_handle );
}

bool TinyPhysicalFile::Seek( const TinyFileOrigin origin, const tiny_ulong offset ) {
	return Tiny::FileSeek( m_handle, origin, offset );
}

tiny_ulong TinyPhysicalFile::Read( const tiny_ulong length, native_pointer data ) {
	TINY_ASSERT( length > 0, "You can't read 0 bytes from file" );
	TINY_ASSERT( data != nullptr, "You can't read bytes to an undefined data buffer" );

	auto count = tiny_cast( 0, tiny_ulong );

	if ( GetCan( TF_ACCESS_READ ) )
		count = Tiny::FileRead( m_handle, length, data );

	return count;
}

tiny_ulong TinyPhysicalFile::Write( const tiny_ulong length, const native_pointer data ) {
	TINY_ASSERT( length > 0, "You can't write 0 bytes from file" );
	TINY_ASSERT( data != nullptr, "You can't write bytes from an undefined data buffer" );

	auto count = tiny_cast( 0, tiny_ulong );

	if ( GetCan( TF_ACCESS_WRITE ) )
		count = Tiny::FileWrite( m_handle, length, data );

	return count;
}

bool TinyPhysicalFile::ReadAll( const tiny_ulong length, native_pointer& storage ) {
	TINY_ASSERT( m_handle.Size <= length, "You can't read all file bytes to a 0 length buffer" );

	auto state = false;

	if ( GetCan( TF_ACCESS_READ ) )
		state = Tiny::FileRead( m_handle, length, storage ) > 0;

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyPhysicalFile::GetIsValid( ) const { return Tiny::GetFileIsValid( m_handle ); }

bool TinyPhysicalFile::GetCan( TinyFileAccesses access ) const {
	return Tiny::GetFileCan( m_handle, access );
}

TinyFileAccesses TinyPhysicalFile::GetAccess( ) const { return m_handle.Access; }

tiny_ulong TinyPhysicalFile::GetSize( ) const { return m_handle.Size; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyPhysicalFile& TinyPhysicalFile::operator=( const tiny_file& file ) {
	if ( Tiny::GetFileIsValid( file ) ) {
		if ( Tiny::GetFileIsValid( m_handle ) )
			Tiny::FileClose( m_handle );

		m_handle = file;
	}

	return tiny_self;
}
