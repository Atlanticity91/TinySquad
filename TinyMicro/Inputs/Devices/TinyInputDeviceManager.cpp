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
TinyInputDeviceManager::TinyInputDeviceManager( ) 
	: _keyboard{ },
	_mouse{ },
	_joystick{ }
{ }

void TinyInputDeviceManager::Notify( const TinyInputNotification& notification ) {
	switch ( notification.Descriptor.Device ) {
		case TID_KEYBOARD : _keyboard.Notify( notification ); break;
		case TID_MOUSE	  : _mouse.Notify( notification );	  break;

		default : break;
	}
}

bool TinyInputDeviceManager::Evaluate( const TinyInputQuery& query ) {
	auto state = false;

	switch ( query.Descriptor.Device ) { 
		case TID_KEYBOARD : state = _keyboard.Evaluate( query ); break;
		case TID_MOUSE	  : state = _mouse.Evaluate( query );	 break;
		case TID_GAMEPAD  : state = _joystick.Evaluate( query );  break;

		default : break;
	}

	return state;
}

void TinyInputDeviceManager::Tick( ) {
	_keyboard.Tick( );
	_mouse.Tick( );
	_joystick.Tick( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_vec2 TinyInputDeviceManager::GetCursor( ) const { return _mouse.GetCursor( ); }

tiny_vec2 TinyInputDeviceManager::GetScroll( ) const { return _mouse.GetScroll( ); }

std::optional<TinyInputJoystick> TinyInputDeviceManager::GetJoystick( ) const {
	return _joystick.Get( );
}

TinyInputValue TinyInputDeviceManager::GetValue( const TinyInputDescriptor& descriptor ) const {
	auto value = TinyInputValue{ };

	switch ( descriptor.Device ) {
		case TID_KEYBOARD : value = _keyboard.GetValue( descriptor ); break;
		case TID_MOUSE	  : value = _mouse.GetValue( descriptor );	  break;
		case TID_GAMEPAD  : value = _joystick.GetValue( descriptor );  break;

		default: break;
	}

	return value;
}

TinyInputValue TinyInputDeviceManager::GetValue( TinyInputDevices device, TinyInputKeys key ) const {
	auto value = TinyInputValue{ };

	switch ( device ) {
		case TID_KEYBOARD : value = _keyboard.GetValue( key ); break;
		case TID_MOUSE	  : value = _mouse.GetValue( key );	   break;
		case TID_GAMEPAD  : value = _joystick.GetValue( key );  break;

		default: break;
	}

	return value;
}
