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
TinyInputNotification::TinyInputNotification( const TinyInputDescriptor& descriptor, tiny_uint modifiers, bool value )
	: Descriptor{ descriptor },
	Modifiers{ modifiers },
	Value{ }
{
	Value.AsButton = value ? TIS_DOWN : TIS_UP;
}

TinyInputNotification::TinyInputNotification( const TinyInputDescriptor& descriptor, tiny_uint modifiers, float value )
	: Descriptor{ descriptor },
	Modifiers{ modifiers },
	Value{ }
{ 
	Value.AsAxis1D = value;
}

TinyInputNotification::TinyInputNotification( const TinyInputDescriptor& descriptor, tiny_uint modifiers, const tiny_vec2& value )
	: Descriptor{ descriptor },
	Modifiers{ modifiers },
	Value{ }
{
	Value.AsAxis2D = value;
}
