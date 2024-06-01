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
	tiny_uint m_cursor;
	tiny_array<Type, Length> m_data;

public:
	tiny_stack( )
		: m_cursor{ 0 },
		m_data{ }
	{ };

	~tiny_stack( ) = default;

	tiny_stack& push( const Type& element ) {
		if ( m_cursor < Length )
			m_data[ m_cursor++ ] = element;

		return tiny_self;
	};

	std::optional<Type> pop( ) {
		if ( m_cursor > 0 )
			return m_data[ m_cursor-- ];

		return { };
	};

	void clear( ) { m_cursor = 0; };

public:
	template<typename... Args>
	tiny_stack& create( Args&&... args ) {
		auto element = Type{ std::forward<Args>( args )... };

		return push( element );
	};

public:
	tiny_uint size( ) const { return m_cursor; };

	tiny_uint capacity( ) const { return Length; };

	bool is_full( ) const { return m_cursor == Length; };

	Type* data( ) { return m_data.data( ); };

	const Type* data( ) const { return m_data.data( ); };

	auto begin( ) noexcept { return m_data.begin( ); };

	auto end( ) noexcept { return m_data.end( ); };

	const auto begin( ) const noexcept { return m_data.begin( ); };

	const auto end( ) const noexcept { return m_data.end( ); };

};
