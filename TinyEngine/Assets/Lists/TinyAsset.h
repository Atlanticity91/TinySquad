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
 * @creation : 10/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Assets/Importers/TinyAssetImportManager.h>

te_struct TinyAsset {

	tiny_hash Hash;
	TinyAssetTypes Type;
	tiny_uint Handle;
	
	TinyAsset( );

	TinyAsset( TinyAssetTypes type );

	bool GetIsValid( ) const;

	bool GetEqual( const TinyAsset& other ) const;

	bool GetNotEqual( const TinyAsset& asset ) const;

	operator bool const ( );

	bool operator==( const TinyAsset& other ) const;

	bool operator!=( const TinyAsset& other ) const;

};
