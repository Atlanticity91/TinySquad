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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyScript::TinyScript( ) 
	: TinyScript{ TINY_NO_ENTITY }
{ }

TinyScript::TinyScript( const tiny_hash entity_hash )
	: TinyComponent{ entity_hash },
	_pre_tick{ },
	_post_tick{ }
{ }

TinyScript& TinyScript::SetPreTick(
	TinyScriptManager& scripts,
	const tiny_string& function
) {
	_pre_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPreTick(
	TinyScriptManager& scripts,
	const tiny_string& script,
	const tiny_string& function
) {
	_pre_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPreTick( TinyScriptNative native ) {
	_pre_tick.Type = TS_TYPE_NATIVE;

	return tiny_self;
}

TinyScript& TinyScript::SetPostTick(
	TinyScriptManager& scripts,
	const tiny_string& function
) {
	_post_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPostTick(
	TinyScriptManager& scripts,
	const tiny_string& script,
	const tiny_string& function
) {
	_post_tick.Type = TS_TYPE_LUA;

	return tiny_self;
}

TinyScript& TinyScript::SetPostTick( TinyScriptNative native ) {
	_post_tick.Type   = TS_TYPE_NATIVE;
	_post_tick.Native = native;

	return tiny_self;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyScript::GetHasPreTick( ) const {
	auto state = false;

	switch ( _pre_tick.Type ) {
		case TS_TYPE_NATIVE : state = _pre_tick.Native != nullptr;   break;
		case TS_TYPE_LUA	: state = _pre_tick.Asset.GetIsValid( ); break;

		default: break;
	}
	
	return state;
}

bool TinyScript::GetHasPostTick( ) const {
	auto state = false;

	switch ( _post_tick.Type ) {
		case TS_TYPE_NATIVE : state = _post_tick.Native != nullptr;   break;
		case TS_TYPE_LUA	: state = _post_tick.Asset.GetIsValid( ); break;

		default: break;
	}

	return state;
}

TinyScriptMetadata& TinyScript::GetPreTick( ) { return _pre_tick; }

TinyScriptMetadata& TinyScript::GetPostTick( ) { return _post_tick; }
