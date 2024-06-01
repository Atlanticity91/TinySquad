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
	m_begin{ 0 },
	m_path{ }
{ }

TinyPhysicalFile TinyArchive::Access( TinyGame* game, tiny_ulong offset ) {
	auto& filesystem = game->GetFilesystem( );
	auto file		 = filesystem.OpenFile( m_path, TF_ACCESS_BINARY_READ );

	file.Seek( TF_ORIGIN_BEGIN, m_begin + offset );

	return file;
}
