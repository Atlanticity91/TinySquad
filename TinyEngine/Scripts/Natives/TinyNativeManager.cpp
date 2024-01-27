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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNativeManager::TinyNativeManager( )
	: _natives{ }
{ }

void TinyNativeManager::Register( const tiny_string& name, TinyScriptNative exec_script ) {
	if ( !name.is_empty( ) && exec_script && !_natives.find( name ) )
		_natives.emplace( name, exec_script );
}

bool TinyNativeManager::Execute( 
	TinyGame* game,
	const tiny_string& name,
	c_pointer instigator
) {
	auto script_id = tiny_cast( 0, tiny_uint );
	auto state = false;
	
	if ( _natives.find( name, script_id ) ) {
		auto& function = _natives.at( script_id );

		state = std::invoke( function, game, instigator );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyNativeManager::GetExist( const tiny_string& name ) const { return false; }
