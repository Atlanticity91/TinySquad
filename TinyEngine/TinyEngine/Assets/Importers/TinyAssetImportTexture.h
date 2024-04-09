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

#include "TinyAssetHeader.h"

namespace TinyImport { 

	tiny_dll bool ImportTexture2D( 
		TinyGame* game, 
		TinyFile& file, 
		const TinyPathInformation& path_info
	);

	tiny_dll bool ExportTexture2D(
		TinyGame* game, 
		TinyFile& file,
		const c_pointer builder
	);

	tiny_dll bool ExportCubemap(
		TinyGame* game,
		TinyFile& file,
		const c_pointer builder
	);

	tiny_dll bool ExportAtlas(
		TinyGame* game,
		TinyFile& file,
		const c_pointer builder
	);

	tiny_dll bool ExportLut(
		TinyGame* game,
		TinyFile& file,
		const c_pointer builder
	);

	tiny_dll bool ExportAnimation2D(
		TinyGame* game,
		TinyFile& file,
		const c_pointer builder
	);

};
