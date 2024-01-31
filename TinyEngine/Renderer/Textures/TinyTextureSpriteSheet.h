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

#pragma once

#include <TinyEngine/Renderer/Utils/TinyRenderBuffer.h>

te_class TinyTextureSpriteSheet {

protected:
	tiny_uint _rows;
	tiny_uint _columns;
	tiny_vec2 _uv;

public:
	TinyTextureSpriteSheet( );

	virtual ~TinyTextureSpriteSheet( ) = default;
	
	void SetDimensions( tiny_uint rows, tiny_uint columns );

public:
	tiny_uint GetRows( ) const;

	tiny_uint GetColumns( ) const;
	
	const tiny_vec2& GetUV( ) const;

	const tiny_vec4 GetUV( const tiny_upoint& sprite ) const;

	const tiny_vec4 GetUV( tiny_uint columns, tiny_uint rows ) const;

	tiny_uint& GetEditColumns( );

	tiny_uint& GetEditRows( );

};
