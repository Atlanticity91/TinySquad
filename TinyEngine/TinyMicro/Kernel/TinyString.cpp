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
 * @creation : 16/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_string::tiny_string( )
	: _handle( "" ),
	_length{ 0 }
{ }

tiny_string::tiny_string( under_layer string )
	: tiny_string{ }
{ 
	asign( string );
}

tiny_string::tiny_string( const std::string& string )
	: tiny_string{ } 
{
	asign( string );
}

tiny_string::tiny_string( const tiny_string& other )
	: tiny_string{ }
{
	asign( other );
}

tiny_string::tiny_string( tiny_uint length, c_pointer address )
	: _handle{ tiny_cast( address, under_layer ) },
	_length{ length }
{ }

tiny_string& tiny_string::asign( under_layer string ) {
	if ( string ) {
		_length = tiny_cast( strlen( string ), tiny_uint );

		if ( _length > 0 )
			_handle = string;
	} else {
		_handle = nullptr;
		_length = 0;
	}

	return tiny_self;
}

tiny_string& tiny_string::asign( const std::string& string ) {
	_handle = string.c_str( );
	_length = tiny_cast( string.length( ), tiny_uint );

	return tiny_self;
}

tiny_string& tiny_string::asign( const tiny_string& other ) {
	_handle = other.get( );
	_length = other.length( );

	return tiny_self;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool tiny_string::is_valid( ) const { return _handle && _length > 0; }

tiny_string::under_layer tiny_string::get( ) const { return _handle; }

char* tiny_string::as_chars( ) const { return tiny_cast( _handle, char* ); }

std::string tiny_string::as_string( ) const { return std::string{ _handle }; }

char& tiny_string::at( tiny_uint char_id ) {
	char_id = char_id < _length ? char_id : _length + 1;

	return tiny_lvalue( tiny_cast( tiny_rvalue( _handle[ char_id ] ), char* ) );
}

const char tiny_string::at( tiny_uint char_id ) const {
	if ( char_id < length( ) )
		return _handle[ char_id ];

	return '\0';
}

std::string tiny_string::make_string( char start, char stop ) const {
	auto string	   = std::string{ _handle };
	auto str_start = string.find_last_of( start )+1;
	auto str_stop  = string.find_last_of( stop );

	return string.substr( str_start, str_stop - str_start );
}

tiny_uint tiny_string::length( ) const { return _length; }

bool tiny_string::is_empty( ) const { return _handle && length( ) == 0; }

tiny_string::under_layer tiny_string::sub_chars( 
	const tiny_string& sequence, 
	bool cut_after
) const {
	auto* sub = tiny_cast( nullptr, under_layer );

	if ( is_valid( ) && sequence.is_valid( ) ) {
		sub = strstr( _handle, sequence.as_chars( ) );

		if ( sub && cut_after )
			sub += sequence.length( );
	}

	return sub;
}

tiny_string tiny_string::sub_string( const tiny_string& sequence, bool cut_after ) const {
	auto sub = tiny_string{ };

	if ( is_valid( ) && sequence.is_valid( ) ) {
		auto* tmp = strstr( _handle, sequence.as_chars( ) );

		if ( tmp && cut_after )
			tmp += sequence.length( );

		sub = tmp;
	}

	return sub;
}

tiny_string tiny_string::sub_string( const tiny_uint offset ) const {
	auto sub = tiny_string{ };

	if ( offset < _length )
		sub.asign( _handle + offset );

	return sub;
}

bool tiny_string::equal( under_layer string ) const {
	auto state = is_valid( string ) && length( ) > 0;

	if ( state )
		state = strcmp( string, _handle ) == 0;

	return state;
}

bool tiny_string::equal( const tiny_string& other ) const {
	auto string = other.get( );

	return equal( string );
}

bool tiny_string::equal( const std::string& other ) const {
	auto string = other.c_str( );

	return equal( string );
}

bool tiny_string::not_equal( under_layer string ) const {
	return !equal( string );
}

bool tiny_string::not_equal( const tiny_string& other ) const {
	return !equal( other );
}

bool tiny_string::not_equal( const std::string& other ) const {
	return !equal( other );
}

tiny_string::iterator tiny_string::begin( ) { return { as_chars( ) }; }

tiny_string::iterator tiny_string::end( ) { return { as_chars( ) + ( _length + 1 ) }; }

const tiny_string::iterator tiny_string::begin( ) const { return { as_chars( ) }; }

const tiny_string::iterator tiny_string::end( ) const { 
	return { as_chars( ) + ( _length + 1 ) };
}

tiny_string::regex_iterator tiny_string::begin_regex( const tiny_string& regex ) const {
	auto expression = std::regex{ regex.as_chars( ), regex.length( ) };

	return regex_iterator{ _handle, tiny_rvalue( _handle[ _length + 1 ] ), expression };
}

tiny_string::regex_iterator tiny_string::end_regex( ) const { return regex_iterator{ }; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool tiny_string::is_valid( under_layer string ) const { 
	return string && strlen( string ) > 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_string::operator bool( ) const { return is_valid( ); }

tiny_string::operator under_layer ( ) const { return get( ); }

tiny_string::operator std::string ( ) const { return as_chars( ); }

tiny_string& tiny_string::operator=( under_layer string ) { return asign( string ); }

tiny_string& tiny_string::operator=( const std::string string ) { return asign( string ); }

tiny_string& tiny_string::operator=( const tiny_string& other ) { return asign( other ); }

bool tiny_string::operator==( under_layer string ) const { return equal( string ); }

bool tiny_string::operator==( const tiny_string& other ) const { return equal( other ); }

bool tiny_string::operator==( const std::string& other ) const { return equal( other ); }

bool tiny_string::operator!=( under_layer string ) const {
	return not_equal( string );
}

bool tiny_string::operator!=( const tiny_string& other ) const {
	return not_equal( other );
}

bool tiny_string:: operator!=( const std::string& other ) const { 
	return not_equal( other );
}

char& tiny_string::operator[]( tiny_uint char_id ) { return at( char_id ); }

const char tiny_string::operator[]( tiny_uint char_id ) const { return at( char_id ); }
