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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicPipelineDrawcall::TinyGraphicPipelineDrawcall(
	TinyGraphicDrawModes mode, 
	tiny_uint indexes 
)
	: TinyGraphicPipelineDrawcall{ mode, indexes, 1, 0, 0, 0 } 
{ }

TinyGraphicPipelineDrawcall::TinyGraphicPipelineDrawcall( 
	TinyGraphicDrawModes mode,
	tiny_uint indexes, 
	tiny_uint count
)
	: TinyGraphicPipelineDrawcall{ mode, indexes, count, 0, 0, 0 }
{ }

TinyGraphicPipelineDrawcall::TinyGraphicPipelineDrawcall( 
	TinyGraphicDrawModes mode,
	tiny_uint indexes, 
	tiny_uint count, 
	tiny_uint start_vertex,
	tiny_uint start_instance 
)
	: TinyGraphicPipelineDrawcall{ mode, indexes, count, 0, start_vertex, start_instance } 
{ }

TinyGraphicPipelineDrawcall::TinyGraphicPipelineDrawcall( 
	TinyGraphicDrawModes mode, 
	tiny_uint indexes, 
	tiny_uint count, 
	tiny_uint start_index,
	tiny_uint start_vertex,
	tiny_uint start_instance 
)
	: Mode{ mode },
	Indexes{ indexes },
	Count{ count },
	StartIndex{ start_index },
	StartVertex{ start_vertex },
	StartInstance{ start_instance } 
{ }
