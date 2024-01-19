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
 * @creation : 05/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Threads/TinyThreadManager.h>

tm_class TinyVirtualFile final { 

private:
	tiny_ptr  _memory;
	tiny_uint _offset;
	tiny_uint _size;

public:
	TinyVirtualFile( );

	TinyVirtualFile( const tiny_storage& storage );

	~TinyVirtualFile( ) = default;

	bool Skip( tiny_uint count );

	tiny_uint Read( tiny_uint size, c_ptr buffer );

	tiny_uint Write( tiny_uint size, const c_ptr buffer );

	TinyVirtualFile& Asign( const tiny_storage& storage );

public:
	template<typename Type>
	bool Read( Type& element ) { 
		constexpr auto size = tiny_sizeof( Type );

		return Read( size, tiny_cast( tiny_rvalue( element ), c_ptr ) ) == size;
	};

	template<typename Type>
	bool Read( Type& element, tiny_uint count ) {
		constexpr auto size = count * tiny_sizeof( Type );

		return count > 0 && Read( size, tiny_cast( tiny_rvalue( element ), c_ptr ) ) == size;
	};

	template<typename Type>
	bool Write( Type& element ) {
		constexpr auto size = tiny_sizeof( Type );

		return Write( size, tiny_cast( tiny_rvalue( element ), const c_ptr ) ) == size;
	};

	template<typename Type>
	bool Write( Type& element, tiny_uint count ) {
		constexpr auto size = count * tiny_sizeof( Type );

		return count > 0 && Write( size, tiny_cast( tiny_rvalue( element ), const c_ptr ) ) == size;
	};

public:
	bool GetIsValid( ) const;

public:
	operator bool ( ) const;

	TinyVirtualFile& operator=( const tiny_storage& storage );

};
