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

	using TinyAssetExporter = std::function<bool( TinyGame*, TinyFile&, c_pointer& )>;

private:
	tiny_map<TinyAssetImporter>					 _importers;
	tiny_array<TinyAssetExporter, TA_TYPE_COUNT> _exporters;

public:
	TinyAssetImportManager( );

	~TinyAssetImportManager( ) = default;

	void Register( tiny_init<tiny_string> extensions, const TinyAssetImporter& importer );

	void Initialize( );

	bool Import(
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	bool Export( TinyGame* game, tiny_uint type, TinyFile& file, c_pointer& asset  );

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

	static bool ExportTexture2D( TinyGame* game, TinyFile& file, c_pointer& asset );

	static bool ExportTexture3D( TinyGame* game, TinyFile& file, c_pointer& asset );

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

	static bool ExportSPV( TinyGame* game, TinyFile& file, c_pointer& asset );

	static bool ExportMaterial( TinyGame* game, TinyFile& file, c_pointer& asset );

	static bool ImportLua( 
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	static bool ExportLua( TinyGame* game, TinyFile& file, c_pointer& asset );

	static bool ImportWav(
		TinyGame* game,
		const TinyPathInformation& path,
		tiny_storage& file,
		tiny_storage& storage
	);

	static bool ExportWav( TinyGame* game, TinyFile& file, c_pointer& asset );

public:
	const TinyAssetImporter& Get( const tiny_string& extension ) const;

	tiny_uint GetTypeOf( const tiny_string& extension ) const;

public:
	const TinyAssetImporter& operator[]( const tiny_string& extension ) const;

};
