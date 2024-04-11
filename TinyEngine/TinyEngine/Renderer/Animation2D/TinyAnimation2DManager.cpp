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
 * @creation : 16/01/2024
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
TinyAnimation2DManager::TinyAnimation2DManager( ) 
	: TinyAssetContainer{ }
{ }

bool TinyAnimation2DManager::Create(
	TinyGame* game,
	const tiny_string& alias,
	const c_pointer builder
) {
	return false;
}

bool TinyAnimation2DManager::Load(
	TinyGame* game,
	const tiny_string& alias,
	TinyFile& file
) {
	/*
	auto& collection = animation.GetCollection( );

	return file.Read( collection );
	*/

	return false;
}
