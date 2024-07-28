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
 * @creation : 26/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Graphics/Pipeline/Utils/TinyGraphicPipelineDrawcall.h>

#define TINY_VULKAN_PIPELINE_CACHE "TPC"

tm_struct TinyGraphicPipelineCacheHeader{

	char Magic[ 4 ]  = TINY_VULKAN_PIPELINE_CACHE;
	tiny_uint CRC	 = 0;
	tiny_uint Vendor = 0;
	tiny_uint Device = 0;
	tiny_ulong Size  = 0;

};
