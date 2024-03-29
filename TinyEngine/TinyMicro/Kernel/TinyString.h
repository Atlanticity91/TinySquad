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

typedef void c_pointer_base;
typedef c_pointer_base* c_pointer;
typedef tiny_ubyte tiny_pointer_base;
typedef tiny_pointer_base* tiny_pointer;

typedef const char* c_string;

tm_struct tiny_string_view {

	const c_string* Address = nullptr;
	tiny_uint Count   = 0;

};

tm_class tiny_string final {

	using under_layer	 = c_string;
	using iterator		 = tiny_iterator<char>;
	using regex_iterator = std::cregex_iterator;

private:
	under_layer _handle;
	tiny_uint	_length;

public:
	tiny_string( );

	tiny_string( under_layer string );

	tiny_string( const std::string& string );

	tiny_string( const tiny_string& other );

	tiny_string( c_pointer address, tiny_uint length );

	~tiny_string( ) = default;

	tiny_string& asign( under_layer string );

	tiny_string& asign( const std::string& string );

	tiny_string& asign( const tiny_string& other );

public:
	bool is_valid( ) const;

	under_layer get( ) const;

	std::string as_string( ) const;

	char* as_chars( ) const;

	char& at( tiny_uint char_id );

	const char at( tiny_uint char_id ) const;

	std::string make_string( char start, char stop ) const;

	tiny_uint length( ) const;

	bool is_empty( ) const;

	under_layer sub_chars( const tiny_string& sequence, bool cut_after ) const;

	tiny_string sub_string( const tiny_string& sequence, bool cut_after ) const;

	bool equal( under_layer string ) const;

	bool equal( const tiny_string& other ) const;

	bool equal( const std::string& other ) const;

	bool not_equal( under_layer string ) const;

	bool not_equal( const tiny_string& other ) const;

	bool not_equal( const std::string& other ) const;

	iterator begin( );

	iterator end( );

	const iterator begin( ) const;

	const iterator end( ) const;

	regex_iterator begin_regex( const tiny_string& regex ) const;

	regex_iterator end_regex( ) const;

private:
	bool is_valid( under_layer string ) const;

public:
	explicit operator bool ( ) const;

	operator under_layer ( ) const;

	operator std::string ( ) const;

	tiny_string& operator=( under_layer string );

	tiny_string& operator=( const std::string string );

	tiny_string& operator=( const tiny_string& other );

	bool operator==( under_layer string ) const;

	bool operator==( const tiny_string& other ) const;

	bool operator==( const std::string& other ) const;

	bool operator!=( under_layer string ) const;

	bool operator!=( const tiny_string& other ) const;

	bool operator!=( const std::string& other ) const;

	char& operator[]( tiny_uint char_id );

	const char operator[]( tiny_uint char_id ) const;

};
