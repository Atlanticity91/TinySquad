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
	tiny_uint _head;
	tiny_uint _tail;
	tiny_uint _size;
	Type _data[ Length ];

public:
	tiny_queue( )
		: _head{ 0 },
		_tail{ 0 },
		_size{ 0 },
		_data{ }
	{ };

	~tiny_queue( ) = default;

	tiny_queue& enqueue( const Type& element ) {
		if ( _size < Length ) {
			_size += 1;
			
			_data[ _tail ] = std::move( element );

			 _tail = ( _tail + 1 ) % Length;
		}

		return tiny_self;
	};

	std::optional<Type> dequeue( ) {
		if ( _size > 0 ) {
			_size -= 1;

			auto old_head = _head;

			_head = ( _head + 1 ) % Length;

			return std::move( _data[ old_head ] );
		}

		return { };
	};

public:
	bool get_is_empty( ) const { return _size == 0; }

	bool get_is_full( ) const { return _size == Length; };

	tiny_uint length( ) const { return Length; };

	tiny_uint size( ) const { return _size; };

	const Type* peek( ) const {
		auto* element = tiny_cast( nullptr, const Type* );

		if ( _size > 0 )
			element = _data + _head;

		return element;
	};

};
