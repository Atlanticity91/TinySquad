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
	tiny_uint Column = 0;
	tiny_uint Row	 = 0;

};

te_class TinyAnimation2D {

public:
	using FrameCollection = tiny_list<TinyAnimation2DFrame>;

private:
	tiny_map<FrameCollection> _collection;

public:
	TinyAnimation2D( );

	~TinyAnimation2D( ) = default;

	TinyAnimation2D& Create( 
		const tiny_string& name,
		tiny_init<TinyAnimation2DFrame> frames 
	);

	TinyAnimation2D& Add( const tiny_string& name, const TinyAnimation2DFrame& frame );

	tiny_inline TinyAnimation2D& Add(
		const tiny_string& name,
		float duration, 
		tiny_uint column,
		tiny_uint row
	);

	TinyAnimation2D& Insert(
		const tiny_string& name, 
		tiny_uint frame_id, 
		const TinyAnimation2DFrame& frame 
	);

	tiny_inline TinyAnimation2D& Insert(
		const tiny_string& name,
		tiny_uint frame_id,
		float duration,
		tiny_uint column,
		tiny_uint row
	);

	TinyAnimation2D& Remove( const tiny_string& name );

	TinyAnimation2D& Remove( const tiny_string& name, tiny_uint frame_id );

public:
	tiny_map<FrameCollection>& GetCollection( );

	void GetAnimations( tiny_list<tiny_string>& list ) const;

	tiny_inline FrameCollection* Get( const tiny_string& animation_name );

	FrameCollection* Get( const tiny_hash animation_hash );

	tiny_inline const FrameCollection* Get( const tiny_string& animation_name ) const;

	const FrameCollection* Get( const tiny_hash animation_hash ) const;

	const TinyAnimation2DFrame* Peek( 
		const tiny_hash animation_hash, 
		tiny_uint& frame_id 
	) const;

	const TinyAnimation2DFrame* Next( 
		const tiny_hash animation_hash,
		tiny_uint& frame_id, 
		bool reverse,
		bool restart
	) const;

};
