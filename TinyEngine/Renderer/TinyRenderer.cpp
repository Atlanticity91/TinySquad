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
	: _cameras{ },
	_uniforms { },
	_batchs{ },
	_debug{ },
	_post_process{ }
{ }

bool TinyRenderer::Initialize( TinyGraphicManager& graphics, TinyFilesystem filesystem ) {
	_cameras.Initialize( );

	auto state = _uniforms.Create( graphics ) && _batchs.Initialize( graphics );

	if ( state ) {
		graphics.AddCompilerMacros( 
			{
				// === PI ===
				{ "TinyPI", "3.1415926535897932384626433832795" },

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
					"layout( std140, set=SET, binding=BIND ) writeonly buffer NAME"
				},
				{
					"tiny_ssbo_io( SET, BIND, NAME )"
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

TinyRenderProjection& TinyRenderer::CreateProjection( const tiny_string& alias ) {
	return _cameras.CreateProjection( alias );
}

void TinyRenderer::RemoveProjection( const tiny_string& alias ) {
	_cameras.RemoveProjection( alias );
}

void TinyRenderer::RemoveProjection( const tiny_hash hash ) {
	_cameras.RemoveProjection( hash );
}

TinyRenderCamera& TinyRenderer::CreateCamera( const tiny_string& entity_name ) {
	return _cameras.CreateCamera( entity_name );
}

TinyRenderCamera& TinyRenderer::CreateCamera(
	const tiny_string& entity_name,
	const tiny_string& projection
) {
	return _cameras.CreateCamera( entity_name, projection );
}

void TinyRenderer::RemoveCamera( const tiny_string& entity_name ) {
	_cameras.RemoveCamera( entity_name );
}

void TinyRenderer::RemoveCamera( const tiny_hash entity_hash ) {
	_cameras.RemoveCamera( entity_hash );
}

void TinyRenderer::ReCalculate( ) { _cameras.ReCalculate( ); }

void TinyRenderer::ReCalculate( const tiny_hash entity_hash ) { 
	_cameras.ReCalculate( entity_hash ); 
}

void TinyRenderer::ReCalculateCurrent( ) { _cameras.ReCalculateCurrent( ); }

void TinyRenderer::SetDebugLineWidth( float width ) { _debug.SetLineWidth( width ); }

void TinyRenderer::Prepare( TinyGraphicManager& graphics ) {
	_cameras.Prepare( graphics, _batchs.GetStaging( ), _uniforms );
}

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

void TinyRenderer::DrawDebug( const TinyRenderDebugPrimitive& primitive ) {
	_debug.Draw( primitive );
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
TinyRenderCameraManager& TinyRenderer::GetCameras( ) { return _cameras; }

TinyRenderUniformManager& TinyRenderer::GetUniforms( ) { return _uniforms; }

TinyRenderBatchManager& TinyRenderer::GetBatchs( ) { return _batchs; }

TinyRenderPostProcessor& TinyRenderer::GetPostProcess( ) { return _post_process; }

bool TinyRenderer::FindProjection( const tiny_string& alias ) const { 
	return _cameras.FindProjection( alias );
}

bool TinyRenderer::FindProjection( const tiny_hash hash ) const {
	return _cameras.FindProjection( hash );
}

bool TinyRenderer::FindCamera( const tiny_string& entity_name ) const {
	return _cameras.FindCamera( entity_name );
}

bool TinyRenderer::FindCamera( const tiny_hash entity_hash ) const {
	return _cameras.FindCamera( entity_hash );
}

TinyRenderProjection& TinyRenderer::GetProjection( const tiny_string& alias ) {
	return _cameras.GetProjection( alias );
}

const TinyRenderProjection& TinyRenderer::GetProjection( const tiny_string& alias ) const {
	return _cameras.GetProjection( alias );
}

TinyRenderProjection& TinyRenderer::GetProjection( const tiny_hash hash ) {
	return _cameras.GetProjection( hash );
}

const TinyRenderProjection& TinyRenderer::GetProjection( const tiny_hash hash ) const {
	return _cameras.GetProjection( hash );
}

TinyRenderCamera& TinyRenderer::GetCamera( const tiny_string& entity_name ) {
	return _cameras.GetCamera( entity_name );
}

const TinyRenderCamera& TinyRenderer::GetCamera( const tiny_string& entity_name ) const {
	return _cameras.GetCamera( entity_name );
}

TinyRenderCamera& TinyRenderer::GetCamera( const tiny_hash entity_hash ) {
	return _cameras.GetCamera( entity_hash );
}

const TinyRenderCamera& TinyRenderer::GetCamera( const tiny_hash entity_hash ) const {
	return _cameras.GetCamera( entity_hash );
}

TinyRenderProjection& TinyRenderer::GetCurrentProjection( ) {
	return _cameras.GetCurrentProjection( );
}

const TinyRenderProjection& TinyRenderer::GetCurrentProjection( ) const {
	return _cameras.GetCurrentProjection( );
}

TinyRenderCamera& TinyRenderer::GetCurrentCamera( ) {
	return _cameras.GetCurrentCamera( );
}

const TinyRenderCamera& TinyRenderer::GetCurrentCamera( ) const {
	return _cameras.GetCurrentCamera( ); 
}

const tiny_mat4& TinyRenderer::GetCameraMatrix( ) const { 
	return _cameras.GetCurrentMatrix( ); 
}

float TinyRenderer::GetDebugLineWidth( ) const { return _debug.GetLineWidth( ); }
