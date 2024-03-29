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
 * @creation : 29/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyNutUI.h"

tiny_nut_class TinyNutContext final {

private:
	VkDescriptorPool _local_pools;
	ImGuiContext*	 _imgui;

public:
	TinyNutContext( );

	~TinyNutContext( ) = default;

	bool Create( TinyNut* nut_game );

	void Prepare( TinyNut* nut_game );

	void Flush( TinyNut* nut_game );

	void Terminate( TinyNut* nut_game );

private:
	bool CreateImGuiPools( TinyGraphicManager& graphics );

	bool CreateImGuiContext( TinyWindow& window, TinyGraphicManager& graphics );

	void SetTheme( );

public:
	ImGuiContext* GetContext( );

};
