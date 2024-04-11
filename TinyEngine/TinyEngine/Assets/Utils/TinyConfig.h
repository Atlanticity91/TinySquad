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
 * @creation : 04/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Assets/Containers/TinyAssetContainer.h>

te_class TinyConfig final : tiny_inherit( TinyAsset ) {

private:
	TinyAppConfig		   _application;
	tiny_list<std::string> _archives;
	std::string			   _start_scene;

public:
	TinyConfig( );

	~TinyConfig( ) = default;

	void SetDimensions( const tiny_uint width, const tiny_uint height );

	void AddArchive( const std::string& archive );

	bool Load( TinyFile& file );

	void Save( TinyFile& file );

public:
	const TinyAppConfig& GetAppConfig( ) const;

	const tiny_list<std::string>& GetArchives( ) const;

	const tiny_string GetStartScene( ) const;

public:
	operator const TinyAppConfig& ( ) const;

};
