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

	bool ImportAudioWav(
		TinyGame* game,
		TinyFile& file,
		const TinyPathInformation& path_info
	) {
		auto builder = TinyCueBuilder{ };
		auto state = false;
		auto riff = TinyRiffChunck{ };

		if (
			file.Read( riff ) &&
			riff.RIFF == TINY_CUE_RIFF &&
			riff.Type == TINY_CUE_WAVE
		) {
			auto chunk_id = tiny_cast( 0, tiny_uint );

			if ( file.Read( chunk_id ) ) {
				if ( chunk_id == TINY_CUE_JUNK ) {
					file.Seek( 32 );
					file.Read( chunk_id );
				}

				if ( chunk_id == TINY_CUE_FMT ) {
					file.Read( chunk_id );
					file.Read( builder.Format.wFormatTag );
					file.Read( builder.Format.nChannels );
					file.Read( builder.Format.nSamplesPerSec );
					file.Read( builder.Format.nAvgBytesPerSec );
					file.Read( builder.Format.nBlockAlign );
					file.Read( builder.Format.wBitsPerSample );

					builder.Format.cbSize = 0;

					file.Read( chunk_id );
				}

				if ( chunk_id == TINY_CUE_DATA && file.Read( builder.Data ) )
					state = ExportAudio( game, file, tiny_rvalue( builder ) );
			}
		}

		return state;
	}
	
	bool ImportAudioMp3(
		TinyGame* game,
		TinyFile& file,
		const TinyPathInformation& path_info
	) {
		return false;
	}
	
	bool ExportAudio(
		TinyGame* game,
		TinyFile& file,
		const c_pointer builder
	) {
		if ( builder ) {
			auto* builder_ = tiny_cast( builder, TinyCueBuilder* );

			file.Write( TinyAssetHeader{ TA_TYPE_CUE } );
			file.Write( builder_->Format );
			file.Write( builder_->Context );
			file.Write( builder_->Data );
		}

		return builder;
	}

};
