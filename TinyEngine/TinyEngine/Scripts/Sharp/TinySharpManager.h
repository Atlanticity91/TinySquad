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
 * @creation : 23/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinySharpAssemblyManager.h"

te_class TinySharpManager final : tiny_inherit( ITinyManager ) {

private:
	TinySharpContext m_context;
	TinySharpAssemblyManager m_assemblies;

public:
	TinySharpManager( );

	~TinySharpManager( ) = default;

	tiny_implement( bool Initialize( TinyFilesystem& filesystem, TinyWindow& window ) );

	bool LoadAssembly( const std::string& path );

	bool LoadAssembly( const tiny_string& alias, const std::string& path );

	void UnLoadAssembly( const tiny_string& alias );

	tiny_implement( void Terminate( TinyFilesystem& filesystem, TinyWindow& window ) );

public:
	TinySharpContext& GetContext( );

	TinySharpAssemblyManager& GetAssemblies( );

};
