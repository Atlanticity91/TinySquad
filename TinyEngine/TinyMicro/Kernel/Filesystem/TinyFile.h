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
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Kernel/Memory/TinyMemoryManager.h>

tm_abstract_class TinyFile {

public:
	TinyFile( );

	virtual ~TinyFile( ) = default;

	tiny_inline bool Seek( tiny_ulong offset );

	tiny_abstract( bool Seek( TinyFileOrigin origin, tiny_ulong offset ) );

	tiny_abstract( tiny_uint Read( tiny_uint length, native_pointer data ) );

	tiny_abstract( tiny_uint Write( tiny_uint length, const native_pointer data ) );

	tiny_abstract( bool ReadAll( const tiny_ulong length, native_pointer& storage ) );

public:
	template<typename Type>
	bool Seek( ) { return Seek( tiny_sizeof( Type ) ); };

	template<typename Type>
	bool Seek( TinyFileOrigin origin ) { return Seek( origin, tiny_sizeof( Type ) ); };

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) && !tiny_is( Type, tiny_string ) )
	tiny_uint Read( Type& data ) {
		auto* data_ = tiny_cast( tiny_rvalue( data ), native_pointer );
		auto length = tiny_sizeof( Type );

		return Read( length, data_ );
	};

	template<>
	tiny_uint Read<std::string>( std::string& string ) { 
		auto length = tiny_cast( 0, tiny_uint );

		if ( Read( length ) > 0 && length > 0 ) {
			string.resize( length );

			auto* data = tiny_cast( string.c_str( ), const native_pointer );

			length = Read( length, data );
		}
			
		return length;

	};

	template<typename Type, tiny_uint Length>
		requires ( !tiny_is_pointer( Type ) && Length > 0 )
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

		if ( size > 0 && size <= Length )
			size = Read( size, data );
		else
			size = 0;

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

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_uint Write( const Type& data ) {
		auto* data_ = tiny_cast( tiny_rvalue( data ), const native_pointer );
		auto length = tiny_sizeof( Type );

		return Write( length, data_ );
	};

	template<>
	tiny_uint Write<tiny_string>( const tiny_string& string ) {
		auto* chars = string.as_native( );
		auto length = string.length( );

		Write( length );

		if ( length > 0 )
			length = Write( length, chars );

		return length;
	};

	template<>
	tiny_uint Write<std::string>( const std::string& string ) {
		auto* chars = tiny_cast( string.c_str( ), const native_pointer );
		auto length = tiny_cast( string.length( ), tiny_uint );

		Write( length );

		if ( length > 0 )
			length = Write( length, chars );

		return length;
	};

	template<typename Type, tiny_uint Size>
		requires ( !tiny_is_pointer( Type ) && Size > 0 )
	tiny_uint Write( const tiny_array<Type, Size>& array_ ) {
		auto* data  = array_.data( );
		auto length = tiny_cast( 0, tiny_uint );

		Write( Size );

		for ( auto& element : array_ )
			length += Write( element );

		return length;
	};

	template<tiny_uint Size>
		requires ( Size > 0 )
	tiny_uint Write( const tiny_buffer<Size>& buffer ) {
		auto* data  = buffer.get( );
		auto length = buffer.length( );

		Write( length );

		return Write( length, data );
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_uint Write( const tiny_list<Type>& list ) {
		auto size = list.size( );

		Write( size );

		if ( size > 0 ) {
			size = 0;

			for ( auto& element : list )
				size += Write( element );
		} else
			size = 0;

		return size;
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_uint Write( const tiny_map<Type>& map ) {
		auto size = map.size( );

		Write( size );

		if ( size > 0 ) {
			size = 0;

			for ( auto& element : map ) {
				size += Write( element.String );
				size += Write( element.Data );
			}
		} else
			size = 0;

		return size;
	};

	template<typename... Args>
	tiny_uint Write( const tiny_string& format, const Args&... args ) {
		auto* data  = format.as_native( );
		auto length = format.length( );

		tiny_compile_if( tiny_countof( Args ) > 0 ) {
			auto buffer = tiny_buffer<256>{ };

			Tiny::Sprintf( buffer, format, args... );

			length = buffer.size( );
			data   = buffer.as_native( );
		}

		Write( length );

		if ( length > 0 )
			length = Write( length, data );

		return length;
	};


public:
	tiny_abstract( bool GetIsValid( ) const );

	tiny_abstract( TinyFileAccesses GetAccess( ) const );

	tiny_abstract( bool GetCan( TinyFileAccesses access ) const );

	tiny_abstract( tiny_ulong GetSize( ) const );

public:
	virtual operator bool( ) const;

	virtual operator tiny_ulong( ) const;

};
