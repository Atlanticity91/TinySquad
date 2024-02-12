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
 * @creation : 10/01/2024
 * @version  : 2024.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyLuaParameter.h"

te_struct TinyLuaExecution {

	tiny_string Function;
	tiny_list<TinyLuaParameter> Inputs;
	tiny_list<TinyLuaParameter> Outputs;

	TinyLuaExecution( );

	TinyLuaExecution( const tiny_string& function );

	TinyLuaExecution( const tiny_string& function, tiny_init<TinyLuaParameter> inputs );

	TinyLuaExecution( 
		const tiny_string& function,
		tiny_init<TinyLuaParameter> inputs,
		tiny_init<TinyLuaParameter> outputs
	);

};
