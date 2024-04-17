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
 * @creation : 26/11/2023
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
TinyTexture3DManager::TinyTexture3DManager( ) 
	: TinyAssetContainer{ }
{ }

bool TinyTexture3DManager::Create(
	TinyGame* game,
	const tiny_string& alias,
	const c_pointer builder
) {
	auto state = false;

	if ( builder ) {
	}

	return state;
}

bool TinyTexture3DManager::Load(
	TinyGame* game,
	const tiny_string& alias,
	TinyFile& file
) {
	return Create( game, alias, nullptr );
}
