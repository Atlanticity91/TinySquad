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
    _has_changed{ false },
    _type_count{ TinyAssetTypes::TA_TYPE_COUNT },
    _type_to_string{ TinyToolContent::TypeToString },
    _type_editors{ },
    _action{ },
    _metadata{ nullptr }
{ }

void TinyToolContent::Create(
    TinyGame* game,
    TinyEngine& engine,
    TinyToolbox& toolbox
) {
    Register<TinyToolTexture2D, TA_TYPE_CONFIG>( );
    Register<TinyToolTexture2D, TA_TYPE_TEXTURE_2D>( );
}

bool TinyToolContent::OpenAssetEditor( 
    TinyGame* game, 
    const tiny_string name,
    TinyAssetMetadata& metadata 
) {
    auto& assets = game->GetAssets( );
    auto asset   = TinyAsset{ metadata.Type, name };
    auto state   = false;

    if ( assets.Acquire( game, asset ) ) {
        auto* value = assets.GetAsset( asset );

        if ( value )
            state = _type_editors[ metadata.Type ]->Open( game, name, value );
    }

    return state;
}

void TinyToolContent::RenderEditors( TinyGame* game ) {
    auto& assets = game->GetAssets( );

    for ( auto& editor : _type_editors )
        editor->Tick( game, assets );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolContent::OnTick(
    TinyGame* game,
    TinyEngine& engine,
    TinyToolbox& toolbox
) {
    auto& filesystem = engine.GetFilesystem( );
    auto& assets     = engine.GetAssets( );
    auto& registry   = assets.GetRegistry( );
    
    auto path_buffer = tiny_buffer<256>{ };
    auto button_size = ( ImGui::GetContentRegionAvail( ).x - ImGui::GetStyle( ).ItemSpacing.x ) * .5f;
    auto filters = "Tiny Registry (*.tinyregistry)\0*.tinyregistry\0";

    if ( ImGui::Button( "Load", { button_size, 0.f } ) ) {
        if ( Tiny::OpenDialog( Tiny::TD_TYPE_OPEM_FILE, filters, path_buffer.length( ), path_buffer ) ) {
            registry.Load( filesystem, path_buffer );

            _has_changed = false;
        }
    }

    ImGui::SameLine( );

    ImGui::BeginDisabled( !_has_changed );
    if ( ImGui::Button( "Save", { button_size, 0.f } ) ) {
        if ( Tiny::OpenDialog( Tiny::TD_TYPE_SAVE_FILE, filters, path_buffer.length( ), path_buffer ) )
            registry.Save( filesystem, path_buffer );
    }
    ImGui::EndDisabled( );

    if ( ImGui::Button( "Import", { -1.f, 0.f } ) ) {
        auto path = std::string{ filesystem.GetWorkingDir( ).get( ) } + "Ressources\\";

        if ( Tiny::OpenDialog( Tiny::TD_TYPE_OPEM_FILE, path, "All Files (*.*)\0*.*\0Texture (*.png)\0*.png\0", path_buffer.length( ), path_buffer ) ) {
            _has_changed = !filesystem.GetIsFile( path_buffer, TINY_REGISTRY_EXT );

            if ( _has_changed ) {
                if ( filesystem.GetIsAssetFile( path_buffer ) || filesystem.GetIsArchiveFile( path_buffer ) )
                    _has_changed = assets.LoadPath( game, path_buffer );
                else
                    _has_changed = assets.Import( game, path_buffer );
            }

            if ( !_has_changed )
                ImGui::OpenPopup( "Import Failed" );
        }
    }

    if ( TinyImGui::BeginModal( "Import Failed" ) ) {
        ImGui::Text( "Asset importation failed for :" );
        ImGui::Text( path_buffer );

        ImGui::Separator( );

        if ( TinyImGui::RightButton( "OK" ) )
            ImGui::CloseCurrentPopup( );

        TinyImGui::EndModal( );
    }

    ImGui::SeparatorText( "Assets" );

    const auto flags      = ImGuiTableFlags_Borders | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTableFlags_RowBg;
    const auto node_flags = ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_SpanAllColumns;
    const auto leaf_flags = node_flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    const auto char_size  = ImGui::CalcTextSize( "#" ).x;

    if ( ImGui::BeginTable( "Asset List", 3, flags ) ) {
        ImGui::TableSetupColumn( "Asset",  ImGuiTableColumnFlags_WidthStretch );
        ImGui::TableSetupColumn( "Count",  ImGuiTableColumnFlags_WidthFixed, char_size * 6.0f );
        ImGui::TableSetupColumn( "Action", ImGuiTableColumnFlags_WidthFixed, char_size * 10.0f );
        ImGui::TableHeadersRow( );

        auto spacing = ImGui::GetStyle( ).ItemSpacing.x;
        auto type    = tiny_cast( 1, tiny_uint );

        while ( type < _type_count ) {
            auto name = _type_to_string( type );

            if ( strlen( name ) > 0 ) {
                ImGui::TableNextRow( );
                ImGui::TableNextColumn( );

                auto metadatas = registry.GetMetadatas( type );
                auto open      = ImGui::TreeNodeEx( name, node_flags );

                ImGui::TableNextColumn( );
                ImGui::Text( "%u", metadatas.size( ) );
                ImGui::TableNextColumn( );

                if ( open ) {
                    for ( auto& metadata : metadatas ) {
                        auto name_str = metadata->String.c_str( );

                        ImGui::TableNextRow( );
                        ImGui::TableNextColumn( );
                        ImGui::TreeNodeEx( name_str, leaf_flags );
                        ImGui::TableNextColumn( );
                        ImGui::Text( "%d", metadata->Data.Reference );
                        ImGui::TableNextColumn( );

                        TINY_IMGUI_SCOPE_ID(
                            if ( ImGui::Button( TF_ICON_REDO ) ) {
                                _action   = TTC_ACTION_RELOAD;
                                _metadata = metadata;
                            }
                        );
                        ImGui::SameLine( .0f, spacing * .25f );
                        
                        TINY_IMGUI_SCOPE_ID(
                            if ( ImGui::Button( TF_ICON_EDIT ) ) {
                                _action   = TTC_ACTION_EDIT;
                                _metadata = metadata;
                            }
                        );
                        
                        ImGui::SameLine( .0f, spacing * .25f );

                        TINY_IMGUI_SCOPE_ID(
                            if ( ImGui::Button( TF_ICON_TRASH_ALT ) ) {
                                _action   = TTC_ACTION_REMOVE;
                                _metadata = metadata;
                            }
                        );
                    }

                    ImGui::TreePop( );
                }
            }

            type += 1;
        }

        ImGui::EndTable( );
    }

    if ( _metadata ) {
        switch ( _action ) {
            case TTC_ACTION_RELOAD : assets.Import( game, _metadata->Data.Source ); break;
            case TTC_ACTION_EDIT   : OpenAssetEditor( game, _metadata->String, _metadata->Data );break;
            case TTC_ACTION_REMOVE : registry.Remove( _metadata->Hash ); break;

            default: break;
        }

        _metadata = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
c_str TinyToolContent::TypeToString( tiny_uint type ) {
    auto string = "";

    switch ( type ) {
        case TA_TYPE_TEXTURE_2D   : string = "TEXTURE 2D";   break;
        case TA_TYPE_TEXTURE_3D   : string = "TEXTURE 3D";   break;
        case TA_TYPE_SHADER       : string = "SHADER";       break;
        case TA_TYPE_MATERIAL     : string = "MATERIAL";     break;
        case TA_TYPE_GEOMETRY     : string = "GEOMETRY";     break;
        case TA_TYPE_CUE          : string = "CUE";          break;
        case TA_TYPE_SCRIPT       : string = "SCRIPT";       break;
        case TA_TYPE_ANIMATION_2D : string = "ANIMATION 2D"; break;
        case TA_TYPE_ANIMATION_3D : string = "ANIMATION 3D"; break;

        default: break;
    }

    return string;
}
