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
 * @creation : 22/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicPipelineVertex.h"

tiny_enum( TinyGraphicDrawModes ) {

	TGD_MODE_DIRECT = 0,
	TGD_MODE_INDEXED,

};

tm_struct TinyGraphicPipelineDrawcall {

	TinyGraphicDrawModes Mode;
	tiny_uint Indexes;
	tiny_uint Count;
	tiny_uint StartIndex;
	tiny_uint StartVertex;
	tiny_uint StartInstance;

	TinyGraphicPipelineDrawcall( TinyGraphicDrawModes mode, tiny_uint indexes );

	TinyGraphicPipelineDrawcall(
		TinyGraphicDrawModes mode, 
		tiny_uint indexes, 
		tiny_uint count 
	);

	TinyGraphicPipelineDrawcall(
		TinyGraphicDrawModes mode,
		tiny_uint indexes,
		tiny_uint count,
		tiny_uint start_vertex,
		tiny_uint start_instance 
	);

	TinyGraphicPipelineDrawcall(
		TinyGraphicDrawModes mode,
		tiny_uint indexes,
		tiny_uint count,
		tiny_uint start_index,
		tiny_uint start_vertex, 
		tiny_uint start_instance 
	);

};
