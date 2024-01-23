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
 * @creation : 23/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolMaterial::TinyToolMaterial( )
	: TinyToolAssetEditor{ "Material" }
{ }

void TinyToolMaterial::Save( TinyGame* game ) {
}

void TinyToolMaterial::Tick( TinyGame* game, TinyAssetManager& assets ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyToolMaterial::OnOpen( TinyGame* game, const tiny_string& name, c_ptr asset ) {
	return true;
}

void TinyToolMaterial::OnTick( TinyGame* game, TinyAssetManager& assets ) {
}

void TinyToolMaterial::OnClose( TinyGame* game, TinyAssetManager& assets ) {
}
