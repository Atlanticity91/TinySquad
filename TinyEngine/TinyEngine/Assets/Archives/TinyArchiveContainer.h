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
 * @creation : 07/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyArchive.h"

te_struct TinyArchiveEntry {

	tiny_hash Archive{ };
	tiny_uint Type    = 0;
	tiny_ulong Offset = 0;
	
};

te_class TinyArchiveContainer final : tiny_inherit( TinyAssetContainer<TinyArchive> ) {

private:
	tiny_map<TinyArchiveEntry> _entries;

public:
	TinyArchiveContainer( );

	~TinyArchiveContainer( ) = default;

	tiny_implement( bool Create(
		TinyGame* game,
		const tiny_string& alias,
		const c_pointer builder
	) );

	tiny_implement( bool Load(
		TinyGame* game,
		const tiny_string& alias,
		TinyFile& file
	) );

	bool Load( TinyGame* game, const tiny_string& asset_name );

	bool Load( TinyGame* game, const TinyAssetHandle& asset_handle );

};
