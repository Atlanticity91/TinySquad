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
 * @creation : 29/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyImGuiTab::TinyImGuiTab( )
	: TinyImGuiTab{ "" }
{ }

TinyImGuiTab::TinyImGuiTab( const tiny_string& name )
	: m_name{ name } 
{ }

bool TinyImGuiTab::Tick(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	native_pointer user_data
) {
    auto* name = m_name.get( );
    auto state = ImGui::BeginTabItem( name );

    if ( state ) {
        OnTick( graphics, inputs, user_data );

        ImGui::EndTabItem( );
    }

    return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const tiny_string& TinyImGuiTab::GetName( ) const { return m_name; }
