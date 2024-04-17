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
	const c_pointer builder
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

void TinySceneManager::Spawn(
	TinyGame* game,
	const tiny_string& entity_name,
	std::function<void( const tiny_uint, TinyGame*, TinyECS& )> entity_factory
) {
	if ( entity_name.is_valid( ) && entity_factory ) {
		auto& ecs	   = game->GetECS( );
		auto entity_id = ecs.Create( entity_name );

		std::invoke( entity_factory, entity_id, game, ecs );
	}
}
