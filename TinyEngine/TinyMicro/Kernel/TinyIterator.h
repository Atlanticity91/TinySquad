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
 * @creation : 10/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Maths/TinyCRC.h"

template<typename Type>
class tiny_iterator final {

public:
	using iterator_category = std::forward_iterator_tag;
	using difference_type	= std::ptrdiff_t;
	using value_type		= Type;
	using pointer			= Type*;
	using reference			= Type&;

private:
	pointer m_data;

public:
	tiny_iterator( pointer data )
		: m_data{ data }
	{ };

	~tiny_iterator( ) = default;

public:
	tiny_iterator& operator++( ) {
		m_data++;

		return tiny_self;
	};

	tiny_iterator operator++( int ) {
		auto tmp = tiny_self;

		m_data++;

		return tmp;
	};

	tiny_iterator& operator--( ) {
		m_data--;

		return tiny_self;
	};

	tiny_iterator operator--( int ) {
		auto tmp = tiny_self;

		m_data++;

		return tmp;
	};

	reference operator*( ) const { return tiny_lvalue( m_data ); };

	pointer operator->( ) { return m_data; };

	bool operator<( const tiny_iterator& other ) {
		return m_data < other.m_data;
	};

	bool operator<=( const tiny_iterator& other ) {
		return m_data <= other.m_data;
	};

	bool operator>( const tiny_iterator& other ) {
		return m_data > other.m_data;
	};

	bool operator>=( const tiny_iterator& other ) {
		return m_data >= other.m_data;
	};

	bool operator==( const tiny_iterator& other ) const {
		return m_data == other.m_data;
	};

	bool operator!=( const tiny_iterator& other ) const {
		return m_data != other.m_data;
	};

};
