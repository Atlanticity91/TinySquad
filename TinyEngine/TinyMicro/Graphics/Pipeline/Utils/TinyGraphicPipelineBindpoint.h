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
 * @creation : 22/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicPipelineConstant.h"

tiny_enum( TinyGraphicBindpointTypes ) {

	TGB_TYPE_TEXTURE = 0,
	TGB_TYPE_BUFFER,
	TGB_TYPE_UPDATE

};

tm_struct TinyGraphicPipelineBindpoint {

	TinyGraphicBindpointTypes Type;
	tiny_uint Description;
	tiny_uint Set;
	tiny_uint Binding;
	c_pointer Value;

	TinyGraphicPipelineBindpoint( );

	TinyGraphicPipelineBindpoint(
		tiny_uint set,
		tiny_uint binding,
		const TinyGraphicTexture& texture
	);

	TinyGraphicPipelineBindpoint(
		tiny_uint set,
		tiny_uint binding,
		const TinyGraphicBuffer& buffer
	);

	TinyGraphicPipelineBindpoint(
		tiny_uint set,
		tiny_uint binding,
		VkDescriptorType type,
		VkDescriptorBufferInfo* buffer
	);

private:
	TinyGraphicPipelineBindpoint(
		TinyGraphicBindpointTypes type,
		tiny_uint set,
		tiny_uint binding
	);

};
