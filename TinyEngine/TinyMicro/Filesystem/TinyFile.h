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

#pragma once

#include "TinyVirtualFile.h"

tm_class TinyFile final {

private:
	Tiny::File _file;

public:
	TinyFile( );

	TinyFile( const Tiny::File& file );

	~TinyFile( );

	tiny_inline bool Seek( tiny_uint offset );

	bool Seek( Tiny::FileOrigin origin, tiny_uint offset );

	tiny_uint Read( tiny_uint length, c_pointer data );

	tiny_uint Write( tiny_uint length, const c_pointer data );

	tiny_uint ReadAll( tiny_uint length, c_pointer& storage );

public:
	template<typename Type>
	bool Seek( ) { 
		return Seek( Tiny::TF_ORIGIN_CURSOR, tiny_sizeof( Type ) );
	};

	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	tiny_uint Read( Type& element ) { 
		auto* data = tiny_cast( tiny_rvalue( element ), c_pointer );

		return Read( tiny_sizeof( Type ), data );
	};

	template<>
	tiny_uint Read<std::string>( std::string& element ) {
		auto size = tiny_cast( 0, tiny_uint );

		Read( size );

		if ( size > 0 ) {
			element.resize( size );

			auto* data = tiny_cast( element.c_str( ), c_pointer );

			size = Read( size, data );
		}

		return size;
	};

	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	tiny_uint Read( tiny_list<Type>& list ) {
		auto size = tiny_cast( 0, tiny_uint );

		Read( size );

		if ( size > 0 ) {
			list = size;

			size = 0;

			for ( auto& element : list )
				size += Read( element );
		} else
			list.clear( );

		return size;
	};

	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	tiny_uint Read( tiny_map<Type>& map ) {
		auto count = tiny_cast( 0, tiny_uint );
		auto size  = tiny_cast( 0, tiny_uint );

		Read( count );

		if ( count > 0 ) {
			auto element = Type{ };
			auto alias   = std::string{ };

			while ( count-- > 0 ) {
				size += Read( alias );
				size += Read( element );

				map.emplace( alias, element );
			}
		}

		return size;
	};

	template<typename Type, tiny_uint Length>
		requires ( !std::is_pointer<Type>::value&& Length > 0 )
	tiny_uint Read( tiny_array<Type, Length>& array_ ) {
		auto size = tiny_cast( 0, tiny_uint );

		Read( size );

		if ( size > 0 ) {
			size = 0;

			for ( auto& element : array_ )
				size += Read( element );
		}

		return size;
	};

	template<tiny_uint Length>
		requires ( Length > 0 )
	tiny_uint Read( tiny_buffer<Length>& buffer ) {
		auto* data = buffer.get( );
		auto size  = tiny_cast( 0, tiny_uint );

		Read( size );

		if ( size > 0 )
			size = Read( size, data );

		return size;
	};

	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	tiny_uint Write( const Type& element ) { 
		auto* data = tiny_cast( tiny_rvalue( element ), const c_pointer );

		return Write( tiny_sizeof( Type ), data );
	};

	template<>
	tiny_uint Write<std::string>( const std::string& text ) {
		return Write<tiny_string>( text );
	};

	template<>
	tiny_uint Write<tiny_string>( const tiny_string& text ) { 
		auto length = text.length( );
		auto* data  = tiny_cast( text.as_chars( ), const c_pointer );

		Write( length );

		return Write( length * tiny_sizeof( char ), data );
	};

	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	tiny_uint Write( const tiny_list<Type>& list ) {
		auto size = list.size( );

		Write( size );

		for ( auto& element : list )
			size += Write( element );

		return size;
	};

	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	tiny_uint Write( const tiny_map<Type>& map ) { 
		auto size = map.size( );

		Write( size );

		size = 0;

		for ( auto& element : map ) {
			size += Write( element.String );
			size += Write( element.Data );
		}

		return size;
	};

	template<typename Type, tiny_uint Length>
		requires ( !std::is_pointer<Type>::value && Length > 0 )
	tiny_uint Write( const tiny_array<Type, Length>& array_ ) {
		auto* data = array_.data( );
		auto size  = Length;

		Write( size );

		for ( auto& element : array_ )
			size += Write( element );

		return size;
	};

	template<tiny_uint Length>
		requires ( Length > 0 )
	tiny_uint Write( const tiny_buffer<Length>& buffer ) { 
		auto length = buffer.length( );
		auto* data  = buffer.get( );

		Write( length );

		return Write( length, data );
	};

	template<typename... Args>
	tiny_uint Write( const tiny_string& format, const Args&... args ) {
		auto length = format.length( );
		auto* data  = tiny_cast( format.as_chars( ), const c_pointer );

		tiny_compile_if( tiny_countof( Args ) > 0 ) {
			auto buffer = tiny_buffer<256>{ };

			Tiny::Sprintf( buffer, format, args... );

			length = buffer.size( );
			data   = buffer.get( );
		}

		Write( length );

		return Write( length * tiny_sizeof( char ), data );
	};

public:
	bool GetIsValid( ) const;

	bool GetCan( Tiny::FileAccesses access ) const;

	Tiny::FileAccesses GetAccess( ) const;

	tiny_uint GetSize( ) const;

public:
	operator bool( ) const;

	TinyFile& operator=( Tiny::File& handle );

public:
	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	TinyFile& operator>>( Type& element ) { 
		Read<Type>( element );

		return tiny_self; 
	};

	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	TinyFile& operator<<( const Type& element ) { 
		Write<Type>( element );

		return tiny_self; 
	};

};
