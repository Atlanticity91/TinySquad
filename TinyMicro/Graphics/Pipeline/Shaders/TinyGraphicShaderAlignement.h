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
 * @creation : 26/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Graphics/Ressources/TinyGraphicBurner.h>

tm_struct VkVertex2D {

	tiny_vec2 Location;
	tiny_vec2 UV;

};

tm_struct VkVertex3D {

	tiny_vec3 Location;
	tiny_vec2 UV;

};

#define vk_int alignas(4) tiny_int
#define vk_float alignas(4) float
#define vk_vec2 alignas(16) tiny_vec2
#define vk_vec3 alignas(16) tiny_vec3
#define vk_vec4 alignas(16) tiny_vec4
#define vk_mat4 alignas(16) tiny_mat4
