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

	tiny_inline bool Seek( const tiny_ulong offset );

	tiny_abstract( bool Seek( const TinyFileOrigin origin, const tiny_ulong offset ) );

	tiny_abstract( tiny_ulong Read( const tiny_ulong length, native_pointer data ) );

	tiny_abstract( tiny_ulong Write( const tiny_ulong length, const native_pointer data ) );

	tiny_abstract( bool ReadAll( const tiny_ulong length, native_pointer& storage ) );

public:
	template<typename Type>
	bool Seek( ) { return Seek( tiny_sizeof( Type ) ); };

	template<>
	bool Seek<tiny_string>( ) { return Seek<std::string>( ); };

	template<>
	bool Seek<std::string>( ) {
		auto length = tiny_cast( 0, tiny_uint );
		auto state = false;

		if ( Read( length ) > 0 )
			state = Seek( TF_ORIGIN_CURSOR, length );

		return state;
	};

	template<typename Type>
	bool Seek( const TinyFileOrigin origin ) { 
		return Seek( origin, tiny_sizeof( Type ) ); 
	};

	template<>
	bool Seek<tiny_string>( const TinyFileOrigin origin ) { 
		return Seek<std::string>( origin );
	};

	template<>
	bool Seek<std::string>( const TinyFileOrigin origin ) {
		auto length = tiny_cast( 0, tiny_uint );
		auto state = false;

		if ( Read( length ) > 0 )
			state = Seek( origin, length );

		return state;
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) && !tiny_is( Type, tiny_string ) )
	tiny_ulong Read( Type& data ) {
		auto* data_ = tiny_cast( tiny_rvalue( data ), native_pointer );
		auto length = tiny_sizeof( Type );

		return Read( length, data_ );
	};

	template<>
	tiny_ulong Read<std::string>( std::string& string ) {
		auto length = tiny_cast( 0, tiny_ulong );
		auto count  = tiny_cast( 0, tiny_uint );

		if ( Read( count ) > 0 && count > 0 ) {
			string.resize( count );

			auto* data = tiny_cast( string.c_str( ), const native_pointer );

			length = Read( length, data );
		}
			
		return length;

	};

	template<typename Type, tiny_uint Length>
		requires ( !tiny_is_pointer( Type ) && Length > 0 )
	tiny_ulong Read( tiny_array<Type, Length>& array_ ) {
		auto length = tiny_cast( 0, tiny_ulong );
		auto size  = tiny_cast( 0, tiny_uint );

		Read( size );

		if ( size > 0 ) {
			for ( auto& element : array_ )
				length += Read( element );
		}

		return length;
	};

	template<tiny_uint Length>
		requires ( Length > 0 )
	tiny_ulong Read( tiny_buffer<Length>& buffer ) {
		auto length = tiny_cast( 0, tiny_ulong );
		auto* data  = buffer.get( );
		auto size   = tiny_cast( 0, tiny_uint );

		Read( size );

		if ( size > 0 && size <= Length )
			length = Read( size, data );
		
		return length;
	};

	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	tiny_ulong Read( tiny_list<Type>& list ) {
		auto length = tiny_cast( 0, tiny_ulong );
		auto size   = tiny_cast( 0, tiny_uint );

		Read( size );

		if ( size > 0 ) {
			list = size;

			for ( auto& element : list )
				length += Read( element );
		} else
			list.clear( );

		return length;
	};

	template<typename Type>
		requires ( !std::is_pointer<Type>::value )
	tiny_ulong Read( tiny_map<Type>& map ) {
		auto length = tiny_cast( 0, tiny_ulong );
		auto count  = tiny_cast( 0, tiny_uint );

		Read( count );

		if ( count > 0 ) {
			auto element = Type{ };
			auto alias   = std::string{ };

			while ( count-- > 0 ) {
				length += Read( alias );
				length += Read( element );

				map.emplace( alias, element );
			}
		}

		return length;
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_ulong Write( const Type& data ) {
		auto* data_ = tiny_cast( tiny_rvalue( data ), const native_pointer );
		auto length = tiny_sizeof( Type );

		return Write( length, data_ );
	};

	template<>
	tiny_ulong Write<tiny_string>( const tiny_string& string ) {
		auto* chars = string.as_native( );
		auto length = string.length( );
		auto count  = tiny_cast( 0, tiny_ulong );

		Write( length );

		if ( length > 0 )
			count = Write( length, chars );

		return count;
	};

	template<>
	tiny_ulong Write<std::string>( const std::string& string ) {
		auto* chars = tiny_cast( string.c_str( ), const native_pointer );
		auto length = tiny_cast( string.length( ), tiny_uint );
		auto count  = tiny_cast( 0, tiny_ulong );

		Write( length );

		if ( length > 0 )
			count = Write( length, chars );

		return count;
	};

	template<typename Type, tiny_uint Size>
		requires ( !tiny_is_pointer( Type ) && Size > 0 )
	tiny_ulong Write( const tiny_array<Type, Size>& array_ ) {
		auto* data = array_.data( );
		auto count = tiny_cast( 0, tiny_ulong );

		Write( Size );

		for ( auto& element : array_ )
			count += Write( element );

		return count;
	};

	template<tiny_uint Size>
		requires ( Size > 0 )
	tiny_ulong Write( const tiny_buffer<Size>& buffer ) {
		auto* data  = buffer.get( );
		auto length = buffer.length( );

		Write( length );

		return Write( length, data );
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_ulong Write( const tiny_list<Type>& list ) {
		auto size  = list.size( );
		auto count = tiny_cast( 0, tiny_ulong );

		Write( size );

		if ( size > 0 ) {
			for ( auto& element : list )
				count += Write( element );
		}

		return count;
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_ulong Write( const tiny_map<Type>& map ) {
		auto size  = map.size( );
		auto count = tiny_cast( 0, tiny_ulong );

		Write( size );

		if ( size > 0 ) {
			for ( auto& element : map ) {
				count += Write( element.String );
				count += Write( element.Data );
			}
		}
		return count;
	};

	template<typename... Args>
	tiny_ulong Write( const tiny_string& format, const Args&... args ) {
		auto* data  = format.as_native( );
		auto length = format.length( );
		auto count  = tiny_cast( 0, tiny_ulong );

		tiny_compile_if( tiny_countof( Args ) > 0 ) {
			auto buffer = tiny_buffer<256>{ };

			Tiny::Sprintf( buffer, format, args... );

			length = buffer.size( );
			data   = buffer.as_native( );
		}

		Write( length );

		if ( length > 0 )
			count = Write( length, data );

		return count;
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
