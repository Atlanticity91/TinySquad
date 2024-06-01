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
 * @creation : 19/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Renderer/Batchs/TinyRenderBatchTextures.h>

template<typename DrawContext_t>
class TinyRenderBatchInstance {

public:
	using Callback_t = std::function<void(
		TinyGraphicWorkContext&,
		TinyMaterial&,
		TinyRenderUniformManager&,
		tiny_uint 
	)>;

protected:
	tiny_hash		_render_pass;
	TinyAssetHandle _material;
	Callback_t		_callback;

public:
	TinyRenderBatchInstance( )
		: _render_pass{ },
		_material{ TA_TYPE_MATERIAL },
		_callback{ }
	{ };

	~TinyRenderBatchInstance( ) = default;

	tiny_abstract( bool Create( 
		TinyGraphicManager& graphics,
		TinyRenderUniformManager& uniforms
	) );

	virtual bool Prepare(
		TinyGraphicManager& graphics,
		const tiny_hash render_pass,
		Callback_t callback
	) {
		auto state = _render_pass == render_pass;

		if ( !state )
			state = graphics.BeginPass( render_pass );

		if ( state ) {
			_render_pass = render_pass;
			_callback	 = callback;
		}

		return state;
	};

	tiny_abstract( void Draw(
		TinyGame* game,
		TinyGraphicBufferStaging& staging,
		TinyRenderUniformManager& uniforms,
		const DrawContext_t& draw_context
	) );

	virtual void Flush( 
		TinyAssetManager& assets, 
		TinyGraphicManager& graphics, 
		TinyGraphicBufferStaging& staging,
		TinyRenderUniformManager& uniforms
	) {
		auto* material = assets.GetAssetAs<TinyMaterial>( _material );
		
		if ( material && _callback ) {
			auto instance_count = UploadBuffers( graphics, staging, uniforms );

			if ( instance_count > 0 ) {
				auto& work_context = graphics.GetWorkdContext( );

				material->Mount( work_context );

				OnFlush( work_context, tiny_lvalue( material ) );

				std::invoke( _callback, work_context, tiny_lvalue( material ), uniforms, instance_count );
			}
		}

		_render_pass.undefined( );
	};

	tiny_abstract( void Terminate( ) );

protected:
	tiny_abstract( tiny_uint UploadBuffers(
		TinyGraphicManager& graphics,
		TinyGraphicBufferStaging& staging,
		TinyRenderUniformManager& uniforms
	) );

	tiny_abstract( void OnFlush( 
		TinyGraphicWorkContext& work_context,
		TinyMaterial& material
	) );

};
