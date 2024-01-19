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
 * @creation : 17/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Framework/Sound/TinySound_System.h>

enum TinyScriptTypes { 

	TS_TYPE_UNDEFINED = 0,
	TS_TYPE_NATIVE,
	TS_TYPE_LUA,

};

typedef bool ( *TinyScriptNative )( TinyGame*, TinyEngine&, class TinyScript& );

struct TinyScriptMetadata { 

	TinyScriptTypes Type	= TS_TYPE_UNDEFINED;
	TinyAsset Asset{};
	tiny_string Function    = "";
	TinyScriptNative Native = nullptr;

};

TINY_FRAMEWORK_COMP( TinyScript ) {

private:
	TinyScriptMetadata _pre_tick;
	TinyScriptMetadata _post_tick;

public:
	TinyScript( );

	TinyScript( const tiny_hash entity_hash );

	~TinyScript( ) = default;

	TinyScript& SetPreTick(
		class TinyScriptManager& scripts, 
		const tiny_string& function
	);

	TinyScript& SetPreTick(
		class TinyScriptManager& scripts,
		const tiny_string& script,
		const tiny_string& function
	);

	TinyScript& SetPreTick( TinyScriptNative native );

	TinyScript& SetPostTick(
		class TinyScriptManager& scripts,
		const tiny_string& function
	);

	TinyScript& SetPostTick(
		class TinyScriptManager& scripts,
		const tiny_string& script,
		const tiny_string& function
	);

	TinyScript& SetPostTick( TinyScriptNative native );

public:
	TINY_COMP_NAME( TinyScript );

	bool GetHasPreTick( ) const;

	bool GetHasPostTick( ) const;

	TinyScriptMetadata& GetPreTick( );

	TinyScriptMetadata& GetPostTick( );

};
