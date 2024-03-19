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

te_class TinyFontManager final 
	: tiny_inherit( TinyAssetList<TA_TYPE_FONT, TinyFont> )
{

public:
	TinyFontManager( );

	~TinyFontManager( ) = default;

protected:
	tiny_implement( bool OnLoad( TinyGame* game, TinyFile& file, TinyFont& font ) );

	tiny_implement( void OnUnLoad( TinyGame* game, TinyFont& font ) );

	tiny_implement( bool OnCreate( TinyGame* game, c_pointer asset_builder, TinyFont& font ) );

};
