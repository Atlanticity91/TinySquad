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

#include "TinyImGuiTab.h"

tm_class TinyImGuiTabManager : tiny_inherit( TinyImGuiWindow ) { 

protected:
	tiny_string m_tab_alias;
	ImGuiTabBarFlags m_tab_flags;
	tiny_uint m_current;
	tiny_map<TinyImGuiTab*> m_tabs;

public:
	TinyImGuiTabManager( );

	TinyImGuiTabManager( 
		const tiny_string& name, 
		const tiny_string& tab_alias,
		ImGuiTabBarFlags tab_flags = ImGuiTabBarFlags_None 
	);

	TinyImGuiTabManager(
		const tiny_string& name,
		bool is_visible,
		const tiny_string& tab_alias,
		ImGuiTabBarFlags tab_flags = ImGuiTabBarFlags_None
	);

	virtual ~TinyImGuiTabManager( ) = default;

	void RemoveTab( const tiny_string& name );

	tiny_implement( void Delete( native_pointer user_data ) );

protected:
	tiny_implement( void OnTick(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	) );

public:
	template<typename Tab, typename... Args>
		requires ( tiny_is_child_of( Tab, TinyImGuiTab ) )
	void AddTab( native_pointer user_data, Args&... args ) {
		auto* tab = new Tab( args... );

		if ( tab ) {
			auto& name = tab->GetName( );

			if ( !m_tabs.find( name ) ) {
				tab->OnCreate( user_data );

				m_tabs.emplace( name, tab );
			} else
				delete tab;
		}
	};

public:
	tiny_uint GetCurrentTabID( ) const;

	bool GetHasTab( const tiny_string& name ) const;

	TinyImGuiTab* GetTab( const tiny_string& name );

public:
	template<typename Tab, typename... Args>
		requires ( tiny_is_child_of( Tab, TinyImGuiTab ) )
	Tab* GetTabAs( const tiny_string& name ) { 
		return tiny_cast( GetTab( name ), Tab* );
	};

};
