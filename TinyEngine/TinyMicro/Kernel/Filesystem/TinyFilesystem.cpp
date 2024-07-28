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
	: m_is_folder_disabled{ false },
	m_developer{ developer },
	m_work_dir{ },
	m_game_dir{ },
	m_save_dir{ },
	m_dev_dir{ },
	m_game{ },
	m_cache{ },
	m_dialog_path{ }
{ }

void TinyFilesystem::DisableGameFolder( ) { m_is_folder_disabled = true; }

bool TinyFilesystem::Initialize( const TinyWindow& window ) {
	auto title = window.GetTitle( ).as_string( );
	
	return !m_is_folder_disabled ? SetExecutable( m_developer, title ) : true;
}

bool TinyFilesystem::SetExecutable( 
	const std::string& developer, 
	const std::string& title 
) {
	auto state = false;

	m_work_dir = Tiny::GetWorkingDir( );
	m_game_dir = Tiny::GetDocumentDir( ) + developer + "\\" + title + "\\";

#	ifdef TINY_DEV_ONLY
	if ( GetDirExist( m_game_dir ) || CreateDir( m_game_dir ) ) {
		m_work_dir = Tiny::GetWorkingDir( );
		m_save_dir = m_work_dir + "Saves\\";
		m_dev_dir  = m_work_dir + "Dev\\";
		m_log_dir  = m_work_dir + "Logs\\";
		m_game	   = m_work_dir + title + "." + TINY_GAME_EXT;
		m_cache    = m_work_dir + title + "." + TINY_CACHE_EXT;
	}
#	else
	m_save_dir = m_game_dir + "Saves\\";
	m_dev_dir  = m_game_dir + "Dev\\";
	m_log_dir  = m_game_dir + "Logs\\";
	m_game	   = m_work_dir + title + "." + TINY_GAME_EXT;
	m_cache    = m_game_dir + title + "." + TINY_CACHE_EXT;
#	endif

	if ( !GetDirExist( m_log_dir ) )
		CreateDir( m_log_dir );

	state = GetDirExist( m_save_dir );

	if ( !state )
		state = CreateDir( m_save_dir );

	return state;
}

std::string TinyFilesystem::CreatePath(
	TinyPathTypes path_type,
	const std::string& name, 
	const tiny_string& extension 
) const {
	auto directory = GetPath( path_type );

	return directory + "\\" + name + "." + extension.as_string( );
}

std::string TinyFilesystem::CreatePath(
	TinyPathTypes path_type,
	const tiny_string& name,
	const tiny_string& extension
) const {
	auto directory = GetPath( path_type );

	return directory + "\\" + name.as_string( ) + "." + extension.as_string( );
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
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyFilesystem::GetIsFolderDisabled( ) const { return m_is_folder_disabled; }

const std::string& TinyFilesystem::GetDeveloper( ) const { return m_developer; }

native_string TinyFilesystem::GetDeveloperNative( ) const { return m_developer.c_str( ); }

const std::string& TinyFilesystem::GetWorkingDir( ) const { return m_work_dir; }

native_string TinyFilesystem::GetWorkingDirNative( ) const { return m_work_dir.c_str( ); }

const std::string& TinyFilesystem::GetGameDir( ) const { return m_game_dir; }

native_string TinyFilesystem::GetGameDirNative( ) const { return m_game_dir.c_str( ); }

const std::string& TinyFilesystem::GetSaveDir( ) const { return m_save_dir; }

native_string TinyFilesystem::GetSaveDirNative( ) const { return m_save_dir.c_str( ); }

const std::string& TinyFilesystem::GetDevDir( ) const { return m_dev_dir; }

native_string TinyFilesystem::GetDevDirNative( ) const { return m_dev_dir.c_str( ); }

const std::string& TinyFilesystem::GetLogDir( ) const { return m_log_dir; }

native_string TinyFilesystem::GetLogDirNative( ) const { return m_log_dir.c_str( ); }

const std::string& TinyFilesystem::GetConfigPath( ) const { return m_game; }

native_string TinyFilesystem::GetConfigPathNative( ) const { return m_game.c_str( ); }

const std::string& TinyFilesystem::GetCachePath( ) const { return m_cache; }

native_string TinyFilesystem::GetCachePathNative( ) const { return m_cache.c_str( ); }

const std::string& TinyFilesystem::GetPath( const TinyPathTypes path_type ) const {
	switch ( path_type ) {
		case TP_TYPE_WORK : return m_work_dir;
		case TP_TYPE_GAME : return m_game_dir;
		case TP_TYPE_SAVE : return m_save_dir;

		default : break;
	}

	return m_dev_dir;
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
