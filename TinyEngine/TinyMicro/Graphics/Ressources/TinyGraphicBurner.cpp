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
 * @creation : 18/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBurner::TinyGraphicBurner(
    TinyGraphicContext& graphic,
    VkQueueTypes queue_type 
) : _queue_type{ queue_type },
    _queue{ nullptr },
    _fence{ VK_NULL_HANDLE },
    _logical{ graphic.Logical }
{
    _queue = graphic.Queues.Acquire( queue_type );

    if ( _queue ) {
        vk::BeginCommandBuffer( _queue->CommandBuffer );

        auto fence_info = VkFenceCreateInfo{ VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };

        fence_info.pNext = VK_NULL_HANDLE;
        fence_info.flags = VK_NULL_FLAGS;

        if ( !vk::Check( vkCreateFence( graphic.Logical, &fence_info, vk::GetAllocator( ), &_fence ) ) ) {
            vk::EndCommandBuffer( _queue->CommandBuffer );

            _queue->InUse = VK_FALSE;
            _queue        = nullptr;
        }
    }
}

TinyGraphicBurner::~TinyGraphicBurner( ) { 
    if ( GetIsValid( ) ) {
        Execute( );

        vkDestroyFence( _logical, _fence, vk::GetAllocator( ) );

        _queue->InUse = VK_FALSE;
    }
}

void TinyGraphicBurner::Transit( 
    TinyGraphicTexture& texture,
    VkImageLayout target_layout 
) {
    if ( GetIsValid( ) ) {
        auto properties = texture.GetProperties( );
        auto src_stage  = VK_PIPELINE_STAGE_NONE;
        auto dst_stage  = VK_PIPELINE_STAGE_NONE;
        auto barrier    = VkImageMemoryBarrier{ VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };

        barrier.pNext               = VK_NULL_HANDLE;
        barrier.oldLayout           = properties.Layout;
        barrier.newLayout           = target_layout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image               = texture.GetImage( );
        barrier.subresourceRange = {
            VK_IMAGE_ASPECT_COLOR_BIT,
            0, properties.Levels,
            0, 1
        };

        if ( properties.Layout == VK_IMAGE_LAYOUT_UNDEFINED && target_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL ) {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            src_stage             = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            dst_stage             = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } else if ( properties.Layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && target_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL ) {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
            src_stage             = VK_PIPELINE_STAGE_TRANSFER_BIT;
            dst_stage             = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        } else
            return;

        vkCmdPipelineBarrier(
            _queue->CommandBuffer,
            src_stage, dst_stage,
            VK_NULL_FLAGS,
            0, VK_NULL_HANDLE,
            0, VK_NULL_HANDLE,
            1, &barrier
        );

        texture.SetLayout( target_layout );
    }
}

void TinyGraphicBurner::Upload( 
    const TinyGraphicBuffer& buffer,
    TinyGraphicTexture& texture
) {
    if ( GetIsValid( ) ) { 
        auto properties = texture.GetProperties( );
        auto region     = VkBufferImageCopy{ };

        region.bufferOffset                    = 0;
        region.bufferRowLength                 = 0;
        region.bufferImageHeight               = 0;
        region.imageSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel       = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount     = 1;
        region.imageOffset = { 0, 0, 0 };
        region.imageExtent = {
            properties.Width,
            properties.Height,
            properties.Depth
        };

        vkCmdCopyBufferToImage( _queue->CommandBuffer, buffer, texture, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region );
    }
}

void TinyGraphicBurner::Upload(
    const TinyGraphicBufferStaging& staging, 
    TinyGraphicBuffer& buffer,
    const VkBufferCopy& region
) {
    if ( 
        GetIsValid( )         && 
        staging.GetIsValid( ) &&
        buffer.GetIsValid( )  && 
        region.size > 0 
    )
        vkCmdCopyBuffer( _queue->CommandBuffer, staging.GetBuffer( ), buffer, 1, &region );
}

bool TinyGraphicBurner::Execute( ) {
    auto state = vk::EndCommandBuffer( _queue->CommandBuffer );

    if ( state ) {
        auto submit_info = VkSubmitInfo{ VK_STRUCTURE_TYPE_SUBMIT_INFO };

        submit_info.pNext                = VK_NULL_HANDLE;
        submit_info.waitSemaphoreCount   = 0;
        submit_info.pWaitSemaphores      = VK_NULL_HANDLE;
        submit_info.pWaitDstStageMask    = VK_NULL_HANDLE;
        submit_info.commandBufferCount   = 1;
        submit_info.pCommandBuffers      = &_queue->CommandBuffer.Buffer;
        submit_info.signalSemaphoreCount = 0;
        submit_info.pSignalSemaphores    = VK_NULL_HANDLE;

        vk::Check( vkQueueSubmit( _queue->Queue, 1, &submit_info, _fence ) );

        state = vk::Check( vkWaitForFences( _logical, 1, &_fence, VK_TRUE, UINT_MAX ) ) && 
                vk::ResetCommandBuffer( _queue->CommandBuffer );
    }

    return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyGraphicBurner::GetIsValid( ) const { return _queue != nullptr; }

VkLogicalCommandBuffer& TinyGraphicBurner::GetCommandBuffer( ) { 
	return _queue->CommandBuffer;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBurner::operator bool ( ) const { return GetIsValid( ); }

TinyGraphicBurner::operator VkLogicalCommandBuffer( ) { return GetCommandBuffer( ); }
