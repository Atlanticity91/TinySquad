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
 * @creation : 21/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyToolAssetEditor.h"

te_class TinyToolTexture2D : tiny_inherit( TinyToolAssetEditor ) {

private:
	TinyTexture2D* _texture;
	ImTextureID	   _image;

public:
	TinyToolTexture2D( );

	~TinyToolTexture2D( ) = default;

	tiny_implement( void Save( TinyGame* game ) );

protected:
	tiny_implement( bool OnOpen( TinyGame* game, const tiny_string& name, native_pointer asset ) );

	tiny_implement( void OnTick( TinyGame* game, TinyAssetManager& assets ) );

	tiny_implement( void OnClose( TinyGame* game, TinyAssetManager& assets ) );

private:
	void RenderProperties( TinyGame* game, TinyAssetManager& assets );

	void RenderImage( );

};
