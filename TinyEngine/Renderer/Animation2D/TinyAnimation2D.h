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
 * @creation : 29/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Renderer/Geometries/TinyGeometryManager.h>

te_struct TinyAnimation2DFrame {

	float Duration   = .0f;
	tiny_uint Row	 = 0;
	tiny_uint Column = 0;

};

te_class TinyAnimation2D {

private:
	tiny_list<TinyAnimation2DFrame> _frames;

public:
	TinyAnimation2D( );

	~TinyAnimation2D( ) = default;

	void Add( const TinyAnimation2DFrame& frame );

	tiny_inline void Add( float duration, tiny_uint row, tiny_uint column );

	void Insert( tiny_uint frame_id, const TinyAnimation2DFrame& frame );

	void Remove( tiny_uint frame_id );

public:
	tiny_list<TinyAnimation2DFrame>& Get( );

	const tiny_list<TinyAnimation2DFrame>& Get( ) const;

	const TinyAnimation2DFrame& Peek( tiny_uint& frame_id ) const;

	const TinyAnimation2DFrame& Next( 
		tiny_uint& frame_id, 
		bool reverse,
		bool& restart
	) const;

};
