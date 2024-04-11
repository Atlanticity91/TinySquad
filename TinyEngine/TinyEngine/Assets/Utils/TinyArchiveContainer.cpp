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
 * @creation : 09/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyArchiveContainer::TinyArchiveContainer( )
	: TinyAssetContainer{ },
	_entries{ }
{ }

bool TinyArchiveContainer::Create(
	TinyGame* game,
	const tiny_string& alias,
	const c_pointer builder
) {
	return false;
}

bool TinyArchiveContainer::Load(
	TinyGame* game,
	const tiny_string& alias,
	TinyFile& file
) {
	return false;
}

bool TinyArchiveContainer::Load( TinyGame* game, const tiny_string& asset_name ) {
	auto entry_id = tiny_cast( 0, tiny_uint );
	auto state    = false;
	auto hash	  = tiny_hash{ asset_name };

	if ( _entries.find( hash, entry_id ) ) {
		auto& entry_node = _entries.node( entry_id );
		auto& entry		 = entry_node.Data;
		auto* archive	 = tiny_cast( GetAsset( entry.Archive ), TinyArchive* );
		auto& assets	 = game->GetAssets( );
		auto* container  = assets.GetContainer( entry.Type );

		if ( container ) {
			auto file = archive->Access( game, entry.Offset );

			if ( file )
				state = container->Load( game, { entry_node.String }, file );
		}
	}

	return state;
}

bool TinyArchiveContainer::Load( TinyGame* game, const TinyAssetHandle& asset_handle ) {
	auto entry_id = tiny_cast( 0, tiny_uint );
	auto state	  = false;

	if ( _entries.find( asset_handle, entry_id ) ) {
		auto& entry_node = _entries.node( entry_id );
		auto& entry		 = entry_node.Data;

		if ( entry.Type == asset_handle.Type ) {
			auto* archive   = tiny_cast( GetAsset( entry.Archive ), TinyArchive* );
			auto& assets	= game->GetAssets( );
			auto* container = assets.GetContainer( entry.Type );

			if ( container ) {
				auto file = archive->Access( game, entry.Offset );

				if ( file )
					state = container->Load( game, { entry_node.String }, file );
			}
		}
	}

	return state;
}
