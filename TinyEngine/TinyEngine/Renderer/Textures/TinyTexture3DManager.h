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

#pragma once

#include "TinyTexture3D.h"

te_class TinyTexture3DManager final : tiny_inherit( TinyAssetContainer<TinyTexture3D> ) {

public:
	TinyTexture3DManager( );

protected:
	tiny_implement( bool OnLoad(
		TinyGame* game,
		TinyFile& file,
		TinyTexture3D& texture
	) );

	tiny_implement( void OnUnLoad( TinyGame* game, TinyTexture3D& texture ) );

	tiny_implement( bool OnCreate(
		TinyGame* game,
		c_pointer asset_builder,
		TinyTexture3D& element
	) );

};
