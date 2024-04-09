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
 * @creation : 06/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyAssetConverter.h"

te_class TinyAssetImporter final {

private:
	tiny_map<tiny_uint>			  _extensions;
	tiny_list<tiny_uint>		  _types;
	tiny_list<TinyAssetConverter> _converters;

public:
	TinyAssetImporter( );

	~TinyAssetImporter( ) = default;

	void Initialize( );

	void Register( const tiny_uint type, const tiny_uint converter_id );

	void Register( const tiny_uint type, const TinyAssetConverter& converter );
	
	void Register( tiny_init<tiny_string> extensions, const tiny_uint converter_id );

	void Register( 
		tiny_init<tiny_string> extensions, 
		const TinyAssetConverter& converter 
	);

	bool Import( TinyGame* game, TinyFile& file, const TinyPathInformation& path_info );

	bool Export( 
		TinyGame* game,
		const tiny_uint type,
		const tiny_string& alias, 
		const c_pointer builder 
	);
	
private:
	void RegisterExtensions( );

	void RegisterTypes( );

};
