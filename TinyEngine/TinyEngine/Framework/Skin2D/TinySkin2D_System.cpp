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
void TinySkin2DSystem::PostTick( TinyGame* game ) {
	auto draw_context = TinyRenderDraw2DContext{ };
	auto& renderer	  = game->GetRenderer( );
	auto& assets	  = game->GetAssets( );
	auto& ecs		  = game->GetECS( );
	auto camera		  = renderer.GetCameraMatrix( );

	renderer.Prepare( game, TINY_OUTPASS_HASH, TinySkin2DSystem::Draw );

	for ( auto& component : _components ) {
		auto owner = component.GetOwner( );

		if ( ecs.GetHasFlag( owner, TE_FLAG_VISIBLE ) && component.GetIsActive( ) ) {
			auto* transform = ecs.GetComponentAs<TinyTransform2D>( owner );

			draw_context.Material	  = component.GetMaterial( );
			draw_context.Sprite.Color = component.GetColor( );
			draw_context.Sprite.UV	  = ProcessTexture( assets, draw_context, component );
			draw_context.Tranform	  = camera * transform->GetTransform( );

			renderer.Draw( game, draw_context );
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_vec4 TinySkin2DSystem::ProcessTexture(
	TinyAssetManager& assets,
	TinyRenderDraw2DContext& draw_context,
	TinySkin2D& component
) {
	auto& comp_texture = component.GetTexture( );
	auto* texture	   = tiny_cast( nullptr, TinyTexture2D* );
	auto& sprite	   = component.GetSprite( );

	if ( comp_texture.Type == TA_TYPE_TEXTURE_2D ) {
		draw_context.Textures = 1;
		draw_context.Textures[ 0 ] = assets.GetAssetAs<TinyTexture2D>( comp_texture );
	} else {
		auto texture_id = tiny_cast( 0, tiny_uint );
		auto* atlas		= assets.GetAssetAs<TinyTextureAtlas>( comp_texture );

		draw_context.Textures = atlas->GetComponents( );

		for ( auto* texture = atlas->begin( ); texture < atlas->end( ); texture++ )
			draw_context.Textures[ texture_id++ ] = assets.GetAssetAs<TinyTexture2D>( tiny_lvalue( texture ) );
	}

	texture = draw_context.Textures[ 0 ];

	return texture->GetUV( sprite );
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
	auto* material	  = batchs.GetMaterial( assets );
	auto textures	  = batchs.FlushTextures( );
	auto can_draw	  = false;

	{
		auto& stagging = batchs.GetStaging( );
		auto context   = graphics.GetContext( );
		auto copies	   = batchs.Flush2D( context, vertex_count );

		can_draw = vertex_count > 0;

		if ( can_draw ) {
			auto burner = TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };

			burner.Upload( stagging, uniforms.GetUniform( "ubo_transforms" ), copies[ 0 ] );
			burner.Upload( stagging, uniforms.GetUniform( "ubo_sprites" ), copies[ 1 ] );
		}
	}

	if ( can_draw ) {
		auto work_context = graphics.GetWorkdContext( );

		material->Mount( work_context );
		material->Bind(
			graphics.GetLogical( ),
			work_context,
			{
				uniforms.GetUniform( "ubo_context" ),
				uniforms.GetUniform( "ubo_transforms" ),
				uniforms.GetUniform( "ubo_sprites" )
			}
		);
		material->Bind(
			graphics.GetLogical( ),
			work_context,
			textures.Count,
			tiny_cast( textures.Values, TinyGraphicPipelineBindpoint* )
		);
		material->Draw( work_context, { TGD_MODE_DIRECT, 6, vertex_count } );
	}
}
