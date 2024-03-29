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
 * @creation : 26/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "UI/TinyNutWindow.h"

class tiny_nut_dll TinyNut : public TinyGame {

	friend class TinyNutWindow;

private:
	TinyNutContext _context;
	TinyNutWindow  _window;

public:
	TinyNut( const tiny_string& title );

	virtual ~TinyNut( ) = default;

protected:
	tiny_implement( bool Initialize( TinyEngine& engine ) );

	tiny_no_implement( void SetupBundles( TinyGraphicManager& graphics ) );

	tiny_no_implement( void LoadInterop( TinyLuaContext& lua_context ) );

	tiny_no_implement( void LoadContent( TinyAssetManager& assets ) );

	tiny_no_implement( void LoadECS( TinyECS& ecs ) );

	tiny_abstract( void TickMenubar( ) );

	tiny_abstract( void TickUI( ) );

	tiny_implement( void Tick( ) );

	tiny_implement( void Terminate( ) );

public:
	TinyNutContext& GetNutContext( );

	TinyNutWindow& GetNutWindow( );

};
