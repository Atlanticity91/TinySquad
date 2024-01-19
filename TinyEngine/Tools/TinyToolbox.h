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
 * @creation : 13/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Fonts/TinyFont.h"

te_class TinyToolbox final {

private:
	bool			  _is_in_use;
	ImGuiContext*	  _imgui;
	VkDescriptorPool  _local_pools;
	tiny_map<ImFont*> _fonts;
	TinyToolManager   _tools;

public:
	TinyToolbox( );

	~TinyToolbox( ) = default;

	bool Initialize( TinyGame* game );

	bool LoadFont( 
		TinyFilesystem& filesystem, 
		TinyGraphicManager& graphics,
		const TinyToolboxFont& font 
	);

	bool LoadFonts( 
		TinyFilesystem& filesystem,
		TinyGraphicManager& graphics,
		tiny_init<TinyToolboxFont> fonts 
	);

	bool AddFont( 
		const tiny_string& alias, 
		tiny_int length, 
		const tiny_uint* data,
		float size 
	);

	void SetFont( const tiny_string& name );

	void EnableNavigation( );

	void DisableNavigation( );

	void Show( );

	void Hide( );

	void Toggle( );

	void DisplayAsset( TinyGame* game, const tiny_string& label, TinyAsset& asset );

	void Tick( TinyGame* game, TinyEngine& engine );

	void Terminate( TinyGame* game );

private:
	bool CreateImGui( );

	bool CreateImGuiPools( TinyGraphicManager& graphics );

	bool CreateImGuiContext( TinyWindow& window, TinyGraphicManager& graphics );

	void CreateImGuiTheme( );

};
