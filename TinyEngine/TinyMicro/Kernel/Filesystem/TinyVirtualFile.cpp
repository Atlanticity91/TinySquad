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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyVirtualFile::TinyVirtualFile( ) 
	: TinyVirtualFile{ TF_ACCESS_READ, 0 }
{ }

TinyVirtualFile::TinyVirtualFile( TinyFileAccesses access, const tiny_storage& storage )
	: TinyVirtualFile{ access, storage.Capacity } 
{
	_memory = tiny_cast( storage.GetAddress( ), tiny_pointer );
}

bool TinyVirtualFile::Seek( TinyFileOrigin origin, tiny_ulong offset ) {
	auto state = GetIsValid( ) && offset > 0;

	if ( state ) {
		if ( origin == TF_ORIGIN_BEGIN )
			_offset = offset;
		else if ( origin == TF_ORIGIN_CURSOR ) {
			if ( _size - offset >= _offset )
				_offset += offset;

			_offset = _size;
		} else
			_offset = _size - offset;
	}

	return state;
}

tiny_uint TinyVirtualFile::Read( tiny_uint length, native_pointer data ) {
	TINY_ASSERT( length > 0, "You can't read 0 bytes from file" );
	TINY_ASSERT( data != nullptr, "You can't read bytes to an undefined data buffer" );

	auto size = tiny_cast( 0, tiny_uint );

	if ( GetCan( TF_ACCESS_READ ) ) { }

	return size;
}

tiny_uint TinyVirtualFile::Write( tiny_uint length, const native_pointer data ) {
	TINY_ASSERT( length > 0, "You can't write 0 bytes from file" );
	TINY_ASSERT( data != nullptr, "You can't write bytes from an undefined data buffer" );

	auto size = tiny_cast( 0, tiny_uint );

	return size;
}

bool TinyVirtualFile::ReadAll( const tiny_ulong length, native_pointer& storage ) {
	TINY_ASSERT( _size <= length, "You can't read all file bytes to a 0 length buffer" );

	auto state = false;

	if ( GetCan( TF_ACCESS_READ ) ) {
		auto* address = tiny_cast( _memory, const native_pointer );

		state = Tiny::Memcpy( address, storage, length );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyVirtualFile::TinyVirtualFile( TinyFileAccesses access, const tiny_ulong size )
	: _access{ access },
	_memory{ nullptr },
	_offset{ 0 },
	_size{ size }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyVirtualFile::GetIsValid( ) const { return _memory != nullptr && _size > 0; }

TinyFileAccesses TinyVirtualFile::GetAccess( ) const { return _access; }

bool TinyVirtualFile::GetCan( TinyFileAccesses access ) const {
	return  GetIsValid( ) &&
			_offset < _size &&
			_access == tiny_cast( access ^ TF_ACCESS_BINARY, TinyFileAccesses );
}

tiny_ulong TinyVirtualFile::GetSize( ) const { return _size; }
