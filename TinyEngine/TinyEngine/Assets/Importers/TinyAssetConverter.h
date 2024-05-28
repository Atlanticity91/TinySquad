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
 * @creation : 09/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyAssetImportFont.h"

te_struct TinyAssetConverter {

	using Import_t = std::function<bool( TinyGame*, TinyFile*, const TinyPathInformation& )>;
	using Export_t = std::function<bool( TinyGame*, TinyFile*, const native_pointer )>;

	Import_t Import;
	Export_t Export;

	TinyAssetConverter( Import_t import_ );

	TinyAssetConverter( Export_t export_ );

	TinyAssetConverter( Import_t import_, Export_t export_ );

};
