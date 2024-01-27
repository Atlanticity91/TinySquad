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
	tiny_uint Read( Type& data ) {
		auto* _data = tiny_rvalue( data );

		return Read( tiny_sizeof( Type ), tiny_cast( _data, c_pointer ) );
	};

	template<>
	tiny_uint Read<std::string>( std::string& text ) {
		auto text_str = text.c_str( );
		auto length   = tiny_cast( 0, tiny_uint );

		if ( Read( tiny_sizeof( tiny_uint ), tiny_rvalue( length ) ) > 0 )
			text.resize( tiny_cast( length + 1, size_t ), '\0' );

		return Read( length, tiny_cast( text_str, c_pointer ) );
	};

	template<tiny_uint Length>
	tiny_uint Read( tiny_buffer<Length>& buffer ) {
		return Read( Length, buffer );
	};

	template<typename Type>
	tiny_uint Read( tiny_list<Type>& list ) { 
		auto size = tiny_cast( 0, tiny_uint );

		Read( size );

		if ( size > 0 ) {
			list = size;

			size = Read( size * tiny_sizeof( Type ), list.as_pointer( ) );
		}

		return size;
	};

	template<typename Type>
	tiny_uint Read( const tiny_map<Type>& map ) {
		auto length = tiny_cast( 0, tiny_uint );
		auto size   = tiny_cast( 0, tiny_uint );

		Read( size );

		if ( size > 0 ) {
			map = size;

			for ( auto& node : map ) {
				length += Read( node.String );
				length += Read( node.Hash );
				length += Read( node.Data );
			}
		}

		return length;
	};

	template<>
	tiny_uint Read<std::string>( tiny_list<std::string>& list ) {
		auto size  = tiny_cast( 0, tiny_uint );
		auto count = tiny_cast( 0, tiny_uint );

		Read( size );

		if ( size > 0 ) {
			list = size;

			for ( auto& text : list )
				Read( text );
		}

		return count;
	};

	template<typename Type>
	tiny_uint Write( const Type& data ) {
		auto* _data = tiny_rvalue( data );

		return Write( tiny_sizeof( Type ), tiny_cast( _data, const c_pointer ) );
	};

	template<>
	tiny_uint Write<std::string>( const std::string& text ) { 
		auto tmp_str = tiny_string{ text };

		return Write( tmp_str );
	};

	template<>
	tiny_uint Write<tiny_string>( const tiny_string& text ) {
		auto length = text.length( );

		length = Write( tiny_sizeof( tiny_uint ), tiny_cast( tiny_rvalue( length ), const c_pointer ) );

		if ( length > 0 )
			length = Write( text.length( ), tiny_cast( text.get( ), const c_pointer ) );

		return length;
	};

	template<tiny_uint Length>
	tiny_uint Write( const tiny_buffer<Length>& buffer ) {
		return Write( Length, buffer );
	};

	template<typename Type>
	tiny_uint Write( const tiny_list<Type>& list ) { 
		auto size = list.size( );

		Write( size );

		if ( size > 0 )
			size = Write( size * tiny_sizeof( Type ), tiny_cast( list.data( ), const c_pointer ) );

		return size;
	};

	template<typename Type>
	tiny_uint Write( const tiny_map<Type>& map ) { 
		auto size   = map.size( );
		auto length = tiny_cast( 0, tiny_uint );

		Write( size );
		
		for ( auto& node : map ) {
			length += Write( node.String );
			length += Write( node.Hash );
			length += Write( node.Data );
		}

		return length;
	};

	template<>
	tiny_uint Write<std::string>( const tiny_list<std::string>& list ) {
		auto count = tiny_cast( 0, tiny_uint );
		auto size  = list.size( );

		Write( size );

		for ( auto& text : list )
			count += Write( text );

		return count;
	};

public:
	bool GetIsValid( ) const;

	bool GetCan( Tiny::FileAccesses access ) const;

	Tiny::FileAccesses GetAccess( ) const;

	tiny_uint GetSize( ) const;

public:
	operator bool( ) const;

	TinyFile& operator=( Tiny::File& handle );

};
