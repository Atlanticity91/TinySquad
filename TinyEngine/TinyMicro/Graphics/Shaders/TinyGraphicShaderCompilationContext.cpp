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
 * @creation : 14/03/2024
 * @version  : 2024.2.6
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicShaderCompilationContext::TinyGraphicShaderCompilationContext( )
	: TinyGraphicShaderCompilationContext{ TGS_OPTIMIZATION_PERF, "", "main", "" }
{ }

TinyGraphicShaderCompilationContext::TinyGraphicShaderCompilationContext(
	const tiny_string& name,
	const tiny_string& source
)
	: TinyGraphicShaderCompilationContext{ TGS_OPTIMIZATION_PERF, name, "main", source }
{ }

TinyGraphicShaderCompilationContext::TinyGraphicShaderCompilationContext(
	const tiny_string& name,
	const tiny_string& entry,
	const tiny_string& source
)
	: TinyGraphicShaderCompilationContext{ TGS_OPTIMIZATION_PERF, name, entry, source }
{ }

TinyGraphicShaderCompilationContext::TinyGraphicShaderCompilationContext(
	TinyGraphicShaderOptimizations optimization,
	const tiny_string& name,
	const tiny_string& entry,
	const tiny_string& source
)
	: Optimization{ optimization },
	Name{ name },
	Entry{ entry },
	Source{ source },
	IsHLSL{ false }
{ }
