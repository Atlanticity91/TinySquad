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
 * @creation : 29/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/ImGui/Windows/TinyImGuiWindowManager.h>

tm_class TinyImGuiTab {

protected:
	tiny_string m_name;

public:
	TinyImGuiTab( );

	TinyImGuiTab( const tiny_string& name );

	virtual ~TinyImGuiTab( ) = default;

	tiny_virtual( void OnCreate( native_pointer user_data ) );

	virtual bool Tick( 
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	);

protected:
	tiny_virtual( void OnTick(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	) );

public:
	const tiny_string& GetName( ) const;

};
