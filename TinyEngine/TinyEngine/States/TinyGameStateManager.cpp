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
 * @creation : 20/04/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGameStateManager::TinyGameStateManager( ) 
	: _current{ TINY_UINT_MAX },
	_states{ }
{ }

void TinyGameStateManager::Switch( TinyGame* game, const tiny_uint state_id ) {
	if ( state_id < _states.size( ) ) {
		if ( _current < _states.size( ) ) {
			auto& storage = _states.at( _current );

			storage.As<TinyGameState>( )->OnQuit( game, state_id );
		}

		auto& storage = _states.at( state_id );

		storage.As<TinyGameState>( )->OnChange( game, _current );

		_current = state_id;
	}
}

void TinyGameStateManager::Switch( TinyGame* game, const tiny_string& state_name ) {
	auto state_hash = tiny_hash{ state_name };

	Switch( game, state_hash );
}

void TinyGameStateManager::Switch( TinyGame* game, const tiny_hash state_hash ) {
	auto state_id = tiny_cast( 0, tiny_uint );

	if ( _states.find( state_hash, state_id ) )
		Switch( game, state_id );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyGameStateManager::GetStateID( ) const { return _current; }

tiny_string TinyGameStateManager::GetStateName( ) const {
	auto state_name = "";

	if ( _current < _states.size( ) ) {
		auto& node = _states.node( _current );

		state_name = tiny_string{ node.Alias };
	}

	return state_name;
}

TinyGameState* TinyGameStateManager::GetState( ) const {
	auto* game_state = tiny_cast( nullptr, TinyGameState* );

	if ( _current < _states.size( ) ) {
		auto storage = _states.at( _current );

		game_state = storage.As<TinyGameState>( );
	}

	return game_state;
}

TinyGameState* TinyGameStateManager::GetState( const tiny_uint state_id ) const {
	auto* game_state = tiny_cast( nullptr, TinyGameState* );

	if ( state_id < _states.size( ) ) {
		auto storage = _states.at( state_id );

		game_state = storage.As<TinyGameState>( );
	}

	return game_state;
}

TinyGameState* TinyGameStateManager::GetState( const tiny_string& state_name ) const {
	auto state_hash = tiny_hash{ state_name };

	return GetState( state_hash );
}

TinyGameState* TinyGameStateManager::GetState( const tiny_hash state_hash ) const {
	auto* game_state = tiny_cast( nullptr, TinyGameState* );
	auto state_id	 = tiny_cast( 0, tiny_uint );

	if ( _states.find( state_hash, state_id ) ) {
		auto storage = _states.at( state_id );

		game_state = storage.As<TinyGameState>( );
	}

	return game_state;
}
