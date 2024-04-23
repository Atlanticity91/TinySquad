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
 * @creation : 07/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyArchive::TinyArchive( ) 
	: TinyAsset{ TA_TYPE_ARCHIVE },
	_begin{ 0 },
	_path{ }
{ }

TinyFile TinyArchive::Access( TinyGame* game, tiny_ulong offset ) {
	auto& filesystem = game->GetFilesystem( );
	auto file		 = filesystem.OpenFile( _path, Tiny::TF_ACCESS_READ );

	file.Seek( Tiny::TF_ORIGIN_BEGIN, _begin + offset );

	return file;
}