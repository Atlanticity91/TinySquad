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

class tiny_nut_dll TinyNutWindow : public TinyToolWindow { 

protected:
	tiny_map<TinyNutIcon> _icons;

public:
	TinyNutWindow( const tiny_string& name );

	virtual ~TinyNutWindow( ) = default;

	tiny_implement( void Create( TinyGame* game, TinyToolbox& toolbox ) );

	void RegisterIcon( 
		const tiny_string& name, 
		const tiny_ubyte* icon, 
		const TinyNutIcon::Callback_t& callback 
	);

	tiny_implement( void Tick( TinyGame* game, TinyToolbox& toolbox ) );

	//tiny_implement( void Delete( TinyGame* game, TinyToolbox& toolbox ) );

protected:
	tiny_virtual( void DrawMenus( TinyGame* game ) );

private:
	void DrawBorder( );

	void DrawTitlebarBorder(
		float height, 
		const ImVec2& padding,
		const ImVec2& cursor
	);

	void DrawTitlebarLogo( bool is_maximized, const ImVec2& passing );

	void DrawTitlebarText( const ImVec2& passing );

	void DrawTitlebarIcon( 
		TinyGame* game,
		const ImVec2& offset, 
		const ImVec2& padding,
		const tiny_string& name
	);

	void DrawTitlebar( TinyGame* game, bool is_maximized );

	void DrawMenubar( TinyGame* game, bool is_maximized, bool& is_overed );

	bool Prepare( TinyGame* game, TinyWindow& window );

	void DockSpace( );

};
