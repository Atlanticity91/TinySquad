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

#include "Utils/TinyDefaultCompute.h"

te_class TinyToolbox final {

private:
	bool m_is_in_use;
	bool m_has_dir;
	bool m_show_exemples;
	ImGuiContext* m_imgui;
	VkDescriptorPool m_local_pools;
	tiny_map<ImFont*> m_fonts;
	TinyToolManager m_tools;
	TinyToolWindowManager m_windows;
	TinyToolboxGuizmo m_guizmo;

public:
	TinyToolbox( );

	~TinyToolbox( ) = default;

	bool Initialize( TinyGame* game );

	void Clear( );

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

	bool CreateFont(
		const tiny_string& name,
		float size,
		tiny_init<TinyToolboxFontEmbedded> fonts
	);

	void SetFont( const tiny_string& name );

	void EnableNavigation( );

	void DisableNavigation( );

	void Show( );

	void Hide( );

	void Toggle( );

	void ShowExemples( );

	tiny_inline void ShowWindow( const tiny_string& name );

	tiny_inline void HideWindow( const tiny_string& name );

	tiny_inline void ShowGuizmo2D( const tiny_hash entity_hash );

	tiny_inline void ShowGuizmo3D( const tiny_hash entity_hash );

	tiny_inline void HideGuizmo( );

	void DisplayAsset( TinyGame* game, const tiny_string& label, TinyAssetHandle& asset );

	void Tick( TinyGame* game );

	void Terminate( TinyGame* game );

public:
	template<typename Window>
		requires tiny_is_child_of( Window, TinyToolWindow )
	void Create( TinyGame* game, bool is_visible = true ) {
		m_windows.Create<Window>( game, tiny_self, is_visible );
	};

private:
	bool CreateImGui( );

	bool CreateImGuiPools( TinyGraphicManager& graphics );

	bool CreateImGuiContext( TinyWindow& window, TinyGraphicManager& graphics );

	void CreateImGuiTheme( );

	bool CreateImGuiFont( );

	void CreateSpriteShaders( 
		TinyGame* game, 
		TinyFilesystem& filesystem, 
		const std::string& dev_dir 
	);

	void CreateTextShaders( 
		TinyGame* game, 
		TinyFilesystem& filesystem, 
		const std::string& dev_dir 
	);

	void CreateDevDir( TinyGame* game );

	void Prepare( );

	void Render( TinyGame* game );

public:
	ImGuiContext* GetContext( ) const;

	TinyToolWindow* GetWindow( const tiny_string& name ) const;

	TinyToolboxGuizmo& GetGuizmo( );

	const tiny_hash GetGuizmoSelection( ) const;

public:
	template<typename Window>
		requires tiny_is_child_of( Window, TinyToolWindow )
	TinyToolWindow* GetWindowAs( const tiny_string& name ) {
		auto* window = m_windows.Get( name );

		return tiny_cast( window, Window );
	};

};
