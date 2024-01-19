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
tiny_color::tiny_color( )
	: tiny_color{ 1.f, 1.f, 1.f, 1.f }
{ }

tiny_color::tiny_color( const tiny_vec3& vector )
	: tiny_color{ vector.x, vector.y, vector.z, 1.f }
{ }

tiny_color::tiny_color( const tiny_vec4& vector )
	: tiny_color{ vector.x, vector.y, vector.z, vector.w } 
{ }

tiny_color::tiny_color( float r, float g )
	: tiny_color{ r, g, 0.f, 1.f } 
{ }

tiny_color::tiny_color( float r, float g, float b, float a )
	: Channels{ r, g, b, a }
{ }

tiny_color::tiny_color( tiny_uint r, tiny_uint g, tiny_uint b, float a )
	: tiny_color{ r / 256.f, g / 256.f, b / 256.f, a }
{ }

tiny_color::tiny_color( tiny_int r, tiny_int g, tiny_int b, float a )
	: tiny_color{ r / 256.f, g / 256.f, b / 256.f, a } 
{ }

tiny_color& tiny_color::Asign( TinyColorChannels channel, float value ) {
	if ( channel < TCC_COUNT )
		Channels[ channel ] = value;

	return tiny_self;
}

tiny_color& tiny_color::Asign( TinyColorChannels channel, tiny_uint value ) {
	auto value_f = value / 256.f;

	return Asign( channel, value_f );
}

tiny_color& tiny_color::Asign( const tiny_color& other ) {
	Tiny::Memcpy( other.Channels, Channels, TCC_COUNT );

	return tiny_self;
}

tiny_color& tiny_color::Asign( const tiny_vec3& vector ) {
	Tiny::Memcpy( &vector.x, Channels, 3 );

	return tiny_self;
}

tiny_color& tiny_color::Asign( const tiny_vec4& vector ) {
	Tiny::Memcpy( &vector.x, Channels, 4 );

	return tiny_self;
}

tiny_uint tiny_color::Convert( ) {
	auto converted = tiny_cast( 0, tiny_uint );
	auto channel   = tiny_cast( TCC_COUNT, tiny_uint);

	while ( channel-- > 0 ) {
		auto value = GetChannelAsInt( tiny_cast( channel, TinyColorChannels ) );

		converted |= ( value << ( channel * 8 ) );
	}

	return converted;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
float* tiny_color::Get( ) { return Channels; }

const float* tiny_color::Get( ) const { return Channels; }

float tiny_color::GetChannel( TinyColorChannels channel ) const {
	auto value = .0f;

	if ( channel < TCC_COUNT )
		value = Channels[ channel ];

	return value;
}

tiny_uint tiny_color::GetChannelAsInt( TinyColorChannels channel ) const {
	auto value = tiny_cast( 0, tiny_uint);

	if ( channel < TCC_COUNT )
		value = tiny_cast( ( Channels[ channel ] * 256.f ), tiny_uint );

	return value;
}

float tiny_color::GetR( ) const { return Channels[ 0 ]; }

float tiny_color::GetG( ) const { return Channels[ 1 ]; }

float tiny_color::GetB( ) const { return Channels[ 2 ]; }

float tiny_color::GetA( ) const { return Channels[ 3 ]; }

tiny_vec4 tiny_color::ToVec4( ) const {
	auto vector = tiny_vec4{ };

	Tiny::Memcpy( Channels, &vector.x, 4 );

	return vector;
}

tiny_vec3 tiny_color::ToVec3( ) const {
	auto vector = tiny_vec4{ };

	Tiny::Memcpy( Channels, &vector.x, 3 );

	return vector;
}

VkClearValue tiny_color::ToClear( ) const {
	return {
		Channels[ 0 ],
		Channels[ 1 ],
		Channels[ 2 ],
		Channels[ 3 ]
	};
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_color::operator float* ( ) { return Get( ); }

tiny_color::operator const float* ( ) const { return Get( ); }

tiny_color::operator tiny_uint ( ) { return Convert( ); }

tiny_color::operator tiny_vec3 ( ) const { return ToVec3( ); }

tiny_color::operator tiny_vec4 ( ) const { return ToVec4( ); }

tiny_color::operator VkClearValue ( ) const { return ToClear( ); }

tiny_color& tiny_color::operator=( const tiny_color& other ) { return Asign( other ); }

tiny_color& tiny_color::operator=( const tiny_vec3& vector ) { return Asign( vector ); }

tiny_color& tiny_color::operator=( const tiny_vec4& vector ) { return Asign( vector ); }

float tiny_color::operator[]( TinyColorChannels channel ) const { 
	return GetChannel( channel ); 
}
