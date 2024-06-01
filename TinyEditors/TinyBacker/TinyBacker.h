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

#include <TinyNut/TinyNut.h>

struct TinyBackerArchive { 

	TinyAssetHeader Header{ };
	TinyArchiveBuilder Archive{ };

};

class TinyBacker final : tiny_inherit( TinyNut ) {

private:
	TinyImGui::DropdownContext m_dropdown;
	TinyBackerArchive m_archive;
	tiny_hash m_delete_entry;
	std::string m_import_path;

public:
	TinyBacker( );

	~TinyBacker( ) = default;

	tiny_implement( void OnDragDrop( tiny_int path_count, native_string drop_paths[] ) );

protected:
	tiny_implement( void TickMenubar( ) );

	tiny_implement( void TickUI( ) );

private:
	void LoadContent( );

	void ImportAsset( );

	tiny_inline bool ImportAsset( const std::string& path );

	void DrawEntry( tiny_uint entry_id, tiny_map_node<TinyArchiveEntryBuilder>& entry_node );

	void DrawContent( );

	void DrawPopups( );

private:
	native_string TypeToStr( const tiny_uint type ) const;

};
