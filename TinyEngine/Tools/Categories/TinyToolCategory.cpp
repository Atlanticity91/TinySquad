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
 * @creation : 19/01/2024
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
TinyToolCategory::TinyToolCategory( const tiny_string& name )
    : _name{ name }
{ }

bool TinyToolCategory::Tick( TinyGame* game, TinyEngine& engine, TinyToolbox& toolbox ) {
    auto* name_str = _name.as_chars( );
    auto state     = ImGui::BeginTabItem( name_str );
    
    if ( state ) {
        OnTick( game, engine, toolbox );

        ImGui::EndTabItem( );
    }

    return state;
}
