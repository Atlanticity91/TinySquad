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
 * @creation : 02/08/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyDebugTabManager::TinyDebugTabManager( ) 
	: TinyImGuiTabManager{ "TinyDebug", "__TinyDebug__" }
{ }

void TinyDebugTabManager::OnCreate( native_pointer user_data ) {
	AddTab<TinyDebugTabCommon>( user_data );
	AddTab<TinyDebugTabInputs>( user_data );
	AddTab<TinyDebugTabAssets>( user_data );
	AddTab<TinyDebugTabScene>( user_data );
}
