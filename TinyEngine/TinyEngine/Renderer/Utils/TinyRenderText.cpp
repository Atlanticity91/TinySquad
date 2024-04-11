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
 * @creation : 11/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderTextContext::TinyRenderTextContext( )
	: TinyRenderTextContext{
		{ },
		{ },
		.0f,
		{ }
	}
{ }

TinyRenderTextContext::TinyRenderTextContext(
	const TinyAssetHandle& material,
	const TinyAssetHandle& font, 
	float size,
	const tiny_string& text 
)
	: TinyRenderTextContext{ 
		material,
		font,
		{ },
		size,
		text
	}
{ }

TinyRenderTextContext::TinyRenderTextContext(
	const TinyAssetHandle& material,
	const TinyAssetHandle& font,
	const tiny_color& color,
	float size,
	const tiny_string& text
)
	: Material{ material },
	Font{ font },
	Background{ color },
	Foreground{ },
	Size{ size },
	Spacing{ .0f },
	Location{ },
	Text{ text }
{ }
