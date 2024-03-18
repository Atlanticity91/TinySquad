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
	: _memory{ nullptr },
	_offset{ 0 },
	_size{ 0 }
{ }

TinyVirtualFile::TinyVirtualFile( const tiny_storage& storage )
	: TinyVirtualFile{ }
{ 
	Asign( storage );
}

bool TinyVirtualFile::Skip( tiny_uint count ) {
	_offset += count * tiny_sizeof( tiny_ubyte );

	return _offset < _size;
}

tiny_uint TinyVirtualFile::Read( tiny_uint size, c_pointer buffer ) {
	if ( _offset < _size ) {
		if ( _offset + size > _size )
			size = _size - _offset;

		if ( Tiny::Memcpy( tiny_cast( _memory + _offset, const c_pointer ), buffer, size ) )
			_offset += size;
	} else
		size = 0;

	return size;
}

tiny_uint TinyVirtualFile::Write( tiny_uint size, const c_pointer buffer ) {
	if ( _offset < _size ) {
		if ( _offset + size > _size )
			size = _size - _offset;

		if ( Tiny::Memcpy( buffer, tiny_cast( _memory + _offset, c_pointer ), size ) )
			_offset += size;
	} else
		size = 0;

	return size;
}

TinyVirtualFile& TinyVirtualFile::Asign( const tiny_storage& storage ) {
	if ( storage ) {
		_memory = tiny_cast( storage.GetAddress( ), tiny_pointer );
		_offset = 0;
		_size   = tiny_cast( storage.Capacity, tiny_uint );
	}

	return tiny_self;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyVirtualFile::GetIsValid( ) const { return _memory != nullptr && _offset < _size; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyVirtualFile::operator bool( ) const { return GetIsValid( ); }

TinyVirtualFile& TinyVirtualFile::operator=( const tiny_storage& storage ) {
	return Asign( storage );
}
