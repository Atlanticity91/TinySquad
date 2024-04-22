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
 * @creation : 24/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "ITinySystem.h"

template<typename System>
concept TinyIsSysten = tiny_is_child_of( System, ITinySystem );

tiny_enum( TinySystemFlags ) { 

	TS_FLAG_IS_ACTIVE	 = TINY_LEFT_SHIFT( 1, 0 ),
	TS_FLAG_USE_PRETICK  = TINY_LEFT_SHIFT( 1, 1 ),
	TS_FLAG_USE_POSTTICK = TINY_LEFT_SHIFT( 1, 2 ),

};

template<typename Component>
class TinySystem : tiny_inherit( ITinySystem ) {

public:
	using Component_t = Component;

protected:
	tiny_ubyte			 _flags;
	tiny_list<Component> _components;

public:
	TinySystem( ) 
		: TinySystem{ false, false } 
	{ };

	TinySystem( bool use_pretick, bool use_posttick )
		: _flags{ 0 },
		_components{ }
	{ 
		_flags = TS_FLAG_IS_ACTIVE					|
				 use_pretick  * TS_FLAG_USE_PRETICK |
				 use_posttick * TS_FLAG_USE_POSTTICK;
	};

	virtual ~TinySystem( ) = default;

	tiny_virtual( void RegisterInterop( TinyGame* game ) );

	tiny_implement( void Enable( TinyGame* game ) ) { 
		if ( !GetIsActive( ) ) {
			_flags |= TS_FLAG_IS_ACTIVE;

			OnEnable( game );
		}
	};

	tiny_implement( void Disable( TinyGame* game ) ) {
		if ( GetIsActive( ) ) {
			_flags ^= TS_FLAG_IS_ACTIVE;

			OnDisable( game );
		}
	};

	tiny_implement( void Toggle( TinyGame* game ) ) { 
		if ( GetIsActive( ) )
			Disable( game );
		else
			Enable( game );
	};

	tiny_implement( std::shared_ptr<TinyComponent> Create( 
		const tiny_hash entity_hash 
	) ) {
		return std::make_shared<Component>( entity_hash );
	};

	tiny_implement( TinyComponent* Append( TinyGame* game, const tiny_hash entity_hash ) ) { 
		auto comp_id = CreateID( entity_hash );

		_components.insert( comp_id, { entity_hash } );

		auto comp = tiny_rvalue( _components[ comp_id ] );

		if ( !comp->Create( game ) ) {
			_components.erase( comp_id );

			comp = nullptr;
		}

		return comp;
	};

	tiny_implement( bool Append( TinyGame* game, std::shared_ptr<TinyComponent> component ) ) {
		auto entity_hash = component->GetOwner( );
		auto comp_id	 = CreateID( entity_hash );

		_components.insert( comp_id, { } );

		Tiny::Memcpy( component.get( ), tiny_rvalue( _components[ comp_id ] ), tiny_sizeof( Component ) );

		return _components[ comp_id ].Create( game );
	};

	tiny_implement( bool Set( TinyGame* game, std::shared_ptr<TinyComponent> component ) ) { 
		auto entity_hash = component->GetOwner( );
		auto comp_id	 = FindID( entity_hash );
		auto state		 = GetIsValid( comp_id ) && 
						   _components[ comp_id ].GetOwner( ) == entity_hash;

		if ( state )
			state = Tiny::Memcpy( component.get( ), tiny_rvalue( _components[ comp_id ] ), tiny_sizeof( Component ) );

		return state;
	};

	tiny_implement( void Remove( TinyGame* game, const tiny_hash entity_hash ) ) { 
		auto comp_id = FindID( entity_hash );

		if ( GetIsValid( comp_id ) && _components[ comp_id ].GetOwner( ) == entity_hash )
			_components[ comp_id ].Delete( game );
	};

	virtual void Erase( const TinyEntityGhost& ghost ) override {
		auto comp_id = FindID( ghost.Hash );

		if ( GetIsValid( comp_id ) && _components[ comp_id ].GetOwner( ) == ghost.Hash )
			_components.erase( comp_id );
	};

	tiny_virtual( void PreTick( TinyGame* game ) );

	tiny_virtual( void PostTick( TinyGame* game ) );

protected:
	tiny_virtual( void OnEnable( TinyGame* game ) );

	tiny_virtual( void OnDisable( TinyGame* game ) );

public:
	tiny_implement( bool GetIsActive( ) const ) { return ( _flags & TS_FLAG_IS_ACTIVE ); };

	tiny_implement( tiny_string GetName( ) const ) { return Component::sGetName( ); };

	tiny_implement( bool GetHasPreTick( ) const ) {
		return ( _flags & TS_FLAG_IS_ACTIVE ) && ( _flags & TS_FLAG_USE_PRETICK );
	};

	tiny_implement( bool GetHasPostTick( ) const ) {
		return ( _flags & TS_FLAG_IS_ACTIVE ) && ( _flags & TS_FLAG_USE_POSTTICK );
	};

	tiny_implement( tiny_uint GetComponentID( const tiny_hash entity_hash ) const ) {
		auto comp_id = _components.size( );

		while ( comp_id-- > 0 ) {
			auto& comp = _components[ comp_id ];

			if ( !comp.GetIsActive( ) || comp.GetOwner( ) == entity_hash )
				continue;

			break;
		}

		return comp_id;
	};

	tiny_implement( TinyComponent* GetComponent( const tiny_hash entity_hash ) const ) { 
		auto comp_id = FindID( entity_hash );
		auto* comp   = tiny_cast( nullptr, TinyComponent* );

		if ( 
			GetIsValid( comp_id ) &&
			_components[ comp_id ].GetOwner( ) == entity_hash 
		)
			comp = tiny_cast( tiny_rvalue( _components[ comp_id ] ), TinyComponent* );

		return comp;
	};

	tiny_implement( bool GetComponent(
		const tiny_uint component_id,
		TinyComponent*& component
	) ) { 
		auto state = GetIsValid( component_id );

		if ( state )
			component = tiny_cast( tiny_rvalue( _components[ component_id ] ), TinyComponent* );

		return state;
	};


private:
	bool GetIsValid( const tiny_uint comp_id ) const { 
		return comp_id < _components.size( );
	};

	tiny_uint FindID( const tiny_hash entity_hash ) const {
		auto low   = tiny_cast( 0, tiny_uint );
		auto max   = _components.size( );
		auto high  = max;
		auto pivot = low;

		while ( low < high ) {
			pivot = low + ( high - low ) / 2;

			if ( _components[ pivot ].GetOwner( ) == entity_hash )
				break;

			if ( _components[ pivot ].GetOwner( ) < entity_hash )
				low = pivot < max ? pivot + 1 : pivot;
			else
				high = pivot;
		}

		return pivot;
	};

	tiny_uint CreateID( const tiny_hash entity_hash ) const { 
		auto comp_id   = FindID( entity_hash );

		if ( _components.size( ) > 0 && _components[ comp_id ].GetOwner( ) < entity_hash )
			comp_id += 1;

		return comp_id;
	};

};
