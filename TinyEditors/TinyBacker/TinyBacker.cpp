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
    _history_id{ 0 },
    _delete_id{ TINY_UINT_MAX },
    _import_path{ },
    _history{ },
    _entries{ }
{
    _entries.emplace_back( { 0, false, "t_texture", "Dev/t_texture.png" } );
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
    

    //TinyImGui::Dropdown( "Pack", );
    TinyImGui::InputBegin( "Pack" );

    auto list = tiny_list<native_string>{ };

    /*
    for ( auto& history : _history )
        list.emplace( history.c_str( ) );
    */
    TINY_IMGUI_SCOPE_ID(
        if ( ImGui::Combo( "", tiny_rvalue( _history_id ), list.data( ), (int)list.size( ) ) ) {
            if ( _history_id == 0 ) {
                auto& filesystem = GetFilesystem( );
                auto path = filesystem.GetDevDir( );

                if ( filesystem.OpenDialog( Tiny::TD_TYPE_OPEM_FILE, "", path ) ) {
                    auto path_str = path.as_string( );

                    _history_id = _history.size( );
                    _history.emplace_back( path_str );

                    LoadContent( );
                }
            }
        }
    );
    TinyImGui::InputEnd( );

    TinyImGui::TextVar( "Author", "%s", "Atlanticity91" );
    TinyImGui::TextVar( "Version", "%d.%d.%d", 2024, 2, 7 );
    TinyImGui::TextVar( "Date", "%d/%d/%d-%d:%d:%d", 18, 04, 2024, 0, 0, 0 );
    TinyImGui::EndVars( );

    ImGui::SeparatorText( "Content" );

    if ( ImGui::Button( "Import" ) )
        ImportAsset( );

    DrawContent( );
    DrawPopups( );

    static bool b = true;
    ImGui::ShowDemoWindow( &b );
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyBacker::LoadContent( ) { }

void TinyBacker::ImportAsset( ) {
    auto& filesystem = GetFilesystem( );
    auto path        = filesystem.GetDevDir( );

    if ( filesystem.OpenDialog( Tiny::TD_TYPE_OPEM_FILE, "All Files (*.*)\0*.*\0", path ) ) {
        auto& assets   = GetAssets( );
        auto& importer = assets.GetImporter( );

        _import_path = path.as_string( );

        if ( !assets.Import( this, path ) )
            ImGui::OpenPopup( "Import Fail" );
    }
}

void TinyBacker::DrawEntry( tiny_uint entry_id, TinyBackerEntry& entry ) {
    auto* type_str  = TypeToStr( entry.Type );
    auto* alias_str = entry.Alias.c_str( );
    auto* path_str  = entry.Path.c_str( );

    ImGui::TableNextRow( );
    ImGui::TableNextColumn( );

    if ( TinyImGui::Button( TF_ICON_TRASH_ALT ) )
        _delete_id = entry_id;

    ImGui::SameLine( .0f, .0f );

    if ( TinyImGui::Button( TF_ICON_REDO ) ) { }

    ImGui::SameLine( .0f, .0f );

    if ( TinyImGui::Button( TF_ICON_EDIT ) ) { }

    ImGui::TableNextColumn( );

    TINY_IMGUI_SCOPE_ID(
        ImGui::Checkbox( "", tiny_rvalue( entry.IsCompressed ) );
    );

    {
        //TinyImGui::Theme::NotifYellow NotifOrange
        auto c = TinyImGui::ScopeColors{ ImGuiCol_Text, TinyImGui::Theme::NotifOrange };

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

    if ( _delete_id < _entries.size( ) ) {
        _entries.erase( _delete_id );

        _delete_id = TINY_UINT_MAX;
    }

    if ( ImGui::BeginTable( "Asset List", 5, flags ) ) {
        ImGui::TableSetupColumn( "##_Actions", ImGuiTableColumnFlags_WidthFixed, char_size * 9.f );
        ImGui::TableSetupColumn( "Lz4"       , ImGuiTableColumnFlags_WidthFixed, char_size * 3.f );
        ImGui::TableSetupColumn( "Type"      , ImGuiTableColumnFlags_WidthFixed, char_size * 14.f );
        ImGui::TableSetupColumn( "Alias"     , ImGuiTableColumnFlags_WidthStretch );
        ImGui::TableSetupColumn( "Path"      , ImGuiTableColumnFlags_WidthStretch );
        ImGui::TableHeadersRow( );

        auto entry_id = tiny_cast( 0, tiny_uint );

        for ( auto& entry : _entries )
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
        ImGui::Text( "Failed to import asset :" );
        ImGui::Text( _import_path.c_str( ) );
        ImGui::EndGroup( );

        if ( ImGui::Button( "Close" ) ) 
            ImGui::CloseCurrentPopup( );

        ImGui::EndPopup( );
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
