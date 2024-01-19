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

#include "TinyVar.h"

template<typename Type>
class tiny_ref {

private:
	tiny_uint _block;

public:
	tiny_ref( ) = delete;

	tiny_ref( tiny_uint block )
		: _block{ block } {
		auto* block = tiny_get_block( block );

		if ( block )
			block->Reference += 1;
	};

	~tiny_ref( ) {
		auto* block = tiny_get_block( block );

		if ( block )
			block->Reference -= 1;
	};

public:
	Type* Get( ) { return (Type*)GetAddress( ); };

	const Type* Get( ) const { return (const Type*)GetAddress( ); };

	Type& GetRef( ) { return *Get( ); };

	const Type& GetRef( ) const { return *Get( ); };

private:
	tiny_ptr GetAddress( ) const {
		return (tiny_ptr)tiny_get_address_of( _block );
	};

public:
	operator Type* ( ) { return Get( ); };

	operator const Type* ( ) const { return Get( ); };

	operator Type& ( ) { return GetRef( ); };

	operator const Type& ( ) const { return GetRef( ); };

	Type& operator*( ) { return GetRef( ); };

	const Type& operator*( ) const { return GetRef( ); };

	Type* operator->( ) { return Get( ); };

	const Type* operator->( ) const { return Get( ); };

};
