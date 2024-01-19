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

#include "TinyInputDeviceJoystick.h"

tm_class TinyInputDeviceManager final {

private:
	TinyInputDeviceKeyboard _keyboard;
	TinyInputDeviceMouse	_mouse;
	TinyInputDeviceJoystick _joystick;

public:
	TinyInputDeviceManager( );

	~TinyInputDeviceManager( ) = default;

	void Notify( const TinyInputNotification& notification );

	bool Evaluate( const TinyInputQuery& query );

	void Tick( );

public:
	tiny_vec2 GetCursor( ) const;

	tiny_vec2 GetScroll( ) const;

	std::optional<TinyInputJoystick> GetJoystick( ) const;

	TinyInputValue GetValue( const TinyInputDescriptor& descriptor ) const;

	TinyInputValue GetValue( TinyInputDevices device, TinyInputKeys key ) const;

};
