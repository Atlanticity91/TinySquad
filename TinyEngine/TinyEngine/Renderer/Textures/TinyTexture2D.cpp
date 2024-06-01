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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyTexture2D::TinyTexture2D( )
	: TinyGraphicTexture{ },
	TinyTextureSpriteSheet{ },
	TinyAsset{ TA_TYPE_TEXTURE_2D }
{ }

bool TinyTexture2D::Create(
	TinyGraphicManager& graphics, 
	const TinyTexture2DBuilder& builder,
	const TinyGraphicBufferStaging& staging
) {
	auto graphic = graphics.GetWrapper( );
	auto state   = TinyGraphicTexture::Create( graphic, builder, staging );

	if ( state )
		SetDimensions( builder.Columns, builder.Rows );

	return state;
}

void TinyTexture2D::Terminate( TinyGame* game ) {
	auto& graphics = game->GetGraphics( );
	auto graphic   = graphics.GetWrapper( );

	TinyGraphicTexture::Terminate( graphic );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyTexture2D::operator==( const TinyTexture2D* other ) const {
	return GetImage( ) == other->GetImage( ) && GetSampler( ) != other->GetSampler( );
}

bool TinyTexture2D::operator==( const TinyTexture2D& other ) const {
	return tiny_self == tiny_rvalue( other );
}

bool TinyTexture2D::operator!=( const TinyTexture2D* other ) const {
	return !( tiny_self == other );
}

bool TinyTexture2D::operator!=( const TinyTexture2D& other ) const {
	return tiny_self != tiny_rvalue( other );
}
