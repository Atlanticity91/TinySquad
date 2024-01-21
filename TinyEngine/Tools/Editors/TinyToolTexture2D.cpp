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
 * @creation : 21/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolTexture2D::TinyToolTexture2D( )
	: TinyToolAssetEditor{ "Texture2D" }
{ }

bool TinyToolTexture2D::Open( TinyGame* game, c_ptr asset ) {
	_asset = asset;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolTexture2D::OnTick( TinyGame* game ) {
	auto* texture = tiny_cast( _asset, TinyTexture2D* );

	TinyImGui::CollapsingOpen(
		"Sprite Sheet",
		[ & ]( ) {
			auto columns = texture->GetColumns( );
			auto rows	 = texture->GetRows( );
			auto uv		 = tiny_vec2{ texture->GetUV( ) };

			TinyImGui::BeginVars( );

			if ( 
				TinyImGui::InputScalar( "Columns", columns ) ||
				TinyImGui::InputScalar( "Rows", rows )
			)
				texture->SetDimensions( rows, columns );

			ImGui::BeginDisabled( );
			TinyImGui::InputVec2( "UV", uv );
			ImGui::EndDisabled( );

			TinyImGui::EndVars( );
		}
	);

	auto& properties = texture->GetProperties( );

	TinyImGui::Collapsing(
		"Properties",
		[ & ]( ) {
			TinyImGui::BeginVars( );

			TinyImGui::TextVar( "Format", "%s", vk::CastFormat( properties.Format ) );
			TinyImGui::TextVar( "Layout", "%s", vk::CastLayout( properties.Layout ) );
			TinyImGui::InputScalar( "Width", properties.Width );
			TinyImGui::InputScalar( "Height", properties.Height );
			TinyImGui::InputScalar( "Depth", properties.Depth );
			TinyImGui::TextVar( "Aspect", "%s", vk::CastAspect( properties.Aspect ) );
			TinyImGui::InputScalar( "Levels", properties.Levels );
			TinyImGui::TextVar( "Samples", "%s", vk::CastSamples( properties.Samples ) );
			TinyImGui::TextVar( "Tiling", "%s", vk::CastTiling( properties.Tiling ) );

			TinyImGui::EndVars( );
		}
	);

	TinyImGui::Collapsing(
		"Sampler",
		[ & ]( ) {
			auto& sampler = properties.Sampler;

			TinyImGui::BeginVars( );
			/*
			TinyImGui::Input( "Mag Filter", sampler.MagFilter );
			TinyImGui::Input( "Min Filter", sampler.MinFilter );
			TinyImGui::Input( "Mipmap Mode", sampler.MipmapMode );
			TinyImGui::Input( "Wrap U", sampler.WrapU );
			TinyImGui::Input( "Wrap V", sampler.WrapV );
			TinyImGui::Input( "Wrap W", sampler.WrapW );
			TinyImGui::InputScalar( "Mip Lod Bias", sampler.MipLodBias );
			TinyImGui::InputScalar( "Max Anisotropy", sampler.MaxAnisotropy );
			TinyImGui::InputScalar( "Compare Op", sampler.CompareOp );
			TinyImGui::InputScalar( "Min Lod", sampler.MinLod );
			TinyImGui::InputScalar( "Max Lod", sampler.MaxLod );
			TinyImGui::InputScalar( "Border Color", sampler.BorderColor );
			TinyImGui::InputScalar( "Use Anisotropy", sampler.UseAnisotropy );
			TinyImGui::InputScalar( "Use Compare", sampler.UseCompare );
			TinyImGui::InputScalar( "Unnormalized", sampler.Unnormalized );
			*/
			TinyImGui::EndVars( );
		}
	);

	if ( ImGui::Button( "Close" ) )
		Close( );
}

void TinyToolTexture2D::OnClose( ) {
}
