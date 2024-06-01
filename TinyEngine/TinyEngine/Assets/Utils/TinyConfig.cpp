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
	_application{ false, 1280, 720 },
	_archives{ },
	_start_scene{ }
{ }

void TinyConfig::SetDimensions( const tiny_uint width, const tiny_uint height ) {
	_application.Width  = width;
	_application.Height = height;
}

void TinyConfig::AddArchive( const std::string& archive ) {
	if ( !archive.empty( ) )
		_archives.emplace_back( archive );
}

bool TinyConfig::Load( TinyFilesystem& filesystem, TinyFile& file ) {
	auto header = TinyAssetHeader{ };

	file.Read( header );

	auto state = header.GetIsAsset( _type );

	if ( state ) {
		auto developper = filesystem.GetDeveloper( );

		file.Read( developper );
		file.Read( _application.IsFullScreen );
		file.Read( _application.Width );
		file.Read( _application.Height );
		file.Read( _application.Icon.Width );
		file.Read( _application.Icon.Height );

		auto length = _application.Icon.Width * _application.Icon.Height * 4;

		if ( length > 0 ) {
			tiny_allocate( _application.Icon.Pixels, length );

			file.Read( length, _application.Icon.Pixels );
		}

		file.Read( _archives );
		file.Read( _start_scene );
	}

	return state;
}

void TinyConfig::Save( TinyFilesystem& filesystem, TinyFile& file ) {
	auto developper = tiny_uint{ };
	auto header		= TinyAssetHeader{ _type };

	file.Write( header );
	file.Write( developper );
	file.Seek( developper );
	file.Write( _application.IsFullScreen );
	file.Write( _application.Width );
	file.Write( _application.Height );
	file.Write( _application.Icon.Width );
	file.Write( _application.Icon.Height );
	
	if ( _application.Icon.Pixels ) {
		auto length = _application.Icon.Width* _application.Icon.Height * 4;

		file.Write( length, _application.Icon.Pixels );
	}

	file.Write( _archives );
	file.Write( _start_scene );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const TinyAppConfig& TinyConfig::GetAppConfig( ) const { return _application; }

const tiny_list<std::string>& TinyConfig::GetArchives( ) const { return _archives; }

const tiny_string TinyConfig::GetStartScene( ) const { return tiny_string{ _start_scene }; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyConfig::operator const TinyAppConfig& ( ) const { return GetAppConfig( ); }
