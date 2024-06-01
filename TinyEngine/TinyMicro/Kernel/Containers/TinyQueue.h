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
 * @creation : 29/05/2023
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyMap.h"

template<typename Type, tiny_uint Length>
	requires ( Length > 0 )
class tiny_queue {

private:
	tiny_uint m_head;
	tiny_uint m_tail;
	tiny_uint m_size;
	Type m_data[ Length ];

public:
	tiny_queue( )
		: m_head{ 0 },
		m_tail{ 0 },
		m_size{ 0 },
		m_data{ }
	{ };

	~tiny_queue( ) = default;

	tiny_queue& enqueue( const Type& element ) {
		if ( m_size < Length ) {
			m_size += 1;
			
			m_data[ m_tail ] = std::move( element );
			
			m_tail = ( m_tail + 1 ) % Length;
		}

		return tiny_self;
	};

	std::optional<Type> dequeue( ) {
		if ( m_size > 0 ) {
			m_size -= 1;

			auto old_head = m_head;

			m_head = ( m_head + 1 ) % Length;

			return std::move( m_data[ old_head ] );
		}

		return { };
	};

public:
	bool get_is_empty( ) const { return m_size == 0; }

	bool get_is_full( ) const { return m_size == Length; };

	tiny_uint length( ) const { return Length; };

	tiny_uint size( ) const { return m_size; };

	const Type* peek( ) const {
		auto* element = tiny_cast( nullptr, const Type* );

		if ( m_size > 0 )
			element = m_data + m_head;

		return element;
	};

};
