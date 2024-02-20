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

#include "Entities/TinyEntityManager.h"

#define _eRegisterCompt( COMP, TARGET ) Register< ##COMP##System>( this, TARGET )
#define _eRegisterComp( COMP ) _eRegisterCompt( COMP, TINY_UINT_MAX )

template<typename Component>
concept TinyIsComponent = tiny_is_child_of( Component, TinyComponent );

template<typename... Components>
	requires ( TinyIsComponent<Components> && ... )
struct TinyComponentGroup { };

template<typename System>
concept TinyIsSysten = tiny_is_child_of( System, ITinySystem );

te_class TinyECS final {

private:
	TinyEntityManager _entities;
	TinySystemManager _systems;

public:
	TinyECS( );

	~TinyECS( ) = default;

	bool Remap( const tiny_string& component, tiny_uint target_id );

	void Enable( TinyGame* game, const tiny_string& component );

	void Enable( TinyGame* game, tiny_init<tiny_string> components );

	void Disable( TinyGame* game, const tiny_string& component );

	void Disable( TinyGame* game, tiny_init<tiny_string> components );

	tiny_uint Create( const tiny_string& name );

	tiny_uint Create( const tiny_string& entity_name, const tiny_string& parent_name );

	tiny_uint Create( const tiny_string& entity_name, const tiny_hash parent_hash );

	tiny_uint Create( const tiny_string& entity_name, const tiny_uint parent_id );

	bool Rename( const tiny_string& entity_name, const tiny_string& new_name );

	bool Rename( const tiny_hash entity_hash, const tiny_string& new_name );

	bool Rename( const tiny_uint entity_id, const tiny_string& new_name );

	void Kill( TinyGame* game, const tiny_string& entity_name );

	void Kill( TinyGame* game, const tiny_hash entity_hash );

	void Kill( TinyGame* game, const tiny_uint entity_id );

	tiny_inline bool Attach( const tiny_string& entity_name, const tiny_string& parent );

	tiny_inline bool Attach( const tiny_string& entity_name, const tiny_hash parent );
	
	bool Attach( const tiny_string& entity_name, const tiny_uint parent );

	void Detach( const tiny_string& entity_name );

	void Detach( const tiny_hash entity_hash );

	void Detach( const tiny_uint entity_id );

	void AddFlag( const tiny_string& entity_name, tiny_uint flag_id );

	void AddFlag( const tiny_hash entity_hash, tiny_uint flag_id );

	void AddFlag( const tiny_uint entity_hash, tiny_uint flag_id );

	void ToggleFlag( const tiny_string& entity_name, tiny_uint flag_id );
	
	void ToggleFlag( const tiny_hash entity_hash, tiny_uint flag_id );

	void ToggleFlag( const tiny_uint entity_id, tiny_uint flag_id );

	void DeleteFlag( const tiny_string& entity_name, tiny_uint flag_id );

	void DeleteFlag( const tiny_hash entity_hash, tiny_uint flag_id );

	void DeleteFlag( const tiny_uint entity_id, tiny_uint flag_id );

	void AddFlags( const tiny_string& entity_name, tiny_uint flags );

	void AddFlags( const tiny_hash entity_hash, tiny_uint flags );
	
	void AddFlags( const tiny_uint entity_id, tiny_uint flags );

	void ToggleFlags( const tiny_string& entity_name, tiny_uint flags );

	void ToggleFlags( const tiny_hash entity_hash, tiny_uint flags );
	
	void ToggleFlags( const tiny_uint entity_id, tiny_uint flags );

	void DeleteFlags( const tiny_string& entity_name, tiny_uint flags );

	void DeleteFlags( const tiny_hash entity_hash, tiny_uint flags );

	void DeleteFlags( const tiny_uint entity_id, tiny_uint flags );

	tiny_inline std::shared_ptr<TinyComponent> CreateComponent(
		const tiny_string& entity_name,
		const tiny_string& component 
	);

	std::shared_ptr<TinyComponent> CreateComponent(
		const tiny_hash entity_hash,
		const tiny_string& component
	);

	tiny_inline std::shared_ptr<TinyComponent> CreateComponent(
		const tiny_uint entity_id,
		const tiny_string& component
	);

	tiny_inline TinyComponent* Append(
		TinyGame* game,
		const tiny_string& name, 
		const tiny_string& component 
	);

	tiny_inline TinyComponent* Append(
		TinyGame* game,
		const tiny_hash entity_hash, 
		const tiny_string& component 
	);

	TinyComponent* Append(
		TinyGame* game,
		const tiny_uint entity_id,
		const tiny_string& component
	);

	bool Append( 
		TinyGame* game,
		std::shared_ptr<TinyComponent> component
	);

	bool Set(
		TinyGame* game,
		std::shared_ptr<TinyComponent> component
	);

	tiny_inline void Remove(
		TinyGame* game,
		const tiny_string& name, 
		const tiny_string& component
	);

	tiny_inline void Remove(
		TinyGame* game,
		const tiny_hash entity_hash,
		const tiny_string& component
	);

	void Remove(
		TinyGame* game,
		const tiny_uint entity_id,
		const tiny_string& component
	);

	void Remove(
		TinyGame* game,
		TinyComponent* component
	);

	void PreTick( TinyGame* game );

	void PostTick( TinyGame* game );

	void Terminate( );

public:
	template<typename System>
		requires TinyIsSysten<System>
	bool Register( TinyGame* game, tiny_uint target_id ) { 
		auto* system = new System{ };
		auto state   = system && _systems.Register( tiny_cast( system, ITinySystem* ), target_id );

		if ( state )
			system->RegisterInterop( game );

		return state;
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	void Enable( TinyGame* game ) {
		auto comp_name = Component::sGetName( );
		auto comp_id   = tiny_cast( 0, tiny_uint );

		if ( _systems.GetComponentID( comp_name, comp_id ) )
			_systems.Enable( game, comp_id );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	void Disable( TinyGame* game ) {
		auto comp_name = Component::sGetName( );
		auto comp_id   = tiny_cast( 0, tiny_uint );

		if ( _systems.GetComponentID( comp_name, comp_id ) )
			_systems.Disable( game, comp_id );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	Component* Append( TinyGame* game, const tiny_string& entity_name ) {
		auto component_name = Component::sGetName( );
		auto* component		= Append( game, entity_name, component_name );

		return tiny_cast( component, Component* );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	Component* Append( TinyGame* game, const tiny_hash entity_hash ) {
		auto component_name = Component::sGetName( );
		auto* component		= Append( game, entity_hash, component_name );

		return tiny_cast( component, Component* );
	};

	/*
	template<typename Component>
		requires TinyIsComponent<Component>
	Component* Append(
		TinyGame* game,
		 engine, 
		const tiny_uint entity_id
	) {
		auto component_name = Component::sGetName( );
		auto* component		= Append( game, engine, entity_id, component_name );

		return tiny_cast( component, Component* );
	};
	*/

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	tiny_list<TinyComponent*> Append( TinyGame* game, const tiny_string& entity_name ) {
		auto comps = tiny_list<TinyComponent*>{ };

		( [ & ] {
			auto component_name = Components::sGetName( );
			auto* component		= tiny_cast( Append( game, entity_name, component_name ), TinyComponent* );

			if ( component )
				comps.emplace_back( component );
		}( ), ... );

		return comps;
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	tiny_list<TinyComponent*> Append( TinyGame* game, const tiny_hash entity_hash ) {
		auto comps = tiny_list<TinyComponent*>{ };

		( [ & ] {
			auto component_name = Components::sGetName( );
			auto* component		= tiny_cast( Append( game, entity_hash, component_name ), TinyComponent* );

			if ( component )
				comps.emplace_back( component );
		}( ), ... );

		return comps;
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	tiny_list<TinyComponent*> Append( TinyGame* game, const tiny_uint entity_id ) { 
		auto comps = tiny_list<TinyComponent*>{ };

		( [ & ] {
			auto component_name = Components::sGetName( );
			auto* component		= tiny_cast( Append( game, entity_id, component_name ), TinyComponent* );

			if ( component )
				comps.emplace_back( component );
		}( ), ... );

		return comps;
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	tiny_list<TinyComponent*> Append(
		TinyGame* game,
		const tiny_string& entity_name,
		TinyComponentGroup<Components...>
	) {
		return Append<Components...>( game, entity_name );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	tiny_list<TinyComponent*> Append(
		TinyGame* game,
		const tiny_hash entity_hash,
		TinyComponentGroup<Components...>
	) {
		return Append<Components...>( game, entity_hash );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	tiny_list<TinyComponent*> Append(
		TinyGame* game,
		const tiny_uint entity_id,
		TinyComponentGroup<Components...>
	) {
		return Append<Components...>( game, entity_id );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	void Remove( 
		TinyGame* game,
		const tiny_string& entity_name
	) {
		auto component_name = Component::sGetName( );

		Remove( game, entity_name, component_name );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	void Remove(
		TinyGame* game,
		const tiny_hash entity_hash
	) {
		auto component_name = Component::sGetName( );

		Remove( game, entity_hash, component_name );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	void Remove( 
		TinyGame* game,
		const tiny_uint entity_id 
	) {
		auto component_name = Component::sGetName( );

		Remove( game, entity_id, component_name );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	void Remove(
		TinyGame* game,
		const tiny_string& entity_name
	) {
		( Remove<Components>( game, entity_name ), ... );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	void Remove(
		TinyGame* game,
		const tiny_hash entity_hash
	) {
		( Remove<Components>( game, entity_hash ), ... );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	void Remove(
		TinyGame* game,
		const tiny_uint entity_id
	) {
		( Remove<Components>( game, entity_id ), ... );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	void Remove(
		TinyGame* game,
		const tiny_string& entity_name,
		TinyComponentGroup<Components...>
	) {
		Remove<Components...>( game, entity_name );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	void Remove(
		TinyGame* game,
		const tiny_hash entity_hash,
		TinyComponentGroup<Components...>
	) {
		Remove<Components...>( game, entity_hash );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	void Remove(
		TinyGame* game,
		const tiny_uint entity_id,
		TinyComponentGroup<Components...>
	) {
		Remove<Components...>( game, entity_id );
	};

public:
	tiny_map<TinyEntity>& GetEntities( );

	const tiny_map<TinyEntity>& GetEntities( ) const;

	const tiny_list<tiny_string> GetComponentList( ) const;

	const tiny_list<tiny_string> GetComponentListFor( const tiny_hash entity_hash ) const;

	const tiny_list<ITinySystem*> GetSystems( ) const;

	ITinySystem* GetSystem( const tiny_string& component_name ) const;

	tiny_uint GetEntityCount( ) const;

	bool FindEntity( const tiny_string& entity_name ) const;

	bool FindEntity( const tiny_hash entity_hash ) const;
	
	TinyEntity* GetEntity( const tiny_string& entity_name ) const;

	TinyEntity* GetEntity( const tiny_hash entity_hash ) const;

	tiny_inline TinyEntity* GetEntity( const tiny_uint entity_id ) const;

	tiny_inline bool GetEntityID( 
		const tiny_string& name,
		tiny_uint& entity_id
	) const;

	tiny_inline bool GetEntityID(
		const tiny_hash entity_hash,
		tiny_uint& entity_id 
	) const;

	bool GetIsAlive( const tiny_string& entity_name ) const;

	bool GetIsAlive( const tiny_hash entity_hash ) const;

	bool GetIsAlive( const tiny_uint entity_id ) const;

	bool GetHasParent( const tiny_string& entity_name ) const;

	bool GetHasParent( const tiny_hash enity_hash ) const;

	bool GetHasParent( const tiny_uint enity_id ) const;

	tiny_uint GetParent( const tiny_string& enity_name ) const;

	tiny_uint GetParent( const tiny_hash enity_hash ) const;

	tiny_uint GetParent( const tiny_uint enity_id ) const;

	bool GetHasFlag( const tiny_string& enity_name, tiny_uint flag_id ) const;

	bool GetHasFlag( const tiny_hash entity_hash, tiny_uint flag_id ) const;

	bool GetHasFlag( const tiny_uint entity_id, tiny_uint flag_id ) const;

	bool GetHasFlags( const tiny_string& name, tiny_uint flags ) const;

	bool GetHasFlags( const tiny_hash entity_hash, tiny_uint flags ) const;

	bool GetHasFlags( const tiny_uint entity_id, tiny_uint flags ) const;

	tiny_inline bool GetHasComponent(
		const tiny_string& entity_name, 
		const tiny_string& component 
	) const;
	
	tiny_inline bool GetHasComponent(
		const tiny_hash entity_hash, 
		const tiny_string& component 
	) const;

	bool GetHasComponent( const tiny_uint entity_id, const tiny_string& component ) const;

	tiny_inline bool GetHasComponents(
		const tiny_string& name, 
		tiny_init<tiny_string> components 
	) const;

	tiny_inline bool GetHasComponents(
		const tiny_hash entity_hash,
		tiny_init<tiny_string> components
	) const;

	bool GetHasComponents(
		const tiny_uint entity_id,
		tiny_init<tiny_string> components
	) const;

	tiny_inline TinyComponent* GetComponent(
		const tiny_string& entity_name,
		const tiny_string& component 
	);

	TinyComponent* GetComponent(
		const tiny_hash entity_hash, 
		const tiny_string& component
	);

	tiny_inline TinyComponent* GetComponent(
		const tiny_uint entity_id,
		const tiny_string& component 
	);

	tiny_inline tiny_list<TinyComponent*> GetComponents( const tiny_string& entity_name );

	tiny_inline tiny_list<TinyComponent*> GetComponents( const tiny_hash entity_hash );

	tiny_list<TinyComponent*> GetComponents( const tiny_uint entity_id );

	tiny_inline tiny_list<TinyComponent*> GetComponents(
		const tiny_string& entity_name,
		tiny_init<tiny_string> components 
	);

	tiny_list<TinyComponent*> GetComponents(
		const tiny_hash entity_hash,
		tiny_init<tiny_string> components
	);

	tiny_inline tiny_list<TinyComponent*> GetComponents(
		const tiny_uint entity_id,
		tiny_init<tiny_string> components
	);

public:
	template<typename Component>
		requires TinyIsComponent<Component>
	ITinySystem* GetSystem( ) const { 
		auto comp_name = Component::sGetName( );

		return GetSystem( comp_name );
	};

	template<typename System>
		requires TinyIsSysten<System>
	System* GetSystemAs( ) const {
		auto comp_name = System::Component_t::sGetName( );

		return tiny_cast( GetSystem( comp_name ), System* );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	bool GetHasComponent( const tiny_string& entity_name ) const {
		auto component_name = Component::sGetName( );

		return GetHasComponent( entity_name, component_name );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	bool GetHasComponent( const tiny_hash entity_hash ) const {
		auto component_name = Component::sGetName( );

		return GetHasComponent( entity_hash, component_name );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	bool GetHasComponent( const tiny_uint entity_id ) const {
		auto component_name = Component::sGetName( );

		return GetHasComponent( entity_id, component_name );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	bool GetHasComponents( const tiny_string& entity_name ) const {
		auto state = sizeof...( Components ) > 0 ? true : false;

		( [ & ] {
			if ( state )
				state = GetHasComponent<Components>( entity_name );
		}( ), ... );

		return state;
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	bool GetHasComponents( const tiny_hash entity_hash ) const {
		auto state = sizeof...( Components ) > 0 ? true : false;

		( [ & ] {
			if ( state )
				state = GetHasComponent<Components>( entity_hash );
		}( ), ... );

		return state;
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	bool GetHasComponents( const tiny_uint entity_id ) const {
		auto state = sizeof...( Components ) > 0 ? true : false;

		( [ & ] {
			if ( state )
				state = GetHasComponent<Components>( entity_id );
		}( ), ... );

		return state;
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	bool GetHasComponents( 
		const tiny_string& entity_name,
		TinyComponentGroup<Components...> 
	) const {
		return GetHasComponents<Components...>( entity_name );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )
	bool GetHasComponents(
		const tiny_hash entity_hash,
		TinyComponentGroup<Components...>
	) const {
		return GetHasComponents<Components...>( entity_hash );
	};

	template<typename... Components>
		requires ( TinyIsComponent<Components> && ... )	
	bool GetHasComponents( 
		const tiny_uint entity_id,
		TinyComponentGroup<Components...>
	) const {
		return GetHasComponents<Components...>( entity_id );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	Component* GetComponentAs( const tiny_string& entity_name ) {
		auto component_name = Component::sGetName( );
		auto* component		= GetComponent( entity_name, component_name );

		return tiny_cast( component, Component* );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	Component* GetComponentAs( const tiny_hash entity_hash ) {
		auto component_name = Component::sGetName( );
		auto* component		= GetComponent( entity_hash, component_name );

		return tiny_cast( component, Component* );
	};

	template<typename Component>
		requires TinyIsComponent<Component>
	Component* GetComponentAs( const tiny_uint entity_id ) {
		auto component_name = Component::sGetName( );
		auto* component		= GetComponent( entity_id, component_name );

		return tiny_cast( component, Component* );
	};

};
