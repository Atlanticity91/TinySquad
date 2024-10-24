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
 * @creation : 26/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyFoundry/__tiny_foundry_pch.h>

/**
 *
 * Custom Entry point macro,
 * Take the current game class name and size for the memory allocator.
 * Custom _kb, _mb, _gb operator defined by the engine for speed size definition.
 *
 * _kb : Kilo-Bytes
 * _mb : Mega-Bytes
 * _gb : Giga-Bytes
 *
 **/
TINY_GAME_ENTRY_IMP( TinyFoundry, 256_mb )
