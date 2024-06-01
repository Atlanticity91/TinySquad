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
	: TinyAsset{ TA_TYPE_ANIMATION_2D },
	m_collection{ }
{ }

TinyAnimation2D& TinyAnimation2D::Create(
	const tiny_string& name,
	tiny_init<TinyAnimation2DFrame> frames
) {
	if ( !m_collection.find( name ) )
		m_collection.emplace( name, frames );

	return tiny_self;
}

TinyAnimation2D& TinyAnimation2D::Add(
	const tiny_string& name,
	const TinyAnimation2DFrame& frame
) {
	if ( !m_collection.find( name ) )
		m_collection.emplace( name, { } );

	m_collection[ name ].emplace_back( frame );

	return tiny_self;
}

TinyAnimation2D& TinyAnimation2D::Add(
	const tiny_string& name,
	float duration,
	tiny_uint column,
	tiny_uint row
) {
	auto frame = TinyAnimation2DFrame{ duration, column, row };

	return Add( name, frame );
}

TinyAnimation2D& TinyAnimation2D::Insert(
	const tiny_string& name,
	tiny_uint frame_id,
	const TinyAnimation2DFrame& frame
) {
	auto animation_id = tiny_cast( 0, tiny_uint );

	if ( m_collection.find( name, animation_id ) ) {
		auto& animation = m_collection.at( animation_id );

		animation.insert( frame_id, frame );
	}

	return tiny_self;
}

TinyAnimation2D& TinyAnimation2D::Insert(
	const tiny_string& name,
	tiny_uint frame_id,
	float duration,
	tiny_uint column,
	tiny_uint row
) {
	auto frame = TinyAnimation2DFrame{ duration, column, row };

	return Insert( name, frame_id, frame );
}

TinyAnimation2D& TinyAnimation2D::Remove( const tiny_string& name ) {
	m_collection.erase( name );

	return tiny_self;
}

TinyAnimation2D& TinyAnimation2D::Remove( const tiny_string& name, tiny_uint frame_id ) {
	auto animation_id = tiny_cast( 0, tiny_uint );

	if ( m_collection.find( name, animation_id ) ) {
		auto& animation = m_collection.at( animation_id );
		
		animation.erase( frame_id );
	}

	return tiny_self;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_map<TinyAnimation2D::FrameCollection>& TinyAnimation2D::GetCollection( ) {
	return m_collection;
}

void TinyAnimation2D::GetAnimations( tiny_list<tiny_string>& list ) const {
	for ( auto& node : m_collection ) {
		auto node_str = tiny_string{ node.Alias };

		list.emplace_back( node_str );
	}
}

TinyAnimation2D::FrameCollection* TinyAnimation2D::Get(
	const tiny_string& animation_name
) {
	auto animation_hash = tiny_hash{ animation_name };

	return Get( animation_hash );
}

TinyAnimation2D::FrameCollection* TinyAnimation2D::Get(
	const tiny_hash animation_hash
) {
	auto animation_id = tiny_cast( 0, tiny_uint );
	auto* animation   = tiny_cast( nullptr, FrameCollection* );

	if ( m_collection.find( animation_hash, animation_id ) )
		animation = tiny_rvalue( m_collection.at( animation_id ) );

	return animation;
}

const TinyAnimation2D::FrameCollection* TinyAnimation2D::Get( 
	const tiny_string& animation_name
) const {
	auto animation_hash = tiny_hash{ animation_name };

	return Get( animation_hash );
}

const TinyAnimation2D::FrameCollection* TinyAnimation2D::Get(
	const tiny_hash animation_hash 
) const {
	auto animation_id = tiny_cast( 0, tiny_uint );
	auto* animation   = tiny_cast( nullptr, const FrameCollection* );

	if ( m_collection.find( animation_hash, animation_id ) )
		animation = tiny_rvalue( m_collection.at( animation_id ) );

	return animation;
}

const TinyAnimation2DFrame* TinyAnimation2D::Peek(
	const tiny_hash animation_hash,
	tiny_uint& frame_id
) const {
	auto* animation_frame = tiny_cast( nullptr, const TinyAnimation2DFrame* );
	auto* animation = Get( animation_hash );

	if ( animation )
		animation_frame = animation->get( frame_id );

	return animation_frame;
}

const TinyAnimation2DFrame* TinyAnimation2D::Next(
	const tiny_hash animation_hash,
	tiny_uint& frame_id,
	bool reverse,
	bool restart
) const {
	auto* animation_frame = tiny_cast( nullptr, const TinyAnimation2DFrame* );
	auto* animation		  = Get( animation_hash );

	if ( animation ) {
		auto max_frame = animation->size( ) - 1;

		if ( !reverse ) {
			if ( frame_id < max_frame )
				frame_id += 1;
			else
				frame_id = restart ? 0 : max_frame;
		} else {
			if ( frame_id > 0 )
				frame_id -= 1;
			else
				frame_id = restart ? max_frame : 0;
		}

		animation_frame = animation->get( frame_id );
	}

	return animation_frame;
}
