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
 * @creation : 24/11/2023
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
TinyGraphicPipelineBundle::TinyGraphicPipelineBundle( ) 
	: Type{ TGP_TYPE_2D },
	PassType{ TGR_TYPE_RENDER },
	Subpass{ 0 },
	Pass{ VK_NULL_HANDLE },
	Shaders{ },
	InputBinding{ },
	InputAttributes{ },
	Topology{ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP },
	Tessellation{ 3 },
	DepthEnable{ true },
	StencilEnable{ true },
	DepthOperation{ VK_COMPARE_OP_LESS },
	DepthStencilFront{
		VK_STENCIL_OP_REPLACE,
		VK_STENCIL_OP_REPLACE,
		VK_STENCIL_OP_REPLACE,
		VK_COMPARE_OP_ALWAYS,
		0xff,
		0xff,
		1
	},
	DepthStencilBack{
		VK_STENCIL_OP_REPLACE,
		VK_STENCIL_OP_REPLACE,
		VK_STENCIL_OP_REPLACE,
		VK_COMPARE_OP_ALWAYS,
		0xff,
		0xff,
		1
	},
	ColorBlends{ {
		VK_TRUE,
		VK_BLEND_FACTOR_SRC_ALPHA,
		VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		VK_BLEND_OP_ADD,
		VK_BLEND_FACTOR_SRC_ALPHA,
		VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		VK_BLEND_OP_ADD,
		VK_COLOR_COMP_RGBA
	} },
	Dynamics{ {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	} },
	DescriptorCount{ 0 },
	Descriptors{ },
	Constants{ }
{ }
