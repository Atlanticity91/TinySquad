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

#include "TinyInputDeviceKeyboard.h"

tm_class TinyInputDeviceMouse final : tiny_inherit( TinyInputDevice<TinyInputButtonMeta, TIK_MOUSE_COUNT> ) {

private:
	tiny_vec2 m_cursor;
	tiny_vec2 m_scroll;

public:
	TinyInputDeviceMouse( );

	~TinyInputDeviceMouse( ) = default;

	tiny_implement( void Notify( const TinyInputNotification& notification ) );

	tiny_implement( bool Evaluate( const TinyInputQuery& query ) );

public:
	tiny_vec2 GetCursor( ) const;

	tiny_vec2 GetScroll( ) const;

	tiny_implement( TinyInputValue GetValue( const TinyInputDescriptor& descriptor ) const );

	tiny_implement( TinyInputValue GetValue( TinyInputKeys key ) const );

};
