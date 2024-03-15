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
 * @creation : 16/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Graphics/Pipeline/TinyGraphicPipelineManager.h>

tiny_enum( TinyGraphicShaderOptimizations ) {

	TGS_OPTIMIZATION_NONE = 0,
	TGS_OPTIMIZATION_SIZE,
	TGS_OPTIMIZATION_PERF

};

tm_struct TinyGraphicShaderCompilationContext {

	TinyGraphicShaderOptimizations Optimization;
	tiny_string Name;
	tiny_string Entry;
	tiny_string Source;
	bool IsHLSL;

	TinyGraphicShaderCompilationContext( );

	TinyGraphicShaderCompilationContext( 
		const tiny_string& name,
		const tiny_string& source 
	);

	TinyGraphicShaderCompilationContext( 
		const tiny_string& name,
		const tiny_string& entry,
		const tiny_string& source 
	);

	TinyGraphicShaderCompilationContext(
		TinyGraphicShaderOptimizations optimization,
		const tiny_string& name,
		const tiny_string& entry,
		const tiny_string& source
	);

};
