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
 * @creation : 06/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyAssetImportTexture.h"

namespace TinyImport { 

	tiny_dll bool ImportShaderGLSL(
		TinyGame* game,
		TinyFile* file,
		const TinyPathInformation& path_info
	);

	tiny_dll bool ImportShaderHLSL(
		TinyGame* game,
		TinyFile* file,
		const TinyPathInformation& path_info
	);

	tiny_dll bool ExportShader(
		TinyGame* game,
		TinyFile* file,
		const native_pointer builder
	);

	tiny_dll bool ExportMaterial(
		TinyGame* game,
		TinyFile* file,
		const native_pointer builder
	);

};
