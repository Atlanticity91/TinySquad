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
 * @creation : 09/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyMicro/Kernel/Platform/TinyPlatform.h>

tm_class tiny_hash final {

private:
	tiny_uint m_data;

public:
	tiny_hash( );

	tiny_hash( const tiny_hash& other );

	explicit tiny_hash( native_string string );

	explicit tiny_hash( const tiny_string& string );

	tiny_hash( const tiny_string& string, const tiny_uint offset, const tiny_uint length );

	tiny_hash( const std::string& string );

	~tiny_hash( ) = default;

	tiny_inline tiny_hash& asign( tiny_uint other );

	tiny_inline tiny_hash& asign( const tiny_hash& other );

	tiny_inline tiny_hash& asign( native_string other );

	tiny_hash& asign( const tiny_string& string );

	tiny_inline tiny_hash& asign( const std::string& other );

	tiny_hash& asign( 
		const tiny_string& string, 
		const tiny_uint offset, 
		const tiny_uint length 
	);

	void undefined( );

private:
	tiny_inline tiny_uint generate( tiny_string string ) const;

	tiny_uint generate( tiny_string string, tiny_uint offset, tiny_uint length ) const;

public:
	tiny_uint get( ) const;

	bool get_is_valid( ) const;

	bool get_is_inferior( const tiny_uint other ) const;

	bool get_is_inferior( const tiny_hash& other ) const;

	bool get_is_superior( const tiny_uint other ) const;

	bool get_is_superior( const tiny_hash& other ) const;

	bool equal( const tiny_uint other ) const;

	bool equal( const tiny_hash& other ) const;

	bool equal( const tiny_string& string ) const;

	bool equal( const std::string& other ) const;

	bool not_equal( const tiny_uint other ) const;

	bool not_equal( const tiny_hash& other ) const;

	bool not_equal( const tiny_string& string ) const;

	bool not_equal( const std::string& other ) const;

public:
	operator bool ( ) const;

	tiny_hash& operator=( const tiny_uint other );

	tiny_hash& operator=( const tiny_hash& other );

	tiny_hash& operator=( native_string string );

	tiny_hash& operator=( const tiny_string& string );

	tiny_hash& operator=( const std::string& other );

	bool operator<( const tiny_uint other ) const;

	bool operator<( const tiny_hash& other ) const;

	bool operator>( const tiny_uint other ) const;

	bool operator>( const tiny_hash& other ) const;

	bool operator==( const tiny_uint other ) const;

	bool operator==( const tiny_hash& other ) const;

	bool operator==( const tiny_string& string ) const;

	bool operator==( const std::string& other ) const;

	bool operator!=( const tiny_uint other ) const;

	bool operator!=( const tiny_hash& other ) const;

	bool operator!=( const tiny_string& string ) const;

	bool operator!=( const std::string& other ) const;

};
