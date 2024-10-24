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
TinyImGuiFontManager::TinyImGuiFontManager( ) 
	: m_fonts{ }
{ }

void TinyImGuiFontManager::Initialize( ) {
    if ( AddFont( "Caskaydia", TinyCaskaydia_length, TinyCaskaydia_data, 16.f ) ) {
        CreateFont(
            "Caskaydia", 16.f,
            { { TinyFontAwesome_900_length, tiny_cast( TinyFontAwesome_900_data, tiny_uint* ), TF_ICON_MIN, TF_ICON_MAX } }
        );
    }
}

bool TinyImGuiFontManager::LoadFont(
    TinyFilesystem& filesystem,
    TinyGraphicManager& graphics,
    const TinyImGuiFont& font
) {
    auto state = filesystem.GetFileExist( font.Path );

    if ( state ) {
        auto& io      = ImGui::GetIO( );
        auto* path    = font.Path.get( );
        auto* im_font = io.Fonts->AddFontFromFileTTF( path, font.Size );

        if ( im_font ) {
            m_fonts.emplace( font.Alias, im_font );

            state = io.Fonts->Build( );
        }
    }

    return state;
}

bool TinyImGuiFontManager::LoadFonts(
    TinyFilesystem& filesystem,
    TinyGraphicManager& graphics,
    tiny_init<TinyImGuiFont> fonts
) {
    auto state = fonts.size( ) > 0;

    if ( state ) {
        for ( auto& font : fonts ) {
            state = LoadFont( filesystem, graphics, font );

            if ( !state ) break;
        }
    }

    return state;
}

bool TinyImGuiFontManager::AddFont(
    const tiny_string& alias,
    tiny_int length,
    const tiny_uint* data,
    float size
) {
    auto& io      = ImGui::GetIO( );
    auto* im_font = io.Fonts->AddFontFromMemoryCompressedTTF( tiny_cast( data, native_pointer ), length, size );

    if ( im_font )
        m_fonts.emplace( alias, im_font );

    return io.Fonts->Build( );
}

bool TinyImGuiFontManager::CreateFont(
    const tiny_string& name,
    float size,
    tiny_init<TinyImGuiFontEmbedded> fonts
) {
    auto state = fonts.size( );

    if ( state ) {
        auto config = ImFontConfig{ };
        auto& io = ImGui::GetIO( );

        config.MergeMode = true;

        for ( auto& font : fonts ) {
            ImWchar icons_ranges[] = { font.Min, font.Max, 0 };

            io.Fonts->AddFontFromMemoryCompressedTTF( font.Glyphs, font.Length, size, tiny_rvalue( config ), icons_ranges );
        }

        state = io.Fonts->Build( );

        if ( state )
            m_fonts.emplace( name, ImGui::GetFont( ) );
    }

    return state;
}

void TinyImGuiFontManager::SetFont( const tiny_string& name ) {
    auto* font = m_fonts.get( name );

    if ( font )
        ImGui::SetCurrentFont( font );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyImGuiFontManager::GetHasFont( const tiny_string& name ) const {
	return m_fonts.find( name );
}
