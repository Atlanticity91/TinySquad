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

#pragma once

#include "TinyMemoryBlock.h"

// TODO : STORAGE ONLY USE FOR STORING MEMORY INFORMATION
// TOOD : IMPLEMENT VAR & REF FOR MEMORY ACCESS 
// TODO : TIED REF TO VAR WHEN VAR REMOVED ALL REF ARE INVALIDED, REF IS LINK LIST

tiny_enum( TinyStorageTypes ) {

	TS_TYPE_STATIC = 0,
	TS_TYPE_DYNAMIC,
	TS_TYPE_THREAD,
	TS_TYPE_GRAPHICS,
	TS_TYPE_ASSETS,
	TS_TYPE_HEAP,
		
	TS_TYPE_UNDEFINED

};

tm_struct tiny_storage {

	TinyStorageTypes Type;
	tiny_uint Block;
	tiny_ulong Capacity;

	tiny_storage( );

	tiny_storage( TinyStorageTypes type );
	
	bool GetIsValid( ) const;

	native_pointer GetAddress( );

	const native_pointer GetAddress( ) const;

	operator bool( ) const;

	operator native_pointer( ) const;

	operator const native_pointer ( ) const;

	tiny_storage& operator=( const tiny_storage& other );

	template<typename Type>
	Type* As( ) { return tiny_cast( GetAddress( ), Type* ); };

	template<typename Type>
	const Type* As( ) const { return tiny_cast( GetAddress( ), const Type* ); };

	template<typename Type>
	operator Type*( ) { return As<Type>( ); };

	template<typename Type>
	operator const Type*( ) const { return As<Type>( ); };

};
