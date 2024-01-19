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
    _path_buffer{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolContent::OnTick(
    TinyGame* game,
    TinyEngine& engine,
    TinyToolbox& toolbox
) {
    auto& filesystem = engine.GetFilesystem( );
    auto& assets = engine.GetAssets( );
    auto& registry = assets.GetRegistry( );

    auto button_size = ( ImGui::GetContentRegionAvail( ).x - ImGui::GetStyle( ).ItemSpacing.x ) * .5f;
    auto filters = "Tiny Registry (*.tinyregistry)\0*.tinyregistry\0";

    if ( ImGui::Button( "Load", { button_size, 0.f } ) ) {
        if ( Tiny::OpenDialog( Tiny::TD_TYPE_OPEM_FILE, filters, _path_buffer.length( ), _path_buffer ) ) {
            registry.Load( filesystem, _path_buffer );

            _has_changed = false;
        }
    }

    ImGui::SameLine( );

    ImGui::BeginDisabled( !_has_changed );
    if ( ImGui::Button( "Save", { button_size, 0.f } ) ) {
        if ( Tiny::OpenDialog( Tiny::TD_TYPE_SAVE_FILE, filters, _path_buffer.length( ), _path_buffer ) )
            registry.Save( filesystem, _path_buffer );
    }
    ImGui::EndDisabled( );

    if ( ImGui::Button( "Import", { -1.f, 0.f } ) ) {
        auto path = std::string{ filesystem.GetWorkingDir( ).get( ) } + "Ressources\\";

        if ( Tiny::OpenDialog( Tiny::TD_TYPE_OPEM_FILE, path, "All Files (*.*)\0*.*\0Texture (*.png)\0*.png\0", _path_buffer.length( ), _path_buffer ) ) {
            _has_changed = !filesystem.GetIsFile( _path_buffer, TINY_REGISTRY_EXT );

            if ( _has_changed ) {
                if ( filesystem.GetIsAssetFile( _path_buffer ) || filesystem.GetIsArchiveFile( _path_buffer ) )
                    _has_changed = assets.LoadPath( game, _path_buffer );
                else
                    _has_changed = assets.Import( game, _path_buffer );
            }

            if ( !_has_changed )
                ImGui::OpenPopup( "Import Failed" );
        }
    }

    if ( TinyImGui::BeginModal( "Import Failed" ) ) {
        ImGui::Text( "Asset importation failed for :" );
        ImGui::Text( _path_buffer );

        ImGui::Separator( );

        if ( TinyImGui::RightButton( "OK" ) )
            ImGui::CloseCurrentPopup( );

        TinyImGui::EndModal( );
    }

    ImGui::SeparatorText( "Assets" );

    auto& metadatas = registry.GetMetadatas( );
    auto to_remove = std::string{ "" };

    if ( metadatas.size( ) > 0 ) {
        if ( ImGui::BeginTable( "AssetData", 5, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders ) ) {
            ImGui::TableSetupColumn( "Name", ImGuiTableColumnFlags_WidthFixed );
            ImGui::TableSetupColumn( "Type", ImGuiTableColumnFlags_WidthFixed );
            ImGui::TableSetupColumn( "Use", ImGuiTableColumnFlags_WidthFixed );
            ImGui::TableSetupColumn( "", ImGuiTableColumnFlags_WidthFixed );
            ImGui::TableSetupColumn( "", ImGuiTableColumnFlags_WidthFixed );

            ImGui::TableHeadersRow( );

            for ( auto& metadata : metadatas ) {
                ImGui::TableNextRow( );

                ImGui::TableNextColumn( );
                ImGui::Text( metadata.String.c_str( ) );

                ImGui::TableNextColumn( );
                auto type = ConvertType( metadata.Data.Type );

                ImGui::Text( "%s", type.get( ) );

                ImGui::TableNextColumn( );
                ImGui::Text( "%d", metadata.Data.Reference );

                ImGui::TableNextColumn( );

                TINY_IMGUI_SCOPE_ID(
                    if ( ImGui::Button( "X" ) ) {
                        to_remove = metadata.String;

                        _has_changed = true;
                    }
                );

                ImGui::TableNextColumn( );

                TINY_IMGUI_SCOPE_ID(
                    if ( ImGui::Button( "E" ) ) {
                    }
                );

                /*
                if ( ImGui::IsItemHovered( ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_NoSharedDelay ) ) {
                    if ( ImGui::BeginItemTooltip( ) ) {
                        auto asset = TinyAsset{ TA_TYPE_TEXTURE_2D };

                        asset.Hash = metadata.Hash;
                        asset.Handle = metadata.Data.Handle;

                        auto texture = assets.GetAssetAs<TinyTexture2D>( asset );

                        if ( texture ) {
                            auto m_Dset = ImGui_ImplVulkan_AddTexture( texture->GetSampler( ), texture->GetView( ), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL );

                            ImVec2 viewportPanelSize = ImVec2{ 512, 512 };
                            ImGui::Image( m_Dset, ImVec2{ viewportPanelSize.x, viewportPanelSize.y } );
                        }

                        ImGui::EndTooltip( );
                    }

                    if ( ImGui::IsMouseDoubleClicked( ImGuiMouseButton_Left ) ) {
                        printf( "d\n" );
                    }
                }
                */
            }

            if ( to_remove.size( ) > 0 )
                registry.Remove( to_remove.c_str( ) );

            ImGui::EndTable( );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_string TinyToolContent::ConvertType( TinyAssetTypes type ) const {
    auto string = tiny_string{ "UNDEFINED" };

    switch ( type ) {
        case TA_TYPE_TEXTURE_2D: string = "TEXTURE 2D";   break;
        case TA_TYPE_TEXTURE_3D: string = "TEXTURE 3D";   break;
        case TA_TYPE_SHADER: string = "SHADER";       break;
        case TA_TYPE_MATERIAL: string = "MATERIAL";     break;
        case TA_TYPE_GEOMETRY: string = "GEOMETRY";     break;
        case TA_TYPE_CUE: string = "CUE";          break;
        case TA_TYPE_SCRIPT: string = "SCRIPT";       break;
        case TA_TYPE_ANIMATION_2D: string = "ANIMATION 2D"; break;
        case TA_TYPE_ANIMATION_3D: string = "ANIMATION 3D"; break;

        default: break;
    }

    return string;
}
