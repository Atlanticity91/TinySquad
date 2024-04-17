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
    _history{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
// === PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyBacker::TickMenubar( ) {
    if ( ImGui::BeginMenu( "File" ) ) {
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
    TinyImGui::TextVar( "Pack", "%s", "Dev/Test.tinyasset" );

    //ImGui::Combo( "Pack :", nullptr, nullptr, _history.size( ) );

    ImGui::SameLine( );

    if ( ImGui::Button( "..." ) ) {
        auto& filesystem = GetFilesystem( );
        auto path        = filesystem.GetDevDir( );

        if ( filesystem.OpenDialog( Tiny::TD_TYPE_OPEM_FILE, "", path ) )
            _history.emplace_back( path.as_string( ) );
    }

    TinyImGui::TextVar( "Author", "%s", "Atlanticity91" );
    TinyImGui::TextVar( "Version", "%d.%d.%d", 2024, 2, 7 );
    TinyImGui::TextVar( "Date", "%d/%d/%d", 18, 04, 2024 );
    TinyImGui::EndVars( );

    ImGui::SeparatorText( "Content" );

    const auto flags = ImGuiTableFlags_Borders | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTableFlags_RowBg;
    const auto char_size = ImGui::CalcTextSize( "#" ).x;

    if ( ImGui::BeginTable( "Asset List", 4, flags ) ) {
        ImGui::TableSetupColumn( "Type", ImGuiTableColumnFlags_WidthFixed, char_size * 4.0f );
        ImGui::TableSetupColumn( "Alias", ImGuiTableColumnFlags_WidthStretch );
        ImGui::TableSetupColumn( "Path", ImGuiTableColumnFlags_WidthStretch );
        ImGui::TableSetupColumn( "Compressed", ImGuiTableColumnFlags_WidthFixed, char_size * 10.0f );
        ImGui::TableHeadersRow( );

        const auto node_flags = ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_SpanAllColumns;
        const auto leaf_flags = node_flags |
            ImGuiTreeNodeFlags_FramePadding |
            ImGuiTreeNodeFlags_Leaf |
            ImGuiTreeNodeFlags_Bullet |
            ImGuiTreeNodeFlags_NoTreePushOnOpen |
            ImGuiTreeNodeFlags_AllowOverlap;

        auto spacing = ImGui::GetStyle( ).ItemSpacing.x;

        //auto* type_str = TypeToStr( 0 );

        ImGui::EndTable( );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
c_string TinyBacker::TypeToStr( const tiny_uint type ) const {
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
