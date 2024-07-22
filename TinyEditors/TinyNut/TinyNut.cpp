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

#include <TinyNut/__tiny_nut_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNut::TinyNut( const tiny_string& title )
	: TinyNut{ title, false }
{ }

TinyNut::TinyNut( const tiny_string& title, bool enable_dockspace )
	: TinyGame{ "TinySquadStudio", title, TGO_PAYSAGE_16x9, true },
	m_context{ },
	m_window{ title, enable_dockspace }
{ 
	DisableGameFolder( );
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyNut::Initialize( ) {
	auto state = false;
	
	if ( m_context.Create( this ) ) {
		auto& game_window = GetWindow( );
		auto& filesystem  = GetFilesystem( );
		auto file_dialog  = TinyFileDialog{ };
		auto file_buffer  = tiny_buffer<256>{ };
		auto* file_string = file_buffer.as_chars( );
		auto file_length  = file_buffer.length( );

		game_window.SetCallback( TWC_DRAG_AND_DROP, TinyNut::DragDropCallback );

		file_dialog.Name	= "Load Game";
		file_dialog.Path	= filesystem.GetDevDirNative( );
		file_dialog.Filters = "Tiny Game File (*.tinygame)\0*.tinygame\0";

		if ( Tiny::OpenDialog( file_dialog, file_length, file_string ) ) {
			auto game_path = file_buffer.as_string( );
			auto game_file = filesystem.OpenFile( game_path, TF_ACCESS_READ );

			state = ImportGame( filesystem, file_string, game_file );

			if ( state )
				m_window.Create( this );
		}
	}

	return state;
}

bool TinyNut::ImportGame(
	TinyFilesystem& filesystem, 
	const std::string& game_path,
	TinyFile& game_file 
) {
	auto header = TinyAssetHeader{ };
	auto state  = false;

	game_file.Read( header );

	if ( header.GetIsAsset( TA_TYPE_CONFIG ) ) {
		auto game_path_info = filesystem.GetInformation( game_path );
		auto game_developper = std::string{ };

		game_file.Read( game_developper );

		state = filesystem.SetExecutable( game_developper, game_path_info.Name );
	}

	return state;
}

void TinyNut::Tick( ) {
	m_context.Prepare( this );
	m_window.Tick( this );
	m_context.Flush( this );
}

void TinyNut::Terminate( ) {
	m_window.Terminate( this );
	m_context.Terminate( this );
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PRIVATE STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyNut::DragDropCallback( 
	GLFWwindow* handle,
	tiny_int path_count,
	native_string paths[]
) {
	auto* game = tiny_cast( glfwGetWindowUserPointer( handle ), TinyNut* );

	if ( path_count > 0 )
		game->OnDragDrop( path_count, paths );
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNutContext& TinyNut::GetNutContext( ) { return m_context; }

TinyNutWindow& TinyNut::GetNutWindow( ) { return m_window; }
