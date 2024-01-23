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

tiny_enum( TinyStorageTypes ) {

	TS_TYPE_STATIC = 0,
	TS_TYPE_GRAPHICS,
	TS_TYPE_RESSOURCES,
	TS_TYPE_DYNAMIC

};

tm_struct tiny_storage {

	//TinyStorageTypes Type;
	tiny_uint Block;
	tiny_ulong Capacity;

	tiny_storage( );

	//tiny_storage( TinyStorageTypes type );
	
	bool GetIsValid( ) const;

	//TinyStorageTypes GetType( ) const;

	c_ptr GetAddress( ) const;

	operator bool( ) const;

	operator c_ptr ( ) const;

	template<typename Type>
	Type* As( ) { return (Type*)GetAddress( ); };

	template<typename Type>
	const Type* As( ) const { return (const Type*)GetAddress( ); };

	template<typename Type>
	operator Type* ( ) { return As<Type>( ); };

	template<typename Type>
	operator const Type* ( ) const { return As<Type>( ); };

};
