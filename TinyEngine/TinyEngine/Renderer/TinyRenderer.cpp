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
	auto& staging = _batchs.GetStaging( );

	PushShaderMacros( graphics );

	_cameras.Initialize( );

	return  _batchs.Initialize( graphics, _uniforms ) &&
			_debug.Initialize( graphics, _uniforms )  &&
			_uniforms.Create( graphics, staging );
}

TinyMaterialBuilder TinyRenderer::CreateMaterial(
	TinyGame* game,
	const tiny_string& pass_name,
	tiny_uint subpass
) {
	auto& graphics = game->GetGraphics( );
	auto material  = tiny_cast( graphics.CreatePipeline( TGP_TYPE_NONE, pass_name, subpass ), TinyMaterialBuilder );

	material.PassName = pass_name.as_string( );

	return material;
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
	auto& staging = _batchs.GetStaging( );

	_cameras.Prepare( graphics, staging, _uniforms );
}

void TinyRenderer::Prepare(
	TinyGame* game,
	TinyRenderBatchTypes type,
	const tiny_string& render_pass,
	Callback_t callback
) {
	auto render_hash = tiny_hash{ render_pass };

	_batchs.Prepare( game, type, render_hash, callback, _uniforms );
}

void TinyRenderer::Prepare(
	TinyGame* game,
	TinyRenderBatchTypes type,
	const tiny_hash render_pass,
	Callback_t callback
) {
	_batchs.Prepare( game, type, render_pass, callback, _uniforms );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderSpriteContext& draw_context ) {
	_batchs.Draw( game, _uniforms, draw_context );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderVertexContext& draw_context ) {
	_batchs.Draw( game, _uniforms, draw_context );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderLightContext& draw_context ) {
	_batchs.Draw( game, _uniforms, draw_context );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderTextContext& draw_context ) {
	_batchs.Draw( game, _uniforms, draw_context );
}

void TinyRenderer::Flush( TinyGame* game, TinyRenderBatchTypes type ) {
	_batchs.Flush( game, type, _uniforms ); 
}

void TinyRenderer::DrawDebug( const TinyRenderDebugPrimitive& primitive ) {
	_debug.Draw( primitive );
}

void TinyRenderer::Compose( TinyGame* game ) {
	_batchs.Flush( game, _uniforms );
	_post_process.Compose( game, _uniforms, _batchs );
	_debug.Flush( game, _uniforms, _batchs );
}

void TinyRenderer::Terminate( TinyGraphicManager& graphics ) {
	_debug.Terminate( graphics );
	_batchs.Terminate( graphics );
	_uniforms.Terminate( graphics );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyRenderer::PushShaderMacros( TinyGraphicManager& graphics ) {
	graphics.AddCompilerMacros( {
		// === PI ===
		{ "TinyPI", "3.1415926535897932384626433832795" },
		{ "TinyMaxVertex", TINY_STR( TINY_MAX_VERTEX ) },
		{ "TinyMaxUniform", TINY_STR( TINY_MAX_UNIFORM ) },
		{ "TinyMaxFonts", TINY_STR( TINY_MAX_FONTS ) },

		// === SETS ===
		{ "TinySetID_Core",	   TINY_STR( TINY_RENDER_SET_CORE )    },
		{ "TinySetID_Render",  TINY_STR( TINY_RENDER_SET_RENDER )  },
		{ "TinySetID_Texture", TINY_STR( TINY_RENDER_SET_TEXTURE ) },
		{ "TinySetID_Light",   TINY_STR( TINY_RENDER_SET_LIGHT )   },

		// === OUTPUTS ==
		{ "TinyOutputID_Color",    TINY_STR( TINY_OUTPUT_COLOR )    },
		{ "TinyOutputID_Albedo",   TINY_STR( TINY_OUTPUT_COLOR )    },
		{ "TinyOutputID_Position", TINY_STR( TINY_OUTPUT_POSITION ) },
		{ "TinyOutputID_Normal",   TINY_STR( TINY_OUTPUT_NORMAL )   },
		{ "TinyOutputID_Specular", TINY_STR( TINY_OUTPUT_SPECULAR ) },
		{ "TinyOutputID_Emissive", TINY_STR( TINY_OUTPUT_EMISSIVE ) },

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
			"layout( set=TinySetID_Render, binding=BIND ) uniform sampler2D NAME"
		},
		{
			"tiny_sampler_list( NAME )",
			"tiny_sampler2D( 0, NAME )[]"
		},
		{
			"tiny_texture( TEXTURES, SLOT, UV )",
			"texture( TEXTURES[ nonuniformEXT( SLOT ) ], UV )"
		},
		{
			"tiny_compute_in2D( BIND, FORMAT, NAME )",
			"layout( binding=BIND, FORMAT ) uniform readonly image2D NAME"
		},
		{
			"tiny_compute_out2D( BIND, FORMAT, NAME )",
			"layout( binding=BIND, FORMAT ) uniform writeonly image2D NAME"
		},
	} );
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
