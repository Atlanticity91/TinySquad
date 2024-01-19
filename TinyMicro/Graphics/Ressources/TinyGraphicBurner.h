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

#pragma once

#include <TinyMicro/Graphics/Passes/TinyGraphicRenderManager.h>

tm_class TinyGraphicBurner final {

private:
	VkQueueTypes		_queue_type;
	VkLogicalQueue*		_queue;
	VkFence				_fence;
	TinyGraphicLogical& _logical;

public:
	TinyGraphicBurner( TinyGraphicContext& graphic, VkQueueTypes queue_type );

	~TinyGraphicBurner( );

	void Transit( TinyGraphicTexture& texture, VkImageLayout target_layout );

	void Upload( const TinyGraphicBuffer& buffer, TinyGraphicTexture& texture );

	void Upload( 
		const TinyGraphicBufferStaging& staging,
		TinyGraphicBuffer& buffer, 
		const VkBufferCopy& region 
	);

	bool Execute( );

public:
	bool GetIsValid( ) const;

	VkLogicalCommandBuffer& GetCommandBuffer( );

public:
	operator bool ( ) const;

	operator VkLogicalCommandBuffer( );

};
