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
	: m_entities{ },
	m_removed{ }
{ }

tiny_uint TinyEntityManager::Create( const tiny_string& name, const tiny_uint parent_id ) {
	auto entity_id = TINY_UINT_MAX;
	
	static int i = 0;

	if ( !m_entities.find( name, entity_id ) ) {
		auto entity = TinyEntity{ };

		entity.Flags |= TINY_LEFT_SHIFT( 1, TE_FLAG_ALIVE );
		entity.Flags |= TINY_LEFT_SHIFT( 1, TE_FLAG_VISIBLE );

		m_entities.emplace( name, entity );
		m_entities.find( name, entity_id );
		
		if ( parent_id < TE_NO_PARENT )
			Attach( entity_id, parent_id );
	}

	return entity_id;
}

bool TinyEntityManager::Rename( const tiny_uint entity_id, const tiny_string& new_name ) {
	auto other = tiny_cast( 0, tiny_uint );
	auto state = !GetEntityID( new_name, other );

	if ( state ) {
		auto old_name = m_entities.node( entity_id ).Alias;

		m_entities.remap( old_name, new_name );
	}

	return state;
}

void TinyEntityManager::Kill( const tiny_uint entity_id ) {
	auto& entity = m_entities.node( entity_id );
	
	entity.Data.Flags ^= TINY_LEFT_SHIFT( 1, TE_FLAG_ALIVE );

	m_removed.create_back( entity.Hash, entity_id, TINY_UINT_MAX );
}

void TinyEntityManager::Attach( const tiny_uint entity_id, const tiny_uint parent_id ) {
	auto& entity = m_entities.at( entity_id );
	auto& parent = m_entities.at( parent_id );

	entity.Parent = parent_id;

	if ( parent.Next != TE_NO_PARENT )
		entity.Next = parent.Next;

	parent.Next = entity_id;
}

void TinyEntityManager::Detach( const tiny_uint entity_id ) {
	auto& entity   = m_entities.at( entity_id );
	auto parent_id = entity.Parent;

	if ( parent_id != TE_NO_PARENT )
		m_entities.at( parent_id ).Next = entity.Next;

	entity.Parent = TE_NO_PARENT;
	entity.Next   = TE_NO_CHILD;
}

void TinyEntityManager::AddFlag( const tiny_uint entity_id, tiny_uint flag_id ) {
	m_entities.at( entity_id ).Flags |= TINY_LEFT_SHIFT( 1, flag_id );
}

void TinyEntityManager::DeleteFlag( const tiny_uint entity_id, tiny_uint flag_id ) {
	m_entities.at( entity_id ).Flags ^= TINY_LEFT_SHIFT( 1, flag_id );
}

void TinyEntityManager::AddFlags( const tiny_uint entity_id, tiny_uint flags ) {
	m_entities.at( entity_id ).Flags |= flags;
}

void TinyEntityManager::DeleteFlags( const tiny_uint entity_id, tiny_uint flags ) {
	m_entities.at( entity_id ).Flags ^= flags;
}

bool TinyEntityManager::Append( 
	const tiny_uint entity_id, 
	const tiny_uint component_id,
	tiny_hash& entity_hash
) {
	auto state = m_entities.find_key( entity_id, entity_hash );

	if ( state ) {
		auto& entity = m_entities.at( entity_id );

		if ( !entity.GetHasComponent( component_id ) )
			entity.Components |= TINY_LEFT_SHIFT( 1, component_id );
	}

	return state;
}

void TinyEntityManager::Remove( const tiny_uint entity_id, const tiny_uint component_id ) {
	m_entities.at( entity_id ).Components ^= TINY_LEFT_SHIFT( 1, component_id );
	m_removed.create_back( m_entities.node( entity_id ).Hash, entity_id, component_id );
}

void TinyEntityManager::Clean( ) {
	m_removed.sort(
		[]( auto& a, auto& b ) { return a.EntityID > b.EntityID; }
	);

	for ( auto& entity : m_removed ) {
		if ( entity.ComponentID < TINY_UINT_MAX )
			continue;

		m_entities.erase( entity.EntityID );
	}

	m_removed.clear( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_map<TinyEntity>& TinyEntityManager::GetEntities( ) { return m_entities; }

const tiny_map<TinyEntity>& TinyEntityManager::GetEntities( ) const { return m_entities; }

const tiny_list<TinyEntityGhost>& TinyEntityManager::GetRemoved( ) const { 
	return m_removed; 
}

tiny_uint TinyEntityManager::GetCount( ) const { return m_entities.size( ); }

bool TinyEntityManager::GetExist( const tiny_uint entity_id ) const {
	return entity_id < m_entities.size( ) && m_entities[ entity_id ].GetIsAlive( );
}

bool TinyEntityManager::GetEntityID( const tiny_string& name, tiny_uint& entity_id ) const {
	return !name.get_is_empty( ) && m_entities.find( name, entity_id );
}

bool TinyEntityManager::GetEntityID( const tiny_hash entity_hash, tiny_uint& entity_id ) const {
	return m_entities.find( entity_hash, entity_id );
}

bool TinyEntityManager::GetEntityHash( const tiny_uint entity_id, tiny_hash& hash ) const {
	return m_entities.find_key( entity_id, hash );
}

TinyEntity* TinyEntityManager::GetEntity( const tiny_uint entity_id ) const {
	auto* entity = tiny_cast( nullptr, TinyEntity* );

	if ( entity_id < m_entities.size( ) )
		entity = tiny_cast( tiny_rvalue( m_entities.at( entity_id ) ), TinyEntity* );

	return entity;
}

bool TinyEntityManager::GetIsAlive( const tiny_uint entity_id ) const {
	return entity_id < m_entities.size( ) && m_entities.at( entity_id ).GetIsAlive( );
}

bool TinyEntityManager::GetHasParent( const tiny_uint entity_id ) const {
	return entity_id < m_entities.size( ) && m_entities.at( entity_id ).GetHasParent( );
}

bool TinyEntityManager::GetHasFlag( const tiny_uint entity_id, tiny_uint flag_id ) const {
	return entity_id < m_entities.size( ) && m_entities.at( entity_id ).GetHasFlag( flag_id );
}

bool TinyEntityManager::GetHasFlags( const tiny_uint entity_id, tiny_uint flags ) const {
	return entity_id < m_entities.size( ) && m_entities.at( entity_id ).GetHasFlags( flags );
}

bool TinyEntityManager::GetHasComponent(
	const tiny_uint entity_id, 
	const tiny_uint component_id
) const {
	return  entity_id < m_entities.size( ) && 
			m_entities.at( entity_id ).GetHasComponent( component_id );
}

bool TinyEntityManager::GetHasComponents(
	const tiny_uint entity_id,
	const tiny_uint components 
) const {
	return  entity_id < m_entities.size( ) &&
			m_entities.at( entity_id ).GetHasComponents( components );
}
