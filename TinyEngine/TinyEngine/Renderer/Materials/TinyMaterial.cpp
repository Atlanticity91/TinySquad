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
 * @creation : 16/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyMaterial::TinyMaterial( )
	: TinyAsset{ TA_TYPE_MATERIAL }, 
	TinyGraphicPipeline{ },
	m_shaders{ }
{ }

bool TinyMaterial::Create( 
	TinyGame* game,
	TinyGraphicManager& graphics, 
	TinyMaterialBuilder& builder 
) { 
	auto& assets   = game->GetAssets( );
	auto shader_id = builder.ShaderStages.size( );
	auto pass_name = tiny_string{ builder.PassName };
	auto graphic   = graphics.GetWrapper( );
	auto limits    = graphics.GetPipelineLimits( );
	auto state     = true;

	builder.Pass			= graphics.GetRenderPass( pass_name );
	builder.Shaders			= shader_id;
	builder.DescriptorCount = graphics.GetSwapchainCapacity( );

	m_shaders = shader_id;

	while ( state && shader_id-- > 0 ) {
		auto& asset = m_shaders[ shader_id ];

		asset.Type = TA_TYPE_SHADER;
		asset.Hash = tiny_hash{ builder.ShaderStages[ shader_id ] };

		state = assets.Acquire( game, asset );
	}

	if ( state ) {
		shader_id = builder.ShaderStages.size( );

		while ( shader_id-- > 0 ) {
			auto& shader = m_shaders[ shader_id ];
			auto* asset  = assets.GetAssetAs<TinyShader>( shader );

			builder.Shaders[ shader_id ] = asset->Get( );
		}

		state = TinyGraphicPipeline::Create( graphic, limits, builder );
	}

	return state;
}

void TinyMaterial::Submit(
	TinyGraphicManager& graphics,
	const TinyGraphicPipelineDrawcall& draw_call,
	const tiny_list<TinyGraphicPipelineBindpoint>& bindpoints
) {
	auto& work_context = graphics.GetWorkdContext( );

	Mount( work_context );
	Draw( work_context, draw_call, bindpoints );
}

void TinyMaterial::Terminate( TinyGame* game ) {
	auto& graphics = game->GetGraphics( );
	auto& assets   = game->GetAssets( );
	auto graphic = graphics.GetWrapper( );

	for ( auto& shader : m_shaders )
		assets.Release( game, shader );

	TinyGraphicPipeline::Terminate( graphic );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyMaterial::CreateShaders(
	TinyMaterialBuilder& builder,
	tiny_init<tiny_string> shaders
) {
	auto count = shaders.size( );

	if ( count > 0 ) {
		while ( count-- > 0 ) {
			auto shader = tiny_lvalue( shaders.begin( ) + count ).as_string( );

			builder.ShaderStages.emplace_back( shader );
		}
	}
}
