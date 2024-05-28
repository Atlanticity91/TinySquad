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
 * @creation : 17/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinySampleManager::TinySampleManager( )
	: TinyAssetContainer{ }
{ }

bool TinySampleManager::Create(
	TinyGame* game,
	const tiny_string& alias,
	const native_pointer builder
) {
	auto state = false;

	if ( builder ) {
	}
	
	return state;
}

bool TinySampleManager::Load(
	TinyGame* game,
	const tiny_string& alias,
	TinyFile& file
) {
	return Create( game, alias, nullptr );
}
