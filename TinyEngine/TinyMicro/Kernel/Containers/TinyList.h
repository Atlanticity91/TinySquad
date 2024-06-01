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
	under_layer m_data;

public:
	tiny_list( )
		: m_data{ }
	{ };

	tiny_list( const tiny_uint capacity )
		: m_data{ }
	{ 
		m_data.resize( capacity > 0 ? capacity : 1 );
	};

	tiny_list( tiny_init<Type> elements )
		: m_data{ elements }
	{ };

	tiny_list( const Type& element )
		: tiny_list{ }
	{
		emplace_back( element );
	};

	tiny_list( const tiny_uint capacity, const Type& def_value )
		: m_data{ }
	{
		m_data.resize( capacity > 0 ? capacity : 1 );

		for ( auto& element : m_data )
			element = def_value;
	};

	tiny_list( const tiny_uint size, const native_pointer data ) 
		: m_data{ }
	{ 
		m_data.resize( size / tiny_sizeof( Type ) );

		auto* dst = tiny_cast( m_data.data( ), native_pointer );

		if ( data != nullptr && dst != nullptr )
			Tiny::Memcpy( data, dst, size );
	};

	~tiny_list( ) = default;

	tiny_list& clear( ) { 
		m_data.clear( );

		return tiny_self;
	};

	tiny_list& resize( const tiny_uint capacity ) {
		m_data.resize( capacity );

		return tiny_self;
	};

	tiny_list& insert( const tiny_uint element_id, const Type& element ) {
		auto list_begin = m_data.begin( );

		m_data.insert( list_begin + element_id, element );

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
		auto list_end = m_data.end( );

		m_data.insert( list_end, elements.begin( ), elements.end( ) );

		return tiny_self;
	};

	tiny_list& emplace_back( const tiny_list<Type>& elements ) {
		auto list_end = m_data.end( );

		m_data.insert( list_end, elements.begin( ), elements.end( ) );

		return tiny_self;
	};

	tiny_list& duplicate( const tiny_uint element_id ) {
		if ( element_id < size( ) )
			emplace_back( m_data[ element_id ] );

		return tiny_self;
	};

	tiny_list& duplicate_last( ) { return duplicate( size( ) - 1 ); };
	
	tiny_list& swap( const tiny_uint src_id, const tiny_uint dst_id ) {
		if ( src_id != dst_id && src_id < size( ) && dst_id < size( ) ) {
			auto element = m_data[ src_id ];

			m_data[ src_id ] = m_data[ dst_id ];
			m_data[ dst_id ] = element;
		}

		return tiny_self;
	};

	std::optional<Type> erase( const tiny_uint element_id ) {
		if ( exist( element_id ) ) {
			auto list_begin = m_data.begin( );
			auto element    = m_data[ element_id ];

			m_data.erase( list_begin + element_id );

			return element;
		}

		return { };
	};

	tiny_list& erase( std::function<bool( const Type& )> eraser ) { 
		auto capacity = size( );

		while ( capacity-- > 0 ) {
			if ( !eraser( m_data[ capacity ] ) )
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

				if ( !linear_eraser( claim, capacity, m_data[ capacity ], capacity_n, m_data[ capacity_n ] ) )
					continue;

				erase( claim );
			}
		}

		return tiny_self;
	};

	std::optional<Type> pop_front( ) { return erase( 0 ); };

	std::optional<Type> pop_back( ) { return erase( size( ) - 1 ); };

	tiny_list& asign( const tiny_list& other ) { 
		m_data = other.m_data;

		return tiny_self;
	};

	tiny_list& sort( std::function<bool( Type&, Type& )> compare ) {
		auto list_begin = m_data.begin( );
		auto list_end   = m_data.end( );

		std::sort( list_begin, list_end, compare );

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
	under_layer& get_internal( ) { return m_data; };

	tiny_uint size( ) const { return tiny_cast( m_data.size( ), tiny_uint ); };

	tiny_uint capacity( ) const { return tiny_cast( m_data.capacity( ), tiny_uint ); };

	native_pointer as_pointer( ) { return tiny_cast( m_data.data( ), native_pointer ); }

	Type* data( ) { return m_data.data( ); };

	const Type* data( ) const { return m_data.data( ); };

	bool exist( tiny_uint element_id ) const { return element_id < size( ); };

	tiny_uint find( std::function<bool( const Type& )> search ) const { 
		auto element_id = tiny_cast( 0, tiny_uint );

		for ( const auto& element : m_data ) {
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
			if ( !search( m_data[ previous ] ) )
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

		for ( const auto& element : m_data ) {
			if ( search( m_data[ element_id ] ) )
				element_ids.emplace_back( element_id );

			element_id += 1;
		}

		return element_ids;
	};

	auto begin( ) noexcept { return m_data.begin( ); };

	auto end( ) noexcept { return m_data.end( ); };

	const auto begin( ) const noexcept { return m_data.cbegin( ); };

	const auto end( ) const noexcept { return m_data.cend( ); };

	Type& first( ) { return m_data[ 0 ]; };

	const Type& first( ) const { return m_data[ 0 ]; };

	Type& last( ) { 
		auto last_id = m_data.size( ) - 1;

		return m_data[ last_id ];
	};

	const Type& last( ) const {
		auto last_id = m_data.size( ) - 1;

		return m_data[ last_id ];
	};

	Type* get( tiny_uint element_id ) { 
		auto* result = tiny_cast( nullptr, Type* );

		if ( exist( element_id ) )
			result = tiny_rvalue( m_data[ element_id ] );

		return result;
	};

	const Type* get( tiny_uint element_id ) const {
		auto* result = tiny_cast( nullptr, const Type* );

		if ( exist( element_id ) )
			result = tiny_rvalue( m_data[ element_id ] );

		return result;
	};

	Type& at( tiny_uint element_id ) { return m_data[ element_id ]; };

	const Type& at( tiny_uint element_id ) const { return m_data[ element_id ]; };

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
