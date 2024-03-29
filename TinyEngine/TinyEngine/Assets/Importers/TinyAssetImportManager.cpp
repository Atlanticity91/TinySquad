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
 * @creation : 09/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAssetImportManager::TinyAssetImportManager( ) 
	: _importers{ },
	_exporters{ }
{ }

#define _taim_imp( EXT, TYPE, IMPORTER ) _importers.emplace( #EXT, { TYPE, IMPORTER } )
#define _taim_exp( TYPE, EXPORTER ) _exporters[ tiny_cast( TYPE, tiny_uint ) ] = EXPORTER

void TinyAssetImportManager::Initialize( ) {
	Register( 
		{
			"png",
			"jpg",
			"tga",
			"jpeg",
		},
		{ TA_TYPE_TEXTURE_2D, ImportTexture2D }
	);

	_taim_imp( dds, TA_TYPE_TEXTURE_2D, ImportTextureDDS );

	_taim_exp( TA_TYPE_TEXTURE_2D, ExportTexture2D );
	_taim_exp( TA_TYPE_TEXTURE_3D, ExportTexture3D );

	_taim_imp( ttf, TA_TYPE_FONT, ImportFont );
	_taim_exp( TA_TYPE_FONT, ExportFont );

	_taim_imp( spv,  TA_TYPE_SHADER, ImportGLSL );
	_taim_imp( vert, TA_TYPE_SHADER, ImportGLSL );
	_taim_imp( frag, TA_TYPE_SHADER, ImportGLSL );
	_taim_imp( geom, TA_TYPE_SHADER, ImportGLSL );
	_taim_imp( comp, TA_TYPE_SHADER, ImportGLSL );
	_taim_imp( glsl, TA_TYPE_SHADER, ImportGLSL );
	_taim_imp( hlsl, TA_TYPE_SHADER, ImportHLSL );
	_taim_exp( TA_TYPE_SHADER, ExportSPV );

	_taim_exp( TA_TYPE_MATERIAL, ExportMaterial );

	_taim_imp( lua, TA_TYPE_SCRIPT, ImportLua );
	_taim_exp( TA_TYPE_SCRIPT, ExportLua );

	_taim_imp( wav, TA_TYPE_CUE, ImportWav );
	_taim_exp( TA_TYPE_CUE, ExportWav );
}

void TinyAssetImportManager::Register(
	tiny_init<tiny_string> extensions,
	const TinyAssetImporter& importer
) {
	for ( auto& ext : extensions )
		_importers.emplace( ext, importer );
}

bool TinyAssetImportManager::Import(
	TinyGame* game,
	const TinyPathInformation& path,
	tiny_storage& file,
	tiny_storage& storage
) {
	auto importer_id = tiny_cast( 0, tiny_uint );
	auto state		 = _importers.find( path.Extension, importer_id );

	if ( state ) {
		auto importer = _importers.at( importer_id );

		state = std::invoke( importer.Signature, game, path, file, storage );
	}

	return state;
}

bool TinyAssetImportManager::Export(
	TinyGame* game,
	tiny_uint type,
	TinyFile& file,
	c_pointer& asset 
) {
	auto exporter = _exporters[ type ];
	auto state	  = false;

	if ( exporter )
		state = std::invoke( exporter, game, file, asset );

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAssetImportManager::ImportTexture2D(
	TinyGame* game,
	const TinyPathInformation& path,
	tiny_storage& file,
	tiny_storage& storage
){
	auto state = tiny_make_storage( storage, TinyTexture2DBuilder  );

	if ( state ) {
		auto* builder = storage.As<TinyTexture2DBuilder>( );
		auto* buffer  = file.As<tiny_pointer_base>( );
		auto img_w	  = tiny_cast( 0, tiny_int );
		auto img_h	  = tiny_cast( 0, tiny_int );
		auto img_c    = tiny_cast( 0, tiny_int );

		builder->Texels = stbi_load_from_memory( buffer, tiny_cast( file.Capacity, tiny_int ), tiny_rvalue( img_w ), tiny_rvalue( img_h ), tiny_rvalue( img_c ), 4 );

		state = builder->Texels != nullptr;

		if ( state ) {
			builder->Properties.Type   = TGT_TYPE_TEXTURE_2D;
			builder->Properties.Width  = tiny_cast( img_w, tiny_uint );
			builder->Properties.Height = tiny_cast( img_h, tiny_uint );
			builder->Size			   = tiny_cast( img_w * img_h * 4, tiny_uint );
			builder->Rows			   = 1;
			builder->Columns		   = 1;
		}
	}

	return state;
}

bool TinyAssetImportManager::ImportTextureDDS(
	TinyGame* game,
	const TinyPathInformation& path,
	tiny_storage& file,
	tiny_storage& storage
) {
	return false;
}

bool TinyAssetImportManager::ExportTexture2D( TinyGame* game, TinyFile& file, c_pointer& asset ) {
	auto* builder = tiny_cast( asset, TinyTexture2DBuilder* );
	auto state    = builder != nullptr;

	if ( state ) {
		file.Write( TinyAssetHeader{ TA_TYPE_TEXTURE_2D } );
		file.Write( builder->Rows );
		file.Write( builder->Columns );
		file.Write( builder->Properties );

		if ( builder->Texels ) {
			file.Write( builder->Size );
			file.Write( builder->Size, builder->Texels );

			if ( !builder->IsUserDefined )
				stbi_image_free( builder->Texels );
		}
	}

	return state;
}

bool TinyAssetImportManager::ExportTexture3D( TinyGame* game, TinyFile& file, c_pointer& asset ) {
	auto* builder = tiny_cast( asset, TinyTexture3DBuilder* );
	auto state    = builder != nullptr && builder->Texels;

	if ( state ) {
		file.Write( TinyAssetHeader{ TA_TYPE_TEXTURE_3D } );
		file.Write( builder->Rows );
		file.Write( builder->Columns );
		file.Write( builder->Properties );

		if ( builder->Texels ) {
			file.Write( builder->Size );
			file.Write( builder->Size, builder->Texels );

			if ( !builder->IsUserDefined )
				stbi_image_free( builder->Texels );
		}
	}

	return state;
}

bool TinyAssetImportManager::ImportFont(
	TinyGame* game,
	const TinyPathInformation& path,
	tiny_storage& file,
	tiny_storage& storage
) {
	auto parameters = MsdfParameters{ };
	auto bitmap = MsdfBitmap{ };
	auto atlas  = MsdfAtlas{ };
	auto msdf   = MsdfAtlasGenerator{ };
	auto* ttf   = file.As<const msdfgen::byte>( );
	auto state  = false;

	if ( msdf.Prepare( ttf, file.Capacity ) ) {
		msdf.AddCharset( 0x0020, 0x00FF );

		if ( msdf.GenerateCharset( atlas, bitmap ) ) {
			if ( tiny_make_storage2( storage, TinyFontBuilder, bitmap ) ) {
				auto* builder = tiny_get_address_as( storage, TinyFontBuilder );

				msdf.Process( parameters, atlas, builder->Bitmap );

				auto& f = game->GetFilesystem( );
				auto n = path.Name;
				auto path = f.GetDevDir( ).as_string( ) + "\\f_t_" + n + ".png";

				msdfgen::savePng( msdfgen::BitmapConstRef<uint8_t, 3>{ builder->Bitmap.Buffer.data( ), builder->Bitmap.Width, builder->Bitmap.Height }, path.c_str( ) );

				auto unicode = 0x0020;

				while ( unicode < ( 0x00FF + 1 ) ) {
					auto* glyph = atlas.Geometry.getGlyph( unicode );

					if ( glyph )
						printf( "%d : %u\n", unicode, glyph->getIndex( ) );

					unicode += 1;
				}

				/*
				const auto& fontGeometry = atlas.Geometry;
				const auto& metrics = fontGeometry.getMetrics( );

				float texelWidth  = 1.0f / bitmap.Width;
				float texelHeight = 1.0f / bitmap.Height;

				builder->Scale = 1.f / ( metrics.ascenderY - metrics.descenderY );

				for ( auto& glyph : atlas.Glyphs ) {
					double al, ab, ar, at;
					glyph.getQuadAtlasBounds( al, ab, ar, at );
					glm::vec2 texCoordMin( (float)al, (float)ab );
					glm::vec2 texCoordMax( (float)ar, (float)at );

					texCoordMin *= glm::vec2( texelWidth, texelHeight );
					texCoordMax *= glm::vec2( texelWidth, texelHeight );

					double pl, pb, pr, pt;
					glyph.getQuadPlaneBounds( pl, pb, pr, pt );
					glm::vec2 quadMin( (float)pl * builder->Scale, (float)pb * builder->Scale );
					glm::vec2 quadMax( (float)pr * builder->Scale, (float)pt * builder->Scale );

					struct TinyCharVertice {
						
						tiny_vec4 Location;
						tiny_vec2 UV;

					};

					struct TinyCharGeometry { 
						
						tiny_uint Unicode = 0;
						float Advance	  = 0.f;
						TinyCharVertice Vertices[ 4 ];

					};
					fontGeometry.getGlyph( ' ' );
					TinyCharGeometry geometry{ };
					
					geometry.Unicode = glyph.getCodepoint( );
					geometry.Advance = glyph.getAdvance( );

					geometry.Vertices[ 0 ].Location = tiny_vec4{ quadMin.x, quadMin.y, .0f, 1.f };
					geometry.Vertices[ 0 ].UV		  = texCoordMin;

					geometry.Vertices[ 1 ].Location = tiny_vec4{ quadMin.x, quadMax.y, .0f, 1.f };
					geometry.Vertices[ 1 ].UV		  = { texCoordMin.x, texCoordMax.y };

					geometry.Vertices[ 2 ].Location = tiny_vec4{ quadMax, .0f, 1.f };
					geometry.Vertices[ 2 ].UV		  = texCoordMax;

					geometry.Vertices[ 3 ].Location = tiny_vec4{ quadMax.x, quadMin.y, .0f, 1.f };
					geometry.Vertices[ 3 ].UV		  = { texCoordMax.x, texCoordMin.y };
				}
				*/
			}
		}
	}

	return state;
}

bool TinyAssetImportManager::ExportFont( TinyGame* game, TinyFile& file, c_pointer& asset ) {
	return false;
}

bool TinyAssetImportManager::ImportGLSL(
	TinyGame* game,
	const TinyPathInformation& path,
	tiny_storage& file,
	tiny_storage& storage
) {
	auto state = tiny_make_storage( storage, TinyGraphicShaderProperties );

	if ( state ) {
		auto& graphics = game->GetGraphics( );
		auto* builder  = storage.As<TinyGraphicShaderProperties>( );
		auto* source   = file.GetAddress( );
		auto context   = TinyGraphicShaderCompilationContext{ };

		context.Name   = tiny_string{ path.Name };
		context.Source = tiny_string{ source, tiny_cast( file.Capacity, tiny_uint ) };

		if ( path.Extension == "hlsl" )
			context.IsHLSL = true;

		state = graphics.CompileShader( context, tiny_lvalue( builder ) );
	}

	return state;
}

bool TinyAssetImportManager::ImportHLSL(
	TinyGame* game,
	const TinyPathInformation& path,
	tiny_storage& file,
	tiny_storage& storage
) {
	return false;
}

bool TinyAssetImportManager::ExportSPV( TinyGame* game, TinyFile& file, c_pointer& asset ) {
	auto* builder = tiny_cast( asset, TinyGraphicShaderProperties* );
	auto state	  = builder != nullptr;

	if ( state ) {
		file.Write( TinyAssetHeader{ TA_TYPE_SHADER } );
		file.Write( builder->Type );
		file.Write( builder->Entry );
		file.Write( builder->Code );
	}

	return state;
}

bool TinyAssetImportManager::ExportMaterial( TinyGame* game, TinyFile& file, c_pointer& asset ) {
	auto* builder = tiny_cast( asset, TinyMaterialBuilder* );
	auto state    = builder != nullptr;

	if ( state ) {
		auto descriptor_count = builder->Descriptors.size( );

		file.Write( TinyAssetHeader{ TA_TYPE_MATERIAL } );
		file.Write( builder->PassType );
		file.Write( builder->PassName );
		file.Write( builder->Subpass );
		file.Write( builder->ShaderStages );
		file.Write( builder->InputBinding );
		file.Write( builder->InputAttributes );
		file.Write( builder->Topology );
		file.Write( builder->Tessellation );
		file.Write( builder->DepthEnable );
		file.Write( builder->StencilEnable );
		file.Write( builder->DepthOperation );
		file.Write( builder->DepthStencilFront );
		file.Write( builder->DepthStencilBack );
		file.Write( builder->ColorBlends );
		file.Write( builder->Dynamics );
		file.Write( builder->Descriptors );
		file.Write( builder->Constants );
	}

	return state;
}

bool TinyAssetImportManager::ImportLua(
	TinyGame* game,
	const TinyPathInformation& path,
	tiny_storage& file,
	tiny_storage& storage
) {
	auto state = tiny_allocate( storage, tiny_sizeof( tiny_uint ) + file.Capacity );

	if ( state ) {
		auto* file_addr = tiny_cast( file.GetAddress( ), const c_pointer );
		auto* address   = tiny_cast( storage.GetAddress( ), tiny_pointer );

		tiny_lvalue( tiny_cast( address, tiny_uint* ) ) = tiny_cast( file.Capacity, tiny_uint );

		Tiny::Memcpy( 
			tiny_cast( file_addr, const c_pointer ),
			tiny_cast( address + tiny_sizeof( tiny_uint ), c_pointer ),
			tiny_cast( file.Capacity, tiny_uint ) 
		);
	}

	return state;
}

bool TinyAssetImportManager::ExportLua( TinyGame* game, TinyFile& file, c_pointer& asset ) {
	auto state = asset != nullptr;
	
	if ( state ) {
		auto length  = tiny_lvalue( tiny_cast( asset, tiny_uint* ) );
		auto* source = tiny_cast( tiny_cast( asset, tiny_uint* ) + 1, c_pointer );

		file.Write( TinyAssetHeader{ TA_TYPE_SCRIPT } );
		file.Write( length );
		file.Write( length, source );
	}

	return state;
}

bool TinyAssetImportManager::ImportWav(
	TinyGame* game,
	const TinyPathInformation& path,
	tiny_storage& file,
	tiny_storage& storage
) {
	auto vfile = TinyVirtualFile{ file };
	auto riff  = TinyRiffChunck{ };
	auto state = false;

	if ( 
		tiny_make_storage( storage, TinyCueBuilder ) &&
		vfile.Read( riff )							 && 
		riff.RIFF == TINY_CUE_RIFF					 &&
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

	return state;
}

bool TinyAssetImportManager::ExportWav( TinyGame* game, TinyFile& file, c_pointer& asset ) {
	auto* builder = tiny_cast( asset, TinyCueBuilder* );
	auto state    = builder != nullptr;

	if ( state ) {
		file.Write( TinyAssetHeader{ TA_TYPE_CUE } );
		file.Write( builder->Format );
		file.Write( builder->Context );
		file.Write( builder->Size );
		file.Write( builder->Size, builder->Data );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const TinyAssetImporter& TinyAssetImportManager::Get( const tiny_string& extension ) const {
	return _importers[ extension ];
}

tiny_uint TinyAssetImportManager::GetTypeOf( const tiny_string& extension ) const {
	auto type_id = tiny_cast( 0, tiny_uint );
	auto type	 = tiny_cast( TA_TYPE_UNDEFINED, tiny_uint );

	if ( _importers.find( extension, type_id ) )
		type = _importers.at( type_id ).Type;

	return type;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
const TinyAssetImporter& TinyAssetImportManager::operator[](
	const tiny_string& extension
) const {
	return Get( extension );
}
