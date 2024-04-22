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
 * @creation : 24/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyEntity::TinyEntity( ) 
	: Parent{ TE_NO_PARENT },
	Next{ TE_NO_CHILD },
	Flags{ 0 },
	Components{ 0 }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyEntity::GetIsAlive( ) const { return GetHasFlag( TE_FLAG_ALIVE ); }

bool TinyEntity::GetHasParent( ) const { return Parent < TINY_UINT_MAX; }

bool TinyEntity::GetHasChild( ) const { return Next < TINY_UINT_MAX; }

bool TinyEntity::GetHasFlag( const tiny_uint flag_id ) const {
	return Flags & TINY_LEFT_SHIFT( 1, flag_id ); 
}

bool TinyEntity::GetHasFlags( const tiny_uint flags ) const {
	return ( Flags & flags ) == flags; 
}

bool TinyEntity::GetHasComponent( const tiny_uint compoment_id ) const {
	return Components & TINY_LEFT_SHIFT( 1, compoment_id );
}

bool TinyEntity::GetHasComponents( const tiny_uint components ) const {
	return ( Components & components ) == components;
}
