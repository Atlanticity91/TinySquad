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

#include "TinyGraphicRenderpassProperties.h"

tm_class TinyGraphicRenderpass final {

private:
	VkRenderPass m_handle;
	TinyGraphicRenderpassProperties m_properties;

public:
	TinyGraphicRenderpass( );

	~TinyGraphicRenderpass( ) = default;

	bool Create( 
		const TinyGraphicLogical& logical, 
		const TinyGraphicRenderpassBundle& bundle
	);

	tiny_inline void SetClearValue( tiny_uint attachement, const tiny_color& color );

	tiny_inline void SetClearValue( tiny_uint attachement, const VkClearColorValue& color );

	tiny_inline void SetClearValue( 
		tiny_uint attachement, 
		const VkClearDepthStencilValue& depth_value 
	);

	void SetClearValue( tiny_uint attachement, const VkClearValue& clear_value );

	TinyGraphicRenderpass& Begin(
		TinyGraphicWorkContext& work_context,
		const TinyGraphicRenderFrameManager& frames 
	);

	void Terminate( const TinyGraphicLogical& logical );

public:
	const VkRenderPass Get( ) const;

	const TinyGraphicRenderpassProperties& GetProperties( ) const;

private:
	void GetProperties( const TinyGraphicRenderpassBundle& bundle );

public:
	operator const VkRenderPass( ) const;

};
