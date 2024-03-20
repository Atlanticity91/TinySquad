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
 * @creation : 27/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyArray.h"

template<typename Type, tiny_uint Length>
class tiny_stack { 

public:
	static const tiny_uint Size = Length * tiny_sizeof( Type );

private:
	tiny_uint				 _cursor;
	tiny_array<Type, Length> _data;

public:
	tiny_stack( )
		: _cursor{ 0 },
		_data{ }
	{ };

	~tiny_stack( ) = default;

	tiny_stack& push( const Type& element ) {
		if ( _cursor < Length )
			_data[ _cursor++ ] = element;

		return tiny_self;
	};

	std::optional<Type> pop( ) {
		if ( _cursor > 0 )
			return _data[ _cursor-- ];

		return { };
	};

	void clear( ) { _cursor = 0; };

public:
	template<typename... Args>
	tiny_stack& create( Args&&... args ) {
		auto element = Type{ std::forward<Args>( args )... };

		return push( element );
	};

public:
	tiny_uint size( ) const { return _cursor; };

	tiny_uint capacity( ) const { return Length; };

	bool is_full( ) const { return _cursor == Length; };

	Type* data( ) { return _data.data( ); };

	const Type* data( ) const { return _data.data( ); };

	auto begin( ) noexcept { return _data.begin( ); };

	auto end( ) noexcept { return _data.end( ); };

	const auto begin( ) const noexcept { return _data.begin( ); };

	const auto end( ) const noexcept { return _data.end( ); };

};
