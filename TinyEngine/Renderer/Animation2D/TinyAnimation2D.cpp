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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAnimation2D::TinyAnimation2D( )
	: _frames{ }
{ }

void TinyAnimation2D::Add( const TinyAnimation2DFrame& frame ) {
	_frames.emplace_back( frame );
}

void TinyAnimation2D::Add( float duration, tiny_uint row, tiny_uint column ) {
	return Add( { duration, row, column } );
}

void TinyAnimation2D::Insert( tiny_uint frame_id, const TinyAnimation2DFrame& frame ) {
	_frames.insert( frame_id, frame );
}

void TinyAnimation2D::Remove( tiny_uint frame_id ) { _frames.erase( frame_id ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_list<TinyAnimation2DFrame>& TinyAnimation2D::Get( ) { return _frames; }

const tiny_list<TinyAnimation2DFrame>& TinyAnimation2D::Get( ) const { return _frames; }

const TinyAnimation2DFrame& TinyAnimation2D::Peek( tiny_uint& frame_id ) const {
	return _frames[ frame_id ];
}

const TinyAnimation2DFrame& TinyAnimation2D::Next( 
	tiny_uint& frame_id, 
	bool reverse,
	bool& restart
) const {
	auto max_frame = _frames.size( ) - 1;

	if ( !reverse ) {
		frame_id = frame_id < max_frame ? frame_id + 1 : 0;
		restart  = frame_id == 0;
	} else {
		frame_id = frame_id > 0 ? frame_id - 1 : max_frame;
		restart  = frame_id == max_frame;
	}

	return _frames[ frame_id ];
}
