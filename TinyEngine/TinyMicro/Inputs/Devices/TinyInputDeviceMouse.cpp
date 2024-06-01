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
	m_cursor{ },
	m_scroll{ }
{ }

void TinyInputDeviceMouse::Notify( const TinyInputNotification& notification ) {
	if ( notification.Descriptor.Type != TI_TYPE_AXIS_2D ) {
		auto& key = m_news[ notification.Descriptor.Key ];

		key.Modifier = notification.Modifiers;
		key.IsDown   = notification.Value.AsButton == TI_STATE_DOWN;
	} else if ( notification.Descriptor.Key == TIK_MOUSE_CURSOR )
		m_cursor = notification.Value.AsAxis2D;
	else if ( notification.Descriptor.Key == TIK_MOUSE_SCROLL )
		m_scroll = notification.Value.AsAxis2D;
}

bool TinyInputDeviceMouse::Evaluate( const TinyInputQuery& query ) {
	auto state = query.Descriptor.Type == TI_TYPE_BUTTON;

	if ( state ) {
		auto new_button = m_news[ query.Descriptor.Key ];
		auto old_button = m_olds[ query.Descriptor.Key ];
	
		state = ( query.Modifier == TI_MODIFIER_UNDEFINED || new_button.Modifier == query.Modifier ) &&
				query.State == ProcessButton( old_button.IsDown, new_button.IsDown );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_vec2 TinyInputDeviceMouse::GetCursor( ) const { return m_cursor; }

tiny_vec2 TinyInputDeviceMouse::GetScroll( ) const { return m_scroll; }

TinyInputValue TinyInputDeviceMouse::GetValue( const TinyInputDescriptor& descriptor ) const {
	return GetValue( descriptor.Key );
}

TinyInputValue TinyInputDeviceMouse::GetValue( TinyInputKeys key ) const {
	auto value = TinyInputValue{ };

	if ( key == TIK_MOUSE_CURSOR )
		value.AsAxis2D = m_cursor;
	else if ( key == TIK_MOUSE_SCROLL )
		value.AsAxis2D = m_scroll;
	else
		value.AsButton = ProcessButton( m_olds[ key ].IsDown, m_news[ key ].IsDown );

	return value;
}
