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
 * @creation : 24/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyAnimation2D.h"

te_class TinyAnimation2DManager final
	: tiny_inherit( TinyAssetList<TA_TYPE_ADDON, TinyAnimation2D> ) {

public:
	TinyAnimation2DManager( );

	~TinyAnimation2DManager( ) = default;

protected:
	tiny_implement( bool OnLoad(
		TinyGame* game,
		TinyFile& file,
		TinyAnimation2D& animation
	) );

	tiny_implement( void OnUnLoad( TinyGame* game, TinyAnimation2D& animation ) );

	tiny_implement( bool OnCreate(
		TinyGame* game,
		c_ptr asset_builder,
		TinyAnimation2D& animation
	) );

};
