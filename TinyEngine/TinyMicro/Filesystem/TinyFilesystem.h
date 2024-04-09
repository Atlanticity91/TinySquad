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

#include "TinyFile.h"

#define TINY_ASSET_EXT "tinyasset"
#define TINY_ARCHIVE_EXT "tinyarchive"
#define TINY_REGISTRY_EXT "tinyregistry"

tm_struct TinyPathInformation {

	tiny_string Full{ };
	tiny_string Extension{ };
	std::string Path = "";
	std::string Name = "";

};

class TinyWindow;

tm_class TinyFilesystem final {

private:
	std::string		 _work_dir;
	std::string		 _game_dir;
	std::string		 _save_dir;
	std::string		 _dev_dir;
	std::string		 _game;
	std::string		 _cache;
	tiny_buffer<256> _dialog_path;

public:
	TinyFilesystem( );

	~TinyFilesystem( ) = default;

	bool Initialize( const TinyWindow& window );
	
	std::string CreatePath( const tiny_string& name, const tiny_string& extension );

	bool CreateDir( const tiny_string& path );

	bool RemoveDir( const tiny_string& path );

	bool OpenDialog( 
		Tiny::DialogTypes type, 
		const tiny_string& filters, 
		tiny_string& path
	);

	TinyFile OpenFile( const tiny_string& path, Tiny::FileAccesses access );

	bool RemoveFile( const tiny_string& path );

	bool Dump( const tiny_string& path, const tiny_string& text );

	void Terminate( );

private:
	bool GenerateGameDir( const std::string& title );

public:
	tiny_string GetWorkingDir( ) const;

	tiny_string GetGameDir( ) const;

	tiny_string GetSaveDir( ) const;

	tiny_string GetDevDir( ) const;

	tiny_string GetConfigPath( ) const;

	tiny_string GetCachePath( ) const;

	bool GetDirExist( const tiny_string& path ) const;

	bool GetFileExist( const tiny_string& path ) const;

	tiny_list<Tiny::FileEntry> GetEntries( const tiny_string& path ) const;

	bool GetIsFile( const tiny_string& path, const tiny_string& extension ) const;

	bool GetIsFile( const tiny_string& path, tiny_init<tiny_string> extensions ) const;

	bool GetIsAssetFile( const tiny_string& path ) const;

	bool GetIsArchiveFile( const tiny_string& path ) const;

	std::string GetFilePath( const tiny_string& path ) const;

	std::string GetFileName( const tiny_string& path ) const;

	tiny_string GetFileExtension( const tiny_string& path ) const;

	tiny_string GetFileFullName( const tiny_string& path ) const;

	TinyPathInformation GetInformation( const tiny_string& path ) const;

	std::string ConvertToAsset( const tiny_string& path ) const;

};
