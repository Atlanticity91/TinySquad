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
	: TinyAssetContainer{ },
	_context{ }
{ }

bool TinyScriptManager::Initialize( ) {
	auto state = _context.Create( );

	if ( state )
		GenerateInterop( );

	return state;
}

bool TinyScriptManager::Create(
	TinyGame* game,
	const tiny_string& alias,
	const native_pointer builder
) {

	auto* builder_ = tiny_cast( builder, tiny_pointer );
	auto& script   = Emplace( alias );

	return script.Create( _context, builder_ );
}

bool TinyScriptManager::Load(
	TinyGame* game,
	const tiny_string& alias,
	TinyFile& file
) {
	auto& script = Emplace( alias );

	return script.Create( _context, file );
}

void TinyScriptManager::Register( const tiny_string& name, TinyLuaPrototype prototype ) {
	_context.Register( name, prototype );
}

void TinyScriptManager::UnRegister( const tiny_string& name ) {
	_context.UnRegister( name ); 
}

void TinyScriptManager::SetGlobal( const tiny_string& name, native_pointer value ) {
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

bool TinyScriptManager::Execute( native_string source ) { return _context.Execute( source ); }

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
