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
 * @creation : 11/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyPathInformation.h"

class TinyWindow;

tiny_enum( TinyPathTypes ) { 

	TP_TYPE_WORK = 0,
	TP_TYPE_GAME,
	TP_TYPE_SAVE,
	TP_TYPE_DEV,

	TP_TYPE_COUNT

};

tm_class TinyFilesystem final {

private:
	std::string m_developer;
	std::string m_work_dir;
	std::string m_game_dir;
	std::string m_save_dir;
	std::string	m_dev_dir;
	std::string m_game;
	std::string	m_cache;
	tiny_buffer<256> m_dialog_path;

public:
	TinyFilesystem( const std::string& developer );

	~TinyFilesystem( ) = default;

	bool Initialize( const TinyWindow& window );
	
	bool SetExecutable( const std::string& developer, const std::string& title );

	std::string CreatePath( 
		TinyPathTypes path_type,
		const std::string& name, 
		const tiny_string& extension 
	) const;

	std::string CreatePath( 
		TinyPathTypes path_type,
		const tiny_string& name, 
		const tiny_string& extension 
	) const;

	std::string ConvertTo( const std::string& path, const tiny_string& extension ) const;

	bool CreateDir( const std::string& path );

	bool RemoveDir( const std::string& path );

	TinyPhysicalFile OpenFile( const std::string& path, TinyFileAccesses access );

	TinyPhysicalFile OpenFile( const tiny_string& path, TinyFileAccesses access );

	bool RemoveFile( const std::string& path );

	bool RemoveFile( const tiny_string& path );

	bool Dump( const std::string& path, const std::string& text );

	bool Dump( const std::string& path, const tiny_uint length, const native_pointer data );

	void Terminate( );

public:
	const std::string& GetDeveloper( ) const;

	native_string GetDeveloperNative( ) const;

	const std::string& GetWorkingDir( ) const;

	native_string GetWorkingDirNative( ) const;

	const std::string& GetGameDir( ) const;

	native_string GetGameDirNative( ) const;

	const std::string& GetSaveDir( ) const;

	native_string GetSaveDirNative( ) const;

	const std::string& GetDevDir( ) const;

	native_string GetDevDirNative( ) const;

	const std::string& GetConfigPath( ) const;

	native_string GetConfigPathNative( ) const;

	const std::string& GetCachePath( ) const;

	native_string GetCachePathNative( ) const;

	const std::string& GetPath( const TinyPathTypes path_type ) const;

	bool GetDirExist( const std::string& path ) const;

	bool GetFileExist( const std::string& path ) const;

	tiny_list<tiny_directory_entry> GetEntries( const std::string& path ) const;

	bool GetIsFile( const std::string& path, const tiny_string& extension ) const;

	bool GetIsFile( const std::string& path, tiny_init<tiny_string> extensions ) const;

	std::string GetFilePath( const std::string& path ) const;

	std::string GetFileName( const std::string& path ) const;

	std::string GetFileExtension( const std::string& path ) const;

	std::string GetFileFullName( const std::string& path ) const;

	TinyPathInformation GetInformation( const std::string& path ) const;

};
