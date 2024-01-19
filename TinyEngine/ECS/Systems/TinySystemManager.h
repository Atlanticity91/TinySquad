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

#include "TinySystem.h"

te_class TinySystemManager final {

private:
	tiny_map<tiny_uint>		_systems_ids;
	tiny_list<ITinySystem*> _systems;

public:
	TinySystemManager( );

	~TinySystemManager( ) = default;

	bool Register( ITinySystem* system, tiny_uint target_id );

	bool Remap( const tiny_string& component, tiny_uint target_id );

	void Enable( TinyGame* game, TinyEngine& engine, const tiny_uint system_id );

	void Disable( TinyGame* game, TinyEngine& engine, const tiny_uint system_id );

	std::shared_ptr<TinyComponent> Create( 
		const tiny_uint component_id, 
		const tiny_hash entity_hash
	);

	TinyComponent* Append( 
		TinyGame* game,
		TinyEngine& engine, 
		const tiny_hash entity_hash, 
		const tiny_uint component_id 
	);

	bool Append(
		TinyGame* game,
		TinyEngine& engine,
		const tiny_uint component_id,
		std::shared_ptr<TinyComponent> component
	);

	bool Set( 
		TinyGame* game,
		TinyEngine& engine,
		const tiny_uint component_id,
		std::shared_ptr<TinyComponent> component
	);

	void Remove( 
		TinyGame* game, 
		TinyEngine& engine, 
		const tiny_hash entity_hash,
		const tiny_uint component_id 
	);

	void Kill( TinyGame* game, TinyEngine& engine, const tiny_hash entity_hash );

	void PreTick( TinyGame* game, TinyEngine& engine );

	void PostTick( TinyGame* game, TinyEngine& engine );

	void Terminate( );

public:
	tiny_uint GetComponentCount( ) const;

	const tiny_list<tiny_string> GetComponentList( ) const;

	const tiny_list<tiny_string> GetComponentListFor( tiny_uint component_mask ) const;

	const tiny_list<ITinySystem*> GetSystems( ) const;

	ITinySystem* GetSystem( tiny_uint component_id ) const;

	bool GetComponentID( const tiny_string& component, tiny_uint& component_id ) const;

	tiny_uint GetComponentMask( tiny_init<tiny_string> components ) const;

	TinyComponent* GetComponent(
		const tiny_hash entity_hash,
		const tiny_uint component_id
	) const;

};
