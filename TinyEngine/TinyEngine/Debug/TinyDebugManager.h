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

#include "Tabs/TinyDebugTabManager.h"

te_class TinyDebugManager final {

private:
	TinyImGuiManager m_imgui;

public:
	TinyDebugManager( );

	~TinyDebugManager( ) = default;

	bool Initialize(
		TinyWindow& window,
		TinyGraphicManager& graphics,
		TinyGame* game
	);

	void Tick(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		TinyGame* game
	);

	void Terminate( TinyGraphicManager& graphics, TinyGame* game );

public:
	TinyImGuiManager& GetImGui( );

	TinyImGuizmo& GetGuizmo( );

};
