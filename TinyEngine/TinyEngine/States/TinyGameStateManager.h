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

#pragma once

#include "TinyGameState.h"

template<typename GameState>
concept TinyIsGameState = tiny_is_child_of( GameState, TinyGameState );

te_class TinyGameStateManager final {

private:
	tiny_uint			   _current;
	tiny_map<tiny_storage> _states;

public:
	TinyGameStateManager( );

	~TinyGameStateManager( ) = default;

	void Switch( TinyGame* game, const tiny_uint state_id );

	void Switch( TinyGame* game, const tiny_string& state_name );

	void Switch( TinyGame* game, const tiny_hash state_hash );

public:
	template<typename GameState>
		requires TinyIsGameState<GameState>
	void Register( const tiny_string& name ) { 
		if ( name.get_is_valid( ) && !_states.find( name ) ) {
			auto storage = tiny_storage{ TS_TYPE_STATIC };

			if ( tiny_make_storage( storage, GameState ) )
				_states.emplace( name, storage );
		}
	};

public:
	tiny_uint GetStateID( ) const;

	tiny_string GetStateName( ) const;

	TinyGameState* GetState( ) const;

	TinyGameState* GetState( const tiny_uint state_id ) const;

	TinyGameState* GetState( const tiny_string& state_name ) const;

	TinyGameState* GetState( const tiny_hash state_hash ) const;

};
