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
TinyToolContent::TinyToolContent( ) 
	: TinyToolCategory{ "Content" },
    TinyToolDialog{ "Tiny Registry (*.tinyregistry)\0*.tinyregistry\0" },
    _has_changed{ false },
    _type_count{ TinyAssetTypes::TA_TYPE_COUNT },
    _type_to_string{ TinyToolContent::TypeToString },
    _to_remove{ },
    _import_path{ }
{ }

void TinyToolContent::Create( TinyGame* game, TinyToolbox& toolbox ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolContent::OnTick( TinyGame* game, TinyToolbox& toolbox ) {
    auto& filesystem = game->GetFilesystem( );
    auto& assets     = game->GetAssets( );
    //auto& registry   = assets.GetRegistry( );
    auto button_size = ( ImGui::GetContentRegionAvail( ).x - ImGui::GetStyle( ).ItemSpacing.x ) * .5f;

    if ( ImGui::Button( "Load", { button_size, 0.f } ) ) {
        if ( OpenDialog( filesystem ) ) {
            //registry.Load( filesystem, _dialog_path );

            _has_changed = false;
        }
    }

    ImGui::SameLine( );

    ImGui::BeginDisabled( !_has_changed );
    if ( ImGui::Button( "Save", { button_size, 0.f } ) ) {
        if ( SaveDialog( filesystem ) ) {
            //registry.Save( filesystem, _dialog_path );

            _has_changed = false;
        }
    }
    ImGui::EndDisabled( );

    if ( ImGui::Button( "Import", { -1.f, 0.f } ) ) {
        auto dev_dir = filesystem.GetDevDir( );
        auto path = std::string{ dev_dir.as_chars( ) };

        if ( Tiny::OpenDialog( Tiny::TD_TYPE_OPEM_FILE, path, "All Files (*.*)\0*.*\0Texture (*.png)\0*.png\0", _import_path.length( ), _import_path ) ) {
            _has_changed = assets.Import( game, _import_path );

            if ( !_has_changed )
                ImGui::OpenPopup( "Import Failed" );
        }
    }

    if ( TinyImGui::BeginModal( "Import Failed" ) ) {
        ImGui::Text( "Asset importation failed for :" );
        ImGui::Text( _import_path.as_chars( ) );

        ImGui::Separator( );

        if ( TinyImGui::RightButton( "OK" ) )
            ImGui::CloseCurrentPopup( );

        TinyImGui::EndModal( );
    }

    ImGui::SeparatorText( "Assets" );

    const auto flags      = ImGuiTableFlags_Borders | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTableFlags_RowBg;
    const auto char_size  = ImGui::CalcTextSize( "#" ).x;

    if ( ImGui::BeginTable( "Asset List", 3, flags ) ) {
        ImGui::TableSetupColumn( "Asset",  ImGuiTableColumnFlags_WidthStretch );
        ImGui::TableSetupColumn( "Count",  ImGuiTableColumnFlags_WidthFixed, char_size * 6.0f );
        ImGui::TableSetupColumn( "Action", ImGuiTableColumnFlags_WidthFixed, char_size * 10.0f );
        ImGui::TableHeadersRow( );

        const auto node_flags = ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_SpanAllColumns;
        const auto leaf_flags = node_flags                          |
                                ImGuiTreeNodeFlags_FramePadding     |
                                ImGuiTreeNodeFlags_Leaf             |
                                ImGuiTreeNodeFlags_Bullet           |
                                ImGuiTreeNodeFlags_NoTreePushOnOpen |
                                ImGuiTreeNodeFlags_AllowOverlap;

        auto spacing = ImGui::GetStyle( ).ItemSpacing.x;
        auto type    = tiny_cast( 1, tiny_uint );

        while ( type < _type_count ) {
            auto name = _type_to_string( type );
            /*
            if ( strlen( name ) > 0 ) {
                ImGui::TableNextRow( );
                ImGui::TableNextColumn( );

                auto metadatas = registry.GetMetadatas( type );
                auto open = ImGui::TreeNodeEx( name, node_flags );

                ImGui::TableNextColumn( );
                ImGui::Text( "%u", metadatas.size( ) );
                ImGui::TableNextColumn( );

                if ( open ) {
                    for ( auto& metadata : metadatas ) {
                        auto* name_str = metadata->String.c_str( );
                        auto can_edit  = GetHasEditor( type );

                        ImGui::TableNextRow( );
                        ImGui::TableNextColumn( );

                        ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, { 3.5f, 3.5f } );
                        ImGui::TreeNodeEx( name_str, leaf_flags );
                        ImGui::PopStyleVar( );

                        ImGui::TableNextColumn( );
                        ImGui::Text( "%d", metadata->Data.Reference );
                        ImGui::TableNextColumn( );

                        ImGui::BeginDisabled( !can_edit );
                        if ( TinyImGui::Button( TF_ICON_EDIT ) ) {
                            _action   = TTC_ACTION_EDIT;
                            _metadata = metadata;
                        }
                        ImGui::EndDisabled( );

                        ImGui::SameLine( .0f, spacing * .25f );

                        ImGui::BeginDisabled( metadata->Data.Reference > 0 );
                        if ( TinyImGui::Button( TF_ICON_TRASH_ALT ) ) {
                            _has_changed = true;
                            _action      = TTC_ACTION_REMOVE;
                            _metadata    = metadata;
                        }
                        ImGui::EndDisabled( );
                    }

                    ImGui::TreePop( );
                }
            }
            */
            type += 1;
        }

        ImGui::EndTable( );
    }

    if ( _to_remove ) {
        //assets.UnLoad( game, { 0, _to_remove } );

        _to_remove.empty( );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
c_string TinyToolContent::TypeToString( tiny_uint type ) {
    auto string = "";

    switch ( type ) {
        case TA_TYPE_TEXTURE_2D      : string = "TEXTURE 2D";   break;
        case TA_TYPE_TEXTURE_CUBEMAP : string = "CUBE MAP";     break;
        case TA_TYPE_TEXTURE_ATLAS   : string = "ATLAS";        break;
        case TA_TYPE_TEXTURE_LUT     : string = "LUT";          break;
        case TA_TYPE_FONT            : string = "FONTS";        break;
        case TA_TYPE_SHADER          : string = "SHADER";       break;
        case TA_TYPE_MATERIAL        : string = "MATERIAL";     break;
        case TA_TYPE_GEOMETRY        : string = "GEOMETRY";     break;
        case TA_TYPE_CUE             : string = "CUE";          break;
        case TA_TYPE_SCRIPT          : string = "SCRIPT";       break;
        case TA_TYPE_ANIMATION_2D    : string = "ANIMATION 2D"; break;

        default: break;
    }

    return string;
}
