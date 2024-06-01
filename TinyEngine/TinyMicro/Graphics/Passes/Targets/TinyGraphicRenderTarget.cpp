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
 * @creation : 20/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicRenderTarget::TinyGraphicRenderTarget( )
	: m_textures{ }
{ }

bool TinyGraphicRenderTarget::Create( 
	TinyGraphicWrapper& graphic,
	const tiny_list<TinyGraphicTextureProperties>& textures
) {
	auto texture_id = textures.size( );
	auto state = true;

	m_textures = texture_id;

	while ( state && texture_id-- > 0 )
		state = m_textures[ texture_id ].Create( graphic, textures[ texture_id ] );

	return state;
}

void TinyGraphicRenderTarget::Terminate( TinyGraphicWrapper& graphic ) {
	for ( auto& texture : m_textures )
		texture.Terminate( graphic );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
VkImageLayout TinyGraphicRenderTarget::GetLayout( ) const {
	return m_textures[ 0 ].GetProperties( ).Layout;
}

tiny_list<VkImage> TinyGraphicRenderTarget::GetImages( ) const {
	auto image_count = m_textures.size( );
	auto images		 = tiny_list<VkImage>{ image_count };

	while ( image_count-- > 0 )
		images[ image_count ] = m_textures[ image_count ].GetImage( );

	return images;
}

tiny_list<VkImageView> TinyGraphicRenderTarget::GetViews( ) const {
	auto view_count = m_textures.size( );
	auto views		= tiny_list<VkImageView>{ view_count };

	while ( view_count-- > 0 )
		views[ view_count ] = m_textures[ view_count ].GetView( );

	return views;
}

const VkImageView TinyGraphicRenderTarget::GetView( tiny_uint texture ) const {
	return m_textures[ texture ].GetView( );
}

const tiny_list<TinyGraphicTexture>& TinyGraphicRenderTarget::GetTextures( ) const {
	return m_textures;
}
