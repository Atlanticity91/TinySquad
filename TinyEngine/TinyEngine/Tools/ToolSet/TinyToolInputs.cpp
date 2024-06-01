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
    m_new_input{ "New Input" },
    m_new_query{ },
    m_input_remove{ },
    m_input_query{ TINY_UINT_MAX },
    m_input_devices{ },
    m_input_states{ },
    m_input_modifier{ }
{ 
    m_input_devices.emplace_back( TF_ICON_KEYBOARD );
    m_input_devices.emplace_back( TF_ICON_MOUSE );
    m_input_devices.emplace_back( TF_ICON_GAMEPAD );

    m_input_states   = TinyInputs::GetInputStateList( );
    m_input_modifier = TinyInputs::GetInputModifierList( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolInputs::OnTick( TinyGame* game, TinyToolbox& toolbox ) { 
    auto& inputs    = game->GetInputs( );
    auto& input_map = inputs.GetMap( );

    DrawControls( game, inputs );

    ImGui::SeparatorText( "Inputs Table" );

    DrawNewInput( inputs );
    DrawInputMap( input_map );

    if ( m_input_remove ) {
        if ( m_input_query == TINY_UINT_MAX )
            input_map.erase( m_input_remove );
        else
            input_map[ m_input_remove ].Values.erase( m_input_query );

        m_input_remove.undefined( );
        m_input_query = TINY_UINT_MAX;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolInputs::DrawControls( TinyGame* game, TinyInputManager& inputs ) {
    auto& filesystem = game->GetFilesystem( );
    auto button_size = ( ImGui::GetContentRegionAvail( ).x - ImGui::GetStyle( ).ItemSpacing.x ) * .5f;

    auto file_dialog = TinyFileDialog{ };
    auto file_buffer = tiny_buffer<256>{ };
    auto* file_str   = file_buffer.as_chars( );
    auto file_length = file_buffer.length( );

    file_dialog.Name    = "Load Inputs";
    file_dialog.Path    = filesystem.GetDevDirNative( );
    file_dialog.Filters = "Tiny Inputs (*.tinyinputs)\0*.tinyinputs\0";

    if ( ImGui::Button( "Load", { button_size, 0.f } ) ) {
        if ( Tiny::OpenDialog( file_dialog, file_length, file_str ) ) {
        }
    }

    ImGui::SameLine( );

    file_dialog.Type = TD_TYPE_SAVE_FILE;
    file_dialog.Name = "Save Inputs";

    ImGui::BeginDisabled( true );
    if ( ImGui::Button( "Save", { button_size, 0.f } ) ) {
        if ( Tiny::OpenDialog( file_dialog, file_length, file_str ) ) {
        }
    }

    ImGui::EndDisabled( );

    if ( ImGui::Button( "New", { -1.f, 0.f } ) )
        inputs.Clear( );
}

void TinyToolInputs::DrawNewInput( TinyInputManager& inputs ) {
    TinyImGui::InputText( m_new_input );

    ImGui::SameLine( );

    if ( ImGui::Button( TF_ICON_SHARE_SQUARE ) ) {
        inputs.Register( m_new_input, { { TinyInputKey( KEY_A ), TI_STATE_PRESSED, TI_MODIFIER_UNDEFINED } } );

        m_new_input = "New Input";
    }
}

void TinyToolInputs::DrawInputQwery( TinyInputQuery& query ) {
    TinyImGui::Combo( tiny_cast( query.Descriptor.Device, tiny_uint& ), m_input_devices, 52.f );

    ImGui::SameLine( );

    auto input_types = TinyInputs::GetInputTypeList( query.Descriptor.Device );

    if ( query.Descriptor.Type > input_types.Count - 1 )
        query.Descriptor.Type = tiny_cast( 0, TinyInputTypes );

    TinyImGui::Combo( tiny_cast( query.Descriptor.Type, tiny_uint& ), input_types, 92.f );

    ImGui::SameLine( );

    auto input_keys = TinyInputs::GetInputKeyList( query.Descriptor.Device, query.Descriptor.Type );

    TinyImGui::Combo( tiny_cast( query.Descriptor.Key, tiny_uint& ), input_keys, 136.f );

    ImGui::SameLine( );

    TinyImGui::Combo( tiny_cast( query.State, tiny_uint& ), m_input_states, 96.f );

    ImGui::SameLine( );

    ImGui::BeginDisabled( query.Descriptor.Device > TI_DEVICE_MOUSE );
    auto modifier = tiny_cast( 0, tiny_uint );

    switch ( query.Modifier ) {
        case TI_MODIFIER_SHIFT : modifier = 1; break;
        case TI_MODIFIER_CTRL  : modifier = 2; break;
        case TI_MODIFIER_ALT   : modifier = 3; break;

        default: break;
    }

    TinyImGui::Combo( modifier, m_input_modifier, 70.f );

    switch ( modifier ) {
        case 0 : query.Modifier = TI_MODIFIER_UNDEFINED; break;
        case 1 : query.Modifier = TI_MODIFIER_SHIFT;     break;
        case 2 : query.Modifier = TI_MODIFIER_CTRL;      break;
        case 3 : query.Modifier = TI_MODIFIER_ALT;       break;

        default: break;
    }
    ImGui::EndDisabled( );
}

void TinyToolInputs::DrawInputMap( tiny_map<TinyInputQueries>& inputs ) {
    for ( auto& input : inputs ) {
        auto font_size   = ImGui::GetFontSize( );
        auto region      = ImGui::GetContentRegionAvail( );
        auto& style      = ImGui::GetStyle( );
        auto line_height = font_size + style.FramePadding.y * 2.f;
        auto flags       = ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_AllowOverlap;
        auto is_open     = ImGui::TreeNodeEx( input.Alias.c_str( ), flags );

        ImGui::SameLine( region.x - line_height * 2.2f );

        auto button_size = TinyImGui::CalcTextSize( TF_ICON_EYE_SLASH );

        if ( TinyImGui::Button( input.Data.IsActive ? TF_ICON_EYE : TF_ICON_EYE_SLASH, button_size ) )
            input.Data.IsActive = !input.Data.IsActive;

        ImGui::SameLine( region.x - line_height * .8f );

        if ( TinyImGui::Button( TF_ICON_TRASH_ALT, { line_height, line_height } ) )
            m_input_remove = input.Hash;

        if ( is_open ) {
            auto query_id = tiny_cast( 0, tiny_uint );

            ImGui::Separator( );

            TinyImGui::BeginVars( );
            TinyImGui::Checkbox( "Is Active", input.Data.IsActive );
            ImGui::BeginDisabled( );
            TinyImGui::Checkbox( "Is Consumed", input.Data.IsConsumed );
            ImGui::EndDisabled( );
            TinyImGui::EndVars( );

            ImGui::Separator( );

            DrawInputQwery( m_new_query );

            ImGui::SameLine( );

            if ( ImGui::Button( TF_ICON_SHARE_SQUARE ) ) {
                input.Data.Values.emplace_back( m_new_query );

                m_new_query = TinyInputQuery{ };
            }

            ImGui::Separator( );

            for ( auto& query : input.Data.Values ) {
                if ( TinyImGui::Button( TF_ICON_TRASH_ALT, { line_height, line_height } ) ) {
                    m_input_remove = input.Hash;
                    m_input_query = query_id;
                }

                ImGui::SameLine( );

                DrawInputQwery( query );

                query_id += 1;
            }

            ImGui::TreePop( );
        }

        ImGui::Separator( );
    }
}
