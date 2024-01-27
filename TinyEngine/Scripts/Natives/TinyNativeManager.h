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
 * @creation : 23/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Scripts/Lua/Interop/TinyLuaEntity.h>

typedef std::function<bool( TinyGame*, c_pointer )> TinyScriptNative;

te_class TinyNativeManager final {

private:
	tiny_map<TinyScriptNative> _natives;

public:
	TinyNativeManager( );

	~TinyNativeManager( ) = default;

	void Register( const tiny_string& name, TinyScriptNative script );

	bool Execute( TinyGame* game, const tiny_string& name, c_pointer instigator );

public:
	bool GetExist( const tiny_string& name ) const;

};
