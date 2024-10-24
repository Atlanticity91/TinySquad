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
 * @creation : 29/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/States/TinyGameStateManager.h>

namespace TinyImGui {

	tiny_dll ImTextureID CreateTextureID( TinyTexture2D* texture );

	tiny_dll ImTextureID CreateTextureID( TinyTexture2D& texture );

	tiny_dll void Image( 
		ImTextureID& image, 
		const TinyTexture2D* texture,
		const ImVec2& dimensions 
	);

	tiny_dll void Asset( 
		TinyGame* game, 
		const tiny_string& label,
		TinyAssetHandle& asset 
	);

};
