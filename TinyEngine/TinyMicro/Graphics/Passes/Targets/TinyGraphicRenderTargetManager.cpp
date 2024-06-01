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
TinyGraphicRenderTargetManager::TinyGraphicRenderTargetManager( )
	: m_targets{ }
{ }

bool TinyGraphicRenderTargetManager::Create(
	TinyGraphicWrapper& graphic,
	const tiny_string& name,
	const tiny_list<TinyGraphicTextureProperties>& textures
) {
	auto state = m_targets.find( name );

	if ( !state ) {
		auto target = TinyGraphicRenderTarget{ };

		state = target.Create( graphic, textures );

		if ( state )
			m_targets.emplace( name, target );
	}

	return state;
}

void TinyGraphicRenderTargetManager::Terminate( TinyGraphicWrapper& graphic ) {
	for ( auto& target : m_targets )
		target.Data.Terminate( graphic );
	m_targets.clear( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicRenderTargetManager::GetExist( const tiny_string& name ) const {
	return m_targets.find( name );
}

tiny_uint TinyGraphicRenderTargetManager::GetCount( ) const { 
	return m_targets.capacity( );
}

const TinyGraphicRenderTarget& TinyGraphicRenderTargetManager::GetTarget( 
	tiny_uint target
) const {
	return m_targets[ target ];
}

const TinyGraphicRenderTarget& TinyGraphicRenderTargetManager::GetTarget( 
	const tiny_string& name 
) const {
	auto hash = tiny_hash{ name };

	return m_targets[ hash ];
}

tiny_list<VkImage> TinyGraphicRenderTargetManager::GetImages( 
	tiny_uint target
) const {
	return GetTarget( target ).GetImages( );
}

tiny_list<VkImage> TinyGraphicRenderTargetManager::GetImages(
	const tiny_string& name
) const {
	return GetTarget( name ).GetImages( );
}

tiny_list<VkImageView> TinyGraphicRenderTargetManager::GetViews(
	tiny_uint target
) const {
	return GetTarget( target ).GetViews( );
}

tiny_list<VkImageView> TinyGraphicRenderTargetManager::GetViews( 
	const tiny_string& name 
) const {
	return GetTarget( name ).GetViews( );
}

const VkImageView TinyGraphicRenderTargetManager::GetView(
	tiny_uint target,
	tiny_uint texture
) const {
	return GetTarget( target ).GetView( texture );
}

const VkImageView TinyGraphicRenderTargetManager::GetView(
	const tiny_string& name, 
	tiny_uint texture
) const {
	return GetTarget( name ).GetView( texture );
}

const tiny_list<TinyGraphicTexture>& TinyGraphicRenderTargetManager::GetTextures(
	tiny_uint target 
) const {
	return GetTarget( target ).GetTextures( );
}

const tiny_list<TinyGraphicTexture>& TinyGraphicRenderTargetManager::GetTextures(
	const tiny_string& name 
) const {
	return GetTarget( name ).GetTextures( );
}
