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
 * @creation : 11/01/2024
 * @version  : 2024.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyLuaContext.h"

te_class TinyScriptLua final { 

private:
	tiny_storage _source;

public:
	TinyScriptLua( );

	~TinyScriptLua( ) = default;

	bool Create( TinyLuaContext& context, TinyFile& file );

	bool Create( TinyLuaContext& context, tiny_ptr source );

	void Terminate( TinyLuaContext& context );

};
