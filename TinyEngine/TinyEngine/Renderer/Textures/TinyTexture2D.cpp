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
	TinyTextureSpriteSheet{ }
{ }

bool TinyTexture2D::Create(
	TinyGraphicManager& graphics, 
	const TinyTexture2DBuilder& builder,
	const TinyGraphicBufferStaging& staging
) {
	auto context = graphics.GetContext( );
	auto state   = TinyGraphicTexture::Create( context, builder, staging );

	if ( state )
		SetDimensions( builder.Columns, builder.Rows );

	return state;
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
