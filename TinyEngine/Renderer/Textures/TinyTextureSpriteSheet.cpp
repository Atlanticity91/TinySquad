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
 * @creation : 26/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyTextureSpriteSheet::TinyTextureSpriteSheet( ) 
	: _rows{ 0 },
	_columns{ 0 },
	_uv{ .0f, .0f }
{ }

void TinyTextureSpriteSheet::SetDimensions( tiny_uint rows, tiny_uint columns ) {
	_rows	 = rows;
	_columns = columns;
	_uv.x	 = 1.f / rows;
	_uv.y	 = 1.f / columns;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyTextureSpriteSheet::GetRows( ) const { return _rows; }

tiny_uint TinyTextureSpriteSheet::GetColumns( ) const { return _columns; }

const tiny_vec2& TinyTextureSpriteSheet::GetUV( ) const { return _uv; }

const tiny_vec4 TinyTextureSpriteSheet::GetUV( tiny_uint rows, tiny_uint columns ) const {
	rows	= rows	  < _rows	 ? rows	   : _rows;
	columns = columns < _columns ? columns : _columns;

	return { 
		_uv.x * rows,
		_uv.y * columns,
		_uv.x * rows    + _uv.x,
		_uv.y * columns + _uv.y
	};
}
