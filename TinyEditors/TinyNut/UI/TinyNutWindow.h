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

#include "TinyNutUI.h"

#define _RegisterIcon( GAME, NAME, EMBEDDED, CALLBACK )\
	RegisterIcon( GAME, NAME, tiny_sizeof( EMBEDDED ), EMBEDDED, CALLBACK )

tn_class TinyNutWindow final : tiny_inherit( TinyImGuiWindow ) {

	using Icon_t = TinyNutUI::Icon;

protected:
	bool			 m_is_over;
	bool			 m_has_dockspace;
	tiny_string		 m_name;
	tiny_map<Icon_t> m_icons;

public:
	TinyNutWindow( const tiny_string& name, bool enable_dockspace );

	virtual ~TinyNutWindow( ) = default;

	void OnCreate( native_pointer user_data );

	void RegisterIcon(
		TinyNut* nut_game,
		const tiny_string& name,
		tiny_uint length,
		const tiny_ubyte* image,
		const Icon_t::Callback_t& callback
	);
	
	tiny_implement( void Tick(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	) );

	void Terminate( TinyNut* nut_game );

private:
	void Initialize( TinyNut* nut_game );

	void DrawBorder( );

	void DrawTitlebarBorder(
		float height, 
		const ImVec2& padding,
		const ImVec2& cursor
	);

	void DrawTitlebarLogo( bool is_maximized, const ImVec2& passing );

	void DrawMenubar( TinyNut* nut_game, bool is_maximized );

	void DrawTitlebarText( const ImVec2& passing );

	void DrawTitlebarIcon( 
		TinyNut* nut_game,
		const ImVec2& position,
		const tiny_string& name
	);

	void DrawTitlebar( TinyNut* nut_game, bool is_maximized );

	bool Prepare( TinyNut* nut_game, TinyWindow& window );

private:
	static void Minimize( TinyNut* nut_game );

	static void Restore( TinyNut* nut_game );

	static void Maximize( TinyNut* nut_game );

	static void Close( TinyNut* nut_game );

	static bool TitlebarHit( GLFWwindow* window );

public:
	bool GetIsTitlevarHovered( ) const;

	bool GetHasDockspace( ) const;

	const Icon_t* GetIcon( const tiny_string& alias ) const;

};
