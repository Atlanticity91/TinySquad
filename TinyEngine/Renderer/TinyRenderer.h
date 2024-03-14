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

#include "Debug/TinyRenderDebugManager.h"

te_class TinyRenderer final {

private:
	TinyRenderUniformManager _uniforms;
	TinyRenderBatchManager   _batchs;
	TinyRenderDebugManager	 _debug;
	//TinyRenderPostProcessor _post_process;

public:
	TinyRenderer( );

	~TinyRenderer( ) = default;

	bool Initialize( TinyGraphicManager& graphics, TinyFilesystem filesystem );

	void Prepare( 
		TinyGame* game, 
		const tiny_string& render_pass,
		FlushMethod_t flush_method 
	);

	tiny_inline void Prepare( 
		TinyGame* game,
		const tiny_hash render_pass,
		FlushMethod_t flush_method 
	);

	tiny_inline void Draw( TinyGame* game, const TinyRenderDraw2DContext& draw_context );

	tiny_inline void Draw( TinyGame* game, const TinyRenderDraw3DContext& draw_context );

	tiny_inline void Flush( TinyGame* game );

	tiny_inline void DrawDebug( TinyGame* game, const TinyRenderDebugPrimitive& primitive );

	void Compose( TinyGame* game );

	void Terminate( TinyGraphicManager& graphics );

public:
	TinyRenderUniformManager& GetUniforms( );

	TinyRenderBatchManager& GetBatchs( );

	//TinyRenderPostProcessor& GetPostProcess( );

};
