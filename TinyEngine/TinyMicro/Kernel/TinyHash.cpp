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
 * @creation : 13/10/2023
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
tiny_hash::tiny_hash( )
	: _data{ 0 }
{ }

tiny_hash::tiny_hash( tiny_uint value ) 
	: _data{ value }
{ }

tiny_hash::tiny_hash( const tiny_hash& other )
	: _data{ other.get( ) }
{ }

tiny_hash::tiny_hash( const tiny_string& string ) 
	: tiny_hash{ }
{
	asign( string );
}

tiny_hash::tiny_hash( const tiny_string& string, tiny_uint offset, tiny_uint length )
	: tiny_hash{ }
{ 
	asign( string, offset, length );
}

tiny_hash::tiny_hash( c_string string )
	: tiny_hash{ } 
{
	asign( string );
}

tiny_hash::tiny_hash( const std::string& string )
	: tiny_hash{ }
{ 
	asign( string );
}

tiny_hash& tiny_hash::asign( const tiny_string& string ) {
	_data = generate( string );

	return tiny_self;
}

tiny_hash& tiny_hash::asign( tiny_uint other ) {
	_data = other;

	return tiny_self;
}

tiny_hash& tiny_hash::asign( const tiny_hash& other ) {
	_data = other.get( );

	return tiny_self;
}

tiny_hash& tiny_hash::asign( c_string other ) {
	auto _other = tiny_string{ other };

	return asign( _other );
}

tiny_hash& tiny_hash::asign( const std::string& other ) {
	auto _other = tiny_string{ other.c_str( ) };

	return asign( _other );
}

tiny_hash& tiny_hash::asign(
	const tiny_string& string,
	tiny_uint offset,
	tiny_uint length
) {
	_data = generate( string, offset, length );

	return tiny_self;
}

void tiny_hash::empty( ) { _data = tiny_cast( 0, tiny_uint ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint tiny_hash::generate( tiny_string string ) const {
	return generate( string, 0, string.length( ) );
}

tiny_uint tiny_hash::generate( 
	tiny_string string,
	tiny_uint offset,
	tiny_uint length 
) const {
	// From https://stackoverflow.com/questions/2351087/what-is-the-best-32bit-hash-function-for-short-strings-tag-names
	// Use 1721 as Prime Number from https://en.wikipedia.org/wiki/List_of_prime_numbers

	auto hash = 0;

	length = length <= string.length( ) ? length : string.length( );

	while ( offset < length )
		hash = 1721 * hash + string[ offset++ ];

	return hash;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint tiny_hash::get( ) const { return _data; }

bool tiny_hash::is_valid( ) const { return _data > 0; }

bool tiny_hash::equal( tiny_string string ) const { 
	return _data == generate( string );
}

bool tiny_hash::equal( tiny_uint other ) const { return _data == other; }

bool tiny_hash::equal( const tiny_hash& other ) const { return _data == other.get( ); }

bool tiny_hash::equal( const std::string& other ) const {
	auto _other = tiny_string{ other };

	return equal( _other );
}

bool tiny_hash::not_equal( tiny_string string ) const {
	return _data != generate( string );
}

bool tiny_hash::not_equal( tiny_uint other ) const { return _data != other; }

bool tiny_hash::not_equal( const tiny_hash& other ) const { return _data != other.get( ); }

bool tiny_hash::not_equal( const std::string& other ) const {
	auto _other = tiny_string{ other };

	return not_equal( _other );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_hash::operator bool( ) const { return is_valid( ); }

tiny_hash& tiny_hash::operator=( tiny_string string ) { return asign( string ); }

tiny_hash& tiny_hash::operator=( tiny_uint other ) { return asign( other ); }

tiny_hash& tiny_hash::operator=( const tiny_hash& other ) { return asign( other ); }

tiny_hash& tiny_hash::operator=( const std::string& other ) { return asign( other ); }

bool tiny_hash::operator<( const tiny_hash other ) const { return _data < other.get( ); }

bool tiny_hash::operator>( const tiny_hash other ) const { return _data > other.get( ); }

bool tiny_hash::operator==( tiny_string string ) const { return equal( string ); }

bool tiny_hash::operator==( tiny_uint other ) const { return equal( other ); }

bool tiny_hash::operator==( const tiny_hash& other ) const { return equal( other ); }

bool tiny_hash::operator==( const std::string& other ) const { return equal( other ); }

bool tiny_hash::operator!=( tiny_string string ) const { return not_equal( string ); }

bool tiny_hash::operator!=( tiny_uint other ) const { return not_equal( other ); }

bool tiny_hash::operator!=( const tiny_hash& other ) const { return not_equal( other ); }

bool tiny_hash::operator!=( const std::string& other ) const { return not_equal( other ); }
