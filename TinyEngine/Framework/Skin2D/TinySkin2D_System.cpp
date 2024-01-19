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
 * @creation : 15/11/2023
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
TinySkin2DSystem::TinySkin2DSystem( )
	: TinySystem{ false, true }
{ }

void TinySkin2DSystem::RegisterInterop( TinyGame* game ) {
	tli_make_lua_context( context );

	tli_create( TINY_SKIN2D_NAME );

	tli_createfn( "create", TinyLua::Skin2D::Create );
	tli_createfn( "destroy", TinyLua::Skin2D::Destroy );
	tli_createfn( "set_material", nullptr );
	tli_createfn( "set_texture", nullptr );
	tli_createfn( "set_color", TinyLua::Skin2D::SetColor );
	tli_createfn( "set_sprite_column", nullptr );
	tli_createfn( "set_sprite_row", nullptr );
	tli_createfn( "set_sprite", nullptr );
	tli_createfn( "get_material", nullptr );
	tli_createfn( "get_texture", nullptr );
	tli_createfn( "get_color", TinyLua::Skin2D::GetColor );
	tli_createfn( "get_sprite", nullptr );
	tli_createfn( "to_string", TinyLua::Skin2D::ToString );

	if ( tli_createmeta( TINY_SKIN2D_NAME ) )
		tli_createop( "__tostring", TinyLua::Skin2D::ToString );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinySkin2DSystem::PostTick( TinyGame* game, TinyEngine& engine ) {
	auto draw_context = TinyRenderDraw2DContext{ };
	auto& renderer	  = engine.GetRenderer( );
	auto& assets	  = engine.GetAssets( );
	auto& ecs		  = engine.GetECS( );
	auto* cameras	  = ecs.GetSystemAs<TinyCameraSystem>( );

	if ( !cameras )
		return;

	auto proj_view = cameras->GetProjViewMatrix( );

	renderer.Prepare( game, TinySkin2DSystem::Draw );

	for ( auto& comp : _components ) {
		auto owner = comp.GetOwner( );

		if ( ecs.GetHasFlag( owner, TE_FLAG_VISIBLE ) && comp.GetIsActive( ) ) {
			auto* transform = ecs.GetComponentAs<TinyTransform2D>( owner );

			if ( transform ) {
				auto* texture = assets.GetAssetAs<TinyTexture2D>( comp.GetTexture( ) );

				draw_context.Material	   = comp.GetMaterial( );
				draw_context.Textures	   = 1;
				draw_context.Textures[ 0 ] = texture;
				draw_context.Sprite.Color  = comp.GetColor( );
				draw_context.Sprite.UV     = texture->GetUV( 0, 0 );
				draw_context.Tranform	   = proj_view * transform->GetLocal( );

				renderer.Draw( game, draw_context );
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinySkin2DSystem::Draw(
	TinyGraphicManager& graphics,
	TinyAssetManager& assets,
	TinyRenderUniformManager& uniforms,
	TinyRenderBatchManager& batchs
) {
	auto vertex_count = tiny_cast( 0, tiny_uint );
	auto work_context = graphics.GetWorkdContext( );
	auto* material	  = batchs.GetMaterial( assets );
	auto textures	  = batchs.FlushTextures( );

	{
		auto& stagging = batchs.GetStaging( );
		auto context   = graphics.GetContext( );
		auto copies	   = batchs.Flush2D( context, vertex_count );

		if ( vertex_count > 0 ) {
			auto burner = TinyGraphicBurner{ context, VK_QUEUE_TYPE_DECODE };

			burner.Upload( stagging, uniforms.GetUniform( "ubo_transforms" ), copies[ 0 ] );
			burner.Upload( stagging, uniforms.GetUniform( "ubo_sprites" ), copies[ 1 ] );
		}
	}

	if ( vertex_count > 0 ) {
		material->Mount( work_context );
		material->Bind(
			graphics.GetLogical( ),
			work_context,
			{
				uniforms.GetUniform( "ubo_context" ),
				uniforms.GetUniform( "ubo_transforms" ),
				uniforms.GetUniform( "ubo_sprites" ),
				( (TinyGraphicPipelineBindpoint*)batchs.GetTextures( ).GetData( ) )[ 0 ]
			}
		);

		//material->Bind( graphics.GetLogical( ),context, );
		material->Draw( work_context, { TGD_MODE_DIRECT, 6, vertex_count } );
	}
}
