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
		/*
		auto vfile = TinyVirtualFile{ file };
		auto riff = TinyRiffChunck{ };
		auto state = false;

		if (
			tiny_make_storage( storage, TinyCueBuilder ) &&
			vfile.Read( riff ) &&
			riff.RIFF == TINY_CUE_RIFF &&
			riff.Type == TINY_CUE_WAVE
			) {
			auto chunk_id = tiny_cast( 0, tiny_uint );

			if ( vfile.Read( chunk_id ) ) {
				auto* builder = storage.As<TinyCueBuilder>( );

				if ( chunk_id == TINY_CUE_JUNK ) {
					vfile.Skip( 32 );
					vfile.Read( chunk_id );
				}

				if ( chunk_id == TINY_CUE_FMT ) {
					vfile.Read( chunk_id );
					vfile.Read( builder->Format.wFormatTag );
					vfile.Read( builder->Format.nChannels );
					vfile.Read( builder->Format.nSamplesPerSec );
					vfile.Read( builder->Format.nAvgBytesPerSec );
					vfile.Read( builder->Format.nBlockAlign );
					vfile.Read( builder->Format.wBitsPerSample );

					builder->Format.cbSize = 0;

					vfile.Read( chunk_id );
				}

				if ( chunk_id == TINY_CUE_DATA ) {
					vfile.Read( builder->Size );

					state = tiny_reallocate( storage, storage.Capacity + builder->Size );

					if ( state ) {
						builder = storage.As<TinyCueBuilder>( );

						builder->Data = tiny_cast( builder + 1, tiny_pointer );

						state = vfile.Read( builder->Size, builder->Data );
					}
				}
			}
		}
		*/

		auto builder = TinyCueBuilder{ };
		auto state = false;

		if ( true )
			state = ExportAudio( game, file, tiny_rvalue( builder ) );

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
			file.Write( builder_->Size );
			file.Write( builder_->Size, builder_->Data );
		}

		return builder;
	}

};
