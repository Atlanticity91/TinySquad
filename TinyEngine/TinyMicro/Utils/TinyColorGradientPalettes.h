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
 * @creation : 31/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyColorGradient.h"

#define TINY_COLOR_GRADIENT( NAME, ... )\
	static const tiny_color_gradient NAME = tiny_color_gradient{ __VA_ARGS__ }

namespace TinyColorGradientPalettes {

	// === GRADIENT FROM https://iquilezles.org/articles/palettes/ ===
	TINY_COLOR_GRADIENT( IQUILEZLES_00,
		{  .5f,  .5f,   .5f,  1.f },
		{  .5f,  .5f,   .5f,  1.f },
		{ 1.f,  1.f,   1.f,   1.f },
		{  .0f,  .33f,  .67f, 1.f }
	);

	TINY_COLOR_GRADIENT( IQUILEZLES_01,
		{  .5f,  .5f,   .5f,  1.f },
		{  .5f,  .5f,   .5f,  1.f },
		{ 1.f,  1.f,   1.f,   1.f },
		{  .0f,  .1f,   .2f,  1.f }
	);

	TINY_COLOR_GRADIENT( IQUILEZLES_02,
		{  .5f,  .5f,   .5f,  1.f },
		{  .5f,  .5f,   .5f,  1.f },
		{ 1.f,  1.f,   1.f,   1.f },
		{  .3f,  .2f,   .2f,  1.f }
	);

	TINY_COLOR_GRADIENT( IQUILEZLES_03,
		{  .5f,  .5f,   .5f,  1.f },
		{  .5f,  .5f,   .5f,  1.f },
		{ 1.f,  1.f,   1.f,   1.f },
		{  .8f,  .9f,   .2f,  1.f }
	);

};
