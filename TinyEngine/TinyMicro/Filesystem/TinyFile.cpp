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
 * @creation : 07/11/2023
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
TinyFile::TinyFile( ) 
	: TinyFile{ { } }
{ }

TinyFile::TinyFile( const Tiny::File& file )
	: _file{ file }
{ }

TinyFile::~TinyFile( ) {
	if ( Tiny::GetFileIsValid( _file ) ) 
		Tiny::FileClose( _file );
}

bool TinyFile::Seek( tiny_uint offset ) { return Seek( Tiny::TF_ORIGIN_CURSOR, offset ); }

bool TinyFile::Seek( Tiny::FileOrigin origin, tiny_uint offset ) {
	return Tiny::FileSeek( _file, origin, offset );
}

tiny_uint TinyFile::Read( tiny_uint length, c_pointer data ) {
	auto count = tiny_cast( 0, tiny_uint );
	
	if ( GetCan( Tiny::TF_ACCESS_READ ) )
		count = Tiny::FileRead( _file, length, data );

	return count;
}

tiny_uint TinyFile::Write( tiny_uint length, const c_pointer data ) {
	auto count = tiny_cast( 0, tiny_uint );

	if ( GetCan( Tiny::TF_ACCESS_WRITE ) )
		count = Tiny::FileWrite( _file, length, data );

	return count;
}

tiny_uint TinyFile::ReadAll( tiny_uint length, c_pointer& storage ) {
	auto size = tiny_cast( 0, tiny_uint );

	if ( _file.Size <= length )
		size = Read( _file.Size, storage );

	return size;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyFile::GetIsValid( ) const { return Tiny::GetFileIsValid( _file ); }

bool TinyFile::GetCan( Tiny::FileAccesses access ) const { 
	return Tiny::GetFileCan( _file, access );
}

Tiny::FileAccesses TinyFile::GetAccess( ) const { return _file.Access; }

tiny_uint TinyFile::GetSize( ) const { return _file.Size; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyFile::operator bool( ) const { return GetIsValid( ); }

TinyFile& TinyFile::operator=( Tiny::File & handle ) {
	if ( Tiny::GetFileIsValid( _file ) )
		Tiny::FileClose( _file );
	
	_file = handle;

	return tiny_self;
}
