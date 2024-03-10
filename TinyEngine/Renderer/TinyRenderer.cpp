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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderer::TinyRenderer( )
	: _uniforms{ },
	_batchs{ }/*, 
	_post_process{ }*/
{ }

bool TinyRenderer::Initialize( TinyGraphicManager& graphics, TinyFilesystem filesystem ) {
	auto context = graphics.GetContext( );
	auto state   = _uniforms.Create( graphics ) && _batchs.Initialize( context );

	if ( state ) {
		graphics.AddCompilerMacros( 
			{
				// === SETS ===
				{ "TinySetID_Core",	   TINY_STR( TINY_RENDER_SET_CORE )    },
				{ "TinySetID_Render",  TINY_STR( TINY_RENDER_SET_RENDER )  },
				{ "TinySetID_Texture", TINY_STR( TINY_RENDER_SET_TEXTURE ) },
				{ "TinySetID_Light",   TINY_STR( TINY_RENDER_SET_LIGHT )   },

				// === OUTPUTS ===
				{ "TinyOutputID_Color",    TINY_STR( TINY_OUTPUT_COLOR )    },
				{ "TinyOutputID_Position", TINY_STR( TINY_OUTPUT_POSITION ) },
				{ "TinyOutputID_Normal",   TINY_STR( TINY_OUTPUT_NORMAL )   },
				{ "TinyOutputID_Light",    TINY_STR( TINY_OUTPUT_LIGHT )    },
				
				// === TYPES HELPERS ===
				{ 
					"tiny_ubo( SET, BIND, NAME )", 
					"layout( set=SET, binding=BIND ) uniform NAME " 
				},
				{
					"tiny_ssbo_in( SET, BIND, NAME )"
					"layout( std140, set=SET, binding=BIND ) readonly buffer NAME"
				},
				{
					"tiny_ssbo_out( SET, BIND, NAME )"
					"layout( std140, set=SET, binding=BIND ) buffer NAME"
				},
				{
					"tiny_constant( NAME )",
					"layout( push_constant ) uniform NAME"
				},
				{ 
					"tiny_sampler2D( BIND, NAME )", 
					"layout( set=TinySetID_Texture, binding=BIND ) uniform sampler2D NAME" 
				},
				{
					"tiny_compute_in2D( BIND, FORMAT, NAME )",
					"layout( binding=BIND, FORMAT ) uniform readonly image2D NAME"
				},
				{
					"tiny_compute_out2D( BIND, FORMAT, NAME )",
					"layout( binding=BIND, FORMAT ) uniform writeonly image2D NAME"
				}
			}
		);
	}

	return state;
}

void TinyRenderer::Prepare( TinyGame* game, FlushMethod_t flush_method ) {
	_batchs.Prepare( game, flush_method );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderDraw2DContext& draw_context ) {
	_batchs.Draw( game, draw_context );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderLine2DContext& context ) {
}

void TinyRenderer::Draw(
	TinyGame* game,
	tiny_init<tiny_vec2> points,
	const tiny_color& color
) {
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderDraw3DContext& draw_context ) {
	_batchs.Draw( game, draw_context );
}

void TinyRenderer::Flush( TinyGame* game ) { _batchs.Flush( game ); }

void TinyRenderer::Compose( TinyGame* game ) {
	auto& graphics = game->GetGraphics( );
	
	//_post_process.Compose( graphics, assets );
	graphics.BeginPass( "OutPass" );

	Flush( game );

	/*
	auto ctx   = graphics.GetContext( );
	auto& ecs  = game->GetECS( );
	auto count = ecs.GetEntityCount( );

	auto* camera = ecs.GetSystemAs<TinyCameraSystem>( );

	_staging.Map( ctx, tiny_sizeof( tiny_mat4 ) );

	while ( count-- > 0 ) {
		auto* t = ecs.GetCompomemtAs<TinyTransform2D>( count );
		auto* s = ecs.GetCompomemtAs<TinySkin2D>( count );

		if ( t && s ) {
			auto cache = camera->GetProjViewMatrix( ) * t->GetLocal( );
			auto core  = TinyUBORenderCore{
				{ 1.f, 1.f, 1.f, 1.f },
				{ .0f, .0f, 1.f, 1.f }
			};

			Tiny::Memcpy( (const c_pointer)s->GetColor().Get(), (c_pointer)&core.Color.r, 4 * tiny_sizeof( float ) );


			Tiny::Memcpy( (const c_pointer)glm::value_ptr( cache ), ( (tiny_pointer)_staging.GetAccess( ) ) +( (7-count) * tiny_sizeof( tiny_mat4 ) ), tiny_sizeof( tiny_mat4 ) );
			Tiny::Memcpy( (const c_pointer)&core, ( (tiny_pointer)_staging.GetAccess( ) ) + ( 8 * tiny_sizeof( tiny_mat4 ) ) + ( ( 7 - count )* tiny_sizeof( TinyUBORenderCore ) ), tiny_sizeof( TinyUBORenderCore ) );
		}
	}

	_staging.UnMap( ctx );

	count = ecs.GetEntityCount( );

	auto burn = TinyGraphicBurner{ ctx, VK_QUEUE_TYPE_GRAPHIC };
	auto r = VkBufferCopy{ 0, 0, 8 * tiny_sizeof( tiny_mat4 ) };

	burn.Upload( _staging, _uniforms.GetUniform( "ubo_transforms" ), r );
	
	r.srcOffset = 8 * tiny_sizeof( tiny_mat4 );
	r.size      = 8 * tiny_sizeof( TinyUBORenderCore );
	
	burn.Upload( _staging, _uniforms.GetUniform( "ubo_render_core" ), r );


	auto* skin = ecs.GetCompomemtAs<TinySkin2D>( 0 );

	if ( skin ) {
		auto* material = assets.GetAssetAs<TinyMaterial>( skin->GetMaterial( ) );
		auto* texture  = assets.GetAssetAs<TinyTexture2D>( skin->GetTexture( ) );

		if ( material && texture ) {
			auto draw_call = TinyGraphicPipelineDrawcall{ TGD_MODE_DIRECT, 6, 8 };
			auto& context  = graphics.GetWorkdContext( );
			
			material->Mount( context );
			material->Bind( 
				graphics.GetLogical( ),
				context,
				{
					_uniforms.GetUniform( "ubo_context" ),
					_uniforms.GetUniform( "ubo_transforms" ),
					_uniforms.GetUniform( "ubo_render_core" ),
					{ 2, 0, tiny_lvalue( texture ) }
				}
			);
			material->Draw( context, draw_call );
		}
	}
	*/

	graphics.NextSubpass( );
}

void TinyRenderer::Terminate( TinyGraphicManager& graphics ) {
	auto context = graphics.GetContext( );

	_batchs.Terminate( context );
	_uniforms.Terminate( graphics );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderUniformManager& TinyRenderer::GetUniforms( ) { return _uniforms; }

TinyRenderBatchManager& TinyRenderer::GetBatchs( ) { return _batchs; }

//TinyRenderPostProcessor& TinyRenderer::GetPostProcess( ) { return _post_process; }
