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
 * @creation : 23/01/2024
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
TinyToolAnim2D::TinyToolAnim2D( )
	: TinyToolAssetEditor{ "Animation 2D", { 908.f, 512.f } },
	_collection{ nullptr },
	_texture{ nullptr },
	_image{ nullptr },
	_animation{ },
	_frame_id{ 0 }
{ }

void TinyToolAnim2D::Save( TinyGame* game ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyToolAnim2D::OnOpen( TinyGame* game, const tiny_string& name, native_pointer asset ) {
	_collection = tiny_cast( asset, TinyAnimation2D* );

	if ( false ) {
		auto& assets = game->GetAssets( );

		SetTexture( assets );
	}

	return _collection;
}

void TinyToolAnim2D::OnTick( TinyGame* game, TinyAssetManager& assets ) {
	if ( ImGui::BeginTable( "##TinyToolAnim2D", 2, ImGuiTableFlags_BordersInnerV ) ) {
		ImGui::TableNextRow( );
		ImGui::TableNextColumn( );

		ImGui::BeginGroup( );
		DrawNames();
		ImGui::EndGroup( );

		ImGui::TableNextColumn( );
		DrawPlayer( );

		ImGui::EndTable( );
	}
}

void TinyToolAnim2D::OnClose( TinyGame* game, TinyAssetManager& assets ) {
	TinyToolAssetEditor::OnClose( game, assets );

	TinyImGui::DestroyTextureID( _image );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolAnim2D::SetTexture( TinyAssetManager& assets ) {
	if ( _image )
		TinyImGui::DestroyTextureID( _image );

	auto asset = TinyAssetHandle{ TA_TYPE_TEXTURE_2D };

	_texture = assets.GetAssetAs<TinyTexture2D>( asset );
	_image   = TinyImGui::CreateTextureID( _texture );
}

void TinyToolAnim2D::DrawNames( ) {
	auto& collection = _collection->GetCollection( );

	for ( auto& animation : collection ) {
		if ( animation.Hash != _animation )
			ImGui::Text( animation.Alias.c_str( ) );
		else
			ImGui::Text( "# %s", animation.Alias.c_str( ) );
	}

	//ImGui::InputText( "Animation Name" )
	//ImGui::SameLine( );

	if ( ImGui::Button( "Add", { -1.f, .0f } ) ) { 
	}
}

void TinyToolAnim2D::DrawPlayer( ) {
	auto* animation = _collection->Get( _animation );

	if ( animation ) {
		auto& frame = tiny_lvalue( animation->get( _frame_id ) );

		//auto aspect = tiny_min( 512.f / properties.Width, 512.f / properties.Height );
		//auto size   = ImVec2{ properties.Width * aspect, properties.Height * aspect };
		//auto uv	  = _texture->GetUV( frame.Column, frame.Row );

		//ImGui::Image( _image, size, { uv.x, uv.y }, { uv.z, uv.w } );

		ImGui::Separator( );

		//TF_ICON_PLAY | TF_ICON_PAUSE
		if ( ImGui::Button( "" ) ) {
		}

		// DRAW FRAMES
		auto button_id = tiny_cast( 0, tiny_uint );
		// TF_ICON_PLUS_CIRCLE | TF_ICON_MINUS_CIRCLE
		if ( ImGui::Button( "" ) ) {
			_frame_id = button_id;
		}

		if ( ImGui::Button( "" ) ) {
		}

		ImGui::Separator( );

		TinyImGui::BeginVars( );

		TinyImGui::InputScalar( "Duration", frame.Duration );
		TinyImGui::InputScalar( "Column", frame.Column );
		TinyImGui::InputScalar( "Row", frame.Row );

		TinyImGui::EndVars( );
	}
}
