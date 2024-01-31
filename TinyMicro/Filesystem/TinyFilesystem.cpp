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
 * @creation : 12/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyFilesystem::TinyFilesystem( )
	: _work_dir{ },
	_game_dir{ },
	_save_dir{ },
	_dev_dir{ },
	_game{ },
	_cache{ },
	_dialog_path{ "" }
{ }

bool TinyFilesystem::Initialize( const TinyWindow& window ) {
	auto title = window.GetTitle( ).as_string( );
	auto state = GenerateGameDir( title );

	if ( state ) {
		_work_dir = Tiny::GetWorkingDir( );
		_save_dir = _game_dir + "Saves\\";
		_dev_dir  = _game_dir + "Dev\\";

		if ( !GetDirExist( _save_dir ) )
			CreateDir( _save_dir );

		_game	  = _game_dir + title + ".tinygame";
		_cache	  = _game_dir + title + ".tinycache";
	}

	return state;
}

bool TinyFilesystem::CreateDir( const tiny_string& path ) {
	return path.is_valid( ) && Tiny::CreateDir( path.get( ) );
}

bool TinyFilesystem::RemoveDir( const tiny_string& path ) {
	return path.is_valid( ) && Tiny::RemoveDir( path.get( ) );
}

bool TinyFilesystem::OpenDialog(
	Tiny::DialogTypes type,
	const tiny_string& filters,
	tiny_string& path
) {
	auto* _filters   = filters.as_chars( );
	auto* path_str   = _dialog_path.as_chars( );
	auto path_length = _dialog_path.length( );
	auto state		 = Tiny::OpenDialog( type, _dev_dir, _filters, path_length, path_str );

	if ( state )
		path = path_str;

	return state;
}

TinyFile TinyFilesystem::OpenFile( const tiny_string& path, Tiny::FileAccesses access ) {
	auto file = TinyFile{ };

	if ( path.is_valid( ) ) {
		auto handle = Tiny::FileOpen( path.get( ), access );

		file = handle;
	}

	return file;
}

bool TinyFilesystem::RemoveFile( const tiny_string& path ) {
	return path.is_valid( ) && Tiny::RemoveFile( path.get( ) );
}

bool TinyFilesystem::Dump( const tiny_string& path, const tiny_string& text ) {
	auto file  = OpenFile( path, Tiny::TF_ACCESS_WRITE );
	auto state = file.GetIsValid( );

	if ( state )
		state = file.Write( text.length( ), text.as_chars( ) ) > 0;

	return state;
}

void TinyFilesystem::Terminate( ) { }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyFilesystem::GenerateGameDir( const std::string& title ) {
	auto state = false;

	_game_dir  = Tiny::GetDocumentDir( );
	_game_dir += "TinySquadStudio\\";

	state = GetDirExist( _game_dir ) || CreateDir( _game_dir );

	if ( state ) {
		_game_dir += title + "\\";

		state = GetDirExist( _game_dir ) || CreateDir( _game_dir );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_string TinyFilesystem::GetWorkingDir( ) const { return _work_dir; }

tiny_string TinyFilesystem::GetGameDir( ) const { return _game_dir; }

tiny_string TinyFilesystem::GetSaveDir( ) const { return _save_dir; }

tiny_string TinyFilesystem::GetDevDir( ) const { return _dev_dir; }

tiny_string TinyFilesystem::GetConfigPath( ) const { return _game; }

tiny_string TinyFilesystem::GetCachePath( ) const { return _cache; }

bool TinyFilesystem::GetDirExist( const tiny_string& path ) const {
	return path.is_valid( ) && Tiny::GetIsDir( path.get( ) );
}

bool TinyFilesystem::GetFileExist( const tiny_string& path ) const {
	return path.is_valid( ) && !Tiny::GetIsDir( path.get( ) );
}

tiny_list<Tiny::FileEntry> TinyFilesystem::GetEntries( const tiny_string& path ) const {
	auto entries = tiny_list<Tiny::FileEntry>{ };
	auto entry   = Tiny::FindEntry( path.get( ) );
	
	while ( entry.has_value( ) ) {
		entries.emplace_back( entry.value( ) );

		entry = Tiny::NextEntry( );
	}

	return entries;
}

bool TinyFilesystem::GetIsFile(
	const tiny_string& path, 
	const tiny_string& extension 
) const {
	auto file_ext = GetFileExtension( path );

	return file_ext == extension;
}

bool TinyFilesystem::GetIsFile(
	const tiny_string& path, 
	tiny_init<tiny_string> extensions 
) const {
	auto state = extensions.size( ) > 0;

	if ( state ) {
		auto file_ext = GetFileExtension( path );

		for ( auto& extension : extensions ) {
			state = file_ext.equal( extension );

			if ( state )
				break;
		}
	}

	return state;
}

bool TinyFilesystem::GetIsAssetFile( const tiny_string& path ) const {
	return GetIsFile( path, TINY_ASSET_EXT );
}

bool TinyFilesystem::GetIsArchiveFile( const tiny_string& path ) const {
	return GetIsFile( path, TINY_ARCHIVE_EXT );
}

std::string TinyFilesystem::GetFilePath( const tiny_string& path ) const {
	auto _path  = std::string{ path.get( ) };
	auto offset = _path.find_last_of( '\\' );

	return _path.substr( 0, offset );
}

std::string TinyFilesystem::GetFileName( const tiny_string& path ) const {
	return path.make_string( '\\', '.' );
}

tiny_string TinyFilesystem::GetFileExtension( const tiny_string& path ) const {
	auto char_id = path.length( );

	while ( char_id-- > 0 && path[ char_id ] != '.' );

	return tiny_string{ path.as_chars( ) + ( char_id + 1 ) };
}

tiny_string TinyFilesystem::GetFileFullName( const tiny_string& path ) const {
	auto char_id = path.length( );

	while ( char_id-- > 0 && path[ char_id ] != '\\' );

	return tiny_string{ path.as_chars( ) + ( char_id + 1 ) };
}

TinyPathInformation TinyFilesystem::GetInformation( const tiny_string& path ) const {
	auto path_info = TinyPathInformation{ };
	
	path_info.Full		= path;
	path_info.Extension = GetFileExtension( path );
	path_info.Path		= GetFilePath( path );
	path_info.Name		= GetFileName( path );

	return path_info;
}

std::string TinyFilesystem::ConvertToAsset( const tiny_string& path ) const {
	auto new_path = std::string{ path.get( ) };
	auto delim	  = path.length( );

	while ( delim-- > 0 && path[ delim ] != '.' );
	
	new_path.erase( tiny_cast( delim + 1, size_t ), tiny_cast( path.length( ) - delim, size_t ) );
	new_path.append( TINY_ASSET_EXT );

	return new_path;
}
