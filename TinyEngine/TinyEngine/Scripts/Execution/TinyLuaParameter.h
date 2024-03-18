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

#pragma once

#include <TinyEngine/Assets/TinyAssetManager.h>

tiny_enum( TinyLuaTypes ) {

	TL_TYPE_NONE = 0,
	TL_TYPE_BOOL,
	TL_TYPE_INT,
	TL_TYPE_UINT,
	TL_TYPE_LONG,
	TL_TYPE_ULONG,
	TL_TYPE_FLOAT,
	TL_TYPE_DOUBLE,
	TL_TYPE_USERDATA

};

te_struct TinyLuaParameter {

	TinyLuaTypes Type;
	c_pointer Value;

	TinyLuaParameter( );

	TinyLuaParameter( bool& value );

	TinyLuaParameter( tiny_int& value );

	TinyLuaParameter( tiny_uint& value );

	TinyLuaParameter( tiny_long& value );

	TinyLuaParameter( tiny_ulong& value );

	TinyLuaParameter( float& value );

	TinyLuaParameter( double& value );

	TinyLuaParameter( c_pointer user_data );

	TinyLuaParameter( tiny_pointer user_data );

private:
	TinyLuaParameter( TinyLuaTypes type, auto* data );

};
