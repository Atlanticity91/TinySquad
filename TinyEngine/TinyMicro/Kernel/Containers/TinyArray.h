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
 * @creation : 13/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyBuffer.h"

template<typename Type, tiny_uint Capacity>
	requires ( Capacity > 0 )
class tiny_array {

	using under_layer = std::array<Type, tiny_cast( Capacity, size_t )>;

private:
	under_layer _data;

public:
	tiny_array( )
		: _data{ } 
	{ };

	tiny_array( tiny_init<Type> elements ) 
		: _data{ elements }
	{ };

	~tiny_array( ) = default;

	tiny_array& asign( const tiny_array& other ) {
		_data = other._data;

		return tiny_self;
	};

	tiny_array& sort( std::function<bool( tiny_int, tiny_int )> compare ) {
		std::sort( _data.begin( ), _data.end( ), compare );

		return tiny_self;
	};

public:
	under_layer& get_internal( ) { return _data; };

	tiny_uint capacity( ) const { return Capacity; };

	native_pointer as_pointer( ) const { return tiny_cast( _data.data( ), native_pointer ); };

	Type* data( ) { return _data.data( ); };

	const Type* data( ) const { return _data.data( ); };

	bool exist( tiny_uint element_id ) const { 
		return element_id < capacity( ); 
	};

	tiny_uint find( std::function<bool( const Type& )> search ) const {
		auto element_id = tiny_cast( 0, tiny_uint );

		for ( const auto& element : _data ) {
			if ( !search( element ) )
				element_id += 1;
			else
				break;
		}

		return exist( element_id ) ? element_id : TINY_UINT_MAX;
	};

	bool contain( std::function<bool( const Type& )> search ) const {
		auto element_id = tiny_cast( 0, tiny_uint );

		return contain( element_id, search );
	};

	bool contain( tiny_uint& element_id, std::function<bool( const Type& )> search ) const {
		element_id = find( search );

		return exist( element_id );
	};

	auto begin( ) noexcept { return _data.begin( ); };

	auto end( ) noexcept { return _data.end( ); };

	const auto begin( ) const noexcept { return _data.cbegin( ); };

	const auto end( ) const noexcept { return _data.cend( ); };

	Type& at( tiny_uint element_id ) { return _data[ element_id ]; };

	const Type& at( tiny_uint element_id ) const { return _data[ element_id ]; };

public:
	operator under_layer& ( ) { return get_internal( ); };

	tiny_array& operator=( const tiny_array& other ) { return asign( other ); };

	Type& operator[]( tiny_uint element_id ) { return at( element_id ); };

	const Type& operator[]( tiny_uint element_id ) const { 
		return at( element_id );
	};


};
