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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAsset::TinyAsset( )
	: TinyAsset{ TA_TYPE_UNDEFINED }
{ }

TinyAsset::TinyAsset( TinyAssetTypes type )
	: Hash{ },
	Type{ type },
	Handle{ TINY_UINT_MAX } 
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyAsset::GetIsValid( ) const {
	return Type != TA_TYPE_UNDEFINED && Handle < TINY_UINT_MAX;
}

bool TinyAsset::GetEqual( const TinyAsset& other ) const {
	return Hash == other.Hash && Type == other.Type;
}

bool TinyAsset::GetNotEqual( const TinyAsset& asset ) const { return !GetEqual( asset ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyAsset::operator bool const ( ) { return GetIsValid( ); }

bool TinyAsset::operator==( const TinyAsset& other ) const { return GetEqual( other ); }

bool TinyAsset::operator!=( const TinyAsset& other ) const { return GetNotEqual( other ); }
