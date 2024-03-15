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
	_batchs{ },
	_debug{ },
	_post_process{ }
{ }

bool TinyRenderer::Initialize( TinyGraphicManager& graphics, TinyFilesystem filesystem ) {
	auto state = _uniforms.Create( graphics ) && _batchs.Initialize( graphics );

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

		state = _debug.Initialize( graphics );
	}

	return state;
}

void TinyRenderer::SetDebugLineWidth( float width ) { _debug.SetLineWidth( width ); }

void TinyRenderer::Prepare(
	TinyGame* game,
	const tiny_string& render_pass,
	FlushMethod_t flush_method
) {
	auto render_hash = tiny_hash{ render_pass };

	_batchs.Prepare( game, render_hash, flush_method );
}

void TinyRenderer::Prepare(
	TinyGame* game,
	const tiny_hash render_pass,
	FlushMethod_t flush_method 
) {
	_batchs.Prepare( game, render_pass, flush_method );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderDraw2DContext& draw_context ) {
	_batchs.Draw( game, draw_context );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderDraw3DContext& draw_context ) {
	_batchs.Draw( game, draw_context );
}

void TinyRenderer::Flush( TinyGame* game ) { _batchs.Flush( game ); }

void TinyRenderer::DrawDebug( TinyGame* game, const TinyRenderDebugPrimitive& primitive ) {
	_debug.Draw( game, primitive );
}

void TinyRenderer::Compose( TinyGame* game ) {
	Flush( game );
	
	_post_process.Compose( game, _uniforms, _batchs );

	if ( _debug )
		_debug.Flush( game, _uniforms, _batchs );
}

void TinyRenderer::Terminate( TinyGraphicManager& graphics ) {
	_debug.Terminate( graphics );
	_batchs.Terminate( graphics );
	_uniforms.Terminate( graphics );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderUniformManager& TinyRenderer::GetUniforms( ) { return _uniforms; }

TinyRenderBatchManager& TinyRenderer::GetBatchs( ) { return _batchs; }

TinyRenderPostProcessor& TinyRenderer::GetPostProcess( ) { return _post_process; }

float TinyRenderer::GetDebugLineWidth( ) const { return _debug.GetLineWidth( ); }
