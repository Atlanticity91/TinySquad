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
TinyToolCommon::TinyToolCommon( )
    : TinyToolCategory{ "Common" }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolCommon::OnTick( TinyGame* game, TinyToolbox& toolbox ) {
    auto& filesystem = game->GetFilesystem( );

    TinyImGui::Collapsing( 
        "Guizmo",
        [ & ]( ) {
            auto& guizmo = toolbox.GetGuizmo( );

            guizmo.DrawWidget( );
        }
    );

    TinyImGui::Collapsing( 
        "Graphics",
        [ & ]( ) {
            auto& graphics = game->GetGraphics( );

            if ( ImGui::Button( "ReCreate", { -1.f, 0.f } ) )
                graphics.ReCreate( );

            ImGui::SeparatorText( "Hardware" );

            DrawHardware( graphics );

            ImGui::SeparatorText( "Boundaries" );

            DrawBoundaries( graphics );

            ImGui::SeparatorText( "Swapchain" );

            DrawSwapchain( graphics );

            ImGui::SeparatorText( "Passes" );

            DrawPasses( graphics );
        }
    );

    TinyImGui::Collapsing(
        "Memory",
        [ & ]( ) {
            auto& memory = TinyMemoryManager::GetSingleton( );

            auto occupancy = memory.GetOccupancy( );
            auto capacity  = memory.GetCapacity( );

            TinyImGui::BeginVars( );

            TinyImGui::TextVar( "Memory", "%u / %u", occupancy, capacity );
            TinyImGui::TextVar( "Free", "%u", capacity - occupancy );
            TinyImGui::TextVar( "Blocks", "%u", memory.GetBlockCount( ) );

            TinyImGui::EndVars( );
        }
    );

    TinyImGui::Collapsing(
        "Native Functions",
        [ & ]( ) {
            auto& natives    = game->GetNatives( );
            auto& functions  = natives.GetNatives( );
            auto font_size   = ImGui::GetFontSize( );
            auto& style      = ImGui::GetStyle( );
            auto line_height = font_size + style.FramePadding.y * 2.f;
            auto to_remove   = tiny_hash{ };

            TinyImGui::BeginVars( );

            TinyImGui::TextVar( "Count", "%u", functions.size( ) );

            TinyImGui::EndVars( );

            ImGui::Separator( );

            for ( auto& function : functions ) {
                if ( TinyImGui::Button( TF_ICON_TRASH_ALT, { line_height, line_height } ) )
                    to_remove = function.Hash;

                ImGui::SameLine( );

                ImGui::Text( function.Alias.c_str( ) );
            }

            if ( to_remove ) {
                natives.Remove( to_remove );

                to_remove.empty( );
            }
        }
    );

    TinyImGui::Collapsing(
        "Config",
        [ & ]( ) {
            if ( TinyImGui::Button( "Set Game Icon", { -1.f, .0f } ) ) {
            }
        }
    );

#   ifdef DEBUG
    TinyImGui::Collapsing(
        "Convert To C-Array",
        [ & ]( ) {
            auto ttf_filters    = "TTF Fonts (*.ttf)\0*.ttf\0";
            auto shader_filters = "GLSL (*.glsl)\0*.glsl\0Vertex (*.vert)\0*.vert\0Fragment (*.frag)\0*.frag\0";

            tiny_buffer<256> buffer;

            if ( ImGui::Button( "Convert TTF", { -1.f, 0.f } ) ) {
                if ( Tiny::OpenDialog( TD_TYPE_OPEM_FILE, "", ttf_filters, buffer.length( ), buffer.as_chars( ) ) ) {
                    auto info = filesystem.GetInformation( buffer.as_chars( ) );
                    auto path = info.Path + "\\" + info.Name + "_to_array.cpp";

                    ImGui::CompressTTF( buffer.as_chars( ), path.c_str( ), false, true, true );
                }
            }

            if ( ImGui::Button( "Convert Shader", { -1.f, .0f } ) ) {
                if ( Tiny::OpenDialog( TD_TYPE_OPEM_FILE, "", shader_filters, buffer.length( ), buffer.as_chars( ) ) ) {
                    auto info = filesystem.GetInformation( buffer.as_chars( ) );
                    auto path = info.Path + "\\" + info.Name + "_to_array.cpp";

                    ConvertShader( game, info, path );
                }
            }
        }
    );
#   endif
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolCommon::DrawHardware( TinyGraphicManager& graphics ) {
    auto& physical   = graphics.GetPhysical( );
    auto& properties = physical.GetProperties( );
    auto vendor      = physical.GetVendor( );

    char driver[ 128 ] = "";
    sprintf_s(
        driver,
        tiny_size_chars( driver ),
        "%d.%d.%d",
        VK_VERSION_MAJOR( properties.apiVersion ),
        VK_VERSION_MINOR( properties.apiVersion ),
        VK_VERSION_PATCH( properties.apiVersion )
    );

    TinyImGui::BeginVars( );

    ImGui::BeginDisabled( );
    TinyImGui::TextVar( "Vendor", vendor.get( ) );
    TinyImGui::TextVar( "Driver", driver );
    TinyImGui::TextVar( "Name", (char*)properties.deviceName );
    ImGui::EndDisabled( );

    TinyImGui::EndVars( );
}

void TinyToolCommon::DrawBoundaries( TinyGraphicManager& graphics ) {
    auto& boundaries = graphics.GetBoundaries( );

    TinyImGui::BeginVars( );

    TinyImGui::InputVec2( "Aspect", boundaries.GetAspect( ) );
    TinyImGui::InputVulkan( "Viewport", boundaries.GetViewport( ) );
    TinyImGui::InputVulkan( "Scissor", boundaries.GetScissor( ) );

    TinyImGui::InputSlider( "Depth Min", tiny_cast( tiny_rvalue( boundaries.GetViewport( ).minDepth ), float* ), -1.f, 1.f );
    TinyImGui::InputSlider( "Depth Max", tiny_cast( tiny_rvalue( boundaries.GetViewport( ).maxDepth ), float* ), -1.f, 1.f );

    TinyImGui::EndVars( );
}

void TinyToolCommon::DrawSwapchain( TinyGraphicManager& graphics ) {
    auto& properties = graphics.GetSwapchain( ).GetProperties( );

    TinyImGui::BeginVars( );

    ImGui::BeginDisabled( );
    TinyImGui::TextVar( "Capacity", "%d", properties.Capacity );
    TinyImGui::InputVulkan( "Format", properties.Format );
    TinyImGui::InputVulkan( "Color Space", properties.ColorSpace );
    TinyImGui::InputVulkan( "Present Mode", properties.PresentMode );
    ImGui::EndDisabled( );

    TinyImGui::EndVars( );
}

void TinyToolCommon::DrawPasses( TinyGraphicManager& graphics ) {
    auto& passes = graphics.GetPasses( );
    auto& bundles = passes.GetBundles( );

    for ( auto& bundle : bundles ) {
        auto* name_str = bundle.Alias.c_str( );

        if ( ImGui::CollapsingHeader( name_str, 0 ) ) {
            TinyImGui::BeginVars( );

            for ( auto& target : bundle.Data.Targets ) {
                name_str = target.Name.c_str( );

                TinyImGui::InputColor( name_str, target.Clear.color );

                /*
                if ( ImGui::BeginItemTooltip( ) ) {
                    TinyImGui::Image( );

                    ImGui::EndTooltip( );
                }
                */

            }

            TinyImGui::EndVars( );

            if ( bundles.size( ) > 1 )
                ImGui::Separator( );
        }
    }
}

void TinyToolCommon::ConvertShader( 
    TinyGame* game,
    const TinyPathInformation& in_path,
    const std::string& out_path 
) {
    auto& filesystem = game->GetFilesystem( );
    auto& graphic    = game->GetGraphics( );
    auto file_memory = tiny_storage{ };
    auto shader      = TinyGraphicShaderSpecification{ };

    auto file = filesystem.OpenFile( in_path.Full, TF_ACCESS_READ );
    auto size = file.GetSize( );

    if ( size > 0 && tiny_allocate( file_memory, size ) ) {
        auto context = TinyGraphicShaderCompilationContext{ };
        auto* buffer = file_memory.GetAddress( );

        context.Name   = in_path.Name;
        context.Source = tiny_string{ tiny_cast( file_memory.Capacity, tiny_uint ), buffer };
        
        file.ReadAll( size, buffer );

        if ( graphic.CompileShader( context, shader ) ) {
            auto file = filesystem.OpenFile( out_path, TF_ACCESS_WRITE );
            auto* file_ = tiny_cast( tiny_rvalue( file ), TinyFile* );

            size = shader.Code.size( );

            file_->Write( "static const tiny_uint TinyShaderSize = %u;\n", size );
            file_->Write( "static const tiny_uint TinyShader[ TinyShaderSize ] = {" );
            
            for ( auto idx = tiny_cast( 0, tiny_uint ); idx < size; idx++ )
                file_->Write( "%s0x%08x%c", ( idx % 4 == 0 ) ? "\n\t" : " ", shader.Code[ idx ], ( idx < size - 1 ) ? ',' : ' ' );
            
            file_->Write( "\n};\n" );
        }
    }

    tiny_deallocate( file_memory );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
