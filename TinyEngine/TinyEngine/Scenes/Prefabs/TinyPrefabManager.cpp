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
TinyPrefabManager::TinyPrefabManager( ) 
	: TinyAssetContainer{ }
{ }

bool TinyPrefabManager::Create(
	TinyGame* game,
	const tiny_string& alias,
	const c_pointer builder
) { 
	return false;
}

bool TinyPrefabManager::Load(
	TinyGame* game,
	const tiny_string& alias,
	TinyFile& file
) {
	return Create( game, alias, nullptr );
}

tiny_uint TinyPrefabManager::Spawn(
	TinyGame* game,
	const tiny_string& entity_name,
	const tiny_string& prefab_name
) {
	auto entity_id = TINY_UINT_MAX;
	auto* prefab   = tiny_cast( GetAsset( tiny_hash{ prefab_name } ), TinyPrefab* );

	if ( prefab ) {
		auto& ecs = game->GetECS( );

		entity_id = ecs.Create( entity_name );

		if ( entity_id < TINY_UINT_MAX )
			prefab->Spawn( game, ecs, entity_id );
	}

	return entity_id;
}
