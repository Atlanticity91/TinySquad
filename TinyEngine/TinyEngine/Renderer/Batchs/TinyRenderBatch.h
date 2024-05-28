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
 * @creation : 26/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderBatchFlush.h"

template<typename Type, tiny_uint Capacity>
class TinyRenderBatch {

public:
	static const tiny_uint Size = Capacity * tiny_sizeof( Type );

private:
	tiny_uint	 _count;
	tiny_uint	 _capacity;
	tiny_storage _storage;

public:
	TinyRenderBatch( ) 
		: _count{ 0 },
		_capacity{ Capacity },
		_storage{ }
	{ };

	~TinyRenderBatch( ) = default;

	bool Create( ) {
		return tiny_allocate( _storage, Capacity * tiny_sizeof( Type ) );
	};

	void SetCapacity( tiny_uint value ) { 
		if ( value < Capacity )
			_capacity = value; 
	};

	void Push( const Type& element ) {
		auto* address = tiny_get_address_as( _storage, Type ) + _count++;

		Tiny::Memcpy( tiny_rvalue( element ), address );
	};

	void Push( const tiny_list<Type>& list ) {
		auto* address = tiny_get_address_as( _storage, Type ) + _count;
		auto range    = list.size( );

		_count += range;

		Tiny::Memcpy( list.data( ), address, range );
	};

	TinyRenderBatchFlush Flush( ) { 
		auto values = tiny_cast( GetData( ), tiny_pointer );
		auto result = TinyRenderBatchFlush{ _count, values };

		_count = 0; 

		return result;
	};

	void Terminate( ) { tiny_deallocate( _storage ); };

public:
	bool GetHasSpace( ) const { return _count < Capacity; };

	bool GetHasSpace( tiny_uint offset ) const { return _count + offset < Capacity; };

	tiny_uint GetCapacity( ) const { return Capacity; };

	tiny_uint GetCount( ) const { return _count; };

	tiny_uint GetSize( ) const { return _count * tiny_sizeof( Type ); };

	native_pointer GetData( ) const { return tiny_get_address( _storage ); };

};
