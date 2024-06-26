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

#include "TinyList.h"

template<typename Type>
struct tiny_map_node {

	tiny_hash Hash;
	std::string Alias;
	Type Data;

	tiny_map_node( const std::string& alias, const Type& element ) 
		: Hash{ alias },
		Alias{ alias },
		Data{ element }
	{ };

	operator Type& ( ) { return Data; };

	operator const Type& ( ) const { return Data; };

	Type* operator->( ) { return tiny_rvalue( Data ); };

	const Type* operator->( ) const { return tiny_rvalue( Data ); };

};

template<typename Type>
class tiny_map {

public:
	using under_node  = tiny_map_node<Type>;
	using under_layer = tiny_list<under_node>;

private:
	under_layer m_node_list;

public:
	tiny_map( )
		: m_node_list{ }
	{ };

	tiny_map( tiny_uint capacity )
		: m_node_list{ capacity }
	{ };

	~tiny_map( ) = default;

	tiny_map& clear( ) {
		m_node_list.clear( );

		return tiny_self;
	};

	tiny_map& emplace( const std::string& alias, const Type& element ) {
		auto element_n  = tiny_map_node{ alias, element };
		auto element_id = binary_search( element_n.Hash );

		if ( size( ) > 0 && m_node_list[ element_id ].Hash < element_n.Hash )
			element_id += 1;

		m_node_list.insert( element_id, element_n );

		return tiny_self;
	};

	tiny_map& emplace( const tiny_string& alias, const Type& element ) {
		auto alias_ = alias.to_string( );

		return emplace( alias_, element );
	};

	tiny_map& remap( const std::string& old_alias, const std::string& new_alias ) {
		auto old_hash = tiny_hash{ old_alias };
		auto element  = get( old_hash );

		emplace( new_alias, element );

		return erase( old_hash );
	};

	tiny_map& remap( const tiny_string& old_alias, const tiny_string& new_alias ) {
		auto old_hash = tiny_hash{ old_alias };
		auto element  = get( old_hash );

		emplace( new_alias, element );

		return erase( old_hash );
	};

	tiny_string& duplicate( const tiny_string& old_alias, const tiny_string& new_alias ) {
		auto old_hash = tiny_hash{ old_alias };
		auto element  = get( old_hash );

		return emplace( new_alias, element );
	};

	tiny_map& erase( const std::string& alias ) {
		auto element_hash = tiny_hash{ alias };

		return erase( element_hash );
	};

	tiny_map& erase( const tiny_string& alias ) { 
		auto element_hash = tiny_hash{ alias };

		return erase( element_hash );
	};
	
	tiny_map& erase( const tiny_hash alias_hash ) {
		auto element_id = binary_search( alias_hash );

		return erase( element_id );
	};

	tiny_map& erase( tiny_uint element_id ) {
		if ( get_is_valid( element_id ) )
			m_node_list.erase( element_id );

		return tiny_self;
	};

	tiny_map& asign( const tiny_map& other ) {
		m_node_list = other.m_node_list;

		return tiny_self;
	};

public:
	under_layer& get_internal( ) { return m_node_list; };

	tiny_uint size( ) const { return m_node_list.size( ); };

	tiny_uint capacity( ) const { return m_node_list.capacity( ); };

	bool find( tiny_string string ) const {
		auto hash = tiny_hash{ string };

		return find( hash );
	};

	bool find( tiny_string string, tiny_uint& element_id ) const {
		auto hash = tiny_hash{ string };

		return find( hash, element_id );
	};

	bool find( tiny_hash hash ) const {
		auto element_id = tiny_cast( 0, tiny_uint );

		return find( hash, element_id );
	};

	bool find( tiny_hash hash, tiny_uint& element_id ) const {
		auto state = false;

		element_id = binary_search( hash );

		if ( get_is_valid( element_id ) )
			state = ( m_node_list[ element_id ].Hash == hash );

		return state;
	};

	bool find_key( tiny_uint element_id, tiny_hash& hash ) const { 
		auto state = element_id < m_node_list.size( );

		if ( state )
			hash = m_node_list[ element_id ].Hash;

		return state;
	};

	bool find_key( tiny_uint element_id, std::string& alias ) const {
		auto state = element_id < m_node_list.size( );

		if ( state )
			alias = m_node_list[ element_id ].Alias;

		return state;
	};

	bool find_key( tiny_uint element_id, tiny_string& alias ) const {
		auto state = element_id < m_node_list.size( );

		if ( state )
			alias = tiny_string{ m_node_list[ element_id ].Alias };

		return state;
	};

	auto begin( ) { return m_node_list.begin( ); };

	auto end( ) { return m_node_list.end( ); };

	const auto begin( ) const { return m_node_list.begin( ); };

	const auto end( ) const { return m_node_list.end( ); };

	Type& last( ) { return m_node_list.last( ).Data; };

	const Type& last( ) const { return m_node_list.last( ).Data; };

	Type& get( tiny_string string ) {
		auto hash = tiny_hash{ string };

		return get( hash );
	};

	Type& get( tiny_hash hash ) {
		auto element_id = binary_search( hash );

		return m_node_list[ element_id ].Data;
	};

	const Type& get( tiny_string string ) const {
		auto hash = tiny_hash{ string };

		return get( hash );
	};

	const Type& get( tiny_hash hash ) const {
		auto element_id = binary_search( hash );

		return m_node_list[ element_id ].Data;
	};

	Type& at( tiny_uint element_id ) {
		return m_node_list[ element_id ].Data;
	};

	const Type& at( tiny_uint element_id ) const {
		return m_node_list[ element_id ].Data;
	};

	under_node& node( tiny_uint node ) {
		return m_node_list[ node ];
	};

	const under_node& node( tiny_uint node ) const { 
		return m_node_list[ node ];
	};

private:
	tiny_uint binary_search( const tiny_hash hash ) const {
		auto low   = tiny_cast( 0, tiny_uint );
		auto max   = size( );
		auto high  = max;
		auto pivot = low;
		
		while ( low < high ) {
			pivot = low + ( high - low ) / 2;

			if ( m_node_list[ pivot ].Hash == hash )
				break;

			if ( m_node_list[ pivot ].Hash < hash )
				low = pivot < max ? pivot + 1 : pivot;
			else
				high = pivot;
		}

		return pivot;
	};

public:
	operator under_layer& ( ) { return get_internal( ); };

	tiny_map& operator=( tiny_uint size ) {
		m_node_list = size;

		return tiny_self;
	};

	tiny_map& operator=( const tiny_map& other ) { return asign( other ); };

	Type& operator[]( tiny_string string ) { return get( string ); };

	Type& operator[]( tiny_hash hash ) { return get( hash ); };

	Type& operator[]( tiny_uint element_id ) { return at( element_id ); };

	const Type& operator[]( tiny_string string ) const { return get( string ); };

	const Type& operator[]( tiny_hash hash ) const { return get( hash ); };

	const Type& operator[]( tiny_uint element_id ) const { return at( element_id ); };

private:
	bool get_is_valid( tiny_uint element_id ) const { return element_id < size( ); };

};
