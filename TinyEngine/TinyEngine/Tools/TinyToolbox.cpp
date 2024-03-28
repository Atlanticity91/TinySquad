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
    _windows{ },
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

void TinyToolbox::Clear( ) { _tools.Clear( ); }

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

void TinyToolbox::ShowWindow( const tiny_string& name ) { _windows.Show( name ); }

void TinyToolbox::HideWindow( const tiny_string& name ) { _windows.Hide( name ); }

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

        Prepare( );

        _windows.Tick( game, tiny_self );
        _guizmo.DrawUI( game );
        _tools.Tick( game, tiny_self );

        Render( game );
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
    init_info.DescriptorPool  = _local_pools;
    init_info.RenderPass      = graphics.GetRenderPass( TINY_OUTPASS_NAME );
    init_info.MinImageCount   = graphics.GetMinImageCount( );
    init_info.ImageCount      = graphics.GetImageCount( );
    init_info.MSAASamples     = graphics.GetMSAA( ).MinSamples;
    init_info.PipelineCache   = graphics.GetPipelineCache( );
    init_info.Subpass         = 1;
    init_info.Allocator       = vk::GetAllocator( );
    init_info.CheckVkResultFn = nullptr;

    auto state = ImGui_ImplGlfw_InitForVulkan( window, true ) &&
                 ImGui_ImplVulkan_Init( tiny_rvalue( init_info ) );

    queues.Release( VK_QUEUE_TYPE_GRAPHIC, queue );

    return state;
}

void TinyToolbox::CreateImGuiTheme( ) {
    ImGui::StyleColorsDark( );

    auto& style = ImGui::GetStyle( );

    style.FramePadding    = TinyImGui::Theme::FramePadding;
    style.FrameRounding   = TinyImGui::Theme::FrameRounding;
    style.FrameBorderSize = TinyImGui::Theme::FrameRounding;
    style.IndentSpacing   = TinyImGui::Theme::IndentSpacing;

    auto* colors = style.Colors;

    colors[ ImGuiCol_Text                  ] = TinyImGui::Theme::Text;
    colors[ ImGuiCol_TextDisabled          ] = TinyImGui::Theme::TextDarker;
    colors[ ImGuiCol_WindowBg              ] = TinyImGui::Theme::Titlebar;
    colors[ ImGuiCol_ChildBg               ] = TinyImGui::Theme::Background;
    colors[ ImGuiCol_PopupBg               ] = TinyImGui::Theme::BackgroundPopup;
    colors[ ImGuiCol_Border                ] = TinyImGui::Theme::BackgroundDark;
    colors[ ImGuiCol_BorderShadow          ] = TinyImGui::Theme::Dark;
    colors[ ImGuiCol_FrameBg               ] = TinyImGui::Theme::PropertyField;
    colors[ ImGuiCol_FrameBgHovered        ] = TinyImGui::Theme::PropertyField;
    colors[ ImGuiCol_FrameBgActive         ] = TinyImGui::Theme::PropertyField;
    colors[ ImGuiCol_TitleBg               ] = TinyImGui::Theme::Titlebar;
    colors[ ImGuiCol_TitleBgActive         ] = TinyImGui::Theme::Titlebar;
    colors[ ImGuiCol_TitleBgCollapsed      ] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ ImGuiCol_MenuBarBg             ] = ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f };
    colors[ ImGuiCol_ScrollbarBg           ] = ImVec4{ 0.02f, 0.02f, 0.02f, 0.53f };
    colors[ ImGuiCol_ScrollbarGrab         ] = ImVec4{ 0.31f, 0.31f, 0.31f, 1.0f };
    colors[ ImGuiCol_ScrollbarGrabHovered  ] = TinyImGui::Theme::HoverPurple;
    colors[ ImGuiCol_ScrollbarGrabActive   ] = TinyImGui::Theme::ActivePurple;
    colors[ ImGuiCol_CheckMark             ] = TinyImGui::Theme::ActivePurple;
    colors[ ImGuiCol_SliderGrab            ] = ImVec4{ 0.51f, 0.51f, 0.51f, 0.7f };
    colors[ ImGuiCol_SliderGrabActive      ] = TinyImGui::Theme::ActivePurple;
    colors[ ImGuiCol_Button                ] = ImColor{ 56, 56, 56, 200 };
    colors[ ImGuiCol_ButtonHovered         ] = TinyImGui::Theme::HoverPurple;
    colors[ ImGuiCol_ButtonActive          ] = TinyImGui::Theme::ActivePurple;
    colors[ ImGuiCol_Header                ] = TinyImGui::Theme::GroupHeader;
    colors[ ImGuiCol_HeaderHovered         ] = TinyImGui::Theme::GroupHeader;
    colors[ ImGuiCol_HeaderActive          ] = TinyImGui::Theme::GroupHeader;
    colors[ ImGuiCol_Separator             ] = TinyImGui::Theme::BackgroundDark;
    colors[ ImGuiCol_SeparatorHovered      ] = TinyImGui::Theme::HoverPurple;
    colors[ ImGuiCol_SeparatorActive       ] = TinyImGui::Theme::Highlight;
    colors[ ImGuiCol_ResizeGrip            ] = ImVec4{ 0.91f, 0.91f, 0.91f, 0.25f };
    colors[ ImGuiCol_ResizeGripHovered     ] = ImVec4{ 0.81f, 0.81f, 0.81f, 0.67f };
    colors[ ImGuiCol_ResizeGripActive      ] = ImVec4{ 0.46f, 0.46f, 0.46f, 0.95f };
    colors[ ImGuiCol_Tab                   ] = TinyImGui::Theme::Titlebar;
    colors[ ImGuiCol_TabHovered            ] = TinyImGui::Theme::HoverPurple;
    colors[ ImGuiCol_TabActive             ] = TinyImGui::Theme::ActivePurple;
    colors[ ImGuiCol_TabUnfocused          ] = TinyImGui::Theme::Titlebar;
    colors[ ImGuiCol_TabUnfocusedActive    ] = TinyImGui::Theme::HoverPurple;
    //colors[ ImGuiCol_DockingPreview        ] = TinyImGui::Theme::HoverPurple;
    //colors[ ImGuiCol_DockingEmptyBg        ] = TinyImGui::Theme::GroupHeader;
    colors[ ImGuiCol_PlotLines             ] = TinyImGui::Theme::ActivePurple;
    colors[ ImGuiCol_PlotLinesHovered      ] = TinyImGui::Theme::HoverPurple;
    colors[ ImGuiCol_PlotHistogram         ] = ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
    colors[ ImGuiCol_PlotHistogramHovered  ] = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
    colors[ ImGuiCol_TableHeaderBg         ] = TinyImGui::Theme::GroupHeader;
    colors[ ImGuiCol_TableBorderStrong     ] = ImVec4( 0.31f, 0.31f, 0.35f, 1.00f );
    colors[ ImGuiCol_TableBorderLight      ] = TinyImGui::Theme::BackgroundDark;
    colors[ ImGuiCol_TableRowBg            ] = TinyImGui::Theme::Dark;
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

void TinyToolbox::CreateSpriteShaders( 
    TinyGame* game,
    TinyFilesystem& filesystem,
    const std::string& dev_dir
) {
    auto material_path = dev_dir + "m_sprite_dev.tinyasset";
    auto fragment_path = dev_dir + "sf_sprite_dev.frag";
    auto vertex_path   = dev_dir + "sv_sprite_dev.vert";

    if ( !filesystem.GetFileExist( vertex_path ) )
        filesystem.Dump( vertex_path, TinyDefaultSpriteVertex );

    if ( !filesystem.GetFileExist( fragment_path ) )
        filesystem.Dump( fragment_path, TinyDefaultSpriteFragment );

    if ( !filesystem.GetFileExist( material_path ) ) {
        auto& renderer = game->GetRenderer( );
        auto& assets   = game->GetAssets( );
        auto material  = renderer.CreateMaterial( game, TINY_OUTPASS_NAME, 0 );
        
        TinyMaterial::CreateShaders( material, { "sv_sprite_dev", "sf_sprite_dev" } );
        TinyMaterial::CreateBinding( material, { 0, tiny_sizeof( TinyRenderSpriteVertices ) } );
        TinyMaterial::CreateAttribute(
            material,
            {
                { 0, 0, TPA_TYPE_VEC4, tiny_offset_of( TinyRenderSpriteVertices, Position ) },
                { 1, 0, TPA_TYPE_VEC4, tiny_offset_of( TinyRenderSpriteVertices, Texture  ) },
                { 2, 0, TPA_TYPE_VEC4, tiny_offset_of( TinyRenderSpriteVertices, Color    ) }
            }
        );
        TinyMaterial::CreateSetBind( material, TRS_ID_CORE   , { 0, TGBP_TYPE_UNIFORM , 1              , TGS_STAGE_VERTEX   } );
        TinyMaterial::CreateSetBind( material, TRS_ID_TEXTURE - 1, { 0, TGBP_TYPE_COMBINED, TINY_MAX_VERTEX, TGS_STAGE_FRAGMENT } );

        auto* material_addr = tiny_cast( tiny_rvalue( material ), c_pointer );

        assets.Export( game, TA_TYPE_MATERIAL, material_path, material_addr );
        assets.Remove( game, "m_sprite_dev" );
    }
}

void TinyToolbox::CreateTextShaders(
    TinyGame* game,
    TinyFilesystem& filesystem, 
    const std::string& dev_dir 
) {
    auto material_path = dev_dir + "m_text_dev.tinyasset";
    auto fragment_path = dev_dir + "sf_text_dev.frag";
    auto vertex_path   = dev_dir + "sv_text_dev.vert";

    if ( !filesystem.GetFileExist( vertex_path ) )
        filesystem.Dump( vertex_path, TinyDefaultSpriteVertex );

    if ( !filesystem.GetFileExist( fragment_path ) )
        filesystem.Dump( fragment_path, TinyDefaultSpriteFragment );

    if ( !filesystem.GetFileExist( material_path ) ) {
        auto& renderer = game->GetRenderer( );
        auto& assets   = game->GetAssets( );
        auto material  = renderer.CreateMaterial( game, TINY_OUTPASS_NAME, 0 );

        TinyMaterial::CreateShaders( material, { "sv_text_dev", "sf_text_dev" } );
        TinyMaterial::CreateBinding( material, { 0, tiny_sizeof( TinyRenderTextVertice ) } );
        TinyMaterial::CreateAttribute(
            material,
            {
                { 0, 0, TPA_TYPE_VEC4, tiny_offset_of( TinyRenderTextVertice, Location   ) },
                { 1, 0, TPA_TYPE_VEC2, tiny_offset_of( TinyRenderTextVertice, UV         ) },
                { 2, 0, TPA_TYPE_UINT, tiny_offset_of( TinyRenderTextVertice, Parameters ) }
            }
        );
        TinyMaterial::CreateSetBind( material, TRS_ID_CORE   , { 0, TGBP_TYPE_UNIFORM , 1             , TGS_STAGE_VERTEX   } );
        TinyMaterial::CreateSetBind( material, TRS_ID_RENDER , { 0, TGBP_TYPE_UNIFORM , 1             , TGS_STAGE_VERTEX   } );
        TinyMaterial::CreateSetBind( material, TRS_ID_TEXTURE, { 0, TGBP_TYPE_COMBINED, TINY_MAX_FONTS, TGS_STAGE_FRAGMENT } );

        auto* material_addr = tiny_cast( tiny_rvalue( material ), c_pointer );

        assets.Export( game, TA_TYPE_MATERIAL, material_path, material_addr );
        assets.Remove( game, "m_text_dev" );
    }
}

void TinyToolbox::CreateDevDir( TinyGame* game ) {
    auto& filesystem = game->GetFilesystem( );
    auto dev_dir     = filesystem.GetDevDir( );

    if ( !filesystem.GetDirExist( dev_dir ) )
        filesystem.CreateDir( dev_dir );

    CreateSpriteShaders( game, filesystem, dev_dir );
    CreateTextShaders( game, filesystem, dev_dir );

    _has_dir = true;
}

void TinyToolbox::Prepare( ) {
    ImGui_ImplVulkan_NewFrame( );
    ImGui_ImplGlfw_NewFrame( );

    ImGui::NewFrame( );
    ImGui::ShowDemoWindow( tiny_rvalue( _show_exemples ) );
}

void TinyToolbox::Render( TinyGame* game ) {
    auto& graphics     = game->GetGraphics( );
    auto& work_context = graphics.GetWorkdContext( );

    ImGui::Render( );

    auto* draw_data = ImGui::GetDrawData( );

    ImGui_ImplVulkan_RenderDrawData( draw_data, work_context.Queue->CommandBuffer );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolWindow* TinyToolbox::GetWindow( const tiny_string& name ) const { 
    return _windows.Get( name ); 
}

TinyToolboxGuizmo& TinyToolbox::GetGuizmo( ) { return _guizmo; }

const tiny_hash TinyToolbox::GetGuizmoSelection( ) const { return _guizmo.GetSelection( ); }
