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
 * @creation : 02/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyStorage.h"

// TODO : THREAD-SAFE MEMORY ACCESS
// TODO : REWORK MEMORY API 
// TODO : IMPLEMENT MEMORY POLICY

#define tiny_initialize( CAPACITY )\
	TinyMemoryManager::GetSingleton( ).Initialize( CAPACITY )
#define tiny_allocate2( STORAGE, CAPACITY, DESTRUCTOR )\
	TinyMemoryManager::GetSingleton( ).Allocate( STORAGE, CAPACITY, DESTRUCTOR )
#define tiny_allocate( STORAGE, CAPACITY ) tiny_allocate2( STORAGE, CAPACITY, nullptr )
#define tiny_make_storage( STORAGE, TYPE )\
	TinyMemoryManager::Make<TYPE>( STORAGE )
#define tiny_make_storage2( STORAGE, TYPE, ... )\
	TinyMemoryManager::Make<TYPE>( STORAGE, __VA_ARGS__ )
#define tiny_reallocate( STORAGE, CAPACITY )\
	TinyMemoryManager::GetSingleton( ).ReAllocate( STORAGE, CAPACITY )
#define tiny_deallocate( STORAGE )\
	TinyMemoryManager::GetSingleton( ).DeAllocate( STORAGE )
#define tiny_get_bock( STORAGE )\
	TinyMemoryManager::GetSingleton( ).GetBlock( STORAGE )
#define tiny_get_address( STORAGE )\
	TinyMemoryManager::GetSingleton( ).GetAddress( STORAGE )
#define tiny_get_address_as( STORAGE, TYPE )\
	tiny_cast( tiny_get_address( STORAGE ), TYPE* )
#define tiny_get_address_of( BLOCK )\
	TinyMemoryManager::GetSingleton( ).GetAddress( BLOCK )

tm_class TinyMemoryManager final {

	const tiny_uint MAX_BLOCKS = 512;

private:
	native_pointer	  _block_storage;
	tiny_uint _block_count;
	tiny_ulong _occupancy;
	tiny_ulong _capacity;

public:
	TinyMemoryManager( );

	~TinyMemoryManager( );

	bool Initialize( tiny_ulong capacity );

	bool Allocate( 
		tiny_storage& storage,
		tiny_ulong capacity,
		TinyMemoryBlock::DestructorCall destructor 
	);

	bool ReAllocate( tiny_storage& storage, tiny_ulong capacity );

	void SetDestructor( 
		const tiny_storage& storage,
		TinyMemoryBlock::DestructorCall destructor 
	);

	void DeAllocate( tiny_storage& storage );

public:
	template<typename Type, typename... Args>
	static bool Make( tiny_storage& storage, Args... args ) { 
		auto state = tiny_allocate( storage, tiny_sizeof( Type ) );

		if ( state ) {
			auto* address = storage.As<Type>( );

			address = new ( address ) Type{ args... };
		}

		return state;
	};

public:
	tiny_uint GetBlockCount( ) const;

	tiny_ulong GetOccupancy( ) const;

	tiny_ulong GetCapacity( ) const;

	TinyMemoryBlock* GetBlock( tiny_uint block ) const;

	native_pointer GetAddress( const tiny_storage& storage ) const;

	native_pointer GetAddress( tiny_uint block ) const;

private:
	bool FindEmpty( tiny_uint& block_id, TinyMemoryBlock*& block ) const;

public:
	static TinyMemoryManager& GetSingleton( );

};
