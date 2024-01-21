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
    _show_guizmo{ true },
    _use_snap{ false },
    _mode{ TTWG_MODE_WORLD },
    _tool{ TTWG_TOOL_TRANSLATE_2D },
    _snap_translate{ 1.f },
    _snap_rotate{ 1.f },
    _snap_scale{ 1.f },
    _modes{
        "Local", "World"
    },
    _tools{
        "Translate 2D",
        "Rotate 2D",
        "Scale 2D",

        "Translate 3D",
        "Rotate 3D",
        "Scale 3D"
    }
{ }

void TinyToolCommon::SetGuizmoMode( TinyToolboxWidgetGuizmoModes mode ) { _mode = mode; }

void TinyToolCommon::SetGuizmoTool( TinyToolboxWidgetGuizmoTools tool ) { _tool = tool; }

void TinyToolCommon::SetGuizmo(
    TinyToolboxWidgetGuizmoModes mode, 
    TinyToolboxWidgetGuizmoTools tool 
) {
    _mode = mode;
    _tool = tool;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolCommon::OnTick(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) {
    TinyImGui::Collapsing( 
        "Guizmo",
        [ & ]( ) { 
            TinyImGui::BeginVars( );

            if ( TinyImGui::Dropdown( "Mode", _modes ) )
                _mode = _modes.Index == 0 ? TTWG_MODE_LOCAL : TTWG_MODE_WORLD;

            if ( TinyImGui::Dropdown( "Tool", _tools ) )
                _tool = tiny_cast( _tools.Index, TinyToolboxWidgetGuizmoTools );

            auto is_orthographic = _tool == TTWG_TOOL_TRANSLATE_2D ||
                                   _tool == TTWG_TOOL_ROTATE_2D    ||
                                   _tool == TTWG_TOOL_SCALE_2D;

            TinyImGui::EndVars( );

            ImGui::SeparatorText( "Snap Targets" );

            TinyImGui::BeginVars( );

            TinyImGui::Checkbox( "Use Snap", _use_snap );

            if ( is_orthographic ) {
                TinyImGui::InputVector( "Translate", 2, tiny_rvalue( _snap_translate.x ) );
                TinyImGui::InputScalar( "Rotate", _snap_rotate.x );
                TinyImGui::InputVector( "Scale", 2, tiny_rvalue( _snap_scale.x ) );
            } else {
                TinyImGui::InputVec3( "Translate", _snap_translate );
                TinyImGui::InputVec3( "Rotate", _snap_rotate );
                TinyImGui::InputVec3( "Scale", _snap_scale );
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

            ImGui::Separator( );
        }
    );

    TinyImGui::Collapsing(
        "Memory",
        [ & ]( ) { 
            TinyImGui::BeginVars( );

            auto& memory = TinyMemoryManager::GetSingleton( );

            auto occupancy = memory.GetOccupancy( );
            auto capacity = memory.GetCapacity( );

            TinyImGui::TextVar( "Memory", "%u / %u", occupancy, capacity );
            TinyImGui::TextVar( "Free", "%u", capacity - occupancy );
            TinyImGui::TextVar( "Blocks", "%u", memory.GetBlockCount( ) );

            TinyImGui::EndVars( );
        }
    );

#   ifdef DEBUG
    TinyImGui::Collapsing(
        "Fonts",
        [ & ]( ) {
            auto& filesystem = engine.GetFilesystem( );
            auto filters     = "TTF Fonts (*.ttf)\0*.ttf\0";

            tiny_buffer<256> buffer;

            if ( ImGui::Button( "Compress", { -1, 0.f } ) ) {
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

    ImGui::BeginDisabled( );
    TinyImGui::InputVector( "Aspect", 2, (float*)&boundaries.GetAspect( ) );
    TinyImGui::InputVector( "Viewport", 4, (float*)&boundaries.GetViewport( ).x );
    TinyImGui::InputVector( "Scissor", 4, (tiny_int*)&boundaries.GetScissor( ).offset.x );
    ImGui::EndDisabled( );
    TinyImGui::InputSlider( "Depth Min", (float*)&boundaries.GetViewport( ).minDepth, -1.f, 1.f );
    TinyImGui::InputSlider( "Depth Max", (float*)&boundaries.GetViewport( ).maxDepth, -1.f, 1.f );

    TinyImGui::EndVars( );
}

void TinyToolCommon::DrawSwapchain( TinyGraphicManager& graphics ) {
    auto& properties = graphics.GetSwapchain( ).GetProperties( );

    TinyImGui::BeginVars( );

    ImGui::BeginDisabled( );
    TinyImGui::TextVar( "Capacity", "%d", properties.Capacity );
    TinyImGui::TextVar( "Format", "%s", vk::CastFormat( properties.Format ) );
    TinyImGui::TextVar( "Color Space", "%s", vk::CastColorSpace( properties.ColorSpace ) );
    TinyImGui::TextVar( "Present Mode", "%s", vk::CastPresentMode( properties.PresentMode ) );
    ImGui::EndDisabled( );

    TinyImGui::EndVars( );
}

void TinyToolCommon::DrawPasses( TinyGraphicManager& graphics ) {
    auto& passes = graphics.GetPasses( );
    auto& bundles = passes.GetBundles( );

    for ( auto& bundle : bundles ) {
        if ( ImGui::CollapsingHeader( bundle.Name.c_str( ), 0 ) ) {
            TinyImGui::BeginVars( );

            for ( auto& target : bundle.Targets )
                TinyImGui::InputColor( target.Name.c_str( ), (float*)target.Clear.color.float32 );

            TinyImGui::EndVars( );

            if ( bundles.size( ) > 1 )
                ImGui::Separator( );
        }
    }
}
