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
 * @creation : 18/08/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyNutTool.h"

tn_class TinyNutToolTexture2D : tiny_inherit( TinyNutTool ) {

private:
	TinyTexture2D* m_texture;
	ImTextureID	m_image;

public:
	TinyNutToolTexture2D( );

	~TinyNutToolTexture2D( ) = default;

	bool Open( TinyNut* nut_game, TinyTexture2D& texture );

	void Close( TinyNut* nut_game );

};
