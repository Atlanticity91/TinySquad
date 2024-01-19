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
 * @creation : 27/11/2023
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
TinyAssetMetadata::TinyAssetMetadata( )
	: TinyAssetMetadata{ TA_TYPE_UNDEFINED, "", "" }
{ }

TinyAssetMetadata::TinyAssetMetadata( TinyAssetTypes type )
	: TinyAssetMetadata{ type, "", "" }
{ }

TinyAssetMetadata::TinyAssetMetadata( 
	TinyAssetTypes type, 
	const tiny_string& source,
	const tiny_string& target 
)
	: Type{ type },
	Reference{ 0 },
	Handle{ TINY_UINT_MAX },
	Source{ source.get( ) },
	Target{ target.get( ) }
{ }
