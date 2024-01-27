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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyScriptManager::TinyScriptManager( ) 
	: _natives{ },
	_lua{ }
{ }

bool TinyScriptManager::Initialize( ) {
	auto state = _lua.Create( );

	if ( state )
		GenerateInterop( );

	return state;
}

void TinyScriptManager::Register( const tiny_string& name, TinyScriptNative script ) {
	_natives.Register( name, script );
}

bool TinyScriptManager::Execute( 
	TinyGame* game, 
	c_pointer instigator, 
	const TinyScriptContext& context
) {
	auto state = false;

	switch ( context.Type ) {
		case TS_TYPE_NATIVE : state = _natives.Execute( game, context.Name, instigator ); break;
		case TS_TYPE_LUA	: state = _lua.Execute( game, context.Name, instigator );	  break;

		default : break;
	}

	return state;
}

void TinyScriptManager::Terminate( ) { _lua.Terminate( ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyScriptManager::OnLoad(
	TinyGame* game,
	TinyFile& file,
	TinyScriptLua& script
) {
	auto header = TinyAssetHeader{ };
	auto state  = false;

	file.Read( header );

	if ( header.Type == TA_TYPE_SCRIPT )
		state = script.Create( _lua, file );

	return state;
}

bool TinyScriptManager::OnCreate(
	TinyGame* game,
	c_pointer asset_builder,
	TinyScriptLua& script
) {
	auto* address = tiny_cast( asset_builder, tiny_ptr );

	return script.Create( _lua, address );
}

void TinyScriptManager::OnUnLoad( TinyGame* game, TinyScriptLua& script ) {
	script.Terminate( _lua );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyScriptManager::GenerateInterop( ) {
	TinyLua::Point::Register( _lua );
	//TinyLua::Vec2::Register( _lua );
	//TinyLua::Vec3::Register( _lua );
	//TinyLua::Vec4::Register( _lua );
	TinyLua::Color::Register( _lua );
	TinyLua::Engine::Register( _lua );
	//TinyLua::Entity::Register( _lua );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyLuaContext& TinyScriptManager::GetLua( ) { return _lua; }

bool TinyScriptManager::GetExist( const tiny_string& name ) const {
	return _natives.GetExist( name );
}
