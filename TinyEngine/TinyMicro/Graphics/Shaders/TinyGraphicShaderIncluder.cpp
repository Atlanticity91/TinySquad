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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicShaderIncluder::TinyGraphicShaderIncluder( )
    : shaderc::CompileOptions::IncluderInterface{ }
{ }

bool TinyGraphicShaderIncluder::Initalize( ) {
    return true;
}

shaderc_include_result* TinyGraphicShaderIncluder::GetInclude(
    native_string requested_source,
    shaderc_include_type type,
    native_string requesting_source,
    size_t include_depth
) {
    printf( "%s - %s\n", requested_source, requesting_source );
    return nullptr;
}

void TinyGraphicShaderIncluder::ReleaseInclude( shaderc_include_result* data ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
