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
namespace TinyImport {

	bool ImportScript(
		TinyGame* game,
		TinyFile* file,
		const TinyPathInformation& path_info
	) {
		auto storage = tiny_storage{ TS_TYPE_HEAP };
		auto length  = file->GetSize( );
		auto state   = tiny_allocate( storage, length );

		if ( state ) {
			auto* data = storage.GetAddress( );

			if ( file->ReadAll( length, data ) ) {
				auto& filesystem = game->GetFilesystem( );
				auto builder	 = tiny_string{ tiny_cast( length, tiny_uint ), data };
				auto path		 = filesystem.CreatePath( TP_TYPE_DEV, path_info.Name, TINY_ASSET_EXT );
				auto file_		 = filesystem.OpenFile( path, TF_ACCESS_WRITE );

				state = TinyImport::ExportScript( game, tiny_rvalue( file_ ), tiny_rvalue( builder ) );
			}

			tiny_deallocate( storage );
		}

		return state;
	}

	bool ExportScript(
		TinyGame* game,
		TinyFile* file,
		const native_pointer builder
	) {
		auto* builder_ = tiny_cast( builder, tiny_string* );
		auto state	   = false;

		if ( builder ) {
			auto length = builder_->length( );

			file->Write( TinyAssetHeader{ TA_TYPE_SCRIPT } );
			file->Write( length );

			state = file->Write( length, builder_->as_chars( ) ) == length;
		}

		return state;
	}

};
