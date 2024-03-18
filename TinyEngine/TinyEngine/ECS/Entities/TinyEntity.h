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

#pragma once

#include <TinyEngine/ECS/Systems/TinySystemManager.h>

#define TE_NO_PARENT TINY_UINT_MAX
#define TE_NO_CHILD TINY_UINT_MAX

tiny_enum( TinyEntityFlags ) { 

	TE_FLAG_ALIVE = 0,
	TE_FLAG_VISIBLE

};

te_struct TinyEntity {

	tiny_uint Parent;
	tiny_uint Next;
	tiny_uint Flags;
	tiny_uint Components;

	TinyEntity( );

	tiny_inline bool GetIsAlive( ) const;

	bool GetHasParent( ) const;

	bool GetHasChild( ) const;

	bool GetHasFlag( const tiny_uint flag_id ) const;

	bool GetHasFlags( const tiny_uint flags ) const;

	bool GetHasComponent( const tiny_uint compoment_id ) const;

	bool GetHasComponents( const tiny_uint components ) const;

};
