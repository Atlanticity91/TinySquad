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
 * @creation : 19/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Tools/Categories/TinyToolManager.h>

te_class TinyToolCommon final : tiny_inherit( TinyToolCategory ) {

public:
	TinyToolCommon( );

	~TinyToolCommon( ) = default;

protected:
	tiny_implement( void OnTick( TinyGame* game, TinyToolbox& toolbox ) );

private:
	void DrawHardware( TinyGraphicManager& graphics );

	void DrawBoundaries( TinyGraphicManager& graphics );

	void DrawSwapchain( TinyGraphicManager& graphics );

	void DrawPasses( TinyGraphicManager& graphics );

};
