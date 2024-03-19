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
 * @creation : 24/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinySkin2D_Interop.h"

te_class TinySkin2DSystem : tiny_inherit( TinySystem<TinySkin2D> ) { 

public:
	TinySkin2DSystem( );

	~TinySkin2DSystem( ) = default;

	tiny_implement( void RegisterInterop( TinyGame* game ) );

protected:
	tiny_implement( void PostTick( TinyGame* game ) );

private:
	tiny_vec4 ProcessTexture( 
		TinyAssetManager& assets,
		TinyRenderSpriteContext& draw_context,
		TinySkin2D& component
	);

public:
	static void Draw( 
		TinyGraphicManager& graphics, 
		TinyAssetManager& assets,
		TinyRenderUniformManager& uniforms,
		TinyRenderBatchManager& batchs 
	);

};
