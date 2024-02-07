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
TinyInputDeviceKeyboard::TinyInputDeviceKeyboard( )
	: TinyInputDevice{ }
{ }

void TinyInputDeviceKeyboard::Notify( const TinyInputNotification& notification ) {
	auto& input = _news[ notification.Descriptor.Key ];

	input.Modifier = notification.Modifiers;
	input.IsDown   = notification.Value.AsButton == TI_STATE_DOWN;
}

bool TinyInputDeviceKeyboard::Evaluate( const TinyInputQuery& query ) {
	auto state = query.Descriptor.Type == TI_TYPE_BUTTON;

	if ( state ) {
		auto new_button = _news[ query.Descriptor.Key ];
		auto old_button	= _olds[ query.Descriptor.Key ];
	
		state = ( query.Modifier == TI_MODIFIER_UNDEFINED || new_button.Modifier == query.Modifier ) && 
				query.State == ProcessButton( old_button.IsDown, new_button.IsDown );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyInputValue TinyInputDeviceKeyboard::GetValue( const TinyInputDescriptor& descriptor ) const {
	return GetValue( descriptor.Key );
}

TinyInputValue TinyInputDeviceKeyboard::GetValue( TinyInputKeys key ) const {
	auto value = TinyInputValue{ };

	value.AsButton = ProcessButton( _olds[ key ].IsDown, _news[ key ].IsDown );

	return value;
}
