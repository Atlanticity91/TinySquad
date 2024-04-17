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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAssetHandle::TinyAssetHandle( )
	: TinyAssetHandle{ TA_TYPE_UNDEFINED }
{ }

TinyAssetHandle::TinyAssetHandle( TinyAssetTypes type )
	: TinyAssetHandle{ tiny_cast( type, tiny_uint ) }
{ }

TinyAssetHandle::TinyAssetHandle( tiny_uint type )
	: Type{ type },
	Hash{ }
{ }

TinyAssetHandle::TinyAssetHandle( tiny_uint type, const tiny_string& asset )
	: Type{ type },
	Hash{ asset }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAssetHandle::GetIsValid( ) const { 
	return Type < TA_TYPE_UNDEFINED && Hash.is_valid( ); 
}

bool TinyAssetHandle::GetEqual( const TinyAssetHandle& other ) const {
	return Type == other.Type && Hash == other.Hash;
}

bool TinyAssetHandle::GetNotEqual( const TinyAssetHandle& other ) const {
	return !GetEqual( other );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAssetHandle::operator bool( ) const { return GetIsValid( ); }

TinyAssetHandle::operator tiny_hash ( ) const { return Hash; }

TinyAssetHandle& TinyAssetHandle::operator=( const TinyAssetHandle& other ) {
	if ( !GetIsValid( ) && other.GetIsValid( ) ) {
		Type = other.Type;
		Hash = other.Hash;
	}

	return tiny_self;
}

bool TinyAssetHandle::operator==( const TinyAssetHandle& other ) const {
	return GetEqual( other ); 
}

bool TinyAssetHandle::operator!=( const TinyAssetHandle& other ) const {
	return GetNotEqual( other );
}
