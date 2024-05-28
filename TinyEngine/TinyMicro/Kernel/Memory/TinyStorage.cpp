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
 * @creation : 06/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
///////////////////////////////////////////////////////////////////////////////////////////
tiny_storage::tiny_storage( )
	: tiny_storage{ TS_TYPE_UNDEFINED }
{ }

tiny_storage::tiny_storage( TinyStorageTypes type )
	: Type{ type },
	Block{ TINY_UINT_MAX },
	Capacity{ 0 } 
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool tiny_storage::GetIsValid( ) const { 
	return /*Type < TS_TYPE_UNDEFINED &&*/ Block < TINY_UINT_MAX && Capacity > 0;
}

native_pointer tiny_storage::GetAddress( ) { return tiny_get_address( tiny_self ); }

const native_pointer tiny_storage::GetAddress( ) const { return tiny_get_address( tiny_self ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_storage::operator bool( ) const { return GetIsValid( ); }

tiny_storage::operator native_pointer ( ) const { return GetAddress( ); }

tiny_storage::operator const native_pointer( ) const { return GetAddress( ); }

tiny_storage& tiny_storage::operator=( const tiny_storage& other ) {
	if ( other.GetIsValid( ) ) {
		if ( GetIsValid( ) )
			tiny_deallocate( tiny_self );

		Tiny::Memcpy( tiny_rvalue( other ), this );
	}

	return tiny_self;
}
