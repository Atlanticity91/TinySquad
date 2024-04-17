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

#include "TinyNutContext.h"

#define _RegisterIcon( GAME, NAME, EMBEDDED, CALLBACK )\
	RegisterIcon( GAME, NAME, tiny_sizeof( EMBEDDED ), EMBEDDED, CALLBACK )

tn_class TinyNutWindow final {

	using Icon_t = TinyNutUI::Icon;

protected:
	bool			 _is_over;
	bool			 _has_dockspace;
	tiny_string		 _name;
	tiny_map<Icon_t> _icons;

public:
	TinyNutWindow( const tiny_string& name, bool enable_dockspace );

	virtual ~TinyNutWindow( ) = default;

	void Create( TinyNut* nut_game );

	void RegisterIcon(
		TinyNut* nut_game,
		const tiny_string& name,
		tiny_uint length,
		const tiny_ubyte* image,
		const Icon_t::Callback_t& callback
	);
	
	void Tick( TinyNut* nut_game );

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
		const ImVec2& offset, 
		const ImVec2& padding,
		const ImVec2& expand,
		const tiny_string& name
	);

	void DrawTitlebar( TinyNut* nut_game, bool is_maximized );

	bool Prepare( TinyNut* nut_game, TinyWindow& window );

	void DockSpace( );

private:
	static void Minimize( TinyNut* nut_game );

	static void Restore( TinyNut* nut_game );

	static void Maximize( TinyNut* nut_game );

	static void Close( TinyNut* nut_game );

	static bool TitlebarHit( GLFWwindow* window );

public:
	bool GetIsTitlevarHovered( ) const;

	bool GetHasDockspace( ) const;

};
