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

#pragma once

#include "Interop/TinyLuaEntity.h"

te_class TinyScriptManager final 
	: tiny_inherit( TinyAssetList<TA_TYPE_SCRIPT, TinyScriptLua> )
{

private:
	TinyLuaContext _context;

public:
	TinyScriptManager( );

	~TinyScriptManager( ) = default;

	bool Initialize( );

	tiny_inline void SetGlobal( const tiny_string& name, c_pointer value );

	tiny_inline void SetGlobal( const tiny_string& name, bool value );

	tiny_inline void SetGlobal( const tiny_string& name, tiny_int value );

	tiny_inline void SetGlobal( const tiny_string& name, tiny_uint value );

	tiny_inline void SetGlobal( const tiny_string& name, tiny_long value );

	tiny_inline void SetGlobal( const tiny_string& name, tiny_ulong value );

	tiny_inline void SetGlobal( const tiny_string& name, float value );

	tiny_inline void SetGlobal( const tiny_string& name, double value );

	tiny_inline void SetGlobal( const tiny_string& name, const tiny_point& value );

	tiny_inline void SetGlobal( const tiny_string& name, const tiny_vec2& value );

	tiny_inline void SetGlobal( const tiny_string& name, const tiny_vec3& value );

	tiny_inline void SetGlobal( const tiny_string& name, const tiny_vec4& value );

	tiny_inline void SetGlobal( const tiny_string& name, const tiny_color& value );

	tiny_inline void SetGlobal( const tiny_string& name, TinyLuaPrototype function );

	void Execute( const TinyLuaExecution& execution );

	void Execute( const tiny_string& function, TinyGame* game, c_pointer component );

	void Terminate( );

protected:
	tiny_implement( bool OnLoad(
		TinyGame* game,
		TinyFile& file,
		TinyScriptLua& script
	) );

	tiny_implement( bool OnCreate(
		TinyGame* game,
		c_pointer asset_builder,
		TinyScriptLua& script
	) );

	tiny_implement( void OnUnLoad( TinyGame* game, TinyScriptLua& script ) );

private:
	void GenerateInterop( );

public:
	template<typename Type>
	void SetGlobal( const tiny_string& name, Type* value ) {
		_context.SetGlobal<Type>( name, value );
	};

public:
	TinyLuaContext& GetContext( );

	tiny_inline bool GetExist( const tiny_string& name ) const;

};
