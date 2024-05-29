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
 * @creation : 16/04/2024
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
TinySceneManager::TinySceneManager( ) 
	: TinyAssetContainer{ }
{ }

bool TinySceneManager::Create(
	TinyGame* game,
	const tiny_string& alias,
	const native_pointer builder
) {
	return false;
}

bool TinySceneManager::Load(
	TinyGame* game,
	const tiny_string& alias,
	TinyFile& file
) {
	return false;
}

tiny_uint TinySceneManager::Spawn(
	TinyGame* game,
	const tiny_string& entity_name,
	std::function<void( const tiny_uint, TinyGame*, TinyECS& )> entity_factory
) {
	auto entity_id = TINY_UINT_MAX;

	if ( entity_name.get_is_valid( ) && entity_factory ) {
		auto& ecs = game->GetECS( );
		
		entity_id = ecs.Create( entity_name );

		if ( entity_id < TINY_UINT_MAX )
			std::invoke( entity_factory, entity_id, game, ecs );
	}

	return entity_id;
}

tiny_uint TinySceneManager::Spawn(
	TinyGame* game,
	const tiny_string& entity_name,
	const tiny_string& prefab_name
) {
	auto entity_id = TINY_UINT_MAX;

	if ( entity_name.get_is_valid( ) && prefab_name.get_is_valid( ) ) {
		auto& assets  = game->GetAssets( );
		auto* prefabs = assets.GetContainerAs<TinyPrefabManager>( TA_TYPE_PREFAB );

		if ( prefabs )
			entity_id = prefabs->Spawn( game, entity_name, prefab_name );
	}

	return entity_id;
}
