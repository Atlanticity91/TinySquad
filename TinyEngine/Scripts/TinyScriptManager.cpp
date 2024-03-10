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

void TinyScriptManager::Register( const tiny_string& name, TinyLuaPrototype prototype ) {
	_context.Register( name, prototype );
}

void TinyScriptManager::UnRegister( const tiny_string& name ) {
	_context.UnRegister( name ); 
}

void TinyScriptManager::SetGlobal( const tiny_string& name, c_pointer value ) {
	_context.SetGlobal( name, value );
}

void TinyScriptManager::SetGlobal( const tiny_string& name, bool value ) {
	_context.SetGlobal( name, value );
}

void TinyScriptManager::SetGlobal( const tiny_string& name, tiny_int value ) {
	_context.SetGlobal( name, value );
}
	
void TinyScriptManager::SetGlobal( const tiny_string& name, tiny_uint value ) {
	_context.SetGlobal( name, value );
}
	
void TinyScriptManager::SetGlobal( const tiny_string& name, tiny_long value ) {
	_context.SetGlobal( name, value );
}

void TinyScriptManager::SetGlobal( const tiny_string& name, tiny_ulong value ) {
	_context.SetGlobal( name, value );
}
	
void TinyScriptManager::SetGlobal( const tiny_string& name, float value ) {
	_context.SetGlobal( name, value );
}
	
void TinyScriptManager::SetGlobal( const tiny_string& name, double value ) {
	_context.SetGlobal( name, value );
}
	
void TinyScriptManager::SetGlobal( const tiny_string& name, const tiny_point& value ) {
	_context.SetGlobal( name, value );
}
	
void TinyScriptManager::SetGlobal( const tiny_string& name, const tiny_vec2& value ) {
	_context.SetGlobal( name, value );
}
	
void TinyScriptManager::SetGlobal( const tiny_string& name, const tiny_vec3& value ) {
	_context.SetGlobal( name, value );
}
	
void TinyScriptManager::SetGlobal( const tiny_string& name, const tiny_vec4& value ) {
	_context.SetGlobal( name, value );
}

void TinyScriptManager::SetGlobal( const tiny_string& name, const tiny_color& value ) {
	_context.SetGlobal( name, value );
}

void TinyScriptManager::RemoveGlobal( const tiny_string& name ) { 
	_context.RemoveGlobal( name ); 
}

void TinyScriptManager::Push( const TinyLuaParameter& parameter ) { 
	_context.Push( parameter );
}

bool TinyScriptManager::Pop( TinyLuaParameter& parameter ) {
	return _context.Pop( parameter );
}

bool TinyScriptManager::Execute( c_string source ) { return _context.Execute( source ); }

bool TinyScriptManager::Execute( const tiny_string& source ) { 
	return _context.Execute( source ); 
}

void TinyScriptManager::Execute( TinyGame* game, const TinyScriptExecution& execution ) {
	auto* script = tiny_cast( GetAsset( execution.Script ), TinyScriptLua* );

	if ( script )
		script->Execute( _context, execution );
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
	c_pointer asset_builder,
	TinyScriptLua& script
) {
	auto* address = tiny_cast( asset_builder, tiny_pointer );

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

bool TinyScriptManager::GetExist( const tiny_string& function_name ) const {
	return _context.GetExist( function_name );
}
