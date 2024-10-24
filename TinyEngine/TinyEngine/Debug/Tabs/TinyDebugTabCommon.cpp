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
 * @creation : 02/08/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyDebugTabCommon::TinyDebugTabCommon( )
	: TinyImGuiTab{ "Common" } 
{ }

void TinyDebugTabCommon::OnCreate( native_pointer user_data ) { 
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyDebugTabCommon::OnTick(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	native_pointer user_data
) { 
	auto* game       = tiny_cast( user_data, TinyGame* );
    auto& filesystem = game->GetFilesystem( );
    
    TinyImGui::Collapsing(
        "Guizmo",
        [ & ]( ) {
            auto& debug  = game->GetDebug( );
            auto& guizmo = debug.GetGuizmo( );
            
            guizmo.TickWidget( graphics, inputs, game );
        }
    );

    TinyImGui::Collapsing(
        "Graphics",
        [ & ]( ) {
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

                to_remove.undefined( );
            }
        }
    );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyDebugTabCommon::DrawHardware( TinyGraphicManager& graphics ) {
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
    TinyImGui::TextVar( "Name", tiny_cast( properties.deviceName, char* ) );
    ImGui::EndDisabled( );

    TinyImGui::EndVars( );
}

void TinyDebugTabCommon::DrawBoundaries( TinyGraphicManager& graphics ) {
    auto& boundaries = graphics.GetBoundaries( );

    TinyImGui::BeginVars( );

    TinyImGui::InputVec2( "Aspect", boundaries.GetAspect( ) );
    TinyImGui::InputVulkan( "Viewport", boundaries.GetViewport( ) );
    TinyImGui::InputVulkan( "Scissor", boundaries.GetScissor( ) );

    TinyImGui::InputSlider( "Depth Min", tiny_cast( tiny_rvalue( boundaries.GetViewport( ).minDepth ), float* ), -1.f, 1.f );
    TinyImGui::InputSlider( "Depth Max", tiny_cast( tiny_rvalue( boundaries.GetViewport( ).maxDepth ), float* ), -1.f, 1.f );

    TinyImGui::EndVars( );
}

void TinyDebugTabCommon::DrawSwapchain( TinyGraphicManager& graphics ) {
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

void TinyDebugTabCommon::DrawPasses( TinyGraphicManager& graphics ) {
    auto& passes  = graphics.GetPasses( );
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
