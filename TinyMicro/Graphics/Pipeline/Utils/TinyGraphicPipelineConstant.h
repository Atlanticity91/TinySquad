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
 * @creation : 23/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicPipelineProperties.h"

tm_struct TinyGraphicPipelineConstant {

	VkShaderStageFlags Stage;
	tiny_uint Offset;
	tiny_uint Size;
	c_pointer Value;

	template<typename Type>
	TinyGraphicPipelineConstant( VkShaderStageFlags stage, const Type& data ) 
		: TinyGraphicPipelineConstant{ stage, 0, data }
	{ };

	template<typename Type>
	TinyGraphicPipelineConstant( VkShaderStageFlags stage, tiny_uint offset, const Type& data )
		: Stage{ stage },
		Offset{ offset },
		Size{ tiny_sizeof( Type ) },
		Value{ &data }
	{ };

};
