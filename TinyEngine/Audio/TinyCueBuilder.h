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
 * @creation : 04/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Scripts/TinyScriptManager.h>

#define TINY_CUE_RIFF TINY_FOURCC( RIFF )
#define TINY_CUE_WAVE TINY_FOURCC( WAVE )
#define TINY_CUE_XWMA TINY_FOURCC( XWMA )
#define TINY_CUE_JUNK TINY_FOURCC( JUNK )
#define TINY_CUE_DATA TINY_FOURCC( data )
#define TINY_CUE_DPDS TINY_FOURCC( dpds )
#define TINY_CUE_FMT  TINY_FOURCC2( "fmt " )

te_struct TinyRiffChunck {

	tiny_uint RIFF;
	tiny_uint Size;
	tiny_uint Type;

};

te_struct TinyCueContext {

	float FadeIn  = .0f;
	float FadeOut = .0f;

};

te_struct TinyCueBuilder {

	TinyCueFormat Format{ };
	TinyCueContext Context{ };
	tiny_uint Size = 0;
	tiny_ptr Data  = nullptr;

};
