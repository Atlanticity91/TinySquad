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

	tiny_uint Read( std::string& text );

	tiny_uint Read( tiny_uint length, c_pointer data );

	tiny_uint Write( const tiny_string& text );

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
		requires ( !std::is_same<Type, tiny_string>::value )
	tiny_uint Write( const Type& data ) {
		auto* _data = tiny_rvalue( data );

		return Write( tiny_sizeof( Type ), tiny_cast( _data, const c_pointer ) );
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

	template<typename... Args>
	tiny_uint Write( const tiny_string& format, Args... args ) {
		auto buffer = tiny_buffer<256>{ };
		
		Tiny::Sprintf( buffer, format, std::forward<Args>( args )... );

		auto length = buffer.size( );
		auto* data  = buffer.get( );

		Write( length );

		return Write( length, data );
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
	TinyFile& operator>>( Type& element ) { return tiny_self; };

	template<typename Type>
	TinyFile& operator<<( const Type& element ) { 
		return tiny_self; 
	};

};
