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

		if (
			msdf.GenerateCharset( atlas, bitmap )
		) {
			msdf.Process( parameters, atlas, bitmap );
		}

		/*
		auto* font = msdfgen::loadFontData( freetype, ttf, file.Capacity );

		if ( font ) {
			auto glyphs   = std::vector<msdf_atlas::GlyphGeometry>{ };
			auto geometry = msdf_atlas::FontGeometry{ tiny_rvalue( glyphs ) };
			auto charset  = msdf_atlas::Charset( );

			struct TinyFontCharset { 

				tiny_uint Start;
				tiny_uint Stop;

				TinyFontCharset( tiny_uint start, tiny_uint stop )
					: Start{ start },
					Stop{ stop + 1 }
				{ };

			};

			TinyFontCharset charsets[] = { { 0x0020, 0x00FF } };

			for ( auto& _charset : charsets ) {
				auto char_id = _charset.Start;

				while ( char_id < _charset.Stop )
					charset.add( char_id++ );
			}

			auto loaded = geometry.loadCharset( font, 1.0, charset );

			auto packer = msdf_atlas::TightAtlasPacker{ };

			packer.setPixelRange( 2.0 );
			packer.setMiterLimit( 1.0 );
			packer.setPadding( 0 );
			packer.setScale( 40.0 );

			state = packer.pack( glyphs.data( ), tiny_cast( glyphs.size( ), tiny_int ) ) == 0;

			if ( state ) {
				auto width  = 0;// tiny_cast( 0, tiny_int );
				auto height = 0;// tiny_cast( 0, tiny_int );
				auto scale  = packer.getScale( );

				packer.getDimensions( width, height );


				#define DEFAULT_ANGLE_THRESHOLD 3.0
				#define LCG_MULTIPLIER 6364136223846793005ull
				#define LCG_INCREMENT 1442695040888963407ull
				#define THREAD_COUNT 8

				uint64_t coloringSeed = 0;
				bool expensiveColoring = false;
				if ( expensiveColoring ) {
					msdf_atlas::Workload( [ &glyphs = glyphs, &coloringSeed ]( int i, int threadNo ) -> bool {
						unsigned long long glyphSeed = ( LCG_MULTIPLIER * ( coloringSeed ^ i ) + LCG_INCREMENT ) * !!coloringSeed;
						glyphs[ i ].edgeColoring( msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed );
						return true;
					}, glyphs.size( ) ).finish( THREAD_COUNT );
				} else {
					unsigned long long glyphSeed = coloringSeed;
					for ( msdf_atlas::GlyphGeometry& glyph : glyphs ) {
						glyphSeed *= LCG_MULTIPLIER;
						glyph.edgeColoring( msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed );
					}
				}

				msdf_atlas::ImmediateAtlasGenerator<
					float, 3, 
					msdf_atlas::msdfGenerator,
					msdf_atlas::BitmapAtlasStorage<tiny_ubyte, 3>
				> generator{ width, height };
				msdf_atlas::GeneratorAttributes attributes;

				attributes.config.overlapSupport = true;
				attributes.scanlinePass = true;

				generator.setAttributes( attributes );
				generator.setThreadCount( 2 );
				generator.generate( glyphs.data( ), tiny_cast( glyphs.size( ), tiny_int ) );

				auto bitmap = ( msdfgen::BitmapConstRef<tiny_ubyte, 3> )generator.atlasStorage( );
				
				msdfgen::savePng( bitmap, "test.png" );
			}
		}
		*/
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

		context.Name   = path.Name;
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
		file.Write( builder->Type );
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
		file.Write( descriptor_count );

		if ( descriptor_count > 0 ) {
			for ( auto& descriptor : builder->Descriptors )
				file.Write( descriptor );
		}

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
		auto* address = tiny_cast( storage.GetAddress( ), tiny_pointer );

		tiny_lvalue( tiny_cast( address, tiny_uint* ) ) = tiny_cast( file.Capacity, tiny_uint );

		Tiny::Memcpy( 
			tiny_cast( file.GetAddress( ), const c_pointer ), 
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