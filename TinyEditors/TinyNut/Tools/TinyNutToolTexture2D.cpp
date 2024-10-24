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
 * @creation : 18/08/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyNut/__tiny_nut_pch.h>

//ImGuiWindowFlags_UnsavedDocument

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNutToolTexture2D::TinyNutToolTexture2D( )
	: TinyNutTool{ "ToolTexture2D" },
	m_texture{ nullptr },
	m_image{ ImTextureNull }
{ }

bool TinyNutToolTexture2D::Open( TinyNut* nut_game, TinyTexture2D& texture ) {
	m_image = TinyImGui::CreateTextureID( m_texture );

	return m_image != ImTextureNull;
}

void TinyNutToolTexture2D::Close( TinyNut* nut_game ) {
	TinyImGui::DestroyTextureID( m_image );
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
