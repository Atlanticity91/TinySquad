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
 * @creation : 19/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Tools/Editors/TinyToolLua.h>

te_class TinyToolContent final  : tiny_inherit( TinyToolCategory ) {

	typedef native_string ( *AssetTypeToString )( tiny_uint );

private:
	bool _has_changed;
	tiny_uint _type_count;
	AssetTypeToString _type_to_string;
	tiny_hash _to_remove;
	tiny_buffer<256> _import_path;

public:
	TinyToolContent( );

	~TinyToolContent( ) = default;

	tiny_implement( void Create( TinyGame* game, TinyToolbox& toolbox ) );

protected:
	tiny_implement( void OnTick( TinyGame* game, TinyToolbox& toolbox ) );

private:
	static native_string TypeToString( tiny_uint type );

};
