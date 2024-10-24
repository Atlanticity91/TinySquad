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

#include "TinyImGui.h"

tm_class TinyImGuiManager {

private:
	TinyImGuiContext m_context;
	TinyImGuiBackend m_backend;
	TinyImGuiFontManager m_font_manager;
	TinyImGuiTheme m_theme_manager;
	TinyImGuiWindowManager m_window_manager;
	
public:
	TinyImGuiManager( );

	virtual ~TinyImGuiManager( ) = default;

	bool Initialize(
		TinyWindow& window,
		TinyGraphicManager& graphics,
		const TinyImGuiSpecification& specification,
		native_pointer user_data 
	);

	tiny_inline void Show( );

	tiny_inline void Hide( );

	tiny_inline void Toggle( );

	tiny_inline void ShowExemples( );

	tiny_inline void HideExemples( );

	tiny_inline bool LoadFont(
		TinyFilesystem& filesystem,
		TinyGraphicManager& graphics,
		const TinyImGuiFont& font
	);

	tiny_inline bool LoadFonts(
		TinyFilesystem& filesystem,
		TinyGraphicManager& graphics,
		tiny_init<TinyImGuiFont> fonts
	);

	tiny_inline bool AddFont(
		const tiny_string& alias,
		tiny_int length,
		const tiny_uint* data,
		float size
	);

	tiny_inline bool CreateFont(
		const tiny_string& name,
		float size,
		tiny_init<TinyImGuiFontEmbedded> fonts
	);

	tiny_inline void SetFont( const tiny_string& name );

	tiny_inline void ShowWindow( const tiny_string& alias, native_pointer user_data );

	tiny_inline void HideWindow( const tiny_string& alias, native_pointer user_data );

	tiny_inline void ToggleWindow( const tiny_string& alias, native_pointer user_data );

	tiny_inline void DeleteWindow( const tiny_string& alias, native_pointer user_data );

	void DockSpace( const tiny_string& name );

	void Tick( 
		TinyGraphicManager& graphics, 
		TinyInputManager& inputs, 
		native_pointer user_data 
	);

	void Terminate( 
		TinyGraphicManager& graphics,
		native_pointer user_data 
	);

public:
	template<typename Window, typename... Args>
		requires ( tiny_is_child_of( Window, TinyImGuiWindow ) )
	void Create( native_pointer user_data, Args&... args ) {
		m_window_manager.Create<Window, Args...>( user_data, args... );
	};

public:
	tiny_inline bool GetIsVisible( ) const;

	bool GetIsExemplesVisivle( ) const;

	TinyImGuiContext& GetContext( );

	TinyImGuiBackend& GetBackend( );

	TinyImGuiFontManager& GetFontManager( );

	TinyImGuiTheme& GetTheme( );

	TinyImGuiWindowManager& GetWindowManager( );

	tiny_inline bool GetHasWindow( const tiny_string& alias ) const;

	tiny_inline bool GetWindowExist( const tiny_uint window_id ) const;

	tiny_inline TinyImGuiWindow* GetWindow( const tiny_string& alias ) const;

	tiny_inline TinyImGuiWindow* GetWindow( const tiny_uint window_id ) const;

public:
	template<typename Window>
		requires ( tiny_is_child_of( Window, TinyImGuiWindow ) )
	Window* GetWindowAs( const tiny_string& alias ) {
		return tiny_cast( GetWindow( alias ), Window* );
	};

	template<typename Window>
		requires ( tiny_is_child_of( Window, TinyImGuiWindow ) )
	Window* GetWindowAs( const tiny_uint window_id ) {
		return tiny_cast( GetWindow( window_id ), Window* );
	};

public:
	operator ImGuiContext* ( ) const;

};
