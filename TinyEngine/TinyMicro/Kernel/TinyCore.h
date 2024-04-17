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
 * @creation : 09/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#ifdef _MSC_VER
#	pragma warning( push )
#	pragma warning( disable : 4099 )
#	pragma warning( disable : 4217 )
#	pragma warning( disable : 4251 )
#	pragma warning( disable : 4275 )
#	pragma warning( disable : 5103 )
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUDES 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" {

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <inttypes.h>

};

#include <array>
#include <bitset>
#include <chrono>
#include <concepts>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <xhash>

#include <TinyThirdparty/Vulkan/Vulkan.h>

#ifdef _WIN64
#	define TINY_WIN
#	ifdef TM_BUILD
#		define tm_dll __declspec( dllexport )
#	else
#		define tm_dll __declspec( dllimport )
#	endif

#	ifdef TINY_DEBUG
#	define tiny_breakpoint __debugbreak( )
#	define tiny_assert( TEST, FORMAT, ... )\
	do {\
        if (\
            !( TEST ) &&\
            ( 1 == _CrtDbgReport( _CRT_ASSERT, __FILE__, __LINE__, #TEST, FORMAT, __VA_ARGS__ ) )\
        )\
            _CrtDbgBreak( );\
    } while( 0 )
#	else
#		define tiny_breakpoint 
#		define tiny_assert( ... ) 
#	endif

#   include <TinyThirdparty/XAudio2/XAudio2.h>
#   include <TinyThirdparty/GLFW/Glfw_win32.h>

#elif __linux__ || __linux || linux
#	define TINY_LINUX
#	define tm_dll
#	if __has_builtin(__builtin_debugtrap)
#		define tiny_breakpoint __builtin_debugtrap( )
#	elif defined( SIGTRAP )
#		define tiny_breakpoint raise( SIGTRAP )
#	endif

#   include <TinyThirdparty/GLFW/Glfw_linux.h>

#elif __APPLE__
#	define TINY_APPLE
#	define tm_dll
#	define tiny_breakpoint

#   include <TinyThirdparty/GLFW/Glfw_osx.h>

#else
#	error "Unimplemented Platforms"
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HELPER'S
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define tm_union union tm_dll
#define tm_interface struct tm_dll
#define tm_struct tm_interface
#define tm_class class tm_dll
#define tm_abstract_class tm_class
#define tm_enumerable( NAME ) enum tm_class NAME
#define tiny_enum( NAME ) enum NAME : tiny_uint
#define tiny_inherit( ... ) public __VA_ARGS__
#define tiny_abstract( ... ) virtual __VA_ARGS__ = 0
#define tiny_implement( ... ) virtual __VA_ARGS__ override
#define tiny_no_implement( ... ) __VA_ARGS__ {}
#define tiny_no_implementv( RET, ... ) __VA_ARGS__ { return RET; }
#define tiny_virtual( ... ) tiny_no_implement( virtual __VA_ARGS__ ) 
#define tiny_virtualv( RET, ... ) tiny_no_implementv( RET, virtual __VA_ARGS__ ) 
#define tiny_is_child_of( TYPE, BASE ) std::is_base_of<BASE, TYPE>::value
#define tiny_has_contstuctor( TYPE, ARGS ) std::is_constructible<TYPE, ARGS...>::value
#define tiny_is_int( TYPE ) std::is_integral<TYPE>::value
#define tiny_is_float( TYPE ) std::is_floating_point<TYPE>::value
#define tiny_is_literal( TYPE ) std::is_arithmetic<TYPE>::value
#define tiny_is_pointer( TYPE ) std::is_pointer<TYPE>::value
#define tiny_compile_if( ... ) if constexpr ( __VA_ARGS__ )
#define tiny_compile_elif( ... ) else tiny_compile_if( __VA_ARGS__ )
#define tiny_compile_else else
#define tiny_deprecated( SINCE, FOR ) [[deprecated( "Deprecated since " #SINCE "; Use instead : " #FOR )]]
#define tiny_nodiscard [[nodiscard]]
#define tiny_inline inline
#define tiny_init std::initializer_list
#define tiny_cast( VAL, TYPE ) ( (TYPE)(VAL) )
#define tiny_size_array( ARRAY ) ( tiny_cast( ( sizeof ARRAY / sizeof ARRAY[ 0 ] ), tiny_uint ) )
#define tiny_size_chars( ARRAY ) ( tiny_size_array( ARRAY ) - 1 )
#define tiny_sizeof( TYPE ) tiny_cast( sizeof( TYPE ), tiny_uint )
#define tiny_countof( TYPE ) tiny_cast( sizeof...( TYPE ), tiny_uint )
#define tiny_offset_of( FIELD, TYPE ) offsetof( TYPE, FIELD )
#define tiny_lvalue( PTR ) ( *( PTR ) )
#define tiny_rvalue( REF ) ( &( REF ) )
#define tiny_unused( VAR ) tiny_cast( VAR, void )
#define tiny_self tiny_lvalue( this )
#define tiny_sleep_for( TIME ) std::this_thread::sleep_for( std::chrono::milliseconds( TIME ) )

#define TINY_XSTR( VALUE ) #VALUE 
#define TINY_STR( ... ) TINY_XSTR( __VA_ARGS__ )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Types Definition 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TINY_INT_REG( INT, NAME ) typedef INT tiny_##NAME; typedef u##INT tiny_u##NAME

TINY_INT_REG( int8_t,  byte  );
TINY_INT_REG( int16_t, short );
TINY_INT_REG( int32_t, int   );
TINY_INT_REG( int64_t, long  );

#define TINY_UBYTE_MAX	tiny_cast( UCHAR_MAX, tiny_ubyte )
#define TINY_USHORT_MAX tiny_cast( USHRT_MAX, tiny_ushort )
#define TINY_UINT_MAX	tiny_cast( UINT_MAX, tiny_uint )
#define TINY_ULONG_MAX	tiny_cast( ULONG_MAX, tiny_ulong )

#define tiny_kilo( COUNT ) tiny_cast( COUNT * 1024, tiny_uint )
#define tiny_mega( COUNT ) tiny_cast( COUNT * 1024 * 1024, tiny_uint )
#define tiny_giga( COUNT ) tiny_cast( COUNT * 1024 * 1024 * 1024, tiny_uint )

#define TINY_FOURCC2( VAL ) tiny_lvalue( tiny_cast( VAL, tiny_uint* ) )
#define TINY_FOURCC( VAL ) TINY_FOURCC2( #VAL )

#define tiny_clamp( VAL, LOW, HIGH ) ( VAL < LOW ? LOW : ( VAL > HIGH ? HIGH : VAL ) )
#define tiny_min( VAL_A, VAL_B ) ( ( VAL_A < VAL_B ) ? VAL_A : VAL_B )
#define tiny_max( VAL_A, VAL_B ) ( ( VAL_A > VAL_B ) ? VAL_A : VAL_B )
#define tiny_fractional( VAL ) ( VAL - truncf( VAL ) )
#define tiny_signi( VAL ) ( ( 0 < VAL ) - ( VAL < 0 ) )
#define tiny_signf( VAL ) ( ( .0f < VAL ) - ( VAL < .0f ) )

#define TINY_LEFT_SHIFT( VAL ) ( 1 << VAL )
#define TINY_RIGHT_SHIFT( VAL ) ( 1 >> VAL )

#define TINY_STR_OP( NAME, ... ) constexpr tiny_ulong operator""_##NAME##( tiny_ulong size ) { __VA_ARGS__; }

TINY_STR_OP( b, return size );
TINY_STR_OP( kb, return tiny_kilo( size ) );
TINY_STR_OP( mb, return tiny_mega( size ) );
TINY_STR_OP( gb, return tiny_giga( size ) );
