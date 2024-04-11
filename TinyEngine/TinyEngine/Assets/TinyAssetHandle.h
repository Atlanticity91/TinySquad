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
 * @creation : 03/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Importers/TinyAssetImporter.h"

tiny_enum( TinyAssetTypes ) {

	TA_TYPE_UNDEFINED = TINY_UINT_MAX,
	TA_TYPE_CONFIG = 0,
	TA_TYPE_ARCHIVE,
	TA_TYPE_TEXTURE_2D,
	TA_TYPE_TEXTURE_3D,
	TA_TYPE_TEXTURE_ATLAS,
	TA_TYPE_TEXTURE_CUBEMAP,
	TA_TYPE_TEXTURE_LUT,
	TA_TYPE_ANIMATION_2D,
	TA_TYPE_ANIMATION_3D,
	TA_TYPE_FONT,
	TA_TYPE_SHADER,
	TA_TYPE_MATERIAL,
	TA_TYPE_GEOMETRY,
	TA_TYPE_CUE,
	TA_TYPE_SANPLES,
	TA_TYPE_SCRIPT,
	TA_TYPE_SCENE,
	TA_TYPE_LOCALISATION,
	TA_TYPE_TROPHY,
	TA_TYPE_SAVE,

	TA_TYPE_COUNT

};

te_struct TinyAssetHandle {

	tiny_uint Type;
	tiny_hash Hash;

	TinyAssetHandle( );

	TinyAssetHandle( TinyAssetTypes type );

	TinyAssetHandle( tiny_uint type );

	TinyAssetHandle( tiny_uint type, const tiny_string& asset );

	bool GetIsValid( ) const;

	bool GetEqual( const TinyAssetHandle& other ) const;

	bool GetNotEqual( const TinyAssetHandle& other ) const;

	operator bool( ) const;

	operator tiny_hash ( ) const;

	TinyAssetHandle& operator=( const TinyAssetHandle& other );

	bool operator==( const TinyAssetHandle& other ) const;

	bool operator!=( const TinyAssetHandle& other ) const;

};
