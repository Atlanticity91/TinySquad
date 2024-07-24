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

#include <TinyEngine/Assets/TinyAssetManager.h>
#include <TinyThirdparty/Coral/Coral.h>

te_class TinySharpContext final {

private:
	Coral::HostSettings m_settings;
	Coral::HostInstance m_instance;

public:
	TinySharpContext( );

	~TinySharpContext( ) = default;

	bool Initialize( TinyFilesystem& filesystem );

	void Terminate( );

private:
	static void OnMessageReceive( std::string_view message, Coral::MessageLevel gravity );

	static void OnExceptionThrow( std::string_view exception );

};
