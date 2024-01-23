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
	: TinyToolAssetEditor{ "Texture2D" },
	_image{ nullptr }
{ }

void TinyToolTexture2D::Save( TinyGame* game ) {
	auto* texture    = tiny_cast( _asset, TinyTexture2D* );
	auto& properties = texture->GetProperties( );
	auto& assets	 = game->GetAssets( );
	auto builder	 = TinyTexture2DBuilder{ };
	auto* address	 = tiny_cast( tiny_rvalue( builder ), c_ptr );

	Tiny::Memcpy( tiny_rvalue( properties ), tiny_rvalue( builder.Properties ) );

	builder.Columns = texture->GetColumns( );
	builder.Rows	= texture->GetRows( );

	assets.Export( game, _asset_name, address );
}

void TinyToolTexture2D::Tick( TinyGame* game, TinyAssetManager& assets ) {
	if ( !_asset && _image )
		TinyImGui::DestroyTextureID( _image );


	TinyImGui::ScopeVars{ ImGuiStyleVar_WindowMinSize, { 512.f + 256.f, 512.f} };

	TinyToolAssetEditor::Tick( game, assets );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyToolTexture2D::OnOpen( TinyGame* game, const tiny_string& name, c_ptr asset ) {
	_image = TinyImGui::CreateTextureID( tiny_cast( asset, TinyTexture2D* ) );

	return _image;
}

void TinyToolTexture2D::OnTick( TinyGame* game, TinyAssetManager& assets ) {
	auto* texture = tiny_cast( _asset, TinyTexture2D* );

	if ( ImGui::BeginTable( "table1", 2, ImGuiTableFlags_SizingFixedFit ) ) {
		ImGui::TableNextRow( );

		ImGui::TableNextColumn( );

		RenderProperties( game, assets, texture );

		ImGui::TableNextColumn( );

		RenderImage( texture );

		ImGui::EndTable( );
	}
}

void TinyToolTexture2D::OnClose( TinyGame* game, TinyAssetManager& assets ) { 
	Save( game ); 
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolTexture2D::RenderProperties( 
	TinyGame* game,
	TinyAssetManager& assets,
	TinyTexture2D* texture 
) {
	TinyImGui::CollapsingOpen(
		"Sprite Sheet",
		[ & ]( ) {
			TinyImGui::InputScalar( "Columns", texture->GetEditColumns( ) );
			TinyImGui::InputScalar( "Rows", texture->GetEditRows( ) );
			TinyImGui::InputVec2( "UV", texture->GetUV( ) );
		}
	);

	auto& properties = texture->GetEditProperties( );

	TinyImGui::Collapsing(
		"Properties",
		[ & ]( ) {
			ImGui::BeginDisabled( );

			TinyImGui::InputVulkan( "Format", properties.Format );
			TinyImGui::InputVulkan( "Layout", properties.Layout );
			TinyImGui::InputScalar( "Width", properties.Width );
			TinyImGui::InputScalar( "Height", properties.Height );
			TinyImGui::InputScalar( "Depth", properties.Depth );
			TinyImGui::InputVulkan( "Aspect", properties.Aspect );
			TinyImGui::InputScalar( "Levels", properties.Levels );
			TinyImGui::InputVulkan( "Samples", properties.Samples );
			TinyImGui::InputVulkan( "Tiling", properties.Tiling );
			TinyImGui::InputVulkan( "Usage", properties.Usage );

			ImGui::EndDisabled( );
		}
	);

	TinyImGui::Collapsing(
		"Sampler",
		[ & ]( ) {
			auto& sampler = properties.Sampler;

			TinyImGui::InputVulkan( "Mag Filter", sampler.MagFilter );
			TinyImGui::InputVulkan( "Min Filter", sampler.MinFilter );
			TinyImGui::InputVulkan( "Mipmap Mode", sampler.MipmapMode );
			TinyImGui::InputVulkan( "Wrap U", sampler.WrapU );
			TinyImGui::InputVulkan( "Wrap V", sampler.WrapV );
			TinyImGui::InputVulkan( "Wrap W", sampler.WrapW );
			TinyImGui::InputScalar( "Mip Lod Bias", sampler.MipLodBias );
			TinyImGui::InputScalar( "Max Anisotropy", sampler.MaxAnisotropy );
			TinyImGui::InputVulkan( "Compare Op", sampler.CompareOp );
			TinyImGui::InputScalar( "Min Lod", sampler.MinLod );
			TinyImGui::InputScalar( "Max Lod", sampler.MaxLod );
			TinyImGui::InputVulkan( "Border Color", sampler.BorderColor );
			TinyImGui::Checkbox( "Use Anisotropy", sampler.UseAnisotropy );
			TinyImGui::Checkbox( "Use Compare", sampler.UseCompare );
			TinyImGui::Checkbox( "Unnormalized", sampler.Unnormalized );
		}
	);

	auto button_size = TinyImGui::ButtonSpan( 2 );

	if ( ImGui::Button( "Save", button_size ) )
		Save( game );

	ImGui::SameLine( );

	if ( ImGui::Button( "Close", button_size ) )
		Close( game );
}

void TinyToolTexture2D::RenderImage( TinyTexture2D* texture ) {
	auto& properties = texture->GetProperties( );
	auto columns	 = texture->GetColumns( );
	auto rows		 = texture->GetRows( );
	auto aspect		 = properties.Width / properties.Height;

	auto cursor = ImGui::GetCursorScreenPos( );
	auto size   = ImVec2{ 512, 512 };

	ImGui::Image( _image, size, { .0f, 0.f }, { 1.f, 1.f } );
	
	TinyImGui::Grid( cursor, size, { columns, rows } );
}
