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
TinyFilesystem::TinyFilesystem( const std::string& developer )
	: _developer_name{ developer },
	_work_dir{ },
	_game_dir{ },
	_save_dir{ },
	_dev_dir{ },
	_game{ },
	_cache{ },
	_dialog_path{ }
{ }

bool TinyFilesystem::Initialize( const TinyWindow& window ) {
	auto title = window.GetTitle( ).as_string( );
	auto state = GenerateGameDir( title );

	if ( state ) {
		_work_dir = Tiny::GetWorkingDir( );
		_save_dir = _game_dir + "Saves\\";
		_dev_dir  = _game_dir + "Dev\\";
		_game	  = _game_dir + title + "." + TINY_GAME_EXT;
		_cache	  = _game_dir + title + "." + TINY_CACHE_EXT;

		if ( !GetDirExist( _save_dir ) )
			CreateDir( _save_dir );
	}

	return state;
}

std::string TinyFilesystem::CreatePath(
	TinyPathTypes path_type,
	const std::string& name, 
	const tiny_string& extension 
) const {
	auto dir = GetPath( path_type );

	return dir + "\\" + name + "." + extension.as_string( );
}

std::string TinyFilesystem::CreatePath(
	TinyPathTypes path_type,
	const tiny_string& name,
	const tiny_string& extension
) const {
	auto dir = GetPath( path_type );

	return dir + "\\" + name.as_string( ) + "." + extension.as_string( );
}

std::string TinyFilesystem::ConvertTo(
	const std::string& path,
	const tiny_string& extension
) const {

	auto* ext_str = extension.get( );
	auto new_path = std::string{ path };
	auto length   = path.length( );
	auto delim	  = length;

	while ( delim-- > 0 && path[ delim ] != '.' );

	new_path.erase( delim + 1, length - delim );
	new_path.append( ext_str );

	return new_path;
}

bool TinyFilesystem::CreateDir( const std::string& path ) {
	auto* path_str = path.c_str( );

	return !path.empty( ) && Tiny::CreateDir( path_str );
}

bool TinyFilesystem::RemoveDir( const std::string& path ) {
	auto* path_str = path.c_str( );

	return !path.empty( ) && Tiny::RemoveDir( path_str );
}

bool TinyFilesystem::OpenDialog(
	TinyDialogTypes type,
	const std::string& filters,
	std::string& path
) {
	auto* _filters   = filters.c_str( );
	auto path_str   = _dialog_path.as_chars( );
	auto* dev_dir	 = _dev_dir.c_str( );
	auto path_length = _dialog_path.length( );
	auto state		 = Tiny::OpenDialog( type, dev_dir, _filters, path_length, path_str );

	if ( state )
		path = std::string{ path_str, path_length };

	return state;
}

TinyPhysicalFile TinyFilesystem::OpenFile( 
	const std::string& path, 
	TinyFileAccesses access 
) {
	auto path_ = tiny_string{ path };

	return OpenFile( path_, access );
}

TinyPhysicalFile TinyFilesystem::OpenFile(
	const tiny_string& path,
	TinyFileAccesses access
) {
	auto file = TinyPhysicalFile{ };

	if ( path.get_is_valid( ) ) {
		auto handle = Tiny::FileOpen( path, access );

		file = handle;
	}

	return file;
}

bool TinyFilesystem::RemoveFile( const std::string& path ) {
	auto path_ = tiny_string{ path };

	return RemoveFile( path_ );
}

bool TinyFilesystem::RemoveFile( const tiny_string& path ) {
	return path.get_is_valid( ) && Tiny::RemoveFile( path.get( ) );
}

bool TinyFilesystem::Dump( const std::string& path, const std::string& text ) {
	auto state  = false;
	auto path_  = tiny_string{ path };
	auto file   = OpenFile( path_, TF_ACCESS_WRITE );
	auto length = tiny_cast( text.length( ), tiny_uint );

	if ( length > 0 && file.GetIsValid( ) ) {
		auto* string = tiny_cast( text.c_str( ), const native_pointer );

		state = file.Write( length, string ) > 0;
	}

	return state;
}

bool TinyFilesystem::Dump(
	const std::string& path,
	const tiny_uint length, 
	const native_pointer data 
) {
	auto state = false;
	auto path_ = tiny_string{ path };
	auto file  = OpenFile( path_, TF_ACCESS_WRITE );

	if ( length > 0 && data && file.GetIsValid( ) )
		state = file.Write( length, data ) > 0;

	return state;
}

void TinyFilesystem::Terminate( ) { }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyFilesystem::GenerateGameDir( const std::string& title ) {
	_game_dir = Tiny::GetDocumentDir( ) + _developer_name + "\\";
	
	auto state = GetDirExist( _game_dir ) || CreateDir( _game_dir );

	if ( state ) {
		_game_dir += title + "\\";

		state = GetDirExist( _game_dir ) || CreateDir( _game_dir );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const std::string& TinyFilesystem::GetDeveloperName( ) const { return _developer_name; }

const std::string& TinyFilesystem::GetWorkingDir( ) const { return _work_dir; }

const std::string& TinyFilesystem::GetGameDir( ) const { return _game_dir; }

const std::string& TinyFilesystem::GetSaveDir( ) const { return _save_dir; }

const std::string& TinyFilesystem::GetDevDir( ) const { return _dev_dir; }

const std::string& TinyFilesystem::GetConfigPath( ) const { return _game; }

const std::string& TinyFilesystem::GetCachePath( ) const { return _cache; }

const std::string& TinyFilesystem::GetPath( const TinyPathTypes path_type ) const {
	switch ( path_type ) {
		case TP_TYPE_WORK : return _work_dir;
		case TP_TYPE_GAME : return _game_dir;
		case TP_TYPE_SAVE : return _save_dir;

		default : break;
	}

	return _dev_dir;
}

bool TinyFilesystem::GetDirExist( const std::string& path ) const {
	auto* path_str = path.c_str( );

	return !path.empty( ) && Tiny::GetIsDir( path_str );
}

bool TinyFilesystem::GetFileExist( const std::string& path ) const {
	auto* path_str = path.c_str( );

	return !path.empty( ) && Tiny::GetIsFile( path_str );
}

tiny_list<tiny_directory_entry> TinyFilesystem::GetEntries( const std::string& path ) const {
	auto* path_str = path.c_str( );
	auto entries   = tiny_list<tiny_directory_entry>{ };
	auto entry	   = Tiny::FindEntry( path_str );
	
	while ( entry.has_value( ) ) {
		auto entry_ = entry.value( );

		entries.emplace_back( entry_ );

		entry = Tiny::NextEntry( );
	}

	return entries;
}

bool TinyFilesystem::GetIsFile(
	const std::string& path, 
	const tiny_string& extension 
) const {
	auto state = extension.get_is_valid( );

	if ( state ) {
		auto file_ext = GetFileExtension( path );

		state = extension == file_ext;
	}

	return state;
}

bool TinyFilesystem::GetIsFile(
	const std::string& path, 
	tiny_init<tiny_string> extensions 
) const {
	auto state = extensions.size( ) > 0;

	if ( state ) {
		auto file_ext = GetFileExtension( path );

		for ( auto& extension : extensions ) {
			state = extension == file_ext;

			if ( state )
				break;
		}
	}

	return state;
}

std::string TinyFilesystem::GetFilePath( const std::string& path ) const {
	auto offset = path.find_last_of( '\\' );

	return path.substr( 0, offset );
}

std::string TinyFilesystem::GetFileName( const std::string& path ) const {
	auto start = path.find_last_of( '\\' );
	auto stop  = path.find_last_of( '.' );

	return path.substr( start, stop );
}

std::string TinyFilesystem::GetFileExtension( const std::string& path ) const {
	auto offset = path.find_last_of( '.' );

	return path.substr( offset + 1 );
}

std::string TinyFilesystem::GetFileFullName( const std::string& path ) const {
	auto offset = path.find_last_of( '\\' );

	return path.substr( offset + 1 );
}

TinyPathInformation TinyFilesystem::GetInformation( const std::string& path ) const {
	auto path_info = TinyPathInformation{ };
	
	path_info.Full		= path;
	path_info.Extension = GetFileExtension( path );
	path_info.Path		= GetFilePath( path );
	path_info.Name		= GetFileName( path );

	return path_info;
}
