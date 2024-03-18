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

#include "TinyInputDevice.h"

tm_struct TinyInputButtonMeta {

	TinyInputModifier Modifier;
	bool IsDown;

};

tm_class TinyInputDeviceKeyboard final : tiny_inherit( TinyInputDevice<TinyInputButtonMeta, TIK_KEY_COUNT> ) {

public:
	TinyInputDeviceKeyboard( );

	~TinyInputDeviceKeyboard( ) = default;

	tiny_implement( void Notify( const TinyInputNotification& notification ) );

	tiny_implement( bool Evaluate( const TinyInputQuery& query ) );

public:
	tiny_implement( TinyInputValue GetValue( const TinyInputDescriptor& descriptor ) const );

	tiny_implement( TinyInputValue GetValue( TinyInputKeys key ) const );

};
