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
 * @creation : 11/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Filesystem/TinyFilesystem.h>

tm_struct tiny_rect {

	float X;
	float Y;
	float Width;
	float Height;

	tiny_rect( ) 
		: tiny_rect{ 0.f, 0.f, 0.f, 0.f }
	{ };

	tiny_rect( float size )
		: tiny_rect{ 0.f, 0.f, size, size }
	{ };

	tiny_rect( float width, float height ) 
		: tiny_rect{ 0.f, 0.f, width, height }
	{ };

	tiny_rect( float x, float y, float width, float height ) 
		: X{ x },
		Y{ y },
		Width{ width },
		Height{ height }
	{ };

	tiny_rect SetPosition( float size ) {
		return SetPosition( size, size );
	};

	tiny_rect SetPosition( const tiny_vec2& position ) {
		return SetPosition( position.x, position.y );
	};

	tiny_rect SetPosition( float x, float y ) {
		X = x;
		Y = y;

		return tiny_self;
	};

	tiny_vec2 GetPosition( ) const {
		return { X, Y };
	};

	tiny_vec2 GetBoundaries( ) const {
		return { Width, Height };
	};

	tiny_vec4 ToVec4( ) const {
		return { X, Y, Width, Height };
	};

	operator float* ( ) { return &X; };

	operator tiny_vec4 ( ) const { return ToVec4( ); };

	tiny_vec2 operator[]( tiny_uint query_id ) {
		return query_id % 2 == 0 ? GetPosition( ) : GetBoundaries( );
	};

};
