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
 * @creation : 25/06/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRemap.h"

tm_class TinyRandom final {

public:
	TinyRandom( ) = delete;

public:
	/**
	 * Setup static method
	 * @note : Setup the random generator with default configuration.
	 **/
	static void Setup( );


	/**
	 * Setup static method
	 * @note : Set the random generator seed;
	 * @param seed : New random generator seed;
	 **/
	static void SetSeed( const tiny_ulong seed );

public:
	/**
	 * Next template static function
	 * @note : Generate a random number of the type Literal
	 * @template Literal : Type of number to generate, only literal type supported.
	 * @param max : Upper limit of the generator.
	 * @return : Random number from interval [0:max]
	 **/
	template<typename Literal>
		requires ( tiny_is_literal( Literal ) )
	static Literal Next( const Literal max ) {
		tiny_compile_if( tiny_is_int( Literal ) ) {
			return ( tiny_cast( rand( ), Literal ) % max );
		} tiny_compile_else{
			auto rand_value = tiny_cast( rand( ), Literal ) / tiny_cast( RAND_MAX, Literal );

			return rand_value * max;
		}
	};

	/**
	 * Next template static function
	 * @note : Generate a random number of the type Literal
	 * @template Literal : Type of number to generate, only literal type supported.
	 * @param min : Lower limit of the generator.
	 * @param max : Upper limit of the generator.
	 * @return : Random number from interval [min:max]
	 **/
	template<typename Literal>
		requires ( tiny_is_literal( Literal ) )
	static Literal Next( const Literal min, const Literal max ) { 
		tiny_compile_if( tiny_is_int( Literal ) ) {
			auto tmp_max = max - min;

			return min + ( tiny_cast( rand( ), Literal ) % tmp_max );
		} tiny_compile_else {
			auto rand_value = tiny_cast( rand( ), Literal ) / tiny_cast( RAND_MAX, Literal );
			auto tmp_max	= max - min;

			return min + rand_value * tmp_max;
		}
	};

};
