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

#pragma once

#include "TinyMath.h"

#define tiny_range_b(  min, max ) tiny_range<tiny_byte, min, max>
#define tiny_range_ub( min, max ) tiny_range<tiny_ubyte, min, max>
#define tiny_range_s(  min, max ) tiny_range<tiny_short, min, max>
#define tiny_range_us( min, max ) tiny_range<tiny_ushort, min, max>
#define tiny_range_i(  min, max ) tiny_range<tiny_int, min, max>
#define tiny_range_ui( min, max ) tiny_range<tiny_uint, min, max>
#define tiny_range_l(  min, max ) tiny_range<tiny_long, min, max>
#define tiny_range_ul( min, max ) tiny_range<tiny_ulong, min, max>
#define tiny_range_f(  min, max ) tiny_range<float, min, max>
#define tiny_range_d(  min, max ) tiny_range<double, min, max>

template<typename Type, Type Min, Type Max>
	requires tiny_is_literal( Type )
struct tiny_range {

	Type Value;

	tiny_range( ) = default;

	tiny_range( const Type& value )
		: Value{ tiny_clamp( value, Min, Max ) }
	{ };

	Type& Get( ) { return Value; };

	const Type& Get( ) const { return Value; };

	operator Type& ( ) { return Get( ); };

	operator const Type& ( ) const { return Get( ); };

	tiny_range& operator=( const Type& other ) {
		Value = tiny_clamp( other.Value, Min, Max );

		return tiny_self;
	};

	tiny_range operator+( const tiny_range& operand ) {
		return tiny_range<Type, Min, Max>( Value + operand.Value );
	}

	tiny_range operator-( const tiny_range& operand ) {
		return tiny_range<Type, Min, Max>( Value - operand.Value );
	}

	tiny_range operator*( const tiny_range& operand ) {
		return tiny_range<Type, Min, Max>( Value * operand.Value );
	}

	tiny_range operator/( const tiny_range& operand ) {
		return tiny_range<Type, Min, Max>( Value / operand.Value );
	}

	template<typename Operand = Type>
		requires tiny_is_int( Operand )
	Type operator%( const Operand operand ) {
		return Value % operand;
	};

	bool operator<( const Type& other ) {
		return Value < other.Value;
	};

	bool operator<=( const Type& other ) {
		return Value <= other.Value;
	};

	bool operator>( const Type& other ) {
		return Value > other.Value;
	};

	bool operator>=( const Type& other ) {
		return Value >= other.Value;
	};

	bool operator==( const Type& other ) {
		return Value == other.Value;
	};

	bool operator!=( const Type& other ) {
		return Value != other.Value;
	};

};
