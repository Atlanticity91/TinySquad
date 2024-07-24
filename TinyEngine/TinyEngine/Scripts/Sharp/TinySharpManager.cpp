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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinySharpManager::TinySharpManager( ) 
	: m_context{ },
	m_assemblies{ }
{
}

bool TinySharpManager::Initialize( TinyFilesystem& filesystem, TinyWindow& window ) {
	return m_context.Initialize( filesystem );
}

bool TinySharpManager::LoadAssembly( const std::string& path ) {
	return LoadAssembly( "", path );
}

bool TinySharpManager::LoadAssembly( const tiny_string& alias, const std::string& path ) {
	return false;
}

void TinySharpManager::UnLoadAssembly( const tiny_string& alias ) {
}

void TinySharpManager::Terminate( TinyFilesystem& filesystem, TinyWindow& window ) {
	m_assemblies.Terminate( m_context );
	m_context.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinySharpContext& TinySharpManager::GetContext( ) { return m_context; }

TinySharpAssemblyManager& TinySharpManager::GetAssemblies( ) { return m_assemblies; }
