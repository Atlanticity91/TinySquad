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

template<typename Tool, typename... Args>
concept tiny_tool_has_open =
	tiny_is_child_of( Tool, TinyNutTool ) &&
	requires( Tool t, TinyNut* nut_game, Args&... args ) 
{
		{ t.Open( nut_game, args... ) } -> std::same_as<bool>;
};

template<typename Tool, typename... Args>
concept tiny_tool_has_close =
	tiny_is_child_of( Tool, TinyNutTool ) &&
	requires( Tool t, TinyNut * nut_game, Args&... args ) 
{
		{ t.Close( nut_game, args... ) } -> std::same_as<bool>;
};

tn_class TinyNut : tiny_inherit( TinyGame ) {

	friend class TinyNutWindow;

private:
	bool m_has_dockspace;
	tiny_string m_name;

public:
	TinyNut( const tiny_string& title );

	TinyNut( const tiny_string& title, bool enable_dockspace );

	virtual ~TinyNut( ) = default;

	tiny_virtual( void OnDragDrop( tiny_int path_count, native_string drop_paths[] ) );

public:
	template<typename Tool, typename... Args>
		requires ( tiny_is_child_of( Tool, TinyNutTool ) )
	void RegisterTool( ) { 
		auto& imgui = GetImGui( );

		imgui.Create<Tool>( this );
	};

	template<typename Tool, typename... Args>
		requires ( tiny_tool_has_open<Tool, Args...> )
	bool Open( const tiny_string& name, Args&... args ) {
		auto* tool = GetTool<Tool>( name );
		auto state = false;

		if ( tool != nullptr )
			state = tool->Open( this, args... );

		return state;
	};

	template<typename Tool, typename... Args>
		requires ( tiny_tool_has_close<Tool, Args...> )
	void Close( const tiny_string& name, Args&... args ) {
		auto* tool = GetTool<Tool>( name );

		if ( tool != nullptr )
			tool->Close( this, args... );
	};

protected:
	tiny_implement( bool Initialize( ) );

	virtual bool ImportGame( 
		TinyFilesystem& filesystem, 
		const std::string& game_path, 
		TinyFile& file 
	);

	bool ImportGameDialog( );

	tiny_no_implement( void SetupBundles( TinyGraphicManager& graphics ) );

	tiny_no_implement( void LoadInterop( TinyLuaContext& lua_context ) );

	tiny_no_implement( void LoadContent( TinyAssetManager& assets ) );

	tiny_no_implement( void LoadECS( TinyECS& ecs ) );

	tiny_abstract( void TickMenubar( ) );

	tiny_abstract( void TickUI( ) );

	tiny_implement( void Terminate( ) );

private:
	static void DragDropCallback( 
		GLFWwindow* handle,
		tiny_int path_count, 
		native_string paths[] 
	);

public:
	tiny_inline TinyImGuiManager& GetImGui( );

	TinyNutWindow& GetNutWindow( );

public:
	template<typename Tool>
		requires ( tiny_is_child_of( Tool, TinyNutTool ) )
	Tool* GetTool( const tiny_string& name ) {
		auto& imgui = GetImGui( );

		return imgui.GetWindowAs<Tool>( name );
	};

};
