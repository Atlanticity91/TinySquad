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
 * @creation : 14/10/2023
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
#define TINY_KEY( KEY )  case GLFW_KEY_##KEY : value = TIK_KEY_##KEY; break

TinyInputKeys TinyInputs::ConvertKey( tiny_int glfw_key ) {
	auto value = TIK_KEY_COUNT;

	switch ( glfw_key ) {
		TINY_KEY( A );
		TINY_KEY( B );
		TINY_KEY( C );
		TINY_KEY( D );
		TINY_KEY( E );
		TINY_KEY( F );
		TINY_KEY( G );
		TINY_KEY( H );
		TINY_KEY( I );
		TINY_KEY( J );
		TINY_KEY( K );
		TINY_KEY( L );
		TINY_KEY( M );
		TINY_KEY( N );
		TINY_KEY( O );
		TINY_KEY( P );
		TINY_KEY( Q );
		TINY_KEY( R );
		TINY_KEY( S );
		TINY_KEY( T );
		TINY_KEY( U );
		TINY_KEY( V );
		TINY_KEY( W );
		TINY_KEY( X );
		TINY_KEY( Y );
		TINY_KEY( Z );

		TINY_KEY( 0 );
		TINY_KEY( 1 );
		TINY_KEY( 2 );
		TINY_KEY( 3 );
		TINY_KEY( 4 );
		TINY_KEY( 5 );
		TINY_KEY( 6 );
		TINY_KEY( 7 );
		TINY_KEY( 8 );
		TINY_KEY( 9 );

		TINY_KEY( F1 );
		TINY_KEY( F2 );
		TINY_KEY( F3 );
		TINY_KEY( F4 );
		TINY_KEY( F5 );
		TINY_KEY( F6 );
		TINY_KEY( F7 );
		TINY_KEY( F8 );
		TINY_KEY( F9 );
		TINY_KEY( F10 );
		TINY_KEY( F11 );
		TINY_KEY( F12 );
		TINY_KEY( F13 );
		TINY_KEY( F14 );
		TINY_KEY( F15 );
		TINY_KEY( F16 );
		TINY_KEY( F17 );
		TINY_KEY( F18 );
		TINY_KEY( F19 );
		TINY_KEY( F20 );
		TINY_KEY( F21 );
		TINY_KEY( F22 );
		TINY_KEY( F23 );
		TINY_KEY( F24 );
		TINY_KEY( F25 );

		TINY_KEY( SPACE );
		TINY_KEY( APOSTROPHE );
		TINY_KEY( COMMA );
		TINY_KEY( MINUS );
		TINY_KEY( PERIOD );
		TINY_KEY( SLASH );
		TINY_KEY( SEMICOLON );
		TINY_KEY( EQUAL );
		TINY_KEY( LEFT_BRACKET );
		TINY_KEY( BACKSLASH );
		TINY_KEY( RIGHT_BRACKET );
		TINY_KEY( GRAVE_ACCENT );
		TINY_KEY( ESCAPE );
		TINY_KEY( ENTER );
		TINY_KEY( TAB );
		TINY_KEY( BACKSPACE );
		TINY_KEY( INSERT );

		case GLFW_KEY_DELETE: value = TIK_KEY_DELETE; break;

		TINY_KEY( RIGHT );
		TINY_KEY( LEFT );
		TINY_KEY( DOWN );
		TINY_KEY( UP );
		TINY_KEY( PAGE_UP );
		TINY_KEY( PAGE_DOWN );
		TINY_KEY( HOME );
		TINY_KEY( END );
		TINY_KEY( CAPS_LOCK );
		TINY_KEY( SCROLL_LOCK );
		TINY_KEY( NUM_LOCK );
		TINY_KEY( PRINT_SCREEN );
		TINY_KEY( PAUSE );
		TINY_KEY( KP_0 );
		TINY_KEY( KP_1 );
		TINY_KEY( KP_2 );
		TINY_KEY( KP_3 );
		TINY_KEY( KP_4 );
		TINY_KEY( KP_5 );
		TINY_KEY( KP_6 );
		TINY_KEY( KP_7 );
		TINY_KEY( KP_8 );
		TINY_KEY( KP_9 );
		TINY_KEY( KP_DECIMAL );
		TINY_KEY( KP_DIVIDE );
		TINY_KEY( KP_MULTIPLY );
		TINY_KEY( KP_SUBTRACT );
		TINY_KEY( KP_ADD );
		TINY_KEY( KP_ENTER );
		TINY_KEY( KP_EQUAL );
		TINY_KEY( LEFT_SHIFT );
		TINY_KEY( LEFT_CONTROL );
		TINY_KEY( LEFT_ALT );
		TINY_KEY( LEFT_SUPER );
		TINY_KEY( RIGHT_SHIFT );
		TINY_KEY( RIGHT_CONTROL );
		TINY_KEY( RIGHT_ALT );
		TINY_KEY( RIGHT_SUPER );
		TINY_KEY( MENU );

		default: break;
	}

	return value;
}
