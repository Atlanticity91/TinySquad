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
 * @creation : 19/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Batchs/TinyRenderBatchManager.h"

te_class TinyRenderer final {

private:
	TinyRenderUniformManager _uniforms;
	TinyRenderBatchManager   _batchs;
	//TinyRenderPostProcessor _post_process;

public:
	TinyRenderer( );

	~TinyRenderer( ) = default;

	bool Initialize( TinyGraphicManager& graphics, TinyFilesystem filesystem );

	tiny_inline void Prepare( TinyGame* game, FlushMethod_t flush_method );

	tiny_inline void Draw( TinyGame* game, const TinyRenderDraw2DContext& draw_context );

	void Draw( TinyGame* game, const TinyRenderLine2DContext& context );

	void Draw( 
		TinyGame* game, 
		tiny_init<tiny_vec2> points,
		const tiny_color& color 
	);

	tiny_inline void Draw( TinyGame* game, const TinyRenderDraw3DContext& draw_context );

	tiny_inline void Flush( TinyGame* game );

	void Compose( TinyGame* game );

	void Terminate( TinyGraphicManager& graphics );

public:
	TinyRenderUniformManager& GetUniforms( );

	TinyRenderBatchManager& GetBatchs( );

	//TinyRenderPostProcessor& GetPostProcess( );

};
