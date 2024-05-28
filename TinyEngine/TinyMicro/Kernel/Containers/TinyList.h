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

#include "TinyStack.h"

template<typename Type>
class tiny_list {

	using under_layer = std::vector<Type>;

private:
	under_layer _data;

public:
	tiny_list( )
		: _data{ } 
	{ };

	tiny_list( tiny_uint capacity ) 
		: _data{ }
	{ 
		_data.resize( capacity > 0 ? capacity : 1 );
	};

	tiny_list( tiny_init<Type> elements )
		: _data{ elements } 
	{ };

	tiny_list( const Type& element )
		: tiny_list{ }
	{
		emplace_back( element );
	};

	tiny_list( tiny_uint capacity, const Type& def_value )
		: _data{ } 
	{
		_data.resize( capacity > 0 ? capacity : 1 );

		for ( auto& element : _data )
			element = def_value;
	};

	tiny_list( tiny_uint size, const tiny_pointer data ) 
		: _data{ }
	{ 
		_data.resize( size / tiny_sizeof( Type ) );

		auto* dst = tiny_cast( _data.data( ), tiny_pointer );

		if ( data && dst )
			Tiny::Memcpy( data, dst, size );
	};

	~tiny_list( ) = default;

	tiny_list& clear( ) { 
		_data.clear( );

		return tiny_self;
	};

	tiny_list& resize( tiny_uint capacity ) { 
		_data.resize( capacity );

		return tiny_self;
	};

	tiny_list& insert( tiny_uint element_id, const Type& element ) { 
		_data.insert( _data.begin( ) + element_id, element );

		return tiny_self;
	};

	tiny_list& emplace_front( const Type& element ) {
		return insert( 0, element );
	};

	tiny_list& emplace_back( const Type& element ) {
		auto capacity = size( );

		return insert( capacity, element );
	};

	tiny_list& emplace_back( tiny_init<Type> elements ) {
		_data.insert( _data.end( ), elements.begin( ), elements.end( ) );

		return tiny_self;
	};

	tiny_list& emplace_back( const tiny_list<Type>& elements ) {
		_data.insert( _data.end( ), elements.begin( ), elements.end( ) );

		return tiny_self;
	};

	tiny_list& duplicate( tiny_uint element_id ) {
		if ( element_id < size( ) )
			emplace_back( _data[ element_id ] );

		return tiny_self;
	};

	tiny_list& duplicate_last( ) { return duplicate( size( ) - 1 ); };
	
	tiny_list& swap( const tiny_uint src_id, const tiny_uint dst_id ) {
		if ( src_id != dst_id && src_id < size( ) && dst_id < size( ) ) {
			auto element = _data[ src_id ];

			_data[ src_id ] = _data[ dst_id ];
			_data[ dst_id ] = element;
		}

		return tiny_self;
	};

	std::optional<Type> erase( tiny_uint element_id ) {
		if ( exist( element_id ) ) {
			auto element = _data[ element_id ];

			_data.erase( _data.begin( ) + element_id );

			return element;
		}

		return { };
	};

	tiny_list& erase( std::function<bool( const Type& )> eraser ) { 
		auto capacity = size( );

		while ( capacity-- > 0 ) {
			if ( !eraser( _data[ capacity ] ) )
				continue;
			
			erase( capacity );
		}
		
		return tiny_self;
	};

	tiny_list& erase( std::function<bool( tiny_uint&, tiny_uint, const Type&, tiny_uint, const Type& )> linear_eraser ) {
		auto capacity = size( );

		if ( capacity > 1 ) {
			capacity -= 1;

			auto capacity_n = tiny_cast( 0, tiny_uint );
			auto claim		= tiny_cast( 0, tiny_uint );

			while ( capacity-- > 1 ) {
				capacity_n = capacity + 1;

				if ( !linear_eraser( claim, capacity, _data[ capacity ], capacity_n, _data[ capacity_n ] ) )
					continue;

				erase( claim );
			}
		}

		return tiny_self;
	};

	std::optional<Type> pop_front( ) { return erase( 0 ); };

	std::optional<Type> pop_back( ) { return erase( size( ) - 1 ); };

	tiny_list& asign( const tiny_list& other ) { 
		_data = other._data;

		return tiny_self;
	};

	tiny_list& sort( std::function<bool( Type&, Type& )> compare ) {
		std::sort( _data.begin( ), _data.end( ), compare );

		return tiny_self;
	};

public:
	template<typename... Args>
	tiny_list& create( tiny_uint element_id, Args&&... args) {
		auto element = Type{ std::forward<Args>( args )... };

		return insert( element_id, element );
	};

	template<typename... Args>
	tiny_list& create_back(  Args&&... args ) {
		auto element = Type{ std::forward<Args>( args )... };

		return emplace_back( element );
	};

	template<typename... Args>
	tiny_list& create_front( tiny_uint element_id, Args&&... args ) {
		auto element = Type{ std::forward<Args>( args )... };

		return emplace_front( element );
	};

public:
	under_layer& get_internal( ) { return _data; };

	tiny_uint size( ) const { return tiny_cast( _data.size( ), tiny_uint ); };

	tiny_uint capacity( ) const { return tiny_cast( _data.capacity( ), tiny_uint ); };

	native_pointer as_pointer( ) { return tiny_cast( _data.data( ), native_pointer ); }

	Type* data( ) { return _data.data( ); };

	const Type* data( ) const { return _data.data( ); };

	bool exist( tiny_uint element_id ) const { return element_id < size( ); };

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

	bool next( tiny_uint& previous, std::function<bool( const Type& )> search ) const {
		auto capacity = size( );

		previous = previous < capacity ? previous + 1 : 0;

		while ( previous < capacity ) {
			if ( !search( _data[ previous ] ) )
				previous += 1;
			else
				break;
		}

		return exist( previous );
	};

	bool contain( std::function<bool( const Type& )> search ) const { 
		auto element_id = tiny_cast( 0, tiny_uint );

		return contain( element_id, search );
	};

	bool contain( tiny_uint& element_id, std::function<bool( const Type& )> search ) const { 
		element_id = find( search );

		return exist( element_id );
	};

	tiny_list<tiny_uint> find_multiple( std::function<bool( const Type& )> search ) const {
		auto element_ids = tiny_list<tiny_uint>{ };
		auto element_id  = tiny_cast( 0, tiny_uint );

		for ( const auto& element : _data ) {
			if ( search( _data[ element_id ] ) )
				element_ids.emplace_back( element_id );

			element_id += 1;
		}

		return element_ids;
	};

	auto begin( ) noexcept { return _data.begin( ); };

	auto end( ) noexcept { return _data.end( ); };

	const auto begin( ) const noexcept { return _data.cbegin( ); };

	const auto end( ) const noexcept { return _data.cend( ); };

	Type& first( ) { return _data[ 0 ]; };

	const Type& first( ) const { return _data[ 0 ]; };

	Type& last( ) { return _data[ _data.size( ) - 1 ]; };

	const Type& last( ) const { return _data[ _data.size( ) - 1 ]; };

	Type* get( tiny_uint element_id ) { 
		auto* result = tiny_cast( nullptr, Type* );

		if ( exist( element_id ) )
			result = tiny_rvalue( _data[ element_id ] );

		return result;
	};

	const Type* get( tiny_uint element_id ) const {
		auto* result = tiny_cast( nullptr, const Type* );

		if ( exist( element_id ) )
			result = tiny_rvalue( _data[ element_id ] );

		return result;
	};

	Type& at( tiny_uint element_id ) { return _data[ element_id ]; };

	const Type& at( tiny_uint element_id ) const { return _data[ element_id ]; };

public:
	operator under_layer& ( ) { return get_internal( ); };

	operator Type* ( ) { return data( ); };

	operator const Type* ( ) const { return data( ); };

	tiny_list& operator=( const tiny_uint capacity ) { return resize( capacity ); };

	tiny_list& operator=( const tiny_list& other ) { return asign( other ); };

	Type& operator[]( tiny_uint element_id ) { return at( element_id ); };

	const Type& operator[]( tiny_uint element_id ) const {
		return at( element_id );
	};

};
