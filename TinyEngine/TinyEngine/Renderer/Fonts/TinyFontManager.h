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
 * @creation : 24/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyFont.h"

te_class TinyFontManager final : tiny_inherit( TinyAssetContainer<TinyFont> ) {

public:
	TinyFontManager( );

	~TinyFontManager( ) = default;

	tiny_implement( bool Create(
		TinyGame* game,
		const tiny_string& alias,
		const c_pointer builder
	) );

	tiny_implement( bool Load(
		TinyGame* game,
		const tiny_string& alias,
		TinyFile& file
	) );

};
