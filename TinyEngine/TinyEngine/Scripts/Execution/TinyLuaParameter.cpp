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
 * @creation : 09/02/2024
 * @version  : 2024.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyLuaParameter::TinyLuaParameter( )
	: Type{ TL_TYPE_NONE },
	Value{ nullptr }
{ }

TinyLuaParameter::TinyLuaParameter( bool& value )
	: TinyLuaParameter{ TL_TYPE_BOOL, tiny_rvalue( value ) }
{ }

TinyLuaParameter::TinyLuaParameter( tiny_int& value )
	: TinyLuaParameter{ TL_TYPE_INT, tiny_rvalue( value ) } 
{ }

TinyLuaParameter::TinyLuaParameter( tiny_uint& value )
	: TinyLuaParameter{ TL_TYPE_UINT, tiny_rvalue( value ) } 
{ }

TinyLuaParameter::TinyLuaParameter( tiny_long& value )
	: TinyLuaParameter{ TL_TYPE_LONG, tiny_rvalue( value ) } 
{ }

TinyLuaParameter::TinyLuaParameter( tiny_ulong& value )
	: TinyLuaParameter{ TL_TYPE_ULONG, tiny_rvalue( value ) } 
{ }

TinyLuaParameter::TinyLuaParameter( float& value )
	: TinyLuaParameter{ TL_TYPE_FLOAT, tiny_rvalue( value ) } 
{ }

TinyLuaParameter::TinyLuaParameter( double& value )
	: TinyLuaParameter{ TL_TYPE_DOUBLE, tiny_rvalue( value ) } 
{ }

TinyLuaParameter::TinyLuaParameter( native_pointer user_data )
	: TinyLuaParameter{ TL_TYPE_USERDATA, user_data }
{ }

TinyLuaParameter::TinyLuaParameter( tiny_pointer user_data )
	: TinyLuaParameter{ TL_TYPE_USERDATA, user_data }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyLuaParameter::TinyLuaParameter( TinyLuaTypes type, auto* data )
	: Type{ type },
	Value{ tiny_cast( data, native_pointer ) }
{ }
