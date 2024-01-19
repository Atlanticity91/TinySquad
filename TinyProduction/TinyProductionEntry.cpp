/******************************************************************************************
 * 
 * @author   : ALVES Quentin
 * @creation : 19/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Game Production template for Tiny Engine usage.
 *
 ******************************************************************************************/

#include <TinyProduction/__tiny_production_pch.h>

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
TINY_GAME_ENTRY_IMP( TinyProduction, 256_mb )
