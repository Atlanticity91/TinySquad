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

#include "TinyIterator.h"

typedef const char* native_string;

tm_struct tiny_string_view {

	const native_string* Address = nullptr;
	tiny_uint Count				 = 0;

};

tm_class tiny_string final {

	using iterator		 = tiny_iterator<char>;
	using regex_iterator = std::cregex_iterator;

private:
	char* m_handle;
	tiny_uint m_length;

public:
	tiny_string( );

	tiny_string( native_string string );

	tiny_string( const tiny_string& other );

	explicit tiny_string( const std::string& string );

	tiny_string( const tiny_uint length, const native_pointer data );

	~tiny_string( ) = default;

	tiny_string& asign( native_string string );

	tiny_string& asign( const tiny_string& other );

	tiny_string& asign( const std::string& string );

	tiny_string& asign( const tiny_uint length, const native_pointer data );

public:
	bool get_is_valid( ) const;

	bool get_is_empty( ) const;

	tiny_uint length( ) const;

	char* get( ) const;

	char* last( ) const;

	native_string as_string( ) const;

	native_pointer as_native( );

	const native_pointer as_native( ) const;

	std::string to_string( ) const;

	char& at( const tiny_uint char_id );

	const char at( const tiny_uint char_id ) const;

	std::string make_string( char start, char stop ) const;

	native_string sub_chars( const tiny_string& sequence, bool cut_after ) const;

	tiny_string sub_string( const tiny_string& sequence, bool cut_after ) const;

	tiny_string sub_string( const tiny_uint offset ) const;

	bool equal( native_string string ) const;

	bool equal( const tiny_string& other ) const;

	bool equal( const std::string& other ) const;

	bool not_equal( native_string string ) const;

	bool not_equal( const tiny_string& other ) const;

	bool not_equal( const std::string& other ) const;

	iterator begin( );

	iterator end( );

	const iterator begin( ) const;

	const iterator end( ) const;

	regex_iterator begin_regex( const tiny_string& regex ) const;

	regex_iterator end_regex( ) const;

private:
	bool get_is_valid( native_string string ) const;

public:
	explicit operator bool ( ) const;

	operator native_string ( ) const;

	operator std::string ( ) const;

	tiny_string& operator=( native_string string );

	tiny_string& operator=( const tiny_string& other );

	tiny_string& operator=( const std::string& string );

	bool operator==( native_string string ) const;

	bool operator==( const tiny_string& other ) const;

	bool operator==( const std::string& other ) const;

	bool operator!=( native_string string ) const;

	bool operator!=( const tiny_string& other ) const;

	bool operator!=( const std::string& other ) const;

	char& operator[]( tiny_uint char_id );

	const char operator[]( tiny_uint char_id ) const;

};
