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

#pragma once

#include "TinyInputKeys.h"

tiny_enum( TinyInputDevices ) {

	TID_KEYBOARD = 0,
	TID_MOUSE,
	TID_GAMEPAD,

	TI_DEVICE_COUNT

};

tiny_enum( TinyInputTypes ) {

	TIT_BUTTON = 0,
	TIT_AXIS_1D,
	TIT_AXIS_2D

};

tm_struct TinyInputDescriptor {

	TinyInputDevices Device;
	TinyInputTypes Type;
	TinyInputKeys Key;

};

namespace TinyInputs {

	#define TINY_REG_DESC( NAME, DEVICE, TYPE, KEY )\
		static const TinyInputDescriptor NAME = TinyInputDescriptor{ DEVICE, TYPE, TIK_##KEY }

	#define TINY_REG_KEY( VALUE )	   TINY_REG_DESC( VALUE, TID_KEYBOARD, TIT_BUTTON, VALUE )
	#define TINY_REG_MOUSE( VALUE )    TINY_REG_DESC( VALUE, TID_MOUSE, TIT_BUTTON, VALUE )
	#define TINY_REG_GP( VALUE, TYPE ) TINY_REG_DESC( VALUE, TID_GAMEPAD, TYPE, VALUE )

	#define TINY_REG_GAMEPAD( VALUE ) TINY_REG_GP( VALUE,TIT_BUTTON )
	#define TINY_REG_GAMEPAD_AXIS_1D( VALUE ) TINY_REG_GP( VALUE, TIT_AXIS_1D )
	#define TINY_REG_GAMEPAD_AXIS_2D( VALUE ) TINY_REG_GP( VALUE, TIT_AXIS_2D )

	// KEYBOARD
	TINY_REG_KEY( KEY_A );
	TINY_REG_KEY( KEY_B );
	TINY_REG_KEY( KEY_C );
	TINY_REG_KEY( KEY_D );
	TINY_REG_KEY( KEY_E );
	TINY_REG_KEY( KEY_F );
	TINY_REG_KEY( KEY_G );
	TINY_REG_KEY( KEY_H );
	TINY_REG_KEY( KEY_I );
	TINY_REG_KEY( KEY_J );
	TINY_REG_KEY( KEY_K );
	TINY_REG_KEY( KEY_L );
	TINY_REG_KEY( KEY_M );
	TINY_REG_KEY( KEY_O );
	TINY_REG_KEY( KEY_P );
	TINY_REG_KEY( KEY_Q );
	TINY_REG_KEY( KEY_R );
	TINY_REG_KEY( KEY_S );
	TINY_REG_KEY( KEY_T );
	TINY_REG_KEY( KEY_U );
	TINY_REG_KEY( KEY_V );
	TINY_REG_KEY( KEY_W );
	TINY_REG_KEY( KEY_X );
	TINY_REG_KEY( KEY_Y );
	TINY_REG_KEY( KEY_Z );
	TINY_REG_KEY( KEY_0 );
	TINY_REG_KEY( KEY_1 );
	TINY_REG_KEY( KEY_2 );
	TINY_REG_KEY( KEY_3 );
	TINY_REG_KEY( KEY_4 );
	TINY_REG_KEY( KEY_5 );
	TINY_REG_KEY( KEY_6 );
	TINY_REG_KEY( KEY_7 );
	TINY_REG_KEY( KEY_8 );
	TINY_REG_KEY( KEY_9 );
	TINY_REG_KEY( KEY_F1 );
	TINY_REG_KEY( KEY_GRAVE_ACCENT );

	// MOUSE
	TINY_REG_MOUSE( MOUSE_LEFT );
	TINY_REG_MOUSE( MOUSE_MIDDLE );
	TINY_REG_MOUSE( MOUSE_RIGHT );

	// GAMEPAD
	TINY_REG_GAMEPAD( GAMEPAD_A );
	TINY_REG_GAMEPAD( GAMEPAD_B );
	TINY_REG_GAMEPAD( GAMEPAD_X );
	TINY_REG_GAMEPAD( GAMEPAD_Y );
	TINY_REG_GAMEPAD( GAMEPAD_LEFT_BUMPER );
	TINY_REG_GAMEPAD( GAMEPAD_RIGHT_BUMPER );
	TINY_REG_GAMEPAD( GAMEPAD_BACK );
	TINY_REG_GAMEPAD( GAMEPAD_START );
	TINY_REG_GAMEPAD( GAMEPAD_GUIDE );
	TINY_REG_GAMEPAD( GAMEPAD_LEFT_THUMB );
	TINY_REG_GAMEPAD( GAMEPAD_RIGHT_THUMB );
	TINY_REG_GAMEPAD( GAMEPAD_DPAD_UP );
	TINY_REG_GAMEPAD( GAMEPAD_DPAD_RIGHT );
	TINY_REG_GAMEPAD( GAMEPAD_DPAD_DOWN );
	TINY_REG_GAMEPAD( GAMEPAD_DPAD_LEFT );

	TINY_REG_GAMEPAD_AXIS_1D( GAMEPAD_AXIS_LEFT_X );
	TINY_REG_GAMEPAD_AXIS_1D( GAMEPAD_AXIS_LEFT_Y );
	TINY_REG_GAMEPAD_AXIS_1D( GAMEPAD_AXIS_RIGHT_X );
	TINY_REG_GAMEPAD_AXIS_1D( GAMEPAD_AXIS_RIGHT_Y );
	TINY_REG_GAMEPAD_AXIS_2D( GAMEPAD_AXIS_LEFT_TRIGGER );
	TINY_REG_GAMEPAD_AXIS_2D( GAMEPAD_AXIS_RIGHT_TRIGGER );

	tm_dll TinyInputKeys ConvertKey( tiny_int glfw_key );

};

