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
	: m_keyboard{ },
	m_mouse{ },
	m_joystick{ }
{ }

void TinyInputDeviceManager::Notify( const TinyInputNotification& notification ) {
	switch ( notification.Descriptor.Device ) {
		case TI_DEVICE_KEYBOARD : m_keyboard.Notify( notification ); break;
		case TI_DEVICE_MOUSE	: m_mouse.Notify( notification );	break;

		default : break;
	}
}

bool TinyInputDeviceManager::Evaluate( const TinyInputQuery& query ) {
	auto state = false;

	switch ( query.Descriptor.Device ) { 
		case TI_DEVICE_KEYBOARD : state = m_keyboard.Evaluate( query ); break;
		case TI_DEVICE_MOUSE	: state = m_mouse.Evaluate( query );	   break;
		case TI_DEVICE_GAMEPAD  : state = m_joystick.Evaluate( query ); break;

		default : break;
	}

	return state;
}

void TinyInputDeviceManager::Tick( ) {
	m_keyboard.Tick( );
	m_mouse.Tick( );
	m_joystick.Tick( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_vec2 TinyInputDeviceManager::GetCursor( ) const { return m_mouse.GetCursor( ); }

tiny_vec2 TinyInputDeviceManager::GetScroll( ) const { return m_mouse.GetScroll( ); }

std::optional<TinyInputJoystick> TinyInputDeviceManager::GetJoystick( ) const {
	return m_joystick.Get( );
}

TinyInputValue TinyInputDeviceManager::GetValue( const TinyInputDescriptor& descriptor ) const {
	auto value = TinyInputValue{ };

	switch ( descriptor.Device ) {
		case TI_DEVICE_KEYBOARD : value = m_keyboard.GetValue( descriptor ); break;
		case TI_DEVICE_MOUSE	: value = m_mouse.GetValue( descriptor );	break;
		case TI_DEVICE_GAMEPAD  : value = m_joystick.GetValue( descriptor ); break;

		default: break;
	}

	return value;
}

TinyInputValue TinyInputDeviceManager::GetValue( TinyInputDevices device, TinyInputKeys key ) const {
	auto value = TinyInputValue{ };

	switch ( device ) {
		case TI_DEVICE_KEYBOARD : value = m_keyboard.GetValue( key ); break;
		case TI_DEVICE_MOUSE	: value = m_mouse.GetValue( key );	 break;
		case TI_DEVICE_GAMEPAD  : value = m_joystick.GetValue( key ); break;

		default: break;
	}

	return value;
}
