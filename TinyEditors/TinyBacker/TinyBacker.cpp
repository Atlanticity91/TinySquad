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

#include <TinyBacker/__tiny_backer_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyBacker::TinyBacker( )
    : TinyNut{ "Tiny Backer" },
    m_history{ "..." },
    m_archive{ },
    m_delete_entry{ },
    m_import_path{ },
    m_import_fails{ }
{ }

void TinyBacker::OnDragDrop( tiny_int path_count, native_string drop_paths[] ) {
    while ( path_count-- > 0 ) {
        m_import_path = drop_paths[ path_count ];

        if ( !ImportAsset( m_import_path ) )
            m_import_fails.create_back( m_import_path, "Undefined" );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyBacker::TickMenubar( ) {
    if ( ImGui::BeginMenu( "File" ) ) {
        if ( ImGui::MenuItem( "New" ) ) {
        }

        if ( ImGui::MenuItem( "Save" ) ) {
        }

        if ( ImGui::MenuItem( "Import" ) ) {
        }

        if ( ImGui::MenuItem( "Create" ) ) {
        }

        ImGui::Separator( );

        if ( ImGui::MenuItem( "Exit" ) )
            Stop( );

        ImGui::EndMenu( );
    }

    if ( ImGui::BeginMenu( "Help" ) ) {
        if ( ImGui::MenuItem( "About" ) ) {
        }

        ImGui::EndMenu( );
    }
}

void TinyBacker::TickUI( ) {
    TinyImGui::BeginVars( );
    
    if ( TinyImGui::Dropdown( "Pack", m_history ) ) {
        if ( m_history.Index == 0 )
            CreateArchive( );
        else
            LoadArchive( { m_history.Values[ m_history.Index ] } );
    }
    
    TinyImGui::InputText( "Author", m_archive.Author );
    TinyImGui::TextVar( 
        "Version", "%d.%d.%d", 
        Tiny::GetVersionMajor( m_archive.Header.Version ),
        Tiny::GetVersionMinor( m_archive.Header.Version ),
        Tiny::GetVersionPatch( m_archive.Header.Version )
    );
    TinyImGui::TextVar(
        "Date", "%d/%d/%d-%d:%d:%d", 
        m_archive.Header.Date.Day , m_archive.Header.Date.Month , m_archive.Header.Date.Year,
        m_archive.Header.Date.Hour, m_archive.Header.Date.Minute, m_archive.Header.Date.Second
    );
    TinyImGui::EndVars( );

    ImGui::SeparatorText( "Content" );

    if ( TinyImGui::ButtonIcon( TF_ICON_DOWNLOAD, "Import" ) )
        ImportAsset( );

    ImGui::SameLine( );

    if ( TinyImGui::ButtonIcon( TF_ICON_SAVE, "Save" ) )
        SaveArchive( { m_history.Values[ m_history.Index ] } );

    DrawContent( );
    DrawPopups( );
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyBacker::ImportAsset( ) {
    auto& filesystem  = GetFilesystem( );
    auto file_dialog  = TinyFileDialog{ };
    auto file_buffer  = tiny_buffer<256>{ };
    auto* file_string = file_buffer.as_chars( );
    auto file_length  = file_buffer.length( );
    
    file_dialog.Name    = "Load Asset";
    file_dialog.Path    = filesystem.GetDevDirNative( );
    file_dialog.Filters = "All Files (*.*)\0*.*\0";

    if ( Tiny::OpenDialog( file_dialog, file_length, file_string ) ) {
        auto asset_path = file_buffer.as_string( );

        ImportAsset( asset_path );
    }
}

bool TinyBacker::ImportAsset( const std::string& path ) {
    auto& assets = GetAssets( );
    auto path_   = tiny_string{ path };
    auto state   = assets.Import( this, path_ );

    if ( state ) {
        // m_archive.Archive.Entries.emplace( "", { } );
    } else
        ImGui::OpenPopup( "Import Fail" );

    return state;
}

void TinyBacker::DrawEntry(
    tiny_uint entry_id, 
    tiny_map_node<TinyArchiveEntryBuilder>& entry_node
) {
    auto& entry = entry_node.Data;
    auto* type_str  = TypeToStr( entry.Type );
    auto* alias_str = entry_node.Alias.c_str( );
    auto* path_str  = entry.Path.c_str( );

    ImGui::TableNextRow( );
    ImGui::TableNextColumn( );

    if ( TinyImGui::Button( TF_ICON_TRASH_ALT ) )
        m_delete_entry = entry_node.Alias;

    ImGui::SameLine( .0f, .0f );

    if ( TinyImGui::Button( TF_ICON_REDO ) ) { }

    ImGui::SameLine( .0f, .0f );

    if ( TinyImGui::Button( TF_ICON_EDIT ) ) { }

    ImGui::TableNextColumn( );

    TINY_IMGUI_SCOPE_ID(
        auto is_compressed = entry.Compresed > 0;
        
        ImGui::BeginDisabled( );
        ImGui::Checkbox( "", tiny_rvalue( is_compressed ) );
        ImGui::EndDisabled( );
    );

    {
        ImGui::TableNextColumn( );
        ImGui::Text( "%s", type_str );
        ImGui::TableNextColumn( );
        ImGui::Text( "%s", alias_str );
        ImGui::TableNextColumn( );
        ImGui::Text( "%s", path_str );
    }
}

void TinyBacker::DrawContent( ) {
    const auto flags     = ImGuiTableFlags_Borders | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTableFlags_RowBg;
    const auto char_size = ImGui::CalcTextSize( "#" ).x;

    if ( m_delete_entry.get_is_valid( ) ) {
        m_archive.Entries.erase( m_delete_entry );

        m_delete_entry.undefined( );
    }

    if ( ImGui::BeginTable( "Asset List", 5, flags ) ) {
        ImGui::TableSetupColumn( "##_Actions", ImGuiTableColumnFlags_WidthFixed, char_size * 9.f );
        ImGui::TableSetupColumn( "Lz4"       , ImGuiTableColumnFlags_WidthFixed, char_size * 3.f );
        ImGui::TableSetupColumn( "Type"      , ImGuiTableColumnFlags_WidthFixed, char_size * 14.f );
        ImGui::TableSetupColumn( "Alias"     , ImGuiTableColumnFlags_WidthStretch );
        ImGui::TableSetupColumn( "Path"      , ImGuiTableColumnFlags_WidthStretch );
        ImGui::TableHeadersRow( );

        auto entry_id = tiny_cast( 0, tiny_uint );

        for ( auto& entry : m_archive.Entries )
            DrawEntry( entry_id++, entry );
        
        ImGui::EndTable( );
    }
}

void TinyBacker::DrawPopups( ) {
    if ( ImGui::BeginPopupModal( "Import Fail", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
        auto& window = GetNutWindow( );
        auto* icon   = window.GetIcon( "Logo" );

        ImGui::Image( icon->Icon.Descriptor, { 48.f, 48.f } );

        ImGui::SameLine( );
        TinyImGui::ShiftCursorX( 20.f );

        ImGui::BeginGroup( );

        for ( auto& fail : m_import_fails ) {
            auto* fail_cause = fail.Cause.c_str( );
            auto* fail_path  = fail.Path.c_str( );

            ImGui::SeparatorText( fail_path );
           
            ImGui::Text( "Importation failed cause(s) : " );
            ImGui::Text( fail_cause );

            ImGui::Separator( );
        }

        ImGui::EndGroup( );

        if ( ImGui::Button( "Close" ) ) {
            ImGui::CloseCurrentPopup( );

            m_import_fails.clear( );
        }

        ImGui::EndPopup( );
    }
}

void TinyBacker::CreateArchive( ) {
    m_archive.Header = TinyAssetHeader{ };
    m_archive.Author = "";
    m_archive.Entries.clear( );
}

void TinyBacker::LoadArchive( const std::string& path ) {
    if ( !path.empty( ) ) {
        auto& filesystem = GetFilesystem( );
        auto file        = filesystem.OpenFile( path, TF_ACCESS_BINARY_READ );

        if ( true )
            SaveArchive( "" );

        if ( file.GetIsValid( ) ) {

        }
    }
}

void TinyBacker::SaveArchive( const std::string& path ) {
    if ( !path.empty( ) ) {
        auto& filesystem = GetFilesystem( );
        auto& assets     = GetAssets( );

        if ( path == "..." ) {
            if ( Tiny::OpenDialog( { }, 0, nullptr ) ) {

            } else
                return;
        }

        auto file = filesystem.OpenFile( path, TF_ACCESS_BINARY_WRITE );

        if ( file.GetIsValid( ) ) {
            assets.Export( file, {} );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
native_string TinyBacker::TypeToStr( const tiny_uint type ) const {
    auto type_str = "Custom";

    switch ( type ) {
        case TA_TYPE_CONFIG          : type_str = "Config";       break;
        case TA_TYPE_ARCHIVE         : type_str = "Archive";      break;
        case TA_TYPE_TEXTURE_2D      : type_str = "Texture 2D";   break;
        case TA_TYPE_TEXTURE_3D      : type_str = "Texture 3D";   break;
        case TA_TYPE_TEXTURE_ATLAS   : type_str = "Atlas";        break;
        case TA_TYPE_TEXTURE_CUBEMAP : type_str = "Cubemap";      break;
        case TA_TYPE_TEXTURE_LUT     : type_str = "Lut";          break;
        case TA_TYPE_ANIMATION_2D    : type_str = "Animation 2D"; break;
        case TA_TYPE_ANIMATION_3D    : type_str = "Animation 3D"; break;
        case TA_TYPE_FONT            : type_str = "Font";         break;
        case TA_TYPE_SHADER          : type_str = "Shader";       break;
        case TA_TYPE_MATERIAL        : type_str = "Material";     break;
        case TA_TYPE_GEOMETRY        : type_str = "Geometry";     break;
        case TA_TYPE_CUE             : type_str = "Cue";          break;
        case TA_TYPE_SANPLES         : type_str = "Sample";       break;
        case TA_TYPE_SCRIPT          : type_str = "Script";       break;
        case TA_TYPE_SCENE           : type_str = "Scene";        break;
        case TA_TYPE_LOCALISATION    : type_str = "Localisation"; break;
        case TA_TYPE_TROPHY          : type_str = "Trophy";       break;
        case TA_TYPE_SAVE            : type_str = "Save";         break;

        default : break;
    }

    return type_str;
}
