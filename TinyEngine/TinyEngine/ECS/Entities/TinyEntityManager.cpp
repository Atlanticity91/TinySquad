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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyEntityManager::TinyEntityManager( )
	: _entities{ },
	_removed{ }
{ }

tiny_uint TinyEntityManager::Create( const tiny_string& name, const tiny_uint parent_id ) {
	auto entity_id = TINY_UINT_MAX;
	
	static int i = 0;

	if ( !_entities.find( name, entity_id ) ) {
		auto entity = TinyEntity{ };

		entity.Flags |= TINY_LEFT_SHIFT( TE_FLAG_ALIVE );
		entity.Flags |= TINY_LEFT_SHIFT( TE_FLAG_VISIBLE );

		_entities.emplace( name, entity );
		_entities.find( name, entity_id );
		
		if ( parent_id < TE_NO_PARENT )
			Attach( entity_id, parent_id );
	}

	return entity_id;
}

bool TinyEntityManager::Rename( const tiny_uint entity_id, const tiny_string& new_name ) {
	auto other = tiny_cast( 0, tiny_uint );
	auto state = !GetEntityID( new_name, other );

	if ( state ) {
		auto old_name = _entities.node( entity_id ).String;

		_entities.remap( old_name, new_name );
	}

	return state;
}

void TinyEntityManager::Kill( const tiny_uint entity_id ) {
	auto& entity = _entities.node( entity_id );
	
	entity.Data.Flags ^= TINY_LEFT_SHIFT( TE_FLAG_ALIVE );

	_removed.create_back( entity.Hash, entity_id, TINY_UINT_MAX );
}

void TinyEntityManager::Attach( const tiny_uint entity_id, const tiny_uint parent_id ) {
	auto& entity = _entities.at( entity_id );
	auto& parent = _entities.at( parent_id );

	entity.Parent = parent_id;

	if ( parent.Next != TE_NO_PARENT )
		entity.Next = parent.Next;

	parent.Next = entity_id;
}

void TinyEntityManager::Detach( const tiny_uint entity_id ) {
	auto& entity   = _entities.at( entity_id );
	auto parent_id = entity.Parent;

	if ( parent_id != TE_NO_PARENT )
		_entities.at( parent_id ).Next = entity.Next;

	entity.Parent = TE_NO_PARENT;
	entity.Next   = TE_NO_CHILD;
}

void TinyEntityManager::AddFlag( const tiny_uint entity_id, tiny_uint flag_id ) {
	_entities.at( entity_id ).Flags |= TINY_LEFT_SHIFT( flag_id );
}

void TinyEntityManager::DeleteFlag( const tiny_uint entity_id, tiny_uint flag_id ) {
	_entities.at( entity_id ).Flags ^= TINY_LEFT_SHIFT( flag_id );
}

void TinyEntityManager::AddFlags( const tiny_uint entity_id, tiny_uint flags ) {
	_entities.at( entity_id ).Flags |= flags;
}

void TinyEntityManager::DeleteFlags( const tiny_uint entity_id, tiny_uint flags ) {
	_entities.at( entity_id ).Flags ^= flags;
}

bool TinyEntityManager::Append( 
	const tiny_uint entity_id, 
	const tiny_uint component_id,
	tiny_hash& entity_hash
) {
	auto state = _entities.find_key( entity_id, entity_hash );

	if ( state ) {
		auto& entity = _entities.at( entity_id );

		if ( !entity.GetHasComponent( component_id ) )
			entity.Components |= TINY_LEFT_SHIFT( component_id );
	}

	return state;
}

void TinyEntityManager::Remove( const tiny_uint entity_id, const tiny_uint component_id ) {
	_entities.at( entity_id ).Components ^= TINY_LEFT_SHIFT( component_id );
	_removed.create_back( _entities.node( entity_id ).Hash, entity_id, component_id );
}

void TinyEntityManager::Clean( ) {
	_removed.sort(
		[]( auto& a, auto& b ) { return a.EntityID > b.EntityID; }
	);

	for ( auto& entity : _removed ) {
		if ( entity.ComponentID < TINY_UINT_MAX )
			continue;

		_entities.erase( entity.EntityID );
	}

	_removed.clear( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_map<TinyEntity>& TinyEntityManager::GetEntities( ) { return _entities; }

const tiny_map<TinyEntity>& TinyEntityManager::GetEntities( ) const { return _entities; }

const tiny_list<TinyEntityGhost>& TinyEntityManager::GetRemoved( ) const { 
	return _removed; 
}

tiny_uint TinyEntityManager::GetCount( ) const { return _entities.size( ); }

bool TinyEntityManager::GetExist( const tiny_uint entity_id ) const {
	return entity_id < _entities.size( ) && _entities[ entity_id ].GetIsAlive( );
}

bool TinyEntityManager::GetEntityID( const tiny_string& name, tiny_uint& entity_id ) const {
	return !name.is_empty( ) && _entities.find( name, entity_id );
}

bool TinyEntityManager::GetEntityID( const tiny_hash entity_hash, tiny_uint& entity_id ) const {
	return _entities.find( entity_hash, entity_id );
}

bool TinyEntityManager::GetEntityHash( const tiny_uint entity_id, tiny_hash& hash ) const {
	return _entities.find_key( entity_id, hash );
}

TinyEntity* TinyEntityManager::GetEntity( const tiny_uint entity_id ) const {
	auto* entity = tiny_cast( nullptr, TinyEntity* );

	if ( entity_id < _entities.size( ) )
		entity = tiny_cast( tiny_rvalue( _entities.at( entity_id ) ), TinyEntity* );

	return entity;
}

bool TinyEntityManager::GetIsAlive( const tiny_uint entity_id ) const {
	return entity_id < _entities.size( ) && _entities.at( entity_id ).GetIsAlive( );
}

bool TinyEntityManager::GetHasParent( const tiny_uint entity_id ) const {
	return entity_id < _entities.size( ) && _entities.at( entity_id ).GetHasParent( );
}

bool TinyEntityManager::GetHasFlag( const tiny_uint entity_id, tiny_uint flag_id ) const {
	return entity_id < _entities.size( ) && _entities.at( entity_id ).GetHasFlag( flag_id );
}

bool TinyEntityManager::GetHasFlags( const tiny_uint entity_id, tiny_uint flags ) const {
	return entity_id < _entities.size( ) && _entities.at( entity_id ).GetHasFlags( flags );
}

bool TinyEntityManager::GetHasComponent(
	const tiny_uint entity_id, 
	const tiny_uint component_id
) const {
	return  entity_id < _entities.size( ) && 
			_entities.at( entity_id ).GetHasComponent( component_id );
}

bool TinyEntityManager::GetHasComponents(
	const tiny_uint entity_id,
	const tiny_uint components 
) const {
	return  entity_id < _entities.size( ) &&
			_entities.at( entity_id ).GetHasComponents( components );
}
