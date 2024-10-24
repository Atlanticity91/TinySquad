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

#include "TinyImGuiWindow.h"

tm_class TinyImGuiWindowManager final {

private:
	bool m_show_exemples;
	tiny_map<TinyImGuiWindow*> m_windows;

public:
	TinyImGuiWindowManager( );

	~TinyImGuiWindowManager( ) = default;

	void ShowExemples( );

	void HideExemples( );

	void Show( const tiny_string& alias, native_pointer user_data );

	void Hide( const tiny_string& alias, native_pointer user_data );

	void Toggle( const tiny_string& alias, native_pointer user_data );

	void Delete( const tiny_string& alias, native_pointer user_data );

	void Tick( 
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	);

	void Terminate( native_pointer user_data );

public:
	template<typename Window, typename... Args>
		requires ( tiny_is_child_of( Window, TinyImGuiWindow ) )
	void Create( native_pointer user_data, Args&... args ) {
		auto* window = new Window( args... );

		if ( window ) {
			auto name = window->GetName( );

			if ( !GetHas( name ) ) {
				window->OnCreate( user_data );

				m_windows.emplace( name, window );
			} else
				delete window;
		}
	};

public:
	bool GetIsExemplesVisivle( ) const;

	bool GetHas( const tiny_string& alias ) const;

	bool GetExist( const tiny_uint window_id ) const;

	TinyImGuiWindow* Get( const tiny_string& alias ) const;

	TinyImGuiWindow* At( const tiny_uint window_id ) const;

};
