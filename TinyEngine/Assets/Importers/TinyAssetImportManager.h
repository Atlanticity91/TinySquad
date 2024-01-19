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

#pragma once

#include "TinyAssetImporter.h"

te_class TinyAssetImportManager final {

	using TinyAssetExporter = std::function<bool( TinyGame*, TinyFile&, c_ptr& )>;

private:
	tiny_map<TinyAssetImporter>					 _importers;
	tiny_array<TinyAssetExporter, TA_TYPE_COUNT> _exporters;

public:
	TinyAssetImportManager( );

	~TinyAssetImportManager( ) = default;

	void Initialize( );

	bool Import(
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	bool Export(
		TinyGame* game,
		TinyAssetTypes type,
		TinyFile& file,
		c_ptr& asset 
	);

private:
	void Register( tiny_init<tiny_string> extensions, const TinyAssetImporter& importer );

private:
	static bool ImportTexture2D( 
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	static bool ImportTextureDDS( 
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	static bool ExportTexture2D( TinyGame* game, TinyFile& file, c_ptr& asset );

	static bool ExportTexture3D( TinyGame* game, TinyFile& file, c_ptr& asset );

	static bool ImportSPV(
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	static bool ImportGLSL(
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	static bool ImportHLSL(
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	static bool ExportSPV( TinyGame* game, TinyFile& file, c_ptr& asset );

	static bool ExportMaterial( TinyGame* game, TinyFile& file, c_ptr& asset );

	static bool ImportLua( 
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	static bool ExportLua( TinyGame* game, TinyFile& file, c_ptr& asset );

	static bool ImportWav(
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	static bool ExportWav( TinyGame* game, TinyFile& file, c_ptr& asset );

public:
	const TinyAssetImporter& Get( const tiny_string& extension ) const;

	TinyAssetTypes GetTypeOf( const tiny_string& extension ) const;

public:
	const TinyAssetImporter& operator[]( const tiny_string& extension ) const;

};
