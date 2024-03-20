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

#include "TinyRenderBatchTextures.h"

template<typename DrawContext_t, tiny_uint TextureCount>
class TinyRenderBatchInstance {

public:
	using Texture_t  = TinyRenderBatch<TinyGraphicPipelineBindpoint, TextureCount>;
	using Callback_t = std::function<void(
		TinyGraphicWorkContext&,
		TinyMaterial&,
		TinyRenderUniformManager&,
		tiny_uint instance_count
	)>;

protected:
	tiny_hash  _render_pass;
	TinyAsset  _material;
	Callback_t _callback;
	tiny_uint  _max_texture_slots;
	Texture_t  _textures;

public:
	TinyRenderBatchInstance( )
		: _render_pass{ },
		_material{ },
		_callback{ },
		_max_texture_slots{ 0 },
		_textures{ }
	{ };

	~TinyRenderBatchInstance( ) = default;

	virtual bool Create( 
		TinyGraphicManager& graphics,
		TinyRenderUniformManager& uniforms
	) {
		auto& physical = graphics.GetPhysical( );
		auto& limits   = physical.GetProperties( ).limits;

		auto image_count   = limits.maxPerStageDescriptorSampledImages;
		auto sampler_count = limits.maxPerStageDescriptorSamplers;

		_max_texture_slots = image_count < sampler_count ? image_count : sampler_count;
		
		return _textures.Create( );
	};

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
				auto textures	   = UploadTextures( );

				material->Mount( work_context );
				material->Bind( work_context, textures.Count, textures.Textures );

				std::invoke( _callback, work_context, tiny_lvalue( material ), uniforms, instance_count );
			}
		}

		_render_pass.empty( );
	};

	virtual void Terminate( ) { _textures.Terminate( ); };

protected:
	tiny_abstract( tiny_uint UploadBuffers(
		TinyGraphicManager& graphics,
		TinyGraphicBufferStaging& staging,
		TinyRenderUniformManager& uniforms
	) );

private:
	TinyRenderBatchTextures UploadTextures( ) {
		auto textures = _textures.Flush( );

		return { textures.Count, tiny_cast( textures.Values, TinyGraphicPipelineBindpoint* ) };
	};

};
