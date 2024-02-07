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

#include "TinyInputDescriptor.h"

tiny_enum( TinyInputModifier ) {

	TI_MODIFIER_UNDEFINED = 0,
	TI_MODIFIER_SHIFT	  = TINY_LEFT_SHIFT( 0 ),
	TI_MODIFIER_CTRL	  = TINY_LEFT_SHIFT( 1 ),
	TI_MODIFIER_ALT		  = TINY_LEFT_SHIFT( 2 ),
	TI_MODIFIER_SUPER	  = TINY_LEFT_SHIFT( 3 ),
	TI_MODIFIER_CAPS_LOCK = TINY_LEFT_SHIFT( 4 ),
	TI_MODIFIER_NUMS_LOCK = TINY_LEFT_SHIFT( 5 )

};

tiny_enum( TinyInputStates ) {

	TI_STATE_PRESSED = 0,
	TI_STATE_RELEASED,
	TI_STATE_DOWN,
	TI_STATE_UP

};

tm_union TinyInputValue {

	TinyInputStates AsButton;
	float AsAxis1D;
	tiny_vec2 AsAxis2D;

};

tm_struct TinyInputNotification {

	TinyInputDescriptor Descriptor;
	TinyInputModifier Modifiers;
	TinyInputValue Value;

	TinyInputNotification( const TinyInputDescriptor& descriptor, tiny_uint modifiers, bool value );

	TinyInputNotification( const TinyInputDescriptor& descriptor, tiny_uint modifiers, float value );

	TinyInputNotification( const TinyInputDescriptor& descriptor, tiny_uint modifiers, const tiny_vec2& value );

};
