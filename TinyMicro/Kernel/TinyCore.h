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
#include <set>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <xhash>

#ifdef _WIN64
#	define TINY_WIN
#	define tiny_breakpoint __debugbreak( )
#	ifdef TM_BUILD
#		define tm_dll __declspec( dllexport )
#	else
#		define tm_dll __declspec( dllimport )
#	endif
#	define USING_XAUDIO2_9
#	define VK_USE_PLATFORM_WIN32_KHR
#	define GLFW_EXPOSE_NATIVE_WIN32
#elif __linux__ || __linux || linux
#	define TINY_LINUX
#	define tm_dll
#	if __has_builtin(__builtin_debugtrap)
#		define tiny_breakpoint __builtin_debugtrap( )
#	elif defined( SIGTRAP )
#		define tiny_breakpoint raise( SIGTRAP )
#	endif
#	ifdef WAYLAND_DISPLAY
#		define GLFW_EXPOSE_NATIVE_WAYLAND
#	else
#		define GLFW_EXPOSE_NATIVE_X11
#	endif
#elif __APPLE__
#	define TINY_APPLE
#	define tm_dll
#	define tiny_breakpoint
#	define GLFW_EXPOSE_NATIVE_COCOA
#else
#	error "Unimplemented Platforms"
#endif

#define GLFW_INCLUDE_NONE

#include <xaudio2.h>
#include <xaudio2fx.h>
#include <vulkan/vulkan.h>
#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv.hpp>
#include <TinyThirdparty/GLFW/glfw3.h>
#include <TinyThirdparty/GLFW/glfw3native.h>

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
#define tiny_str( ... ) #__VA_ARGS__ 
#define tiny_is_child_of( TYPE, BASE ) std::is_base_of<BASE, TYPE>::value
#define tiny_has_contstuctor( TYPE, ARGS ) std::is_constructible<TYPE, ARGS...>::value
#define tiny_enable_if( ... ) requires __VA_ARGS__
#define tiny_deprecated( SINCE, FOR ) [[deprecated( "Deprecated since " #SINCE "; Use instead : " #FOR )]]
#define tiny_nodiscard [[nodiscard]]
#define tiny_inline inline
#define tiny_init std::initializer_list
#define tiny_cast( VAL, TYPE ) ( (TYPE)(VAL) )
#define tiny_size_array( ARRAY ) ( tiny_cast( ( sizeof ARRAY / sizeof ARRAY[ 0 ] ), tiny_uint ) )
#define tiny_size_chars( ARRAY ) ( tiny_size_array( ARRAY ) - 1 )
#define tiny_sizeof( TYPE ) ( tiny_cast( sizeof( TYPE ), tiny_uint ) )
#define tiny_offset_of( TYPE, FIELD ) offsetof( TYPE, FIELD )
#define tiny_lvalue( PTR ) ( *( PTR ) )
#define tiny_rvalue( REF ) ( &( REF ) )
#define tiny_self tiny_lvalue( this )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Types Definition 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TINY_INT_REG( INT, NAME ) typedef INT tiny_##NAME; typedef u##INT tiny_u##NAME

TINY_INT_REG( int8_t,  byte  );
TINY_INT_REG( int16_t, short );
TINY_INT_REG( int32_t, int   );
TINY_INT_REG( int64_t, long  );

#define TINY_LEFT_SHIFT( VAL ) ( 1 << VAL )
#define TINY_RIGHT_SHIFT( VAL ) ( 1 >> VAL )

#define TINY_KILO( COUNT ) (tiny_uint)( COUNT * 1024 )
#define TINY_MEGA( COUNT ) (tiny_uint)( COUNT * 1024 * 1024 )
#define TINY_GIGA( COUNT ) (tiny_uint)( COUNT * 1024 * 1024 * 1024 )

#define TINY_UBYTE_MAX	(tiny_ubyte)UCHAR_MAX
#define TINY_USHORT_MAX (tiny_ushort)USHRT_MAX
#define TINY_UINT_MAX	(tiny_uint)UINT_MAX
#define TINY_ULONG_MAX	(tiny_ulong)ULONG_MAX

#define TINY_FOURCC2( VAL ) ( *( (tiny_uint*) VAL ) )
#define TINY_FOURCC( VAL ) TINY_FOURCC2( #VAL )

#define tiny_clamp( VAL, LOW, HIGH ) ( VAL < LOW ? LOW : ( VAL > HIGH ? HIGH : VAL ) )
#define tiny_min( VAL_A, VAL_B ) ( ( VAL_A < VAL_B ) ? VAL_A : VAL_B )
#define tiny_max( VAL_A, VAL_B ) ( ( VAL_A > VAL_B ) ? VAL_A : VAL_B )
#define tiny_fractional( VAL ) ( VAL - truncf( VAL ) )
#define tiny_signi( VAL ) ( ( 0 < VAL ) - ( VAL < 0 ) )
#define tiny_signf( VAL ) ( ( .0f < VAL ) - ( VAL < .0f ) )

constexpr tiny_ulong operator""_b( tiny_ulong size ) {
	return size;
}

constexpr tiny_ulong operator""_kb( tiny_ulong size ) {
	return TINY_KILO( size );
}

constexpr tiny_ulong operator""_mb( tiny_ulong size ) {
	return TINY_MEGA( size );
}

constexpr tiny_ulong operator""_gb( tiny_ulong size ) {
	return TINY_GIGA( size );
}
