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
	: TinyToolAssetEditor{ "Animation 2D" },
	_animation{ nullptr },
	_texture{ nullptr },
	_image{ nullptr }
{ }

void TinyToolAnim2D::Save( TinyGame* game ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyToolAnim2D::OnOpen( TinyGame* game, const tiny_string& name, c_pointer asset ) {
	_animation = tiny_cast( asset, TinyAnimation2D* );

	if ( false ) {
		auto& assets = game->GetAssets( );

		SetTexture( assets );
	}

	return _animation;
}

void TinyToolAnim2D::OnTick( TinyGame* game, TinyAssetManager& assets ) {
	auto* animation = _animation->Get( "" );
	auto& frame = tiny_lvalue( animation->get( 0 ) );

	auto uv = _texture->GetUV( frame.Column, frame.Row );

	ImGui::Image( _image, {}, { uv.x, uv.y }, { uv.z, uv.w } );
}

void TinyToolAnim2D::OnClose( TinyGame* game, TinyAssetManager& assets ) {
	TinyToolAssetEditor::OnClose( game, assets );

	TinyImGui::DestroyTextureID( _image );
}

void TinyToolAnim2D::SetTexture( TinyAssetManager& assets ) {
	if ( _image )
		TinyImGui::DestroyTextureID( _image );

	auto asset = TinyAsset{ TA_TYPE_TEXTURE_2D, "" };

	_texture = assets.GetAssetAs<TinyTexture2D>( asset );
	_image   = TinyImGui::CreateTextureID( _texture );
}
