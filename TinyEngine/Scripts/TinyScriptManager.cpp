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
	: _context{ }
{ }

bool TinyScriptManager::Initialize( ) {
	auto state = _context.Create( );

	if ( state )
		GenerateInterop( );

	return state;
}

void TinyScriptManager::Terminate( ) { _context.Terminate( ); }

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
		state = script.Create( _context, file );

	return state;
}

bool TinyScriptManager::OnCreate(
	TinyGame* game,
	c_ptr asset_builder,
	TinyScriptLua& script
) {
	auto* address = tiny_cast( asset_builder, tiny_ptr );

	return script.Create( _context, address );
}

void TinyScriptManager::OnUnLoad( TinyGame* game, TinyScriptLua& script ) {
	script.Terminate( _context ); 
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyScriptManager::GenerateInterop( ) {
	TinyLua::Point::Register( _context );
	//TinyLua::Vec2::Register( _context );
	//TinyLua::Vec3::Register( _context );
	//TinyLua::Vec4::Register( _context );
	TinyLua::Color::Register( _context );
	TinyLua::Engine::Register( _context );
	//TinyLua::Entity::Register( _context );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyLuaContext& TinyScriptManager::GetContext( ) { return _context; }
