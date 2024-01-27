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
	: TinyAssetList{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAnimation2DManager::OnLoad(
	TinyGame* game,
	TinyFile& file,
	TinyAnimation2D& animation
) {
	auto& frames = animation.Get( );

	return file.Read( frames );
}

void TinyAnimation2DManager::OnUnLoad( TinyGame* game, TinyAnimation2D& animation ) {
}

bool TinyAnimation2DManager::OnCreate(
	TinyGame* game,
	c_pointer asset_builder,
	TinyAnimation2D& animation
) {
	auto* frames = tiny_cast( asset_builder, tiny_list<TinyAnimation2DFrame>* );
	auto state   = frames != nullptr;

	if ( state )
		animation.Get( ) = tiny_lvalue( frames );

	return state;
}
