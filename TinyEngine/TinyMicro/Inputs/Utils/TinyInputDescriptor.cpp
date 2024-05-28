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
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
static native_string Internal_InputList[] = {
	// === TYPES ===
	"Button",
	"Axis 1D",
	"Axis 2D",

	// === STATES ===
	"Pressed",
	"Released",
	"Down",
	"Up",

	// === MODIFIERS ===
	"None",
	"Shift",
	"Ctrl",
	"Alt",

	// === UNDEFINED===
	"UNDEFINED",

	// === KEYBOARD KEYS ===
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"F16",
	"F17",
	"F18",
	"F19",
	"F20",
	"F21",
	"F22",
	"F23",
	"F24",
	"F25",
	"SPACE",
	"APOSTROPHE",
	"COMMA",
	"MINUS",
	"PERIOD",
	"SLASH",
	"SEMICOLON",
	"EQUAL",
	"LEFT BRACKET",
	"BACKSLASH",
	"RIGHT BRACKET",
	"GRAVE ACCENT",
	"ESCAPE",
	"ENTER",
	"TAB",
	"BACKSPACE",
	"INSERT",
	"DELETE",
	"RIGHT",
	"LEFT",
	"DOWN",
	"UP",
	"PAGE UP",
	"PAGE DOWN",
	"HOME",
	"END",
	"CAPS LOCK",
	"SCROLL LOCK",
	"NUM LOCK",
	"PRINT SCREEN",
	"PAUSE",
	"KP 0",
	"KP 1",
	"KP 2",
	"KP 3",
	"KP 4",
	"KP 5",
	"KP 6",
	"KP 7",
	"KP 8",
	"KP 9",
	"KP DECIMAL",
	"KP DIVIDE",
	"KP MULTIPLY",
	"KP SUBTRACT",
	"KP ADD",
	"KP ENTER",
	"KP EQUAL",
	"LEFT SHIFT",
	"LEFT CONTROL",
	"LEFT ALT",
	"LEFT SUPER",
	"RIGHT SHIFT",
	"RIGHT CONTROL",
	"RIGHT ALT",
	"RIGHT SUPER",
	"MENU",

	// === MOUSE KEYS ===
	"LEFT",
	"RIGHT",
	"MIDDLE",
	"CURSOR",
	"SCROLL",

	// === GAMEPAD KEYS ===
	"A",
	"B",
	"X",
	"Y",
	"LEFT BUMPER",
	"RIGHT BUMPER",
	"BACK",
	"START",
	"GUIDE",
	"LEFT THUMB",
	"RIGHT THUMB",
	"DPAD UP",
	"DPAD RIGHT",
	"DPAD DOWN",
	"DPAD LEFT",
	"AXIS LEFT X",
	"AXIS LEFT Y",
	"AXIS RIGHT X",
	"AXIS RIGHT Y",
	"AXIS LEFT TRIGGER",
	"AXIS RIGHT TRIGGER",
	"AXIS LEFT",
	"AXIS RIGHT",
	"AXIS TRIGGERS"

};

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

tiny_string_view TinyInputs::GetInputTypeList( const TinyInputDevices device ) {
	auto types = tiny_string_view{ tiny_rvalue( Internal_InputList[ 0 ] ), 1 };

	switch ( device ) {
		case TI_DEVICE_MOUSE   : types.Count = 2; break;
		case TI_DEVICE_GAMEPAD : types.Count = 3; break;

		default: break;
	}

	return types;
}

tiny_string_view TinyInputs::GetInputKeyList(
	const TinyInputDevices device,
	const TinyInputTypes type
) {
	auto keys = tiny_string_view{ tiny_rvalue( Internal_InputList[ 11 ] ), 1 };

	switch ( device ) {
		case TI_DEVICE_KEYBOARD :
			keys.Address = tiny_rvalue( Internal_InputList[ 12 ] );
			keys.Count   = 118;

			break;

		case TI_DEVICE_MOUSE : 
			switch ( type ) {
				case TI_TYPE_BUTTON  : 
					keys.Address = tiny_rvalue( Internal_InputList[ 130 ] );
					keys.Count   = 3;
					break;

				case TI_TYPE_AXIS_1D :
					keys.Address = tiny_rvalue( Internal_InputList[ 133 ] );
					keys.Count   = 2; 
					break;

				default: break;
			}

			break;

		case TI_DEVICE_GAMEPAD :
			switch ( type ) {
				case TI_TYPE_BUTTON  :
					keys.Address = tiny_rvalue( Internal_InputList[ 135 ] );
					keys.Count   = 15;
					break;

				case TI_TYPE_AXIS_1D : 
					keys.Address = tiny_rvalue( Internal_InputList[ 150 ] );
					keys.Count = 6;
					break;

				case TI_TYPE_AXIS_2D : 
					keys.Address = tiny_rvalue( Internal_InputList[ 156 ] );
					keys.Count = 3;
					break;

				default: break;
			}

			break;

		default : break;
	}

	return keys;
}

tiny_string_view TinyInputs::GetInputStateList( ) {
	return tiny_string_view{ tiny_rvalue( Internal_InputList[ 3 ] ), 4 };
}

tiny_string_view TinyInputs::GetInputModifierList( ) {
	return tiny_string_view{ tiny_rvalue( Internal_InputList[ 7 ] ), 4 };
}
