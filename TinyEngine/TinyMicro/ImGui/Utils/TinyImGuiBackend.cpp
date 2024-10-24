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
TinyImGuiBackend::TinyImGuiBackend( )
	: m_local_pools{ VK_NULL_HANDLE }
{ }

bool TinyImGuiBackend::Create( 
    TinyWindow& window, 
    TinyGraphicManager& graphics,
    const TinyImGuiSpecification& specification
) {
    return  CreatePools( graphics, specification ) &&
            CreateInstance( window, graphics, specification );
}

void TinyImGuiBackend::Prepare( ) {
    ImGui_ImplVulkan_NewFrame( );
    ImGui_ImplGlfw_NewFrame( );
}

void TinyImGuiBackend::Flush( TinyGraphicManager& graphics ) {
    ImGui::Render( );

    auto& work_context = graphics.GetWorkdContext( );
    auto* draw_data    = ImGui::GetDrawData( );

    ImGui_ImplVulkan_RenderDrawData( draw_data, work_context.Queue->CommandBuffer );
}

void TinyImGuiBackend::Terminate( TinyGraphicManager& graphics ) {
    if ( vk::GetIsValid( m_local_pools ) ) {
        auto& logical = graphics.GetLogical( );

        ImGui_ImplVulkan_Shutdown( );
        ImGui_ImplGlfw_Shutdown( );

        vkDestroyDescriptorPool( logical, m_local_pools, vk::GetAllocator( ) );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyImGuiBackend::CreatePools(
    TinyGraphicManager& graphics,
    const TinyImGuiSpecification& specification
) {
    VkDescriptorPoolSize pool_sizes[] = {
        { VK_DESCRIPTOR_TYPE_SAMPLER               , specification.PoolSize },
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, specification.PoolSize },
        { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE         , specification.PoolSize },
        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE         , specification.PoolSize },
        { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER  , specification.PoolSize },
        { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER  , specification.PoolSize },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER        , specification.PoolSize },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER        , specification.PoolSize },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, specification.PoolSize },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, specification.PoolSize },
        { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT      , specification.PoolSize }
    };

    auto pool_info = VkDescriptorPoolCreateInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
    auto size      = tiny_cast( IM_ARRAYSIZE( pool_sizes ), tiny_uint );

    pool_info.pNext         = VK_NULL_HANDLE;
    pool_info.flags         = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_info.maxSets       = specification.PoolSize * size;
    pool_info.poolSizeCount = size;
    pool_info.pPoolSizes    = pool_sizes;

    return vk::Check( vkCreateDescriptorPool( graphics.GetLogical( ), tiny_rvalue( pool_info ), vk::GetAllocator( ), tiny_rvalue( m_local_pools ) ) );
}

bool TinyImGuiBackend::CreateInstance( 
    TinyWindow& window, 
    TinyGraphicManager& graphics,
    const TinyImGuiSpecification& specification
) {
    auto& queues      = graphics.GetQueues( );
    auto* queue       = queues.Acquire( VK_QUEUE_TYPE_GRAPHIC );
    auto queue_family = queues.GetPhysicalQueue( VK_QUEUE_TYPE_GRAPHIC ).Family;
    auto& render_pass = graphics.GetRenderPass( specification.RenderPass );
    auto init_info    = ImGui_ImplVulkan_InitInfo{ };
    auto state        = false;

    init_info.Instance        = graphics.GetInstance( );
    init_info.PhysicalDevice  = graphics.GetPhysical( );
    init_info.Device          = graphics.GetLogical( );
    init_info.QueueFamily     = queue_family;
    init_info.Queue           = queue->Queue;
    init_info.DescriptorPool  = m_local_pools;
    init_info.RenderPass      = render_pass;
    init_info.MinImageCount   = graphics.GetMinImageCount( );
    init_info.ImageCount      = graphics.GetImageCount( );
    init_info.MSAASamples     = graphics.GetMSAA( ).MinSamples;
    init_info.PipelineCache   = graphics.GetPipelineCache( );
    init_info.Subpass         = specification.Subpass;
    init_info.Allocator       = vk::GetAllocator( );
    init_info.CheckVkResultFn = TinyImGuiBackend::CheckVulkanResult;

    state = ImGui_ImplGlfw_InitForVulkan( window, true ) &&
            ImGui_ImplVulkan_Init( tiny_rvalue( init_info ) );

    queues.Release( VK_QUEUE_TYPE_GRAPHIC, queue );

    return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyImGuiBackend::CheckVulkanResult( VkResult result ) {
    if ( result != VK_SUCCESS ) {
        auto result_string = vk::GetResultString( result );
        auto* message      = result_string.as_string( );

        switch ( result ) {
            default:
            case  VK_NOT_READY:
            case  VK_TIMEOUT:
            case  VK_EVENT_SET:
            case  VK_EVENT_RESET:
            case  VK_INCOMPLETE:
            case  VK_SUBOPTIMAL_KHR:
            case  VK_THREAD_IDLE_KHR:
            case  VK_THREAD_DONE_KHR:
            case  VK_OPERATION_DEFERRED_KHR:
            case  VK_OPERATION_NOT_DEFERRED_KHR:
            case  VK_PIPELINE_COMPILE_REQUIRED_EXT:
                TINY_LOG_WARN( "ImGui Backend : {0:s}", message );
                break;

            case  VK_ERROR_OUT_OF_HOST_MEMORY:
            case  VK_ERROR_OUT_OF_DEVICE_MEMORY:
            case  VK_ERROR_INITIALIZATION_FAILED:
            case  VK_ERROR_DEVICE_LOST:
            case  VK_ERROR_MEMORY_MAP_FAILED:
            case  VK_ERROR_LAYER_NOT_PRESENT:
            case  VK_ERROR_EXTENSION_NOT_PRESENT:
            case  VK_ERROR_FEATURE_NOT_PRESENT:
            case  VK_ERROR_INCOMPATIBLE_DRIVER:
            case  VK_ERROR_TOO_MANY_OBJECTS:
            case  VK_ERROR_FORMAT_NOT_SUPPORTED:
            case  VK_ERROR_FRAGMENTED_POOL:
            case  VK_ERROR_SURFACE_LOST_KHR:
            case  VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            case  VK_ERROR_OUT_OF_DATE_KHR:
            case  VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
            case  VK_ERROR_INVALID_SHADER_NV:
            case  VK_ERROR_OUT_OF_POOL_MEMORY:
            case  VK_ERROR_INVALID_EXTERNAL_HANDLE:
            case  VK_ERROR_FRAGMENTATION:
            case  VK_ERROR_INVALID_DEVICE_ADDRESS_EXT:
            case  VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
            case  VK_ERROR_UNKNOWN:
                TINY_LOG_ERRR( "ImGui Backend : {0:s}", message );

                break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const VkDescriptorPool& TinyImGuiBackend::GetLocalPools( ) const { return m_local_pools; }
