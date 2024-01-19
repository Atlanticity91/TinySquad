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

#include "TinyTexture2DManager.h"

te_struct TinyTexture3DBuilder : tiny_inherit( TinyGraphicTextureBuilder ) {

	tiny_uint Rows = 0;
	tiny_uint Columns = 0;

};

te_class TinyTexture3D final 
	: tiny_inherit( TinyGraphicTexture ),
	tiny_inherit( TinyTextureSpriteSheet )
{

public:
	TinyTexture3D( );

	~TinyTexture3D( ) = default;

	bool Create( TinyGraphicManager& graphics, const TinyTexture3DBuilder& builder );

};
