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

bool TinyArchiveContainer::Load( TinyGame* game, const tiny_string& asset_name ) {
	auto asset_hash = tiny_hash{ asset_name };
	auto entry_id   = tiny_cast( 0, tiny_uint );
	auto state		= false;

	if ( _entries.find( asset_hash, entry_id ) ) {
		auto& entry     = _entries.at( entry_id );
		auto* archive   = tiny_cast( GetAsset( entry.Archive ), TinyArchive* );
		auto& assets    = game->GetAssets( );
		auto* container = assets.GetContainer( entry.Type );

		if ( container ) {
			auto file = archive->Access( game, entry.Offset );

			if ( file )
				state = container->Load( game, asset_name, file );
		}
	}

	return state;
}
