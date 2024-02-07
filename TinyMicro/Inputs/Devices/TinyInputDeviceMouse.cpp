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
TinyInputDeviceMouse::TinyInputDeviceMouse( )
	: TinyInputDevice{ },
	_cursor{ },
	_scroll{ }
{ }

void TinyInputDeviceMouse::Notify( const TinyInputNotification& notification ) {
	if ( notification.Descriptor.Type != TI_TYPE_AXIS_2D ) {
		auto& key = _news[ notification.Descriptor.Key ];

		key.Modifier = notification.Modifiers;
		key.IsDown   = notification.Value.AsButton == TI_STATE_DOWN;
	} else if ( notification.Descriptor.Key == TIK_MOUSE_CURSOR )
		_cursor = notification.Value.AsAxis2D;
	else if ( notification.Descriptor.Key == TIK_MOUSE_SCROLL )
		_scroll = notification.Value.AsAxis2D;
}

bool TinyInputDeviceMouse::Evaluate( const TinyInputQuery& query ) {
	auto state = query.Descriptor.Type == TI_TYPE_BUTTON;

	if ( state ) {
		auto new_button = _news[ query.Descriptor.Key ];
		auto old_button = _olds[ query.Descriptor.Key ];
	
		state = ( query.Modifier == TI_MODIFIER_UNDEFINED || new_button.Modifier == query.Modifier ) &&
				query.State == ProcessButton( old_button.IsDown, new_button.IsDown );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_vec2 TinyInputDeviceMouse::GetCursor( ) const { return _cursor; }

tiny_vec2 TinyInputDeviceMouse::GetScroll( ) const { return _scroll; }

TinyInputValue TinyInputDeviceMouse::GetValue( const TinyInputDescriptor& descriptor ) const {
	return GetValue( descriptor.Key );
}

TinyInputValue TinyInputDeviceMouse::GetValue( TinyInputKeys key ) const {
	auto value = TinyInputValue{ };

	if ( key == TIK_MOUSE_CURSOR )
		value.AsAxis2D = _cursor;
	else if ( key == TIK_MOUSE_SCROLL )
		value.AsAxis2D = _scroll;
	else
		value.AsButton = ProcessButton( _olds[ key ].IsDown, _news[ key ].IsDown );

	return value;
}
