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
 * @creation : 14/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyInputMap::TinyInputMap( )
	: m_queries{ }
{ }

void TinyInputMap::Clear( ) { m_queries.clear( ); }

void TinyInputMap::Register(
	const tiny_string& input_alias, 
	tiny_init<TinyInputQuery> querys 
) {
	auto input_hash = tiny_hash{ input_alias };
	
	if ( !Find( input_hash ) )
		m_queries.emplace( input_alias, { true, true, { } } );
	
	m_queries[ input_hash ].Values.emplace_back( querys );
}

void TinyInputMap::Register( 
	const tiny_string& input_alias, 
	const tiny_list<TinyInputQuery>& querys 
) {
	auto input_hash = tiny_hash{ input_alias };

	if ( !Find( input_hash ) )
		m_queries.emplace( input_alias, { true, true, { } } );

	m_queries[ input_hash ].Values.emplace_back( querys );
}

void TinyInputMap::Lock( tiny_hash input_hash ) { 
	auto* queries = Query( input_hash );

	if ( queries )
		queries->IsActive = false;
}

void TinyInputMap::UnLock( tiny_hash input_hash ) { 
	auto* queries = Query( input_hash );

	if ( queries )
		queries->IsActive = true;
}

void TinyInputMap::Erase( const tiny_string& input ) {
	m_queries.erase( input );
}

void TinyInputMap::Tick( ) {
	for ( auto& query : m_queries )
		query.Data.IsConsumed = false;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_map<TinyInputQueries>& TinyInputMap::Get( ) { return m_queries; }

const tiny_map<TinyInputQueries>& TinyInputMap::Get( ) const { return m_queries; }

bool TinyInputMap::Find( tiny_hash input_hash ) const { 
	return m_queries.find( input_hash );
}

TinyInputQueries* TinyInputMap::Query( tiny_hash input_hash ) {
	auto* queries = tiny_cast( nullptr, TinyInputQueries* );

	if ( Find( input_hash ) )
		queries = tiny_rvalue( m_queries[ input_hash ] );

	return queries;
}
