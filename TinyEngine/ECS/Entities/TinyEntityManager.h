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

#include "TinyEntity.h"

te_struct TinyEntityGhost {

	tiny_hash Hash{ };
	tiny_uint EntityID	  = 0;
	tiny_uint ComponentID = TINY_UINT_MAX;

};

te_class TinyEntityManager final { 

private:
	tiny_map<TinyEntity>	   _entities;
	tiny_list<TinyEntityGhost> _removed;

public:
	TinyEntityManager( );

	~TinyEntityManager( ) = default;

	tiny_uint Create( const tiny_string& name, const tiny_uint parent_id );

	bool Rename( const tiny_uint entity_id, const tiny_string& new_name );

	void Kill( const tiny_uint entity_id );

	void Attach( const tiny_uint entity_id, const tiny_uint parent_id );

	void Detach( const tiny_uint entity_id );

	void AddFlag( const tiny_uint entity_id, tiny_uint flag_id );

	void ToggleFlag( const tiny_uint entity_id, tiny_uint flag_id );

	void DeleteFlag( const tiny_uint entity_id, tiny_uint flag_id );

	void AddFlags( const tiny_uint entity_id, tiny_uint flags );

	void DeleteFlags( const tiny_uint entity_id, tiny_uint flags );

	bool Append( 
		const tiny_uint entity_id, 
		const tiny_uint component_id, 
		tiny_hash& entity_hash 
	);

	void Remove( const tiny_uint entity_id, const tiny_uint component_id );

	void Clean( );

public:
	tiny_map<TinyEntity>& GetEntities( );

	const tiny_map<TinyEntity>& GetEntities( ) const;

	const tiny_list<TinyEntityGhost>& GetRemoved( ) const;

	tiny_uint GetCount( ) const;

	bool GetExist( const tiny_uint entity_id ) const;

	bool GetEntityID( const tiny_string& name, tiny_uint& entity_id ) const;

	bool GetEntityID( const tiny_hash entity_hash, tiny_uint& entity_id ) const;

	bool GetEntityHash( const tiny_uint entity_id, tiny_hash& hash ) const;

	TinyEntity* GetEntity( const tiny_uint entity_id ) const;

	bool GetIsAlive( const tiny_uint entity_id ) const;

	bool GetHasParent( const tiny_uint entity_id ) const;

	bool GetHasFlag( const tiny_uint entity_id, const tiny_uint flag_id ) const;

	bool GetHasFlags( const tiny_uint entity_id, const tiny_uint flags ) const;

	bool GetHasComponent( const tiny_uint entity_id, const tiny_uint component_id ) const;

	bool GetHasComponents( const tiny_uint entity_id, const tiny_uint components ) const;

};
