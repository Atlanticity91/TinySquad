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
 * @creation : 21/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Interop/TinyLuaEntity.h"

te_class TinyScriptManager final 
	: tiny_inherit( TinyAssetList<TA_TYPE_SCRIPT, TinyScriptLua> )
{

private:
	TinyLuaContext _context;

public:
	TinyScriptManager( );

	~TinyScriptManager( ) = default;

	bool Initialize( );

	void Terminate( );

protected:
	tiny_implement( bool OnLoad(
		TinyGame* game,
		TinyFile& file,
		TinyScriptLua& script
	) );

	tiny_implement( bool OnCreate(
		TinyGame* game,
		c_ptr asset_builder,
		TinyScriptLua& script
	) );

	tiny_implement( void OnUnLoad( TinyGame* game, TinyScriptLua& script ) );

private:
	void GenerateInterop( );

public:
	TinyLuaContext& GetContext( );

};
