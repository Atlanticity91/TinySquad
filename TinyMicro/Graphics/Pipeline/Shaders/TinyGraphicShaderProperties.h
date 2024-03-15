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
 * @creation : 26/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicShaderAlignement.h"

tiny_enum( TinyGraphicShaderTypes ) {

	TGS_TYPE_VERTEX = 0,
	TGS_TYPE_FRAGMENT,
	TGS_TYPE_GEOMETRY,
	TGS_TYPE_COMPUTE

};

tm_struct TinyGraphicShaderProperties {

	TinyGraphicShaderTypes Type = TGS_TYPE_VERTEX;
	std::string Entry			= "";
	tiny_list<tiny_uint> Code{ };

};
