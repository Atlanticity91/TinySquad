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
TinyAssetImportManager::TinyAssetImportManager( )
	: m_extensions{ },
	m_types{ TA_TYPE_COUNT },
	m_converters{ }
{ }

void TinyAssetImportManager::Initialize( ) {
	RegisterExtensions( );
	RegisterTypes( );
}

void TinyAssetImportManager::Register( const tiny_uint type, const tiny_uint converter_id ) {
	if ( converter_id < m_converters.size( ) ) {
		if ( type < m_types.size( ) )
			m_types[ type ] = converter_id;
		else if ( type < m_types.size( ) + 1 )
			m_types.emplace_back( converter_id );
	}
}

void TinyAssetImportManager::Register(
	const tiny_uint type,
	const TinyAssetConverter& converter
) {
	if ( converter.Import && converter.Export ) {
		auto converter_id = m_converters.size( );

		m_converters.emplace_back( converter );

		if ( type < m_types.size( ) )
			m_types[ type ] = converter_id;
		else if ( type < m_types.size( ) + 1 )
			m_types.emplace_back( converter_id );
	}
}

void TinyAssetImportManager::Register( 
	tiny_init<tiny_string> extensions, 
	const tiny_uint converter_id 
) { 
	if ( converter_id < m_converters.size( ) ) {
		for ( auto& extension : extensions ) {
			if ( !m_extensions.find( extension ) )
				m_extensions.emplace( extension, converter_id );
		}
	}
}

void TinyAssetImportManager::Register(
	tiny_init<tiny_string> extensions,
	const TinyAssetConverter& converter
) { 
	if ( converter.Import && converter.Export ) {
		auto converter_id = m_converters.size( );

		m_converters.emplace_back( converter );

		Register( extensions, converter_id );
	}
}

bool TinyAssetImportManager::Import( 
	TinyGame* game, 
	TinyFile* file,
	const TinyPathInformation& path_info 
) {
	auto extension_id = tiny_cast( 0, tiny_uint );
	auto state		  = m_extensions.find( path_info.Extension, extension_id );

	if ( state ) {
		auto converter_id = m_extensions.at( extension_id );
		auto& converter   = m_converters[ converter_id ];

		state = tiny_cast( converter.Import, bool );

		if ( state )
			state = std::invoke( converter.Import, game, file, path_info );
	}

	return state;
}

bool TinyAssetImportManager::Export(
	TinyGame* game,
	const tiny_uint type,
	const tiny_string& alias,
	const native_pointer builder
) {
	auto state = false;

	if ( type < m_types.size( ) && alias.get_is_valid( ) && builder ) {
		auto converter_id = m_types[ type ];
		auto& filesystem  = game->GetFilesystem( );
		auto& converter   = m_converters[ converter_id ];
		auto path		  = filesystem.CreatePath( TP_TYPE_DEV, alias, "tinyasset" );
		auto file		  = filesystem.OpenFile( { path }, TF_ACCESS_BINARY_WRITE );

		state = tiny_cast( converter.Export, bool );

		if ( state ) 
			state = std::invoke( converter.Export, game, tiny_rvalue( file ), builder );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyAssetImportManager::RegisterExtensions( ) {
	Register( 
		{
			"png",
			"jpg",
			"tga",
			"jpeg"
		},
		{ 
			TinyImport::ImportTexture2D,
			TinyImport::ExportTexture2D
		}
	);
	Register(
		{
			"glsl",
			"vert",
			"frag",
			"geom"
		},
		{
			TinyImport::ImportShaderGLSL,
			TinyImport::ExportShader
		}
	);
	Register( { "hlsl" }, { TinyImport::ImportShaderHLSL, TinyImport::ExportShader } );
	Register( { "lua"  }, { TinyImport::ImportScript	, TinyImport::ExportScript } );
	Register( { "wav"  }, { TinyImport::ImportAudioWav	, TinyImport::ExportAudio  } ); 
	Register( { "mp3"  }, { TinyImport::ImportAudioMp3	, TinyImport::ExportAudio  } );
	Register( { "yaml" }, { TinyImport::ImportYaml		, TinyImport::ExportYaml   } );
	Register( { "ttf"  }, { TinyImport::ImportFont		, TinyImport::ExportFont   } );
}

void TinyAssetImportManager::RegisterTypes( ) {
	Register( TA_TYPE_TEXTURE_2D	 , 0								 );
	Register( TA_TYPE_TEXTURE_CUBEMAP, { TinyImport::ExportCubemap	   } );
	Register( TA_TYPE_TEXTURE_ATLAS	 , { TinyImport::ExportAtlas	   } );
	Register( TA_TYPE_TEXTURE_LUT	 , { TinyImport::ExportLut		   } );
	Register( TA_TYPE_ANIMATION_2D	 , { TinyImport::ExportAnimation2D } );
	Register( TA_TYPE_FONT			 , 7								 );
	Register( TA_TYPE_SHADER		 , 1								 );
	Register( TA_TYPE_MATERIAL		 , { TinyImport::ExportMaterial    } );
	Register( TA_TYPE_CUE			 , 4								 );
	Register( TA_TYPE_SANPLES		 , 4								 );
	Register( TA_TYPE_SCRIPT		 , 3								 );
}
