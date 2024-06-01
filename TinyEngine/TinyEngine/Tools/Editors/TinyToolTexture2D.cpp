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
	: TinyToolAssetEditor{ "Texture2D", { 908.f, 512.f } },
	m_texture{ nullptr },
	m_image{ nullptr }
{ }

void TinyToolTexture2D::Save( TinyGame* game ) {
	auto& properties = m_texture->GetProperties( );
	auto& assets	 = game->GetAssets( );
	auto builder	 = TinyTexture2DBuilder{ };
	auto* address	 = tiny_cast( tiny_rvalue( builder ), native_pointer );

	Tiny::Memcpy( properties, builder.Properties );

	builder.Columns = m_texture->GetColumns( );
	builder.Rows	= m_texture->GetRows( );

	assets.Export( game, TA_TYPE_TEXTURE_2D, m_asset_name, address );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyToolTexture2D::OnOpen( TinyGame* game, const tiny_string& name, native_pointer asset ) {
	m_texture = tiny_cast( asset, TinyTexture2D* );
	m_image   = TinyImGui::CreateTextureID( m_texture );

	return m_image;
}

void TinyToolTexture2D::OnTick( TinyGame* game, TinyAssetManager& assets ) {
	if ( ImGui::BeginTable( "##TinyToolTexture2D", 2, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_BordersInnerV ) ) {
		ImGui::TableSetupColumn( "Controls", IMGUI_NO_FLAGS, 354.f );
		ImGui::TableSetupColumn( "Image", IMGUI_NO_FLAGS, 512.f );
		ImGui::TableHeadersRow( );

		ImGui::TableNextRow( );
		ImGui::TableNextColumn( );
		
		ImGui::BeginGroup( );
		RenderProperties( game, assets );
		ImGui::EndGroup( );

		ImGui::TableNextColumn( );
		RenderImage( );

		ImGui::EndTable( );
	}
}

void TinyToolTexture2D::OnClose( TinyGame* game, TinyAssetManager& assets ) {
	TinyToolAssetEditor::OnClose( game, assets );

	TinyImGui::DestroyTextureID( m_image );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolTexture2D::RenderProperties( TinyGame* game, TinyAssetManager& assets ) {
	TinyImGui::CollapsingOpen(
		"Sprite Sheet",
		[ & ]( ) {
			TinyImGui::BeginVars( );

			if (
				TinyImGui::InputScalar( "Columns", m_texture->GetEditColumns( ) ) ||
				TinyImGui::InputScalar( "Rows", m_texture->GetEditRows( ) )
			)
				m_texture->ReCalculate( );

			TinyImGui::InputVec2( "UV", m_texture->GetUV( ) );
			TinyImGui::EndVars( );
		}
	);

	auto& properties = m_texture->GetEditProperties( );

	TinyImGui::Collapsing(
		"Properties",
		[ & ]( ) {
			ImGui::BeginDisabled( );

			TinyImGui::BeginVars( );
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
			TinyImGui::EndVars( );

			ImGui::EndDisabled( );
		}
	);

	TinyImGui::Collapsing(
		"Sampler",
		[ & ]( ) {
			auto& sampler = properties.Sampler;

			TinyImGui::BeginVars( );
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
			TinyImGui::EndVars( );
		}
	);

	auto button_size = TinyImGui::ButtonSpanLeft( 2 );

	if ( ImGui::Button( "Save", button_size ) )
		Save( game );

	ImGui::SameLine( );

	if ( ImGui::Button( "Close", button_size ) )
		Close( game );
}

void TinyToolTexture2D::RenderImage( ) {
	auto& properties = m_texture->GetProperties( );
	auto columns	 = m_texture->GetColumns( );
	auto rows		 = m_texture->GetRows( );
	auto height		 = ImGui::GetWindowHeight( );
	auto aspect		 = tiny_min( 512.f / properties.Width, height / properties.Height );
	auto available   = ImVec2{ 512.f, height };
	auto cursor		 = ImGui::GetCursorScreenPos( );
	auto size		 = ImVec2{ properties.Width * aspect, properties.Height * aspect };

	cursor = { 
		cursor.x + ( available.x - size.x ) * .5f,
		cursor.y + ( available.y - size.y ) * .5f
	};

	ImGui::SetCursorScreenPos( cursor );

	TinyImGui::Image( m_image, m_texture, size );
	TinyImGui::Grid( cursor, size, { columns, rows } );
}
