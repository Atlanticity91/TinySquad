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
 * @creation : 18/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicTextureProperties::TinyGraphicTextureProperties( )
	: Image{ VK_NULL_HANDLE },
	View{ VK_NULL_HANDLE },
	Type{ TGT_TYPE_TEXTURE_2D },
	Format{ VK_FORMAT_R8G8B8A8_UNORM },
	Layout{ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL },
	Width{ 0 },
	Height{ 0 },
	Depth{ 1 },
	Aspect{ VK_IMAGE_ASPECT_COLOR_BIT },
	Levels{ 1 },
	Samples{ VK_SAMPLE_COUNT_1_BIT },
	Tiling{ VK_IMAGE_TILING_OPTIMAL },
	Usage{ TGT_USAGE_TEXTURE },
	Sampler{ }
{ }
