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
	: TinyAssetList{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyTexture3DManager::OnLoad(
	TinyGame* game,
	TinyFile& file,
	TinyTexture3D& texture
) {
	return false;
}

void TinyTexture3DManager::OnUnLoad( TinyGame* game, TinyTexture3D& texture ) {
}

bool TinyTexture3DManager::OnCreate(
	TinyGame* game,
	c_pointer asset_builder,
	TinyTexture3D& element
) {
	return false;
}
