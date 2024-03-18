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
	: _queries{ }
{ }

void TinyInputMap::Clear( ) { _queries.clear( ); }

void TinyInputMap::Register( tiny_string input_alias, tiny_init<TinyInputQuery> querys ) {
	auto input_hash = tiny_hash{ input_alias };
	
	if ( !Find( input_hash ) )
		_queries.emplace( input_alias, { true, true, { } } );
	
	_queries[ input_hash ].Values.emplace_back( querys );
}

void TinyInputMap::Register( tiny_string input_alias, const tiny_list<TinyInputQuery>& querys ) {
	auto input_hash = tiny_hash{ input_alias };

	if ( !Find( input_hash ) )
		_queries.emplace( input_alias, { true, true, { } } );

	_queries[ input_hash ].Values.emplace_back( querys );
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

void TinyInputMap::Tick( ) {
	for ( auto& query : _queries )
		query.Data.IsConsumed = false;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_map<TinyInputQueries>& TinyInputMap::Get( ) { return _queries; }

const tiny_map<TinyInputQueries>& TinyInputMap::Get( ) const { return _queries; }

bool TinyInputMap::Find( tiny_hash input_hash ) const { 
	return _queries.find( input_hash ); 
}

TinyInputQueries* TinyInputMap::Query( tiny_hash input_hash ) {
	return Find( input_hash ) ? &_queries[ input_hash ] : nullptr;
}
