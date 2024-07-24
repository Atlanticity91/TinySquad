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

#include "TinyToolWindow.h"

te_class TinyToolWindowManager final {

private:
	tiny_map<TinyToolWindow*> m_windows;

public:
	TinyToolWindowManager( );

	~TinyToolWindowManager( ) = default;

	void Show( const tiny_string& name );

	void Hide( const tiny_string& name );

	void Delete( TinyGame* game, TinyToolbox& toolbox, const tiny_string& name );

	void Tick( TinyGame*, TinyToolbox& toolbox );

public:
	template<typename Window>
		requires tiny_is_child_of( Window, TinyToolWindow )
	void Create( TinyGame* game, TinyToolbox& toolbox, bool is_visible ) {
		auto* window = new Window{ is_visible };

		if ( window ) {
			auto name = window->GetName( );

			if ( !m_windows.find( name ) )
				m_windows.emplace( name, window );
		}
	};

public:
	TinyToolWindow* Get( const tiny_string& name ) const;

};
