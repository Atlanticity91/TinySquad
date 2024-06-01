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
	: m_columns{ 0 }, 
	m_rows{ 0 },
	m_uv{ .0f, .0f }
{ }

void TinyTextureSpriteSheet::SetDimensions( tiny_uint columns, tiny_uint rows ) {
	m_columns = columns;
	m_rows	 = rows;
	
	ReCalculate( );
}

void TinyTextureSpriteSheet::ReCalculate( ) {
	m_uv.x = 1.f / m_columns;
	m_uv.y = 1.f / m_rows;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyTextureSpriteSheet::GetRows( ) const { return m_rows; }

tiny_uint TinyTextureSpriteSheet::GetColumns( ) const { return m_columns; }

const tiny_vec2& TinyTextureSpriteSheet::GetUV( ) const { return m_uv; }

const tiny_vec4 TinyTextureSpriteSheet::GetUV( const tiny_upoint& sprite ) const {
	return GetUV( sprite.x, sprite.y );
}

const tiny_vec4 TinyTextureSpriteSheet::GetUV( tiny_uint columns, tiny_uint rows ) const {
	columns = columns < m_columns ? columns : m_columns;
	rows	= rows	  < m_rows	  ? rows	   : m_rows;

	return { 
		m_uv.x * columns,
		m_uv.y * rows,
		m_uv.x * columns + m_uv.x,
		m_uv.y * rows	 + m_uv.y
	};
}

tiny_uint& TinyTextureSpriteSheet::GetEditColumns( ) { return m_columns; }

tiny_uint& TinyTextureSpriteSheet::GetEditRows( ) { return m_rows; }
