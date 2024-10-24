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
 * @creation : 02/08/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyDebugTabAssets.h"

te_class TinyDebugTabCommon final : tiny_inherit( TinyImGuiTab ) {

public:
	TinyDebugTabCommon( );

	~TinyDebugTabCommon( ) = default;

	tiny_implement( void OnCreate( native_pointer user_data ) );

protected:
	tiny_implement( void OnTick(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	) );

private:
	void DrawHardware( TinyGraphicManager& graphics );

	void DrawBoundaries( TinyGraphicManager& graphics );

	void DrawSwapchain( TinyGraphicManager& graphics );

	void DrawPasses( TinyGraphicManager& graphics );

};
