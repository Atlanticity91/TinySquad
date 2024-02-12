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

#include <TinyEngine/Framework/Sound2D/TinySound2D_System.h>

tiny_enum( TinyScriptTypes ) {

	TS_TYPE_NATIVE = 0,
	TS_TYPE_LUA

};

struct TinyScriptMetadata { 

	TinyScriptTypes Type = TS_TYPE_NATIVE;
	tiny_string Function = "";
	TinyAsset Asset{ TA_TYPE_SCRIPT };

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

	TinyScript& SetPreTick( const tiny_string& function );

	TinyScript& SetPostTick(
		class TinyScriptManager& scripts,
		const tiny_string& function
	);

	TinyScript& SetPostTick(
		class TinyScriptManager& scripts,
		const tiny_string& script,
		const tiny_string& function
	);

	TinyScript& SetPostTick( const tiny_string& function );

	tiny_implement( void DisplayWidget(
		TinyGame* game,
		TinyEngine& engine,
		TinyToolbox& toolbox
	) );

private:
	void DisplayMeta( TinyGame* game, c_string label, TinyScriptMetadata& metadata );

public:
	TINY_COMP_NAME( TinyScript );

	bool GetHasPreTick( ) const;

	bool GetHasPostTick( ) const;

	TinyScriptMetadata& GetPreTick( );

	TinyScriptMetadata& GetPostTick( );

};
