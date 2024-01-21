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
 * @creation : 21/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolInputs::TinyToolInputs( )
	: TinyToolCategory{ "Inputs" },
    _path{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolInputs::OnTick(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) { 
    auto& inputs = engine.GetInputs( );

    auto button_size = ( ImGui::GetContentRegionAvail( ).x - ImGui::GetStyle( ).ItemSpacing.x ) * .5f;
    auto filters = "Tiny Inputs (*.tinyinputs)\0*.tinyinputs\0";

    if ( ImGui::Button( "Load", { button_size, 0.f } ) ) {
        if ( Tiny::OpenDialog( Tiny::TD_TYPE_OPEM_FILE, filters, _path.length( ), _path.as_chars( ) ) ) {
        }
    }

    ImGui::SameLine( );

    ImGui::BeginDisabled( true );
    if ( ImGui::Button( "Save", { button_size, 0.f } ) ) {
        if ( Tiny::OpenDialog( Tiny::TD_TYPE_SAVE_FILE, filters, _path.length( ), _path.as_chars( ) ) ) {
        }
    }

    ImGui::EndDisabled( );

    if ( ImGui::Button( "New", { -1.f, 0.f } ) ) {
    }

    ImGui::SeparatorText( "Inputs Table" );

    auto& input_map = inputs.GetMap( );

    for ( auto& input : input_map ) {
        TINY_IMGUI_SCOPE_ID(
            ImGui::Checkbox( IMGUI_NO_LABEL, tiny_cast( tiny_rvalue( input.Data.IsActive ), bool* ) );
        );
        
        ImGui::SameLine( );

        if ( ImGui::TreeNodeEx( input.String.c_str( ), IMGUI_NO_FLAGS ) ) {
            for ( auto& query : input.Data.Values ) {
                TINY_IMGUI_SCOPE_ID(
                    auto open = ImGui::TreeNodeEx( IMGUI_NO_LABEL, IMGUI_NO_FLAGS );
                );

                ImGui::SameLine( );
                ImGui::Text( "TID_KEYBOARD" );
                ImGui::SameLine( );
                ImGui::Text( "TIT_BUTTON" );

                if ( open ) {
                    //query.Descriptor.Device;
                    //query.Descriptor.Type;
                    //query.Descriptor.Key;
                    //query.Modifier;
                    //query.State;

                    ImGui::TreePop( );
                }
            }

            ImGui::TreePop( );
        }
    }
}
