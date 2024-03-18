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
 * @creation : 17/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicSwapchainTarget.h"

struct TinyGraphicWorkContext;

tm_class TinyGraphicSwapchainSync final { 

private:
	VkSemaphore _acquire;
	VkSemaphore _present;
	VkFence		_fence;

public:
	TinyGraphicSwapchainSync( );

	~TinyGraphicSwapchainSync( ) = default;

	bool Create( const TinyGraphicLogical& logical );

	void Terminate( const TinyGraphicLogical& logical );

private:
	bool CreateSwapchainSemaphore( const TinyGraphicLogical& logical, VkSemaphore& semaphore );

	bool CreateSwapchainFence( const TinyGraphicLogical& logical );

public:
	const VkSemaphore* GetAcquire( ) const;

	const VkSemaphore* GetPresent( ) const;

	const VkFence* GetFence( ) const;

};
