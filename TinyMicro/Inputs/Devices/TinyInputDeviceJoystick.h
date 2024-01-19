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

#include "TinyInputDeviceMouse.h"

#define TINY_JOYSTICK_BUTTONS 14
#define TINY_JOYSTICK_AXIS 6

tm_struct TinyInputJoystickMeta {

	bool Buttons[ TINY_JOYSTICK_BUTTONS ];
	float Axis[ TINY_JOYSTICK_AXIS ];

};

tm_struct TinyInputJoystick {

	tiny_uint Underlaying;
	tiny_string Name;
	tiny_uint AxisCount;
	tiny_uint ButtonCount;
	tiny_vec2 DeadZone;

};

tm_class TinyInputDeviceJoystick final {

private:
	bool				  _is_present;
	tiny_uint			  _joystick;
	tiny_vec2			  _deadzones;
	TinyInputJoystickMeta _news;
	TinyInputJoystickMeta _olds;

public:
	TinyInputDeviceJoystick( );

	~TinyInputDeviceJoystick( ) = default;

	bool Evaluate( const TinyInputQuery& query );

	void Tick( );

private:
	bool PeekJoystick( );

	void ProcessDeadzone( );

public:
	std::optional<TinyInputJoystick> Get( ) const;

	TinyInputValue GetValue( const TinyInputDescriptor& descriptor ) const;

	TinyInputValue GetValue( TinyInputKeys key ) const;

private:
	TinyInputStates ProcessButton( bool old_state, bool new_state ) const;

};
