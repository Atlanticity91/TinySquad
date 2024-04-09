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
	: TinyAsset{ TA_TYPE_TEXTURE_2D },
	_columns{ 0 }, 
	_rows{ 0 },
	_uv{ .0f, .0f }
{ }

void TinyTextureSpriteSheet::SetDimensions( tiny_uint columns, tiny_uint rows ) {
	_columns = columns;
	_rows	 = rows;
	
	ReCalculate( );
}

void TinyTextureSpriteSheet::ReCalculate( ) {
	_uv.x = 1.f / _columns;
	_uv.y = 1.f / _rows;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyTextureSpriteSheet::GetRows( ) const { return _rows; }

tiny_uint TinyTextureSpriteSheet::GetColumns( ) const { return _columns; }

const tiny_vec2& TinyTextureSpriteSheet::GetUV( ) const { return _uv; }

const tiny_vec4 TinyTextureSpriteSheet::GetUV( const tiny_upoint& sprite ) const {
	return GetUV( sprite.x, sprite.y );
}

const tiny_vec4 TinyTextureSpriteSheet::GetUV( tiny_uint columns, tiny_uint rows ) const {
	columns = columns < _columns ? columns : _columns;
	rows	= rows	  < _rows	 ? rows	   : _rows;

	return { 
		_uv.x * columns,
		_uv.y * rows,
		_uv.x * columns + _uv.x,
		_uv.y * rows	+ _uv.y
	};
}

tiny_uint& TinyTextureSpriteSheet::GetEditColumns( ) { return _columns; }

tiny_uint& TinyTextureSpriteSheet::GetEditRows( ) { return _rows; }
