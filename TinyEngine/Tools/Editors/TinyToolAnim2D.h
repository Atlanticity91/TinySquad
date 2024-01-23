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

#pragma once

#include "TinyToolTexture2D.h"

te_class TinyToolAnim2D final : tiny_inherit( TinyToolAssetEditor ) {

private:
	ImTextureID _image;

public:
	TinyToolAnim2D( );

	~TinyToolAnim2D( ) = default;

	tiny_implement( void Save( TinyGame* game ) );

	tiny_implement( void Tick( TinyGame* game, TinyAssetManager& assets ) );

protected:
	tiny_implement( bool OnOpen( TinyGame* game, const tiny_string& name, c_ptr asset ) );

	tiny_implement( void OnTick( TinyGame* game, TinyAssetManager& assets ) );

	tiny_implement( void OnClose( TinyGame* game, TinyAssetManager& assets ) );

};
