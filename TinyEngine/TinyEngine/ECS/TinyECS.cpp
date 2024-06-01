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
TinyECS::TinyECS( )
	: m_entities{ },
	m_systems{ },
	m_dispatcher{ }
{ }

bool TinyECS::Remap( const tiny_string& component, tiny_uint target_id ) {
	return m_systems.Remap( component, target_id );
}

void TinyECS::RegisterCallback( tiny_uint type, native_pointer callback ) {
	m_dispatcher.Register( type, callback );
}

void TinyECS::RegisterCallback( tiny_uint type, tiny_init<native_pointer> callbacks ) {
	m_dispatcher.Register( type, callbacks );
}

void TinyECS::Enable( TinyGame* game, const tiny_string& component ) {
	auto component_id = tiny_cast( 0, tiny_uint );

	if ( m_systems.GetComponentID( component, component_id ) )
		m_systems.Enable( game, component_id );
}

void TinyECS::Enable( TinyGame* game, tiny_init<tiny_string> components ) {
	for ( auto& component : components )
		Enable( game, component );
}

void TinyECS::Disable( TinyGame* game, const tiny_string& component ) {
	auto component_id = tiny_cast( 0, tiny_uint );

	if ( m_systems.GetComponentID( component, component_id ) )
		m_systems.Disable( game, component_id );
}

void TinyECS::Disable( TinyGame* game, tiny_init<tiny_string> components ) {
	for ( auto& component : components )
		Disable( game, component );
}

tiny_uint TinyECS::Create( const tiny_string& entity_name ) {
	return m_entities.Create( entity_name, TE_NO_PARENT );
}

tiny_uint TinyECS::Create( const tiny_string& entity_name, const tiny_string& parent_name ) {
	auto parent_id = tiny_cast( 0, tiny_uint );

	m_entities.GetEntityID( parent_name, parent_id );

	return m_entities.Create( entity_name, parent_id );
}

tiny_uint TinyECS::Create( const tiny_string& entity_name, const tiny_hash parent_hash ) {
	auto parent_id = tiny_cast( 0, tiny_uint );

	m_entities.GetEntityID( parent_hash, parent_id );

	return m_entities.Create( entity_name, parent_id );
}

tiny_uint TinyECS::Create( const tiny_string& entity_name, const tiny_uint parent_id ) {
	return m_entities.Create( entity_name, parent_id );
}

bool TinyECS::Rename( const tiny_string& entity_name, const tiny_string& new_name ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	m_entities.GetEntityID( entity_name, entity_id );

	return Rename( entity_id, new_name );
}

bool TinyECS::Rename( const tiny_hash entity_hash, const tiny_string& new_name ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	m_entities.GetEntityID( entity_hash, entity_id );

	return Rename( entity_id, new_name );
}

bool TinyECS::Rename( const tiny_uint entity_id, const tiny_string& new_name ) {
	auto state = m_entities.GetExist( entity_id );

	if ( state )
		state = m_entities.Rename( entity_id, new_name );

	return state;
}

void TinyECS::Kill( TinyGame* game, const tiny_string& entity_name ) {
	auto entity_hash = tiny_hash{ entity_name };

	return Kill( game, entity_hash );
}

void TinyECS::Kill( TinyGame* game, const tiny_hash entity_hash ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_hash, entity_id ) ) {
		m_entities.Kill( entity_id );
		m_systems.Kill( game, entity_hash );
	}
}

void TinyECS::Kill( TinyGame* game, const tiny_uint entity_id ) {
	auto entity_hash = tiny_hash{ };

	if ( m_entities.GetEntityHash( entity_id, entity_hash ) ) {
		m_entities.Kill( entity_id );
		m_systems.Kill( game, entity_hash );
	}
}

bool TinyECS::Attach( const tiny_string& entity_name, const tiny_string& parent_name ) {
	auto parent_id = tiny_cast( 0, tiny_uint );

	return  m_entities.GetEntityID( parent_name, parent_id ) &&
			Attach( entity_name, parent_id );
}

bool TinyECS::Attach( const tiny_string& entity_name, const tiny_hash parent_hash ) {
	auto parent_id = tiny_cast( 0, tiny_uint );

	return  m_entities.GetEntityID( parent_hash, parent_id ) &&
			Attach( entity_name, parent_id );
}

bool TinyECS::Attach( const tiny_string& entity_name, const tiny_uint parent_id ) {
	auto entity_id = tiny_cast( 0, tiny_uint );
	auto state	   = m_entities.GetEntityID( entity_name, entity_id ) &&
					 m_entities.GetExist( parent_id );

	if ( state )
		m_entities.Attach( entity_id, parent_id );

	return state;
}

void TinyECS::Detach( const tiny_string& entity_name ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_name, entity_id ) )
		m_entities.Detach( entity_id );
}

void TinyECS::Detach( const tiny_hash entity_hash ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_hash, entity_id ) )
		m_entities.Detach( entity_id );
}

void TinyECS::Detach( const tiny_uint entity_id ) {
	if ( m_entities.GetExist( entity_id ) )
		m_entities.Detach( entity_id );
}

void TinyECS::AddFlag( const tiny_string& entity_name, tiny_uint flag_id ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( GetEntityID( entity_name, entity_id ) )
		m_entities.AddFlag( entity_id, flag_id );
}

void TinyECS::AddFlag( const tiny_hash entity_hash, tiny_uint flag_id ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( GetEntityID( entity_hash, entity_id ) )
		m_entities.AddFlag( entity_id, flag_id );
}

void TinyECS::AddFlag( const tiny_uint entity_id, tiny_uint flag_id ) {
	if ( m_entities.GetExist( entity_id ) )
		m_entities.AddFlag( entity_id, flag_id );
}

void TinyECS::ToggleFlag( const tiny_string& entity_name, tiny_uint flag_id ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_name, entity_id ) )
		m_entities.DeleteFlag( entity_id, flag_id );
}

void TinyECS::ToggleFlag( const tiny_hash entity_hash, tiny_uint flag_id ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_hash, entity_id ) )
		m_entities.DeleteFlag( entity_id, flag_id );
}

void TinyECS::ToggleFlag( const tiny_uint entity_id, tiny_uint flag_id ) {
	if ( m_entities.GetExist( entity_id ) )
		m_entities.DeleteFlag( entity_id, flag_id );
}

void TinyECS::DeleteFlag( const tiny_string& entity_name, tiny_uint flag_id ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_name, entity_id ) )
		m_entities.DeleteFlag( entity_id, flag_id );
}

void TinyECS::DeleteFlag( const tiny_hash entity_hash, tiny_uint flag_id ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_hash, entity_id ) )
		m_entities.DeleteFlag( entity_id, flag_id );
}

void TinyECS::DeleteFlag( const tiny_uint entity_id, tiny_uint flag_id ) {
	if ( m_entities.GetExist( entity_id ) )
		m_entities.DeleteFlag( entity_id, flag_id );
}

void TinyECS::AddFlags( const tiny_string& entity_name, tiny_uint flags ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_name, entity_id ) )
		m_entities.AddFlags( entity_id, flags );
}

void TinyECS::AddFlags( const tiny_hash entity_hash, tiny_uint flags ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_hash, entity_id ) )
		m_entities.AddFlags( entity_id, flags );
}

void TinyECS::AddFlags( const tiny_uint entity_id, tiny_uint flags ) {
	if ( m_entities.GetExist( entity_id ) )
		m_entities.AddFlags( entity_id, flags );
}

void TinyECS::ToggleFlags( const tiny_string& entity_name, tiny_uint flags ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_name, entity_id ) )
		m_entities.DeleteFlags( entity_id, flags );
}

void TinyECS::ToggleFlags( const tiny_hash entity_hash, tiny_uint flags ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_hash, entity_id ) )
		m_entities.DeleteFlags( entity_id, flags );
}

void TinyECS::ToggleFlags( const tiny_uint entity_id, tiny_uint flags ) {
	if ( m_entities.GetExist( entity_id ) )
		m_entities.DeleteFlags( entity_id, flags );
}

void TinyECS::DeleteFlags( const tiny_string& entity_name, tiny_uint flags ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_name, entity_id ) )
		m_entities.DeleteFlags( entity_id, flags );
}

void TinyECS::DeleteFlags( const tiny_hash entity_hash, tiny_uint flags ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_hash, entity_id ) )
		m_entities.DeleteFlags( entity_id, flags );
}

void TinyECS::DeleteFlags( const tiny_uint entity_id, tiny_uint flags ) {
	if ( m_entities.GetExist( entity_id ) )
		m_entities.DeleteFlags( entity_id, flags );
}

std::shared_ptr<TinyComponent> TinyECS::CreateComponent(
	const tiny_string& entity_name,
	const tiny_string& component
) {
	auto entity_hash = tiny_hash{ entity_name };

	return CreateComponent( entity_hash, component );
}

std::shared_ptr<TinyComponent> TinyECS::CreateComponent(
	const tiny_hash entity_hash,
	const tiny_string& component
) {
	auto comp_id = tiny_cast( 0, tiny_uint );
	auto comp	 = std::shared_ptr<TinyComponent>{ nullptr };

	if ( m_systems.GetComponentID( component, comp_id ) )
		comp = m_systems.Create( comp_id, entity_hash );

	return comp;
}

std::shared_ptr<TinyComponent> TinyECS::CreateComponent(
	const tiny_uint entity_id,
	const tiny_string& component
) {
	auto entity_hash = tiny_hash{ };

	m_entities.GetEntityHash( entity_id, entity_hash );

	return CreateComponent( entity_hash, component );
}

TinyComponent* TinyECS::Append( 
	TinyGame* game,
	const tiny_string& entity_name,
	const tiny_string& component
) {
	auto entity_id = tiny_cast( 0, tiny_uint );
	auto* comp     = tiny_cast( nullptr, TinyComponent* );

	if ( GetEntityID( entity_name, entity_id ) )
		comp = Append( game, entity_id, component );

	return comp;
}

TinyComponent* TinyECS::Append(
	TinyGame* game,
	const tiny_hash entity_hash,
	const tiny_string& component 
) {
	auto entity_id = tiny_cast( 0, tiny_uint );
	
	m_entities.GetEntityID( entity_hash, entity_id );

	return Append( game, entity_id, component );
}

TinyComponent* TinyECS::Append(
	TinyGame* game,
	const tiny_uint entity_id,
	const tiny_string& component
) {
	auto entity_hash = tiny_hash{ };
	auto comp_id	 = tiny_cast( 0, tiny_uint );
	auto* comp		 = tiny_cast( nullptr, TinyComponent* );

	if (
		m_systems.GetComponentID( component, comp_id ) &&
		m_entities.Append( entity_id, comp_id, entity_hash )
	) {
		comp = m_systems.Append( game, entity_hash, comp_id );

		if ( !comp )
			m_entities.Remove( entity_id, comp_id );
	}

	return comp;
}

bool TinyECS::Append( TinyGame* game, std::shared_ptr<TinyComponent> component ) {
	auto state = component.use_count( ) > 0;

	if ( state ) {
		auto entity_hash = component->GetOwner( );
		auto entity_id   = tiny_cast( 0, tiny_uint );
		auto comp_name   = component->GetName( );
		auto comp_id	 = tiny_cast( 0, tiny_uint );

		state = m_entities.GetEntityID( entity_hash, entity_id ) &&
				m_systems.GetComponentID( comp_name, comp_id );

		if ( state ) {
			if ( !m_entities.GetHasComponent( entity_id, comp_id ) ) {
				m_entities.Append( entity_id, comp_id, entity_hash );

				state = m_systems.Append( game, comp_id, component );
			} else
				state = m_systems.Set( game, comp_id, component );
		}
	}

	return state;
}

bool TinyECS::Set( TinyGame* game, std::shared_ptr<TinyComponent> component ) {
	auto state = component.use_count( ) > 0;

	if ( state ) {
		auto entity_hash = component->GetOwner( );
		auto entity_id	 = tiny_cast( 0, tiny_uint );
		auto comp_name   = component->GetName( );
		auto comp_id	 = tiny_cast( 0, tiny_uint );

		state = m_entities.GetEntityID( entity_hash, entity_id ) &&
				m_systems.GetComponentID( comp_name, comp_id )   &&
				m_entities.GetHasComponent( entity_id, comp_id ) &&
				m_systems.Set( game, comp_id, component );
	}

	return state;
}

void TinyECS::Remove(
	TinyGame* game, 
	const tiny_string& name, 
	const tiny_string& component 
) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( name, entity_id ) )
		Remove( game, entity_id, component );
}

void TinyECS::Remove(
	TinyGame* game,
	const tiny_hash entity_hash,
	const tiny_string& component
) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	if ( m_entities.GetEntityID( entity_hash, entity_id ) )
		Remove( game, entity_id, component );
}

void TinyECS::Remove(
	TinyGame* game,
	const tiny_uint entity_id,
	const tiny_string& component
) {
	auto entity_hash = tiny_hash{ };
	auto comp_id	 = tiny_cast( 0, tiny_uint );

	if (
		m_systems.GetComponentID( component, comp_id ) &&
		m_entities.GetEntityHash( entity_id, entity_hash )
	) {
		m_entities.Remove( entity_id, comp_id );
		m_systems.Remove( game, entity_hash, comp_id );
	}
}

void TinyECS::Remove( TinyGame* game, TinyComponent* component ) {
	if ( component ) {
		auto owner = component->GetOwner( );
		auto name  = component->GetName( );

		Remove( game, owner, name );
	}
}

void TinyECS::PreTick( TinyGame* game ) {
	auto& entities = m_entities.GetRemoved( );

	m_systems.Clean( entities ); 
	m_entities.Clean( );

	m_systems.PreTick( game );
}

void TinyECS::PostTick( TinyGame* game ) {
	m_systems.PostTick( game );
}

void TinyECS::Terminate( ) { m_systems.Terminate( ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_map<TinyEntity>& TinyECS::GetEntities( ) {
	return m_entities.GetEntities( );
}

const tiny_map<TinyEntity>& TinyECS::GetEntities( ) const {
	return m_entities.GetEntities( );
}

const tiny_list<tiny_string> TinyECS::GetComponentList( ) const {
	return m_systems.GetComponentList( );
}

const tiny_list<tiny_string> TinyECS::GetComponentListFor( 
	const tiny_hash entity_hash 
) const {
	auto entity_id		= tiny_cast( 0, tiny_uint );
	auto state			= m_entities.GetEntityID( entity_hash, entity_id );
	auto component_mask = state ? m_entities.GetEntity( entity_id )->Components : 0;

	return m_systems.GetComponentListFor( component_mask );
}

const tiny_list<ITinySystem*> TinyECS::GetSystems( ) const {
	return m_systems.GetSystems( );
}

ITinySystem* TinyECS::GetSystem( const tiny_string& component_name ) const {
	auto* system = tiny_cast( nullptr, ITinySystem* );
	auto comp_id = tiny_cast( 0, tiny_uint );

	if ( m_systems.GetComponentID( component_name, comp_id ) )
		system = m_systems.GetSystem( comp_id );

	return system;
}

tiny_uint TinyECS::GetEntityCount( ) const { return m_entities.GetCount( ); }

bool TinyECS::FindEntity( const tiny_string& enity_name ) const {
	auto  entity_id = tiny_cast( 0, tiny_uint );

	return m_entities.GetEntityID( enity_name, entity_id );
}

bool TinyECS::FindEntity( const tiny_hash entity_hash ) const {
	auto  entity_id = tiny_cast( 0, tiny_uint );

	return m_entities.GetEntityID( entity_hash, entity_id );
}

TinyEntity* TinyECS::GetEntity( const tiny_string& enity_name ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );
	auto entity	   = tiny_cast( nullptr, TinyEntity* );

	if ( m_entities.GetEntityID( enity_name, entity_id ) )
		entity = m_entities.GetEntity( entity_id );

	return entity;
}

TinyEntity* TinyECS::GetEntity( const tiny_hash entity_hash ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );
	auto entity	   = tiny_cast( nullptr, TinyEntity* );

	if ( m_entities.GetEntityID( entity_hash, entity_id ) )
		entity = m_entities.GetEntity( entity_id );

	return entity;
}

TinyEntity* TinyECS::GetEntity( const tiny_uint entity_id ) const {
	return m_entities.GetEntity( entity_id );
}

bool TinyECS::GetEntityID( const tiny_string& enity_name, tiny_uint& entity_id ) const {
	return m_entities.GetEntityID( enity_name, entity_id );
}

bool TinyECS::GetEntityID( const tiny_hash entity_hash, tiny_uint& entity_id ) const {
	return m_entities.GetEntityID( entity_hash, entity_id );
}

bool TinyECS::GetIsAlive( const tiny_string& enity_name ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  m_entities.GetEntityID( enity_name, entity_id ) &&
			m_entities.GetIsAlive( entity_id );
}

bool TinyECS::GetIsAlive( const tiny_hash entity_hash ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  m_entities.GetEntityID( entity_hash, entity_id ) &&
			m_entities.GetIsAlive( entity_id );
}

bool TinyECS::GetIsAlive( const tiny_uint entity_id ) const {
	return  m_entities.GetExist( entity_id ) &&
			m_entities.GetIsAlive( entity_id );
}

bool TinyECS::GetHasParent( const tiny_string& enity_name ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  m_entities.GetEntityID( enity_name, entity_id ) &&
			m_entities.GetHasParent( entity_id );
}

bool TinyECS::GetHasParent( const tiny_hash enity_hash ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  m_entities.GetEntityID( enity_hash, entity_id ) && 
			m_entities.GetHasParent( entity_id );
}

bool TinyECS::GetHasParent( const tiny_uint enity_id ) const {
	return  m_entities.GetExist( enity_id ) &&
			m_entities.GetHasParent( enity_id );
}

tiny_uint TinyECS::GetParent( const tiny_string& enity_name ) const {
	auto entity_hash = tiny_hash{ enity_name };

	return GetParent( entity_hash );
}

tiny_uint TinyECS::GetParent( const tiny_hash enity_hash ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );
	auto parent_id = TINY_UINT_MAX;

	if ( m_entities.GetEntityID( enity_hash, entity_id ) )
		parent_id = m_entities.GetEntity( entity_id )->Parent;

	return parent_id;
}

tiny_uint TinyECS::GetParent( const tiny_uint enity_id ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );
	auto parent_id = TINY_UINT_MAX;

	if ( m_entities.GetExist( entity_id ) )
		parent_id = m_entities.GetEntity( entity_id )->Parent;

	return parent_id;
}

bool TinyECS::GetHasFlag( const tiny_string& enity_name, tiny_uint flag_id ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  m_entities.GetEntityID( enity_name, entity_id ) &&
			m_entities.GetHasFlag( entity_id, flag_id );
}

bool TinyECS::GetHasFlag( const tiny_hash entity_hash, tiny_uint flag_id ) const { 
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  m_entities.GetEntityID( entity_hash, entity_id ) &&
			m_entities.GetHasFlag( entity_id, flag_id );
}

bool TinyECS::GetHasFlag( const tiny_uint entity_id, tiny_uint flag_id ) const { 
	return  m_entities.GetExist( entity_id ) &&
			m_entities.GetHasFlag( entity_id, flag_id );
}

bool TinyECS::GetHasFlags( const tiny_string& enity_name, tiny_uint flags ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  m_entities.GetEntityID( enity_name, entity_id ) &&
			m_entities.GetHasFlags( entity_id, flags );
}

bool TinyECS::GetHasFlags( const tiny_hash entity_hash, tiny_uint flags ) const {
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  m_entities.GetEntityID( entity_hash, entity_id ) &&
			m_entities.GetHasFlags( entity_id, flags );
}

bool TinyECS::GetHasFlags( const tiny_uint entity_id, tiny_uint flags ) const {
	return  m_entities.GetExist( entity_id ) &&
			m_entities.GetHasFlags( entity_id, flags );
}

bool TinyECS::GetHasComponent( 
	const tiny_string& enity_name,
	const tiny_string& component 
) const {
	auto entity_id = tiny_cast( 0, tiny_uint );
	
	return  GetEntityID( enity_name, entity_id )&&
			GetHasComponent( entity_id, component );
}

bool TinyECS::GetHasComponent(
	const tiny_hash entity_hash, 
	const tiny_string& component
) const {
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  GetEntityID( entity_hash, entity_id ) &&
			GetHasComponent( entity_id, component );
}

bool TinyECS::GetHasComponent( 
	const tiny_uint entity_id,
	const tiny_string& component
) const {
	auto comp_id = tiny_cast( 0, tiny_uint );
	
	return  m_systems.GetComponentID( component, comp_id ) &&
			m_entities.GetHasComponent( entity_id, comp_id );
}

bool TinyECS::GetHasComponents(
	const tiny_string& entity_name,
	tiny_init<tiny_string> components
) const {
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  GetEntityID( entity_name, entity_id ) &&
			GetHasComponents( entity_id, components );
}

bool TinyECS::GetHasComponents(
	const tiny_hash entity_hash,
	tiny_init<tiny_string> components
) const {
	auto entity_id = tiny_cast( 0, tiny_uint );

	return  GetEntityID( entity_hash, entity_id ) &&
			GetHasComponents( entity_id, components );
}

bool TinyECS::GetHasComponents(
	const tiny_uint entity_id,
	tiny_init<tiny_string> components
) const {
	auto* entity = GetEntity( entity_id );
	auto state   = components.size( ) > 0 && entity != nullptr;

	if ( state ) {
		auto comp_mask = m_systems.GetComponentMask( components );

		state = entity->GetHasComponents( comp_mask );
	}

	return state;
}

TinyComponent* TinyECS::GetComponent(
	const tiny_string& entity_name,
	const tiny_string& component 
) {
	auto entity_hash = tiny_hash{ entity_name };

	return GetComponent( entity_hash, component );
}

TinyComponent* TinyECS::GetComponent(
	const tiny_hash entity_hash, 
	const tiny_string& component 
) {
	auto comp_id = tiny_cast( 0, tiny_uint );
	auto* comp   = tiny_cast( nullptr, TinyComponent* );

	if ( m_systems.GetComponentID( component, comp_id ) )
		comp = m_systems.GetComponent( entity_hash, comp_id );

	return comp;
}

TinyComponent* TinyECS::GetComponent(
	const tiny_uint entity_id, 
	const tiny_string& component
) {
	auto entity_hash = tiny_hash{ };

	m_entities.GetEntityHash( entity_id, entity_hash );

	return GetComponent( entity_hash, component );
}

tiny_list<TinyComponent*> TinyECS::GetComponents( const tiny_string& entity_name ) {
	auto entity_hash = tiny_hash{ entity_name };

	return GetComponents( entity_hash );
}

tiny_list<TinyComponent*> TinyECS::GetComponents( const tiny_hash entity_hash ) {
	auto entity_id = tiny_cast( 0, tiny_uint );

	m_entities.GetEntityID( entity_hash, entity_id );

	return GetComponents( entity_id );
}

tiny_list<TinyComponent*> TinyECS::GetComponents( const tiny_uint entity_id ) {
	auto* entity = m_entities.GetEntity( entity_id );
	auto comps   = tiny_list<TinyComponent*>{ };

	if ( entity ) {
		auto entity_hash = tiny_hash{ };
		auto comp_id = m_systems.GetComponentCount( );

		m_entities.GetEntityHash( entity_id, entity_hash );

		while ( comp_id-- > 0 ) {
			if ( entity->Components & TINY_LEFT_SHIFT( 1, comp_id ) ) {
				auto* comp = m_systems.GetComponent( entity_hash, comp_id );

				comps.emplace_front( comp );
			}
		}
	}

	return comps;
}

tiny_list<TinyComponent*> TinyECS::GetComponents(
	const tiny_string& entity_name,
	tiny_init<tiny_string> components
) {
	auto entity_hash = tiny_hash{ entity_name };

	return GetComponents( entity_hash, components );
}

tiny_list<TinyComponent*> TinyECS::GetComponents(
	const tiny_hash entity_hash,
	tiny_init<tiny_string> components
) {
	auto* entity = m_entities.GetEntity( entity_hash );
	auto comp_id = tiny_cast( 0, tiny_uint );
	auto comps   = tiny_list<TinyComponent*>{ };

	if ( entity ) {
		for ( auto& comp : components ) {
			if ( m_systems.GetComponentID( comp, comp_id ) ) {
				auto* component = m_systems.GetComponent( entity_hash, comp_id );

				if ( component )
					comps.emplace_back( component );
			}
		}
	}

	return comps;
}

tiny_list<TinyComponent*> TinyECS::GetComponents(
	const tiny_uint entity_id,
	tiny_init<tiny_string> components
) {
	auto entity_hash = tiny_hash{ };
	
	m_entities.GetEntityHash( entity_id, entity_hash );

	return GetComponents( entity_hash, components );
}
