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
 * @creation : 21/10/2023
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyColor.h"

#define TINY_COLOR( NAME, R, G, B, A )\
	static const tiny_color NAME = tiny_color{ R, G, B, A }

namespace TinyPalettes { 

	TINY_COLOR( WHITE, 256, 256, 256, 1.f );
	TINY_COLOR( BLACK,   0,   0,   0, 1.f );
	TINY_COLOR( RED,   256,   0,   0, 1.f );
	TINY_COLOR( GREEN,   0, 256,   0, 1.f );
	TINY_COLOR( BLUE,    0,   0, 256, 1.f );

	// === FLAT COLOR V1 PALETTE ===
	
	TINY_COLOR( TURQUOISE,		 26, 188, 156, 1.f );
	TINY_COLOR( GREEN_SEA,		 22, 160, 133, 1.f );
	TINY_COLOR( SUN_FLOWER,	241, 196,  15, 1.f );
	TINY_COLOR( ORANGE,		243, 156,  18, 1.f );
	TINY_COLOR( EMERALD,		 46, 204, 113, 1.f );
	TINY_COLOR( NEPHRITIS,		 39, 174,  96, 1.f );
	TINY_COLOR( CARROT,		230, 126,  34, 1.f );
	TINY_COLOR( PUMPKIN,		211,  84,   0, 1.f );
	TINY_COLOR( PETER_RIVER,    52, 152, 219, 1.f );
	TINY_COLOR( BELIZE_HOLE,	 41, 128, 185, 1.f );
	TINY_COLOR( ALIZARIN,		231,  76,  60, 1.f );
	TINY_COLOR( POMEGRANATE,	192,  57,  43, 1.f );
	TINY_COLOR( AMETHYST,		155,  89, 182, 1.f );
	TINY_COLOR( WISTERIA,		142,  68, 173, 1.f );
	TINY_COLOR( CLOUDS,		236, 240, 241, 1.f );
	TINY_COLOR( SILVER,		189, 195, 199, 1.f );
	TINY_COLOR( WET_ASPHALT,	 52,  73,  94, 1.f );
	TINY_COLOR( MIDNIGHT_BLUE,  44,  62,  80, 1.f );
	TINY_COLOR( CONCRETE,		149, 165, 166, 1.f );
	TINY_COLOR( ASBESTOS,		127, 140, 141, 1.f );

	// === DEFAULT PALETTE ===

};
