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

#include <TinyMicro/Graphics/Utils/TinyGraphicWorkContext.h>

tm_class TinyGraphicRenderTarget final { 

private:
	tiny_list<TinyGraphicTexture> _textures;

public:
	TinyGraphicRenderTarget( );

	~TinyGraphicRenderTarget( ) = default;

	bool Create( 
		TinyGraphicContext& graphic, 
		const tiny_list<TinyGraphicTextureProperties>& textures
	);

	void Terminate( TinyGraphicContext& graphic );

public:
	VkImageLayout GetLayout( ) const;

	tiny_list<VkImage> GetImages( ) const;

	tiny_list<VkImageView> GetViews( ) const;

	const VkImageView GetView( tiny_uint texture ) const;

	const tiny_list<TinyGraphicTexture>& GetTextures( ) const;

};
