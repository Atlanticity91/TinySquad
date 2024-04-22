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
 * @creation : 14/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinySystemManager::TinySystemManager( )
	: _systems_ids{ },
	_systems{ }
{ }

bool TinySystemManager::Register( ITinySystem* system, tiny_uint target_id ) {
	auto state = system && _systems_ids.size( ) < TINY_MAX_COMPONENT;

	if ( state ) {
		if ( target_id > TINY_MAX_COMPONENT )
			target_id = _systems.size( );
		
		_systems_ids.emplace( system->GetName( ), { target_id } );
		_systems.insert( target_id, system );
	}

	return state;
}

bool TinySystemManager::Remap( const tiny_string& component, tiny_uint target_id ) {
	auto state = _systems_ids.find( component ) && target_id < TINY_MAX_COMPONENT;

	if ( state ) {
		_systems.swap( _systems_ids[ component ], target_id );

		_systems_ids[ component ] = target_id;
	}

	return state;
}

void TinySystemManager::Enable( TinyGame* game, const tiny_uint system_id ) {
	_systems[ system_id ]->Enable( game );
}

void TinySystemManager::Disable( TinyGame* game, const tiny_uint system_id ) {
	_systems[ system_id ]->Disable( game );
}

std::shared_ptr<TinyComponent> TinySystemManager::Create( 
	const tiny_uint component_id,
	const tiny_hash entity_hash
) {
	return _systems[ component_id ]->Create( entity_hash );
}

TinyComponent* TinySystemManager::Append(
	TinyGame* game,
	const tiny_hash entity_hash, 
	const tiny_uint component_id 
) {
	return _systems[ component_id ]->Append( game, entity_hash );
}

bool TinySystemManager::Append(
	TinyGame* game,
	const tiny_uint component_id,
	std::shared_ptr<TinyComponent> component
) {
	return _systems[ component_id ]->Append( game, component );
}

bool TinySystemManager::Set(
	TinyGame* game,
	const tiny_uint component_id,
	std::shared_ptr<TinyComponent> component
) {
	return _systems[ component_id ]->Set( game, component );
}

void TinySystemManager::Remove( 
	TinyGame* game,
	const tiny_hash entity_hash, 
	const tiny_uint component_id
) {
	_systems[ component_id ]->Remove( game, entity_hash );
}

void TinySystemManager::Kill( TinyGame* game, const tiny_hash entity_hash ) {
	for ( auto& system : _systems )
		system->Remove( game, entity_hash );
}

void TinySystemManager::Clean( const tiny_list<TinyEntityGhost>& entities ) {
	for ( auto& ghost : entities ) {
		if ( ghost.ComponentID == TINY_UINT_MAX ) {
			for ( auto* system : _systems ) 
				system->Erase( ghost );
		} else {
			auto* system = _systems.at( ghost.ComponentID );

			system->Erase( ghost );
		}
	}
}

void TinySystemManager::PreTick( TinyGame* game ) {
	for ( auto& system : _systems ) {
		if ( system->GetHasPreTick( ) )
			system->PreTick( game );
	}
}

void TinySystemManager::PostTick( TinyGame* game ) {
	for ( auto& system : _systems ) {
		if ( system->GetHasPostTick( ) )
			system->PostTick( game );
	}
}

void TinySystemManager::Terminate( ) {
	for ( auto& system : _systems )
		delete system;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinySystemManager::GetComponentCount( ) const { return _systems_ids.size( ); }

const tiny_list<tiny_string> TinySystemManager::GetComponentList( ) const {
	auto component_id = tiny_cast( 0, tiny_uint );
	auto components   = tiny_list<tiny_string>{ };

	components = _systems_ids.size( );

	for ( auto& component : _systems_ids )
		components[ component_id++ ] = component.String.c_str( );

	return components;
}

const tiny_list<tiny_string> TinySystemManager::GetComponentListFor(
	tiny_uint component_mask
) const {
	auto components = tiny_list<tiny_string>{ };

	for ( auto& component : _systems_ids ) {
		if ( !( component_mask & TINY_LEFT_SHIFT( 1, component.Data ) ) ) {
			auto name = tiny_string{ component.String };

			components.emplace_back( name );
		}
	}

	return components;
}

const tiny_list<ITinySystem*> TinySystemManager::GetSystems( ) const { return _systems; }

ITinySystem* TinySystemManager::GetSystem( tiny_uint component_id ) const {
	return _systems[ component_id ];
}

bool TinySystemManager::GetComponentID(
	const tiny_string& component,
	tiny_uint& component_id
) const {
	auto system_id = tiny_cast( 0, tiny_uint );
	auto state	   = _systems_ids.find( component, system_id );

	if ( state )
		component_id = _systems_ids[ system_id ];

	return state;
}

tiny_uint TinySystemManager::GetComponentMask( tiny_init<tiny_string> components ) const {
	auto component_mask = tiny_cast( 0, tiny_uint );
	auto component_id   = tiny_cast( 0, tiny_uint );

	for ( auto& component : components ) {
		if ( _systems_ids.find( component, component_id ) )
			component_mask |= TINY_LEFT_SHIFT( 1, component_id );
	}

	return component_mask;
}

TinyComponent* TinySystemManager::GetComponent(
	const tiny_hash entity_hash,
	const tiny_uint component_id
) const {
	return _systems[ component_id ]->GetComponent( entity_hash );
}
