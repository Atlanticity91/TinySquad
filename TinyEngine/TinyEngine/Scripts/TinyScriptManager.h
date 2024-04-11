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

#define TinyLuaGameVar "TinyGame"

te_class TinyScriptManager final : tiny_inherit( TinyAssetContainer<TinyScriptLua> ) {

private:
	TinyLuaContext _context;

public:
	TinyScriptManager( );

	~TinyScriptManager( ) = default;

	bool Initialize( );

	tiny_implement( bool Create(
		TinyGame* game,
		const tiny_string& alias,
		const c_pointer builder
	) );

	tiny_implement( bool Load(
		TinyGame* game,
		const tiny_string& alias,
		TinyFile& file
	) );

	tiny_inline void Register( const tiny_string& name, TinyLuaPrototype prototype );

	tiny_inline void UnRegister( const tiny_string& name );

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

	tiny_inline void RemoveGlobal( const tiny_string& name );

	tiny_inline void Push( const TinyLuaParameter& parameter );

	tiny_inline bool Pop( TinyLuaParameter& parameter );

	tiny_inline bool Execute( c_string source );

	tiny_inline bool Execute( const tiny_string& source );

	void Execute( TinyGame* game, const TinyScriptExecution& execution );

	void Terminate( );

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

public:
	template<typename Type>
	Type GetGlobal( const tiny_string& name ) {
		return _context.GetGlobal<Type>( name );
	};

};
