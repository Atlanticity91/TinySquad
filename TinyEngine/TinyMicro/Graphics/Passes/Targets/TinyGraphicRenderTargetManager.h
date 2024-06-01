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

#include "TinyGraphicRenderTarget.h"

tm_class TinyGraphicRenderTargetManager final {

private:
	tiny_map<TinyGraphicRenderTarget> m_targets;

public:
	TinyGraphicRenderTargetManager( );

	~TinyGraphicRenderTargetManager( ) = default;

	bool Create(
		TinyGraphicWrapper& graphic,
		const tiny_string& name,
		const tiny_list<TinyGraphicTextureProperties>& textures
	);

	void Terminate( TinyGraphicWrapper& graphic );

public:
	bool GetExist( const tiny_string& name ) const;

	tiny_uint GetCount( ) const;

	const TinyGraphicRenderTarget& GetTarget( tiny_uint target ) const;

	const TinyGraphicRenderTarget& GetTarget( const tiny_string& name ) const;

	tiny_list<VkImage> GetImages( tiny_uint target ) const;

	tiny_list<VkImage> GetImages( const tiny_string& name ) const;

	tiny_list<VkImageView> GetViews( tiny_uint target ) const;

	tiny_list<VkImageView> GetViews( const tiny_string& name ) const;

	const VkImageView GetView( tiny_uint target, tiny_uint texture ) const;

	const VkImageView GetView( const tiny_string& name, tiny_uint texture ) const;

	const tiny_list<TinyGraphicTexture>& GetTextures( tiny_uint target ) const;

	const tiny_list<TinyGraphicTexture>& GetTextures( const tiny_string& name ) const;

};
