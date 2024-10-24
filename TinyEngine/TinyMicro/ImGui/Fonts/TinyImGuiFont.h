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
 * @creation : 29/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Embeded/TinyImGuiFontIcons.h"

tm_struct TinyImGuiFont {

	tiny_string Alias = "";
	tiny_string Path  = "";
	float Size		  = 16.f;

};

tm_struct TinyImGuiFontEmbedded {

	tiny_uint Length  = 0;
	tiny_uint* Glyphs = nullptr;
	tiny_ushort Min   = 0;
	tiny_ushort Max   = 0;

};
