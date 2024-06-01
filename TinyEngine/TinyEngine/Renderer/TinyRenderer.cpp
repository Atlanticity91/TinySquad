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
	: m_cameras{ },
	m_uniforms { },
	m_batchs{ },
	m_debug{ },
	m_post_process{ }
{ }

bool TinyRenderer::Initialize( TinyGraphicManager& graphics, TinyFilesystem filesystem ) {
	auto& staging = m_batchs.GetStaging( );

	PushShaderMacros( graphics );

	m_cameras.Initialize( );

	return  m_batchs.Initialize( graphics, m_uniforms ) &&
			m_debug.Initialize( graphics, m_uniforms )  &&
			m_uniforms.Create( graphics, staging );
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
	return m_cameras.CreateProjection( alias );
}

void TinyRenderer::RemoveProjection( const tiny_string& alias ) {
	m_cameras.RemoveProjection( alias );
}

void TinyRenderer::RemoveProjection( const tiny_hash hash ) {
	m_cameras.RemoveProjection( hash );
}

TinyRenderCamera& TinyRenderer::CreateCamera( const tiny_string& entity_name ) {
	return m_cameras.CreateCamera( entity_name );
}

TinyRenderCamera& TinyRenderer::CreateCamera(
	const tiny_string& entity_name,
	const tiny_string& projection
) {
	return m_cameras.CreateCamera( entity_name, projection );
}

void TinyRenderer::RemoveCamera( const tiny_string& entity_name ) {
	m_cameras.RemoveCamera( entity_name );
}

void TinyRenderer::RemoveCamera( const tiny_hash entity_hash ) {
	m_cameras.RemoveCamera( entity_hash );
}

void TinyRenderer::ReCalculate( ) { m_cameras.ReCalculate( ); }

void TinyRenderer::ReCalculate( const tiny_hash entity_hash ) { 
	m_cameras.ReCalculate( entity_hash ); 
}

void TinyRenderer::ReCalculateCurrent( ) { m_cameras.ReCalculateCurrent( ); }

void TinyRenderer::SetDebugLineWidth( float width ) { m_debug.SetLineWidth( width ); }

void TinyRenderer::Prepare( TinyGraphicManager& graphics ) {
	auto& staging = m_batchs.GetStaging( );

	m_cameras.Prepare( graphics, staging, m_uniforms );
}

void TinyRenderer::Prepare(
	TinyGame* game,
	TinyRenderBatchTypes type,
	const tiny_string& render_pass,
	Callback_t callback
) {
	auto render_hash = tiny_hash{ render_pass };

	m_batchs.Prepare( game, type, render_hash, callback, m_uniforms );
}

void TinyRenderer::Prepare(
	TinyGame* game,
	TinyRenderBatchTypes type,
	const tiny_hash render_pass,
	Callback_t callback
) {
	m_batchs.Prepare( game, type, render_pass, callback, m_uniforms );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderSpriteContext& draw_context ) {
	m_batchs.Draw( game, m_uniforms, draw_context );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderVertexContext& draw_context ) {
	m_batchs.Draw( game, m_uniforms, draw_context );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderLightContext& draw_context ) {
	m_batchs.Draw( game, m_uniforms, draw_context );
}

void TinyRenderer::Draw( TinyGame* game, const TinyRenderTextContext& draw_context ) {
	m_batchs.Draw( game, m_uniforms, draw_context );
}

void TinyRenderer::Flush( TinyGame* game, TinyRenderBatchTypes type ) {
	m_batchs.Flush( game, type, m_uniforms ); 
}

void TinyRenderer::DrawDebug( const TinyRenderDebugPrimitive& primitive ) {
	m_debug.Draw( primitive );
}

void TinyRenderer::Compose( TinyGame* game ) {
	m_batchs.Flush( game, m_uniforms );
	m_post_process.Compose( game, m_uniforms, m_batchs );
	m_debug.Flush( game, m_uniforms, m_batchs );
}

void TinyRenderer::Terminate( TinyGraphicManager& graphics ) {
	m_debug.Terminate( graphics );
	m_batchs.Terminate( graphics );
	m_uniforms.Terminate( graphics );
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
TinyRenderCameraManager& TinyRenderer::GetCameras( ) { return m_cameras; }

TinyRenderUniformManager& TinyRenderer::GetUniforms( ) { return m_uniforms; }

TinyRenderBatchManager& TinyRenderer::GetBatchs( ) { return m_batchs; }

TinyRenderPostProcessor& TinyRenderer::GetPostProcess( ) { return m_post_process; }

TinyGraphicBufferStaging& TinyRenderer::GetStaging( ) { return m_batchs.GetStaging( ); }

bool TinyRenderer::FindProjection( const tiny_string& alias ) const { 
	return m_cameras.FindProjection( alias );
}

bool TinyRenderer::FindProjection( const tiny_hash hash ) const {
	return m_cameras.FindProjection( hash );
}

bool TinyRenderer::FindCamera( const tiny_string& entity_name ) const {
	return m_cameras.FindCamera( entity_name );
}

bool TinyRenderer::FindCamera( const tiny_hash entity_hash ) const {
	return m_cameras.FindCamera( entity_hash );
}

TinyRenderProjection& TinyRenderer::GetProjection( const tiny_string& alias ) {
	return m_cameras.GetProjection( alias );
}

const TinyRenderProjection& TinyRenderer::GetProjection( const tiny_string& alias ) const {
	return m_cameras.GetProjection( alias );
}

TinyRenderProjection& TinyRenderer::GetProjection( const tiny_hash hash ) {
	return m_cameras.GetProjection( hash );
}

const TinyRenderProjection& TinyRenderer::GetProjection( const tiny_hash hash ) const {
	return m_cameras.GetProjection( hash );
}

TinyRenderCamera& TinyRenderer::GetCamera( const tiny_string& entity_name ) {
	return m_cameras.GetCamera( entity_name );
}

const TinyRenderCamera& TinyRenderer::GetCamera( const tiny_string& entity_name ) const {
	return m_cameras.GetCamera( entity_name );
}

TinyRenderCamera& TinyRenderer::GetCamera( const tiny_hash entity_hash ) {
	return m_cameras.GetCamera( entity_hash );
}

const TinyRenderCamera& TinyRenderer::GetCamera( const tiny_hash entity_hash ) const {
	return m_cameras.GetCamera( entity_hash );
}

TinyRenderProjection& TinyRenderer::GetCurrentProjection( ) {
	return m_cameras.GetCurrentProjection( );
}

const TinyRenderProjection& TinyRenderer::GetCurrentProjection( ) const {
	return m_cameras.GetCurrentProjection( );
}

TinyRenderCamera& TinyRenderer::GetCurrentCamera( ) {
	return m_cameras.GetCurrentCamera( );
}

const TinyRenderCamera& TinyRenderer::GetCurrentCamera( ) const {
	return m_cameras.GetCurrentCamera( ); 
}

const tiny_mat4& TinyRenderer::GetCameraMatrix( ) const { 
	return m_cameras.GetCurrentMatrix( ); 
}

float TinyRenderer::GetDebugLineWidth( ) const { return m_debug.GetLineWidth( ); }
