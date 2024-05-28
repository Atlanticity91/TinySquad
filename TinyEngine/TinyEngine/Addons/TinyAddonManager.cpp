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
 * @creation : 22/12/2023
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
TinyAddonManager::TinyAddonManager( )
{ }

bool TinyAddonManager::Initialize( TinyGame* game ) {
	auto& filesystem = game->GetFilesystem( );

	auto dir = filesystem.GetGameDir( ) + "Addons\\";

	if ( !filesystem.GetDirExist( dir ) )
		filesystem.CreateDir( dir );

	return true;
}

void TinyAddonManager::PreTick( TinyGame* game ) {
}

void TinyAddonManager::PostTick( TinyGame* game ) {
}

void TinyAddonManager::Terminate( TinyGame* game ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
