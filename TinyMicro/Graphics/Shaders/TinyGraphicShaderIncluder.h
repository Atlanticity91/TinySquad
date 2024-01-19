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

#include "TinyGraphicShaderCompilationContext.h"

tm_class TinyGraphicShaderIncluder final 
	: tiny_inherit( shaderc::CompileOptions::IncluderInterface ) 
{

public:
	TinyGraphicShaderIncluder( );

	~TinyGraphicShaderIncluder( ) = default;

	bool Initalize( );

    tiny_implement( shaderc_include_result* GetInclude( 
        c_str requested_source,
        shaderc_include_type type,
        c_str requesting_source,
        size_t include_depth 
    ) );

    tiny_implement( void ReleaseInclude( shaderc_include_result* data ) );

};
