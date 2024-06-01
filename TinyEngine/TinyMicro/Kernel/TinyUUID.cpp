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
 * @creation : 13/10/2023
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
static std::random_device RandomDevice;
static std::mt19937_64 RandomEngine( RandomDevice( ) );
static std::uniform_int_distribution<uint64_t> RandomDistribution;

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uuid::tiny_uuid( )
	: m_uuid{ RandomDistribution( RandomEngine ) }
{ }

tiny_uuid::tiny_uuid( const tiny_ulong uuid ) 
	: m_uuid{ uuid }
{ }

tiny_uuid::tiny_uuid( const tiny_uuid& other )
	: m_uuid{ other.m_uuid }
{ }

tiny_uuid& tiny_uuid::asign( const tiny_ulong uuid ) {
	m_uuid = uuid;

	return tiny_self;
}

tiny_uuid& tiny_uuid::asign( const tiny_uuid& other ) {
	return asign( other.m_uuid );
}

bool tiny_uuid::equal( const tiny_ulong uuid ) const { return m_uuid == uuid; }

bool tiny_uuid::equal( const tiny_uuid& other ) const { return equal( other.m_uuid ); }

bool tiny_uuid::not_equal( const tiny_ulong uuid ) const { return m_uuid != uuid; }

bool tiny_uuid::not_equal( const tiny_uuid& other ) const { 
	return not_equal( other.m_uuid );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uuid::operator tiny_ulong ( ) const { return m_uuid; }

tiny_uuid& tiny_uuid::operator=( const tiny_ulong uuid ) { return asign( uuid ); }

tiny_uuid& tiny_uuid::operator=( const tiny_uuid& other ) { return asign( other ); }

bool tiny_uuid::operator==( const tiny_ulong uuid ) const { return equal( uuid ); }

bool tiny_uuid::operator==( const tiny_uuid& other ) const { return equal( other ); }

bool tiny_uuid::operator!=( const tiny_ulong uuid ) const { return not_equal( uuid ); }

bool tiny_uuid::operator!=( const tiny_uuid& other ) const { return not_equal( other ); }
