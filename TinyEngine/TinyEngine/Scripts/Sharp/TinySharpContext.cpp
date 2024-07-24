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
TinySharpContext::TinySharpContext( )
	: m_settings{ }, 
	m_instance{ }
{ }

bool TinySharpContext::Initialize( TinyFilesystem& filesystem ) {
	m_settings.CoralDirectory	 = filesystem.GetWorkingDir( );
	m_settings.MessageFilter	 = Coral::MessageLevel::All;
	m_settings.MessageCallback   = tiny_rvalue( TinySharpContext::OnMessageReceive );
	m_settings.ExceptionCallback = tiny_rvalue( TinySharpContext::OnExceptionThrow );

	return m_instance.Initialize( m_settings ) == Coral::CoralInitStatus::Success;
}

void TinySharpContext::Terminate( ) {
	m_instance.Shutdown( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinySharpContext::OnMessageReceive(
	std::string_view message, 
	Coral::MessageLevel gravity
) {
}

void TinySharpContext::OnExceptionThrow( std::string_view exception ) {
}
