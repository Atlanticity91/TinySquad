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
    : TinyToolCategory{ "Common" },
    _guizmo{
        true,
        false,
        ImGuizmo::MODE::WORLD,
        ImGuizmo::OPERATION::TRANSLATE,
        tiny_vec3{ 1.f },
        tiny_vec3{ 1.f },
        tiny_vec3{ 1.f }
    },
    _modes{
        "Local", "World"
    },
    _tools{
        "Translate 2D",
        "Rotate 2D",
        "Scale 2D"
    }
{ }

void TinyToolCommon::SetGuizmoMode( ImGuizmo::MODE mode ) { _guizmo.Mode = mode; }

void TinyToolCommon::SetGuizmoTool( ImGuizmo::OPERATION tool ) { _guizmo.Tool = tool; }

void TinyToolCommon::SetGuizmo( ImGuizmo::MODE mode, ImGuizmo::OPERATION tool ) {
    _guizmo.Mode = mode;
    _guizmo.Tool = tool;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolCommon::OnTick(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) {
    auto& filesystem = engine.GetFilesystem( );

    TinyImGui::Collapsing(
        "Config",
        [ & ]( ) {
            if ( TinyImGui::Button( "Set Game Icon", { -1.f, .0f } ) ) {
            }
        } 
    );

    TinyImGui::Collapsing( 
        "Guizmo",
        [ & ]( ) {
            TinyImGui::BeginVars( );

            if ( TinyImGui::Dropdown( "Mode", _modes ) )
                _guizmo.Mode = _modes.Index == 0 ? ImGuizmo::MODE::LOCAL : ImGuizmo::MODE::WORLD;

            if ( TinyImGui::Dropdown( "Tool", _tools ) ) {
                switch ( _tools.Index ) {
                    case 0 : _guizmo.Tool = TinyGuizmoTranslate2D; break;
                    case 1 : _guizmo.Tool = TinyGuizmoRotate2D;    break;
                    case 2 : _guizmo.Tool = TinyGuizmoScale2D;     break;

                    default : break;
                }

                _guizmo.Tool = tiny_cast( _tools.Index, ImGuizmo::OPERATION );
            }

            auto is_orthographic = _guizmo.Tool == TinyGuizmoTranslate2D ||
                                   _guizmo.Tool == TinyGuizmoRotate2D    ||
                                   _guizmo.Tool == TinyGuizmoScale2D;

            TinyImGui::SeparatorText( "Snap Targets" );
            TinyImGui::Checkbox( "Use Snap", _guizmo.UseSnap );

            if ( is_orthographic ) {
                TinyImGui::InputVector( "Translate", 2, tiny_rvalue( _guizmo.SnapTranslate.x ) );
                TinyImGui::InputScalar( "Rotate", _guizmo.SnapRotate.x );
                TinyImGui::InputVector( "Scale", 2, tiny_rvalue( _guizmo.SnapScale.x ) );
            } else {
                TinyImGui::InputVec3( "Translate", _guizmo.SnapTranslate );
                TinyImGui::InputVec3( "Rotate", _guizmo.SnapRotate );
                TinyImGui::InputVec3( "Scale", _guizmo.SnapScale );
            }

            TinyImGui::EndVars( );
        }
    );

    TinyImGui::Collapsing( 
        "Graphics",
        [ & ]( ) {
            auto& graphics = engine.GetGraphics( );

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
            auto capacity = memory.GetCapacity( );

            TinyImGui::BeginVars( );

            TinyImGui::TextVar( "Memory", "%u / %u", occupancy, capacity );
            TinyImGui::TextVar( "Free", "%u", capacity - occupancy );
            TinyImGui::TextVar( "Blocks", "%u", memory.GetBlockCount( ) );

            TinyImGui::EndVars( );
        }
    );

#   ifdef DEBUG
    TinyImGui::Collapsing(
        "Convert To C-Array",
        [ & ]( ) {
            auto filters     = "TTF Fonts (*.ttf)\0*.ttf\0";

            tiny_buffer<256> buffer;

            if ( ImGui::Button( "Convert TTF", { -1, 0.f } ) ) {
                if ( Tiny::OpenDialog( Tiny::TD_TYPE_OPEM_FILE, filters, buffer.length( ), buffer.as_chars( ) ) ) {
                    auto info = filesystem.GetInformation( buffer.as_chars( ) );
                    auto path = info.Path + "\\" + info.Name + ".cpp";

                    ImGui::CompressTTF( buffer.as_chars( ), path.c_str( ), false, true, true );
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
    auto& physical = graphics.GetPhysical( );
    auto& properties = physical.GetProperties( );
    auto vendor = physical.GetVendor( );

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
    TinyImGui::TextVar( "Vendor", vendor.as_chars( ) );
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
        auto* name_str = bundle.Name.c_str( );

        if ( ImGui::CollapsingHeader( name_str, 0 ) ) {
            TinyImGui::BeginVars( );

            for ( auto& target : bundle.Targets ) {
                name_str = target.Name.c_str( );

                TinyImGui::InputColor( name_str, target.Clear.color );
            }

            TinyImGui::EndVars( );

            if ( bundles.size( ) > 1 )
                ImGui::Separator( );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolGuizmo& TinyToolCommon::GetGuizmo( ) { return _guizmo; }
