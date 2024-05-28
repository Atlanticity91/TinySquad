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

#include "TinyMemoryManager.h"

template<typename Type> class tiny_ref;
template<typename Type>
struct tiny_var {

	using ref_t = tiny_ref<Type>;

	tiny_storage Storage;

	tiny_var( )
		: Storage{ } 
	{
		tiny_allocate( Storage, tiny_sizeof( Type ) );
	};

	tiny_var( const Type& data )
		: tiny_var{ } 
	{
		Set( data );
	};

	~tiny_var( ) { tiny_deallocate( Storage ); };

	template<typename... Args>
	tiny_var& Make( Args... args ) { 
		if ( Storage )
			Storage.As<Type>( )->Type( args... );

		return tiny_self;
	};

	tiny_var& Set( const Type& data ) {
		if ( Storage ) {
			auto* dst = Storage.As<native_pointer_base>( );

			if ( dst )
				Tiny::Memcpy( tiny_cast( tiny_rvalue( data ), const native_pointer ), dst, tiny_sizeof( Type ) );
		}

		return tiny_self;
	};

	ref_t Get( ) const { return ref_t{ Storage.Block }; };

	operator bool( ) const { return Storage.GetIsValid( ); };

	operator tiny_storage&( ) { return Storage; };

	operator const tiny_storage& ( ) const { return Storage; };

	operator ref_t( ) { return Get( ); }

	Type* operator->( ) { return Storage.As<Type>( ); };

	const Type* operator->( ) const { return Storage.As<Type>( ); };

	tiny_var& operator=( const Type& data ) {
		return Set( data );
	};

};
