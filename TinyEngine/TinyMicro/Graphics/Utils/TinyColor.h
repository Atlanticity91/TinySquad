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
 * @version  : 2024.2/8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Audio/TinyAudioManager.h>

tiny_enum( TinyColorChannels ) {

	TCC_RED = 0,
	TCC_GREEN,
	TCC_BLUE,
	TCC_ALPHA,

	TCC_COUNT

};

tm_struct tiny_color {

	float Channels[ TCC_COUNT ];

	tiny_color( );

	tiny_color( const tiny_vec3& vector );

	tiny_color( const tiny_vec4& vector );

	tiny_color( float r, float g );

	tiny_color( float r, float g, float b, float a );

	tiny_color( tiny_uint r, tiny_uint g, tiny_uint b, float a );

	tiny_color( tiny_int r, tiny_int g, tiny_int b, float a );

	tiny_color& Asign( TinyColorChannels channel, float value );

	tiny_color& Asign( TinyColorChannels channel, tiny_uint value );

	tiny_color& Asign( const tiny_color& other );

	tiny_color& Asign( const tiny_vec3& vector );

	tiny_color& Asign( const tiny_vec4& vector );

	tiny_uint Convert( );

	float* Get( );

	const float* Get( ) const;

	float GetChannel( TinyColorChannels channel ) const;

	tiny_uint GetChannelAsInt( TinyColorChannels channel ) const;

	float GetR( ) const;

	float GetG( ) const;

	float GetB( ) const;

	float GetA( ) const;

	tiny_vec3 ToVec3( ) const;

	tiny_vec4 ToVec4( ) const;

	VkClearValue ToClear( ) const;

	operator float* ( );

	operator const float* ( ) const;

	operator tiny_uint ( );

	operator tiny_vec3 ( ) const;

	operator tiny_vec4 ( ) const;

	operator VkClearValue ( ) const;

	tiny_color& operator=( const tiny_color& other );

	tiny_color& operator=( const tiny_vec3& vector );

	tiny_color& operator=( const tiny_vec4& vector );

	float operator[]( TinyColorChannels channel ) const;

};
