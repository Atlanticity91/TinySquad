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

	bool ImportTexture2D(
		TinyGame* game,
		TinyFile& file,
		const TinyPathInformation& path_info
	) {
		auto builder = TinyTexture2DBuilder{ };
		auto img_w   = tiny_cast( 0, tiny_int );
		auto img_h   = tiny_cast( 0, tiny_int );
		auto img_c   = tiny_cast( 0, tiny_int );
		auto state   = false;

		builder.Texels = stbi_load_from_memory( nullptr, 0, tiny_rvalue( img_w ), tiny_rvalue( img_h ), tiny_rvalue( img_c ), 4 );

		if ( builder.Texels ) {
			builder.Properties.Type   = TGT_TYPE_TEXTURE_2D;
			builder.Properties.Width  = tiny_cast( img_w, tiny_uint );
			builder.Properties.Height = tiny_cast( img_h, tiny_uint );
			builder.Size			  = tiny_cast( img_w * img_h * 4, tiny_uint );
			builder.Rows			  = 1;
			builder.Columns			  = 1;

			auto& filesystem = game->GetFilesystem( );
			auto path		 = filesystem.CreatePath( path_info.Name, TINY_ASSET_EXT );
			auto file		 = filesystem.OpenFile( path, Tiny::TF_ACCESS_WRITE );

			state = ExportTexture2D( game, file, tiny_rvalue( builder ) );
		}

		return state;
	}
	
	bool ExportTexture2D(
		TinyGame* game,
		TinyFile& file,
		const c_pointer builder
	) {
		auto* builder_ = tiny_cast( builder, TinyTexture2DBuilder* );
		auto state	   = builder != nullptr;

		if ( state ) {
			file.Write( TinyAssetHeader{ TA_TYPE_TEXTURE_2D } );
			file.Write( builder_->Rows );
			file.Write( builder_->Columns );
			file.Write( builder_->Properties );
			file.Write( builder_->Size );

			if ( builder_->Texels ) {
				file.Write( builder_->Size, builder_->Texels );

				if ( !builder_->IsUserDefined )
					stbi_image_free( builder_->Texels );
			}
		}

		return state;
	}
	
	bool ExportCubemap(
		TinyGame* game,
		TinyFile& file,
		const c_pointer builder
	) {
		return false;
	}
	
	bool ExportAtlas(
		TinyGame* game,
		TinyFile& file,
		const c_pointer builder
	) {
		return false;
	}
	
	bool ExportLut(
		TinyGame* game,
		TinyFile& file,
		const c_pointer builder
	) {
		return false;
	}
	
	bool ExportAnimation2D(
		TinyGame* game,
		TinyFile& file,
		const c_pointer builder
	) {
		return false;
	}

};
