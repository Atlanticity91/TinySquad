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
	tiny_uint m_count;
	tiny_uint m_capacity;
	tiny_storage m_storage;

public:
	TinyRenderBatch( ) 
		: m_count{ 0 },
		m_capacity{ Capacity },
		m_storage{ }
	{ };

	~TinyRenderBatch( ) = default;

	bool Create( ) {
		return tiny_allocate( m_storage, Capacity * tiny_sizeof( Type ) );
	};

	void SetCapacity( tiny_uint value ) { 
		if ( value < Capacity )
			m_capacity = value; 
	};

	void Push( const Type& element ) {
		auto* src = tiny_rvalue( element );
		auto* dst = tiny_get_address_as( m_storage, Type ) + m_count++;

		Tiny::Memcpy( src, dst, tiny_sizeof( Type ) );
	};

	void Push( const tiny_list<Type>& list ) {
		auto* src  = list.data( );
		auto* dst  = tiny_get_address_as( m_storage, Type ) + m_count;
		auto range = list.size( );

		m_count += range;

		Tiny::Memcpy( src, dst, range * tiny_sizeof( Type ) );
	};

	TinyRenderBatchFlush Flush( ) { 
		auto values = tiny_cast( GetData( ), tiny_pointer );
		auto result = TinyRenderBatchFlush{ m_count, values };

		m_count = 0; 

		return result;
	};

	void Terminate( ) { tiny_deallocate( m_storage ); };

public:
	bool GetHasSpace( ) const { return m_count < Capacity; };

	bool GetHasSpace( tiny_uint offset ) const { return m_count + offset < Capacity; };

	tiny_uint GetCapacity( ) const { return Capacity; };

	tiny_uint GetCount( ) const { return m_count; };

	tiny_uint GetSize( ) const { return m_count * tiny_sizeof( Type ); };

	native_pointer GetData( ) const { return tiny_get_address( m_storage ); };

};
