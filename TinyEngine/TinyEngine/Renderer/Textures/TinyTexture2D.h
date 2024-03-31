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

#include "TinyTextureSpriteSheet.h"

te_struct TinyTexture2DBuilder : tiny_inherit( TinyGraphicTextureSpecification ) {

	tiny_uint Rows     = 0;
	tiny_uint Columns  = 0;
	bool IsUserDefined = false;

};

te_class TinyTexture2D final 
	: tiny_inherit( TinyGraphicTexture ), 
	tiny_inherit( TinyTextureSpriteSheet ) 
{

public:
	TinyTexture2D( );

	~TinyTexture2D( ) = default;

	bool Create( 
		TinyGraphicManager& graphics, 
		const TinyTexture2DBuilder& builder,
		const TinyGraphicBufferStaging& stagging
	);

public:
	bool operator==( const TinyTexture2D* other ) const;

	bool operator==( const TinyTexture2D& other ) const;

	bool operator!=( const TinyTexture2D* other ) const;

	bool operator!=( const TinyTexture2D& other ) const;

};
