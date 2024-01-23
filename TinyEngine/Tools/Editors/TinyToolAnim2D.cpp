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
	_image{ nullptr }
{ }

void TinyToolAnim2D::Save( TinyGame* game ) {
}

void TinyToolAnim2D::Tick( TinyGame* game, TinyAssetManager& assets ) {
	if ( !_asset && _image )
		TinyImGui::DestroyTextureID( _image );

	TinyToolAssetEditor::Tick( game, assets );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyToolAnim2D::OnOpen( TinyGame* game, const tiny_string& name, c_ptr asset ) {
	_image = TinyImGui::CreateTextureID( tiny_cast( asset, TinyTexture2D* ) );

	return _image;
}

void TinyToolAnim2D::OnTick( TinyGame* game, TinyAssetManager& assets ) {
}

void TinyToolAnim2D::OnClose( TinyGame* game, TinyAssetManager& assets ) {
	Save( game );
}
