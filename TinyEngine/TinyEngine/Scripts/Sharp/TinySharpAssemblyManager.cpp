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
TinySharpAssemblyManager::TinySharpAssemblyManager( )
	: m_assemblies{ }
{
}

void TinySharpAssemblyManager::Terminate( TinySharpContext& context ) {
	for ( auto& assemnly : m_assemblies )
		assemnly.Data.Terminate( context );

	m_assemblies.clear( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinySharpAssembly* TinySharpAssemblyManager::GetAssembly( const tiny_string& alias ) const {
	auto assembly_id = tiny_cast( 0, tiny_uint );
	auto assembly    = tiny_cast( nullptr, TinySharpAssembly* );

	if ( m_assemblies.find( alias, assembly_id ) )
		assembly = tiny_cast( tiny_rvalue( m_assemblies.at( assembly_id ) ), TinySharpAssembly* );

	return assembly;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinySharpAssembly* TinySharpAssemblyManager::operator[]( const tiny_string& alias ) const {
	return GetAssembly( alias );
}
