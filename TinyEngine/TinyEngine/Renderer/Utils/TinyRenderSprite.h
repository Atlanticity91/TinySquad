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
 * @creation : 19/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderCore.h"

te_struct TinyRenderTransform {

	tiny_mat4 World{ };
	//tiny_mat4 Local{ };

};

te_struct TinyRenderSprite {

	tiny_vec4 UV{ };
	tiny_vec4 Color{ };

};

te_struct TinyRenderSpriteContext {

	TinyAsset Material{ };
	tiny_list<TinyTexture2D*> Textures{ };
	TinyRenderSprite Sprite{ };
	TinyRenderTransform Tranform{ };

};
