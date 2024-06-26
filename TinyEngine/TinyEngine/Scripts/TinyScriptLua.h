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

#include "Execution/TinyLuaContext.h"

te_struct TinyScriptExecution {

	TinyAssetHandle Script{ TA_TYPE_SCRIPT };
	tiny_string Function = "";
	native_pointer Component  = nullptr;

};

te_class TinyScriptLua final : tiny_inherit( TinyAsset ) { 

private:
	tiny_storage		   _source;
	tiny_string			   _table;
	tiny_list<tiny_string> _functions;

public:
	TinyScriptLua( );

	~TinyScriptLua( ) = default;

	bool Create( TinyLuaContext& context, TinyFile& file );

	bool Create( TinyLuaContext& context, tiny_pointer source );

	void Execute( TinyLuaContext& context, const TinyScriptExecution& execution );

	tiny_implement( void Terminate( TinyGame* game ) );

public:
	const tiny_string& GetTable( ) const;

	const tiny_list<tiny_string>& GetFunctions( ) const;

};
