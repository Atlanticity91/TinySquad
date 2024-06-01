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
TinyConfig::TinyConfig( )
	: TinyAsset{ TA_TYPE_CONFIG },
	m_application{ false, 1280, 720 },
	m_archives{ },
	m_start_scene{ }
{ }

void TinyConfig::SetDimensions( const tiny_uint width, const tiny_uint height ) {
	m_application.Width  = width;
	m_application.Height = height;
}

void TinyConfig::AddArchive( const std::string& archive ) {
	if ( !archive.empty( ) )
		m_archives.emplace_back( archive );
}

bool TinyConfig::Load( TinyFilesystem& filesystem, TinyFile& file ) {
	auto header = TinyAssetHeader{ };

	file.Read( header );

	auto state = header.GetIsAsset( m_type );

	if ( state ) {
		auto developper = filesystem.GetDeveloper( );

		file.Read( developper );
		file.Read( m_application.IsFullScreen );
		file.Read( m_application.Width );
		file.Read( m_application.Height );
		file.Read( m_application.Icon.Width );
		file.Read( m_application.Icon.Height );

		auto length = m_application.Icon.Width * m_application.Icon.Height * 4;

		if ( length > 0 ) {
			tiny_allocate( m_application.Icon.Pixels, length );

			file.Read( length, m_application.Icon.Pixels );
		}

		file.Read( m_archives );
		file.Read( m_start_scene );
	}

	return state;
}

void TinyConfig::Save( TinyFilesystem& filesystem, TinyFile& file ) {
	auto developper = tiny_uint{ };
	auto header		= TinyAssetHeader{ m_type };

	file.Write( header );
	file.Write( developper );
	file.Seek( developper );
	file.Write( m_application.IsFullScreen );
	file.Write( m_application.Width );
	file.Write( m_application.Height );
	file.Write( m_application.Icon.Width );
	file.Write( m_application.Icon.Height );
	
	if ( m_application.Icon.Pixels ) {
		auto length = m_application.Icon.Width* m_application.Icon.Height * 4;

		file.Write( length, m_application.Icon.Pixels );
	}

	file.Write( m_archives );
	file.Write( m_start_scene );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const TinyAppConfig& TinyConfig::GetAppConfig( ) const { return m_application; }

const tiny_list<std::string>& TinyConfig::GetArchives( ) const { return m_archives; }

const tiny_string TinyConfig::GetStartScene( ) const { return tiny_string{ m_start_scene }; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyConfig::operator const TinyAppConfig& ( ) const { return GetAppConfig( ); }
