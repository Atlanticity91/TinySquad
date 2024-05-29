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
 * @creation : 29/05/2023
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Kernel/TinyUUID.h>

template<tiny_uint Length>
	requires ( Length > 0 )
class tiny_buffer {

private:
	tiny_uint  _cursor;
	tiny_ubyte _values[ Length ];

public:
	tiny_buffer( ) 
		: _cursor{ 0 },
		_values{ }
	{ };

	tiny_buffer( const tiny_string& string ) 
		: tiny_buffer{ }
	{ 
		store( string );
	};

	~tiny_buffer( ) = default;

	tiny_buffer& clear( ) { 
		_cursor = 0;

		return tiny_self;
	};

	tiny_buffer& set_cursor( const tiny_uint cursor ) {
		TINY_ASSERT_FORMAT( cursor < Length, "You can't asign a cursor value outside buffer range {0:%u}", Length );

		_cursor = cursor;

		return tiny_self;
	}

	tiny_buffer& asign( const tiny_uint length, const native_pointer data ) {
		TINY_ASSERT( length > 0, "You can't asign data to buffer with a 0 length array" );
		TINY_ASSERT_FORMAT( length <= Length, "You can't asign data to buffer with an array with a lenth superior to the buffer length %u", Length );
		TINY_ASSERT( data != nullptr, "You can't asign data to buffer with a null array" );

		auto* dst = tiny_cast( _values, native_pointer );

		if ( Tiny::Memcpy( data, dst, tiny_cast( length, tiny_ulong ) ) )
			_cursor = length;

		return tiny_self;
	};

	tiny_buffer& store( const tiny_uint length, const native_pointer data ) {
		TINY_ASSERT( length > 0, "You can't store data to buffer with a 0 length array" );
		TINY_ASSERT_FORMAT( _cursor + length <= Length, "You can't store data to buffer with an array that dosen't fit inside buffer available space %u", Length - _cursor );
		TINY_ASSERT( data != nullptr, "You can't store data to buffer with a null array" );

		auto* dst = tiny_cast( _values + _cursor, native_pointer );

		if ( Tiny::Memcpy( data, dst, tiny_cast( length, tiny_ulong ) ) )
			_cursor += length;

		return tiny_self;
	};

	tiny_buffer& store_at( 
		const tiny_uint offset, 
		const tiny_uint length, 
		const native_pointer data 
	) {
		TINY_ASSERT( length > 0, "You can't store data to buffer with a 0 length array" );
		TINY_ASSERT_FORMAT( offset < _cursor, "You can't store data to buffer with an offset that is not inside buffer limits {0:%u}", _cursor );
		TINY_ASSERT_FORMAT( offset + length < _cursor, "You can't store data to buffer with an array that dosen't fit inside buffer available space %u", _cursor - offset );
		TINY_ASSERT( data != nullptr, "You can't store data to buffer with a null array" );

		auto* dst = tiny_cast( _values + _cursor, native_pointer );

		Tiny::Memcpy( data, dst, tiny_cast( length, tiny_ulong ) );

		return tiny_self;
	};

public:
	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_buffer& asign( const Type& element ) { 
		auto* data  = tiny_cast( tiny_rvalue( element ), const native_pointer );
		auto length = tiny_sizeof( Type );

		return asign( length, data );
	};

	template<>
	tiny_buffer& asign<tiny_string>( const tiny_string& string ) {
		auto* data  = tiny_cast( string.get( ), const native_pointer );
		auto length = string.length( );

		return asign( length, data );
	};

	template<>
	tiny_buffer& asign<std::string>( const std::string& string ) {
		auto string_ = tiny_string{ string };

		return asign<tiny_string>( string_ );
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_buffer& store( const Type& element ) {
		auto* data  = tiny_cast( tiny_rvalue( element ), const native_pointer );
		auto length = tiny_sizeof( Type );

		return store( length, data );
	};

	template<>
	tiny_buffer& store<tiny_string>( const tiny_string& string ) {
		auto* data  = tiny_cast( string.get( ), const native_pointer );
		auto length = string.length( );

		return store( length, data );
	};

	template<>
	tiny_buffer& store<std::string>( const std::string& string ) {
		auto string_ = tiny_string{ string };

		return store<tiny_string>( string_ );
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_buffer& store_at( const tiny_uint offset, const Type& element ) {
		auto* data  = tiny_cast( tiny_rvalue( element ), const native_pointer );
		auto length = tiny_sizeof( Type );

		return store_at( offset, length, data );
	};

	template<>
	tiny_buffer& store_at<tiny_string>( const tiny_uint offset, const tiny_string& string ) {
		auto* data  = tiny_cast( string.get( ), const native_pointer );
		auto length = string.length( );

		return store_at( offset, length, data );
	};

	template<>
	tiny_buffer& store_at<std::string>( const tiny_uint offset, const std::string& string ) {
		auto string_ = tiny_string{ string };

		return store_at<tiny_string>( offset, string_ );
	};

public:
	tiny_uint length( ) const { return Length; };

	tiny_uint size( ) const { return _cursor; };

	tiny_uint remain( ) const { return Length - _cursor; };

	tiny_pointer data( ) { return _values; };

	const tiny_pointer data( ) const { return _values; };

	bool get_has_space( ) const { return _cursor < Length; };

	bool get_has_space( const tiny_uint size ) const { 
		return ( _cursor + size ) <= Length;
	};

	native_pointer as_native( ) { return tiny_cast( _values, native_pointer ); };

	const native_pointer as_native( ) const {
		return tiny_cast( _values, const native_pointer );
	};

	char* as_chars( ) const { return tiny_cast( _values, char* ); };

	tiny_string as_string( ) const {
		auto* string = as_native( );

		return tiny_string{ _cursor, string };
	};

	std::string to_string( ) const {
		auto* string = as_native( );

		return std::string{ _cursor, string };
	};

	tiny_buffer& extract( const tiny_uint length, native_pointer& data ) { 
		TINY_ASSERT( _cursor > 0, "You can't extract buffer data from an empty buffer" );
		TINY_ASSERT( length > 0, "You can't extract buffer data to a 0 length array" );
		TINY_ASSERT_FORMAT( length <= _cursor, "You can't extract buffer data where query data as a superior size from available data %u", _cursor );
		TINY_ASSERT( data != nullptr, "You can't extract buffer data to a null array" );

		_cursor -= length;

		auto* src = tiny_cast( _values + _cursor, const native_pointer );

		Tiny::Memcpy( nullptr, tiny_rvalue( data ), tiny_cast( length, tiny_ulong ) );

		return tiny_self;
	};

	tiny_buffer& extract_at(
		const tiny_uint offset,
		const tiny_uint length,
		native_pointer& data
	) {
		TINY_ASSERT( _cursor > 0, "You can't extract buffer data from an empty buffer" );
		TINY_ASSERT( length > 0, "You can't extract buffer data to a 0 length array" );
		TINY_ASSERT_FORMAT( offset + length <= _cursor, "You can't extract buffer data where query data as a superior size from available data %u", _cursor );
		TINY_ASSERT( data != nullptr, "You can't extract buffer data to a null array" );

		_cursor -= length;

		auto* src = tiny_cast( _values + offset, const native_pointer );

		Tiny::Memcpy( nullptr, tiny_rvalue( data ), tiny_cast( length, tiny_ulong ) );

		return tiny_self;
	};

public:
	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_buffer& extract( Type& element ) {
		auto* data  = tiny_cast( tiny_rvalue( element ), native_pointer );
		auto length = tiny_sizeof( Type );

		return extract( length, data );
	};

	template<>
	tiny_buffer& extract<tiny_string>( tiny_string& element ) {
		element = as_string( );

		return tiny_self;
	};

	template<>
	tiny_buffer& extract<std::string>( std::string& element ) {
		element = to_string( );

		return tiny_self;
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) && !tiny_is( Type, tiny_string ) && !tiny_is( Type, std::string ) )
	tiny_buffer& extract_at(
		const tiny_uint offset,
		Type& element
	) {
		auto* data  = tiny_cast( tiny_rvalue( element ), native_pointer );
		auto length = tiny_sizeof( Type );

		return extract_at( offset, length, data );
	};

public:
	operator tiny_uint( ) const { return size( ); };

	operator tiny_pointer( ) { return data( ); };

	operator const tiny_pointer( ) const { return data( ); };

	operator native_pointer( ) { return as_native( ); };

	operator const native_pointer( ) const { return as_native( ); };

	operator tiny_string( ) const { return as_string( ); };

	operator std::string( ) const { return to_string( ); };

public:
	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_buffer& operator=( const Type& element ) {
		return asign( element );
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_buffer& operator+=( const Type& element ) {
		return store( element );
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_buffer& operator-=( Type& element ) {
		return extract( element );
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_buffer& operator<<( const Type& element ) {
		return store( element );
	};

	template<typename Type>
		requires ( !tiny_is_pointer( Type ) )
	tiny_buffer& operator>>( Type& element ) {
		return extract( element );
	};

};
