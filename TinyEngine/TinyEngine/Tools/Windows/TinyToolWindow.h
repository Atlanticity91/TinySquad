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
 * @creation : 28/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Tools/ToolSet/TinyToolWorld.h>

te_class TinyToolWindow {

protected:
	bool m_is_visible;
	tiny_string m_name;

public:
	TinyToolWindow( const tiny_string& name, bool is_visible );

	virtual ~TinyToolWindow( ) = default;

	tiny_virtual( void Create( TinyGame* game, TinyToolbox& toolbox ) );

	void Show( );

	void Hide( );

	virtual void Tick( TinyGame* game, TinyToolbox& toolbox );

	tiny_virtual( void Delete( TinyGame* game, TinyToolbox& toolbox ) );

protected:
	tiny_abstract( void OnRender( TinyGame* game, TinyToolbox& toolbox ) );

public:
	bool GetIsVisible( ) const;

	tiny_virtualv( true, bool GetShouldRender( ) const );

	const tiny_string& GetName( ) const;

};
