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

	TIM_UNDEFINED = 0,
	TIM_SHIFT	  = 1 << 0,
	TIM_CTRL	  = 1 << 1,
	TIM_ALT		  = 1 << 2,
	TIM_SUPER	  = 1 << 3,
	TIM_CAPS_LOCK = 1 << 4,
	TIM_NUMS_LOCK = 1 << 5

};

tiny_enum( TinyInputStates ) {

	TIS_PRESSED = 0,
	TIS_RELEASED,
	TIS_DOWN,
	TIS_UP

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
