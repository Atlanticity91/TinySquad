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
 * @creation : 13/10/2023
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
TinyToolbox::TinyToolbox( )
    : _is_in_use{ true },
    _has_dir{ false },
    _show_exemples{ true },
    _imgui{ nullptr },
    _local_pools{ nullptr },
    _fonts{ },
    _tools{ },
    _guizmo{ }
{ }

bool TinyToolbox::Initialize( TinyGame* game ) {
    auto& window   = game->GetWindow( );
    auto& graphics = game->GetGraphics( );
    auto state     = CreateImGui( )               && 
                     CreateImGuiPools( graphics ) && 
                     CreateImGuiContext( window, graphics );

    if ( state ) {
        CreateImGuiTheme( );

        state = CreateImGuiFont( ) && _tools.Initialize( game, tiny_self );
    }
    
    return state;
}

bool TinyToolbox::LoadFont(
    TinyFilesystem& filesystem,
    TinyGraphicManager& graphics,
    const TinyToolboxFont& font 
) {
    auto state = filesystem.GetFileExist( font.Path );

    if ( state ) {
        auto& io    = ImGui::GetIO( );
        auto* path  = font.Path.as_chars( );
        auto* _font = io.Fonts->AddFontFromFileTTF( path, font.Size );

        if ( _font ) {
            _fonts.emplace( font.Alias, _font );

            state = io.Fonts->Build( );
        }
    }

    return state;
}

bool TinyToolbox::LoadFonts(
    TinyFilesystem& filesystem,
    TinyGraphicManager& graphics,
    tiny_init<TinyToolboxFont> fonts
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

bool TinyToolbox::AddFont(
    const tiny_string& alias,
    tiny_int length,
    const tiny_uint* data,
    float size
) {
    auto& io = ImGui::GetIO( );
    auto* font = io.Fonts->AddFontFromMemoryCompressedTTF( tiny_cast( data, c_pointer ), length, size );

    if ( font ) {
        auto alias_str = alias.as_chars( );

        _fonts.emplace( alias_str, font );
    }

    return io.Fonts->Build( );
}

bool TinyToolbox::CreateFont(
    const tiny_string& name,
    float size,
    tiny_init<TinyToolboxFontEmbedded> fonts
) {
    auto state = fonts.size( );

    if ( state ) {
        auto config = ImFontConfig{ };
        auto& io    = ImGui::GetIO( );

        config.MergeMode = true;

        for ( auto& font : fonts ) {
            ImWchar icons_ranges[] = { font.Min, font.Max, 0 };
            
            io.Fonts->AddFontFromMemoryCompressedTTF( font.Glyphs, font.Length, size, tiny_rvalue( config ), icons_ranges );
        }

        state = io.Fonts->Build( );

        if ( state )
            _fonts.emplace( name, ImGui::GetFont( ) );
    }

    return state;
}

void TinyToolbox::SetFont( const tiny_string& name ) {
    auto* font = _fonts.get( name );

    if ( font )
        ImGui::SetCurrentFont( font );
}

void TinyToolbox::EnableNavigation( ) {
    auto& io = ImGui::GetIO( );
    
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}

void TinyToolbox::DisableNavigation( ) {
    auto& io = ImGui::GetIO( );

    io.ConfigFlags ^= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags ^= ImGuiConfigFlags_NavEnableGamepad;
}

void TinyToolbox::Show( ) { _is_in_use = true; }

void TinyToolbox::Hide( ) { _is_in_use = false; }

void TinyToolbox::Toggle( ) { _is_in_use = !_is_in_use; }

void TinyToolbox::ShowExemples( ) { _show_exemples = true; }

void TinyToolbox::ShowGuizmo2D( const tiny_hash entity_hash ) {
    _guizmo.Show( entity_hash, true );
}

void TinyToolbox::ShowGuizmo3D( const tiny_hash entity_hash ) {
    _guizmo.Show( entity_hash, false );
}

void TinyToolbox::HideGuizmo( ) { _guizmo.Hide( ); }

void TinyToolbox::DisplayAsset(
    TinyGame* game,
    const tiny_string& label,
    TinyAsset& asset 
) {
    auto& assets    = game->GetAssets( );
    auto asset_list = assets.GetAssets( asset.Type );
    auto context    = TinyImGui::DropdownContext{ asset_list, asset.Hash };

    if ( TinyImGui::Dropdown( label, context ) ) {
        assets.Release( game, asset );

        if ( context.Index > 0 ) {
            asset.Hash = tiny_hash{ context.Values[ context.Index ] };

            if ( !assets.Acquire( game, asset ) )
                asset.Hash = 0;
        } else
            asset.Hash = 0;
    }
}

void TinyToolbox::Tick( TinyGame* game ) {
    auto& inputs = game->GetInputs( );

    if ( inputs.Evaluate( "Show Dev", true ) )
        _is_in_use = !_is_in_use;

    if ( _is_in_use ) {
        if ( !_has_dir )
            CreateDevDir( game );

        ImGui_ImplVulkan_NewFrame( );
        ImGui_ImplGlfw_NewFrame( );

        ImGui::NewFrame( );
        _guizmo.DrawUI( game );

        ImGui::ShowDemoWindow( tiny_rvalue( _show_exemples ) );

        _tools.Tick( game, tiny_self );

        ImGui::Render( );

        auto* draw_data    = ImGui::GetDrawData( );
        auto& graphics     = game->GetGraphics( );
        auto& work_context = graphics.GetWorkdContext( );

        ImGui_ImplVulkan_RenderDrawData( draw_data, work_context.Queue->CommandBuffer );
    }
}

void TinyToolbox::Terminate( TinyGame* game ) {
    if ( _imgui ) {
        _tools.Terminate( game );

        ImGui_ImplVulkan_Shutdown( );
        ImGui_ImplGlfw_Shutdown( );
        ImGui::DestroyContext( );

        if ( _local_pools ) {
            auto& graphics = game->GetGraphics( );
            auto& logical  = graphics.GetLogical( );

            vkDestroyDescriptorPool( logical, _local_pools, vk::GetAllocator( ) );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyToolbox::CreateImGui( ) {
    IMGUI_CHECKVERSION( );

    _imgui = ImGui::CreateContext( );

    return _imgui != nullptr;
}

bool TinyToolbox::CreateImGuiPools( TinyGraphicManager& graphics ) {
    VkDescriptorPoolSize pool_sizes[] = {
        { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
    };

    auto pool_info = VkDescriptorPoolCreateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
    auto size      = tiny_cast( IM_ARRAYSIZE( pool_sizes ), tiny_uint );

    pool_info.pNext         = VK_NULL_HANDLE;
    pool_info.flags         = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_info.maxSets       = 1000 * size;
    pool_info.poolSizeCount = size;
    pool_info.pPoolSizes    = pool_sizes;

    return vk::Check( vkCreateDescriptorPool( graphics.GetLogical( ), tiny_rvalue( pool_info ), vk::GetAllocator( ), tiny_rvalue( _local_pools ) ) );
}

bool TinyToolbox::CreateImGuiContext( TinyWindow& window, TinyGraphicManager& graphics ) {
    auto& queues      = graphics.GetQueues( );
    auto* queue       = queues.Acquire( VK_QUEUE_TYPE_GRAPHIC );
    auto queue_family = queues.GetPhysicalQueue( VK_QUEUE_TYPE_GRAPHIC ).Family;
    auto& render_pass = graphics.GetRenderPass( TINY_OUTPASS_NAME );
    auto init_info    = ImGui_ImplVulkan_InitInfo{ };

    init_info.Instance        = graphics.GetInstance( );
    init_info.PhysicalDevice  = graphics.GetPhysical( );
    init_info.Device          = graphics.GetLogical( );
    init_info.QueueFamily     = queue_family;
    init_info.Queue           = queue->Queue;
    init_info.PipelineCache   = graphics.GetPipelineCache( );
    init_info.DescriptorPool  = _local_pools;
    init_info.Subpass         = 1;
    init_info.MinImageCount   = graphics.GetMinImageCount( );
    init_info.ImageCount      = graphics.GetImageCount( );
    init_info.MSAASamples     = graphics.GetMSAA( ).MinSamples;
    init_info.Allocator       = VK_NULL_HANDLE;
    init_info.CheckVkResultFn = nullptr;

    auto state = ImGui_ImplGlfw_InitForVulkan( window, true ) &&
                 ImGui_ImplVulkan_Init( tiny_rvalue( init_info ), render_pass );

    queues.Release( VK_QUEUE_TYPE_GRAPHIC, queue );

    return state;
}

void TinyToolbox::CreateImGuiTheme( ) {
    ImGui::StyleColorsDark( );

    auto& style = ImGui::GetStyle( );

    style.FramePadding = ImVec2{ 4.f, 4.f };

    auto* colors = style.Colors;

    colors[ ImGuiCol_Text                  ] = ImVec4( 1.00f, 1.00f, 1.00f, 1.00f );
    colors[ ImGuiCol_TextDisabled          ] = ImVec4( 0.50f, 0.50f, 0.50f, 1.00f );
    colors[ ImGuiCol_WindowBg              ] = ImVec4( 0.06f, 0.06f, 0.06f, 0.94f );
    colors[ ImGuiCol_ChildBg               ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
    colors[ ImGuiCol_PopupBg               ] = ImVec4( 0.08f, 0.08f, 0.08f, 0.94f );
    colors[ ImGuiCol_Border                ] = ImVec4( 0.43f, 0.43f, 0.50f, 0.50f );
    colors[ ImGuiCol_BorderShadow          ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
    colors[ ImGuiCol_FrameBg               ] = ImVec4( 0.44f, 0.44f, 0.44f, 0.60f );
    colors[ ImGuiCol_FrameBgHovered        ] = ImVec4( 0.57f, 0.57f, 0.57f, 0.70f );
    colors[ ImGuiCol_FrameBgActive         ] = ImVec4( 0.76f, 0.76f, 0.76f, 0.80f );
    colors[ ImGuiCol_TitleBg               ] = ImVec4( 0.04f, 0.04f, 0.04f, 1.00f );
    colors[ ImGuiCol_TitleBgActive         ] = ImVec4( 0.16f, 0.16f, 0.16f, 1.00f );
    colors[ ImGuiCol_TitleBgCollapsed      ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.60f );
    colors[ ImGuiCol_MenuBarBg             ] = ImVec4( 0.14f, 0.14f, 0.14f, 1.00f );
    colors[ ImGuiCol_ScrollbarBg           ] = ImVec4( 0.02f, 0.02f, 0.02f, 0.53f );
    colors[ ImGuiCol_ScrollbarGrab         ] = ImVec4( 0.31f, 0.31f, 0.31f, 1.00f );
    colors[ ImGuiCol_ScrollbarGrabHovered  ] = ImVec4( 0.41f, 0.41f, 0.41f, 1.00f );
    colors[ ImGuiCol_ScrollbarGrabActive   ] = ImVec4( 0.51f, 0.51f, 0.51f, 1.00f );
    colors[ ImGuiCol_CheckMark             ] = ImVec4( 0.13f, 0.75f, 0.55f, 0.80f );
    colors[ ImGuiCol_SliderGrab            ] = ImVec4( 0.13f, 0.75f, 0.75f, 0.80f );
    colors[ ImGuiCol_SliderGrabActive      ] = ImVec4( 0.13f, 0.75f, 1.00f, 0.80f );
    colors[ ImGuiCol_Button                ] = ImVec4( 0.13f, 0.75f, 0.55f, 0.40f );
    colors[ ImGuiCol_ButtonHovered         ] = ImVec4( 0.13f, 0.75f, 0.75f, 0.60f );
    colors[ ImGuiCol_ButtonActive          ] = ImVec4( 0.13f, 0.75f, 1.00f, 0.80f );
    colors[ ImGuiCol_Header                ] = ImVec4( 0.13f, 0.75f, 0.55f, 0.40f );
    colors[ ImGuiCol_HeaderHovered         ] = ImVec4( 0.13f, 0.75f, 0.75f, 0.60f );
    colors[ ImGuiCol_HeaderActive          ] = ImVec4( 0.13f, 0.75f, 1.00f, 0.80f );
    colors[ ImGuiCol_Separator             ] = ImVec4( 0.13f, 0.75f, 0.55f, 0.40f );
    colors[ ImGuiCol_SeparatorHovered      ] = ImVec4( 0.13f, 0.75f, 0.75f, 0.60f );
    colors[ ImGuiCol_SeparatorActive       ] = ImVec4( 0.13f, 0.75f, 1.00f, 0.80f );
    colors[ ImGuiCol_ResizeGrip            ] = ImVec4( 0.13f, 0.75f, 0.55f, 0.40f );
    colors[ ImGuiCol_ResizeGripHovered     ] = ImVec4( 0.13f, 0.75f, 0.75f, 0.60f );
    colors[ ImGuiCol_ResizeGripActive      ] = ImVec4( 0.13f, 0.75f, 1.00f, 0.80f );
    colors[ ImGuiCol_Tab                   ] = ImVec4( 0.13f, 0.75f, 0.55f, 0.80f );
    colors[ ImGuiCol_TabHovered            ] = ImVec4( 0.13f, 0.75f, 0.75f, 0.80f );
    colors[ ImGuiCol_TabActive             ] = ImVec4( 0.13f, 0.75f, 1.00f, 0.80f );
    colors[ ImGuiCol_TabUnfocused          ] = ImVec4( 0.18f, 0.18f, 0.18f, 1.00f );
    colors[ ImGuiCol_TabUnfocusedActive    ] = ImVec4( 0.36f, 0.36f, 0.36f, 0.54f );
    //colors[ ImGuiCol_DockingPreview        ] = ImVec4( 0.13f, 0.75f, 0.55f, 0.80f );
    //colors[ ImGuiCol_DockingEmptyBg        ] = ImVec4( 0.13f, 0.13f, 0.13f, 0.80f );
    colors[ ImGuiCol_PlotLines             ] = ImVec4( 0.61f, 0.61f, 0.61f, 1.00f );
    colors[ ImGuiCol_PlotLinesHovered      ] = ImVec4( 1.00f, 0.43f, 0.35f, 1.00f );
    colors[ ImGuiCol_PlotHistogram         ] = ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
    colors[ ImGuiCol_PlotHistogramHovered  ] = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
    colors[ ImGuiCol_TableHeaderBg         ] = ImVec4( 0.19f, 0.19f, 0.20f, 1.00f );
    colors[ ImGuiCol_TableBorderStrong     ] = ImVec4( 0.31f, 0.31f, 0.35f, 1.00f );
    colors[ ImGuiCol_TableBorderLight      ] = ImVec4( 0.23f, 0.23f, 0.25f, 1.00f );
    colors[ ImGuiCol_TableRowBg            ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
    colors[ ImGuiCol_TableRowBgAlt         ] = ImVec4( 1.00f, 1.00f, 1.00f, 0.07f );
    colors[ ImGuiCol_TextSelectedBg        ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.35f );
    colors[ ImGuiCol_DragDropTarget        ] = ImVec4( 1.00f, 1.00f, 0.00f, 0.90f );
    colors[ ImGuiCol_NavHighlight          ] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
    colors[ ImGuiCol_NavWindowingHighlight ] = ImVec4( 1.00f, 1.00f, 1.00f, 0.70f );
    colors[ ImGuiCol_NavWindowingDimBg     ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.20f );
    colors[ ImGuiCol_ModalWindowDimBg      ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.35f );
}

bool TinyToolbox::CreateImGuiFont( ) {
    auto state = AddFont( "Caskaydia", TinyCaskaydia_length, TinyCaskaydia_data, 16.f );

    if ( state ) {
        state = CreateFont(
            "Caskaydia",
            16.f,
            {
                { TinyFontAwesome_900_length, tiny_cast( TinyFontAwesome_900_data, tiny_uint* ), TF_ICON_MIN, TF_ICON_MAX }
            }
        );
    }

    return state;
}

void TinyToolbox::CreateDevDir( TinyGame* game ) {
    auto& filesystem = game->GetFilesystem( );
    auto dev_dir     = filesystem.GetDevDir( );

    if ( !filesystem.GetDirExist( dev_dir ) )
        filesystem.CreateDir( dev_dir );

    auto vert_path = std::string{ dev_dir.as_chars( ) } + "sv_default.vert";
    auto frag_path = std::string{ dev_dir.as_chars( ) } + "sf_default.frag";
    auto mat_path  = std::string{ dev_dir.as_chars( ) } + "m_default.tinyasset";

    if ( !filesystem.GetFileExist( vert_path ) )
        filesystem.Dump( vert_path, TinyDefaultVertex );

    if ( !filesystem.GetFileExist( frag_path ) )
        filesystem.Dump( frag_path, TinyDefaultFragment );

    if ( !filesystem.GetFileExist( mat_path ) ) {
        auto material_path = tiny_string{ mat_path.c_str( ) };
        auto& graphics     = game->GetGraphics( );
        auto& assets       = game->GetAssets( );
        auto material      = tiny_cast( graphics.CreatePipeline( TGP_TYPE_2D, TINY_OUTPASS_NAME, 0 ), TinyMaterialBuilder );

        material.InputBinding.clear( );
        material.InputAttributes.clear( );

        material.PassName = TINY_OUTPASS_NAME;
        material.ShaderStages = 2;
        material.ShaderStages[ 0 ] = "sv_default";
        material.ShaderStages[ 1 ] = "sf_default";

        material.Descriptors = 3;
        material.Descriptors[ TINY_RENDER_SET_CORE    ] = 1;
        material.Descriptors[ TINY_RENDER_SET_RENDER  ] = 2;
        material.Descriptors[ TINY_RENDER_SET_TEXTURE ] = 1;

        _pCreateSetBind( material, TINY_RENDER_SET_CORE,    0, TGBP_TYPE_UNIFORM, TGS_STAGE_VERTEX    );
        _pCreateSetBind( material, TINY_RENDER_SET_RENDER,  0, TGBP_TYPE_UNIFORM, TGS_STAGE_VERTEX    );
        _pCreateSetBind( material, TINY_RENDER_SET_RENDER,  1, TGBP_TYPE_UNIFORM, TGS_STAGE_VERTEX    );
        _pCreateSetBind( material, TINY_RENDER_SET_TEXTURE, 0, TGBP_TYPE_COMBINED, TGS_STAGE_FRAGMENT );

        auto* material_addr = tiny_cast( tiny_rvalue( material ), c_pointer );

        assets.Export( game, TA_TYPE_MATERIAL, material_path, material_addr );
        assets.Remove( game, "m_default" );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolboxGuizmo& TinyToolbox::GetGuizmo( ) { return _guizmo; }

const tiny_hash TinyToolbox::GetGuizmoSelection( ) const { return _guizmo.GetSelection( ); }
