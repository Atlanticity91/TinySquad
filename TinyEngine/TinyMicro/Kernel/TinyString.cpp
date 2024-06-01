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
	: m_handle( nullptr ),
	m_length{ 0 }
{ }

tiny_string::tiny_string( native_string string )
	: tiny_string{ }
{ 
	asign( string );
}

tiny_string::tiny_string( const tiny_string& other )
	: tiny_string{ }
{
	asign( other );
}

tiny_string::tiny_string( const std::string& string )
	: tiny_string{ } 
{
	asign( string );
}
tiny_string::tiny_string( const tiny_uint length, const native_pointer data )
	: tiny_string{ }
{ 
	asign( length, data );
}

tiny_string& tiny_string::asign( native_string string ) {
	auto* data  = tiny_cast( string, const native_pointer );
	auto length = tiny_cast( strlen( string ), tiny_uint );

	return asign( length, data );
}

tiny_string& tiny_string::asign( const tiny_string& other ) {
	auto* data  = other.as_native( );
	auto length = other.length( );

	return asign( length, data );
}

tiny_string& tiny_string::asign( const std::string& string ) {
	auto* data  = tiny_cast( string.c_str( ), const native_pointer );
	auto length = tiny_cast( string.length( ), tiny_uint );

	return asign( length, data );
}

tiny_string& tiny_string::asign( const tiny_uint length, const native_pointer data ) {
	TINY_ASSERT( length > 0, "You can't extract buffer data to a 0 length array" );
	TINY_ASSERT( data != nullptr, "You can't extract buffer data to a null array" );

	m_handle = tiny_cast( data, char* );
	m_length = length;

	return tiny_self;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool tiny_string::get_is_valid( ) const { return m_handle != nullptr && m_length > 0; }

bool tiny_string::get_is_empty( ) const { return length( ) == 0; }

tiny_uint tiny_string::length( ) const { return m_length; }

char* tiny_string::get( ) const { return m_handle; }

char* tiny_string::last( ) const { return m_handle + m_length; }

native_string tiny_string::as_string( ) const { return m_handle; }

native_pointer tiny_string::as_native( ) { return tiny_cast( m_handle, native_pointer ); }

const native_pointer tiny_string::as_native( ) const { 
	return tiny_cast( m_handle, const native_pointer );
}

std::string tiny_string::to_string( ) const { return std::string{ m_handle, m_length }; }

char& tiny_string::at( const tiny_uint char_id ) {
	TINY_ASSERT_FORMAT( char_id < m_length, "You can't access character outside the string limits {0:%u}", m_length );

	return tiny_lvalue( m_handle + char_id );
}

const char tiny_string::at( const tiny_uint char_id ) const {
	TINY_ASSERT_FORMAT( char_id < m_length, "You can't access character outside the string limits {0:%u}", m_length );
	
	return m_handle[ char_id ];
}

std::string tiny_string::make_string( char start, char stop ) const {
	auto string	   = std::string{ m_handle };
	auto str_start = string.find_last_of( start )+1;
	auto str_stop  = string.find_last_of( stop );

	return string.substr( str_start, str_stop - str_start );
}

native_string tiny_string::sub_chars(
	const tiny_string& sequence, 
	bool cut_after
) const {
	auto* sub_string = tiny_cast( nullptr, native_string );

	if ( get_is_valid( ) && sequence.get_is_valid( ) ) {
		auto* sequence_ = sequence.as_string( );
		sub_string		= strstr( m_handle, sequence_ );

		if ( sub_string && cut_after )
			sub_string += sequence.length( );
	}

	return sub_string;
}

tiny_string tiny_string::sub_string( const tiny_string& sequence, bool cut_after ) const {
	auto sub = tiny_string{ };

	if ( get_is_valid( ) && sequence.get_is_valid( ) ) {
		auto* sequence_ = sequence.as_string( );
		auto* tmp		= strstr( m_handle, sequence_ );

		if ( tmp && cut_after )
			tmp += sequence.length( );

		sub = tmp;
	}

	return sub;
}

tiny_string tiny_string::sub_string( const tiny_uint offset ) const {
	auto sub = tiny_string{ };

	if ( offset < m_length )
		sub.asign( m_handle + offset );

	return sub;
}

bool tiny_string::equal( native_string string ) const {
	auto state = false;

	if ( get_is_valid( string ) && length( ) > 0 )
		state = strcmp( string, m_handle ) == 0;

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

bool tiny_string::not_equal( native_string string ) const {
	return !equal( string );
}

bool tiny_string::not_equal( const tiny_string& other ) const {
	return !equal( other );
}

bool tiny_string::not_equal( const std::string& other ) const {
	return !equal( other );
}

tiny_string::iterator tiny_string::begin( ) { return { get( ) }; }

tiny_string::iterator tiny_string::end( ) { return { last( ) + 1 }; }

const tiny_string::iterator tiny_string::begin( ) const { return { get( ) }; }

const tiny_string::iterator tiny_string::end( ) const { return { last( ) + 1 }; }

tiny_string::regex_iterator tiny_string::begin_regex( const tiny_string& regex ) const {
	auto* string	= regex.get( );
	auto length		= regex.length( );
	auto expression = std::regex{ string, length };

	return regex_iterator{ m_handle, m_handle + ( m_length + 1 ), expression };
}

tiny_string::regex_iterator tiny_string::end_regex( ) const { return regex_iterator{ }; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool tiny_string::get_is_valid( native_string string ) const {
	return string != nullptr && strlen( string ) > 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_string::operator bool( ) const { return get_is_valid( ); }

tiny_string::operator native_string ( ) const { return get( ); }

tiny_string::operator std::string ( ) const { return to_string( ); }

tiny_string& tiny_string::operator=( native_string string ) { return asign( string ); }

tiny_string& tiny_string::operator=( const tiny_string& other ) { return asign( other ); }

tiny_string& tiny_string::operator=( const std::string& string ) { return asign( string ); }

bool tiny_string::operator==( native_string string ) const { return equal( string ); }

bool tiny_string::operator==( const tiny_string& other ) const { return equal( other ); }

bool tiny_string::operator==( const std::string& other ) const { return equal( other ); }

bool tiny_string::operator!=( native_string string ) const {
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
