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

#include "TinyGraphicSwapchainProperties.h"

tm_class TinyGraphicSwapchain final {

private:
	VkSwapchainKHR				   _swap_chain;
	TinyGraphicSwapchainProperties _properties;

public:
	TinyGraphicSwapchain( );

	~TinyGraphicSwapchain( ) = default;

	bool Create( TinyGraphicContext& graphic );

	void Terminate( const TinyGraphicLogical& logical );

public:
	const VkSwapchainKHR Get( ) const;

	const TinyGraphicSwapchainProperties& GetProperties( ) const;

private:
	void GetSwapchainProperties( const TinyGraphicSurface& surface, const VkSurfaceCapabilitiesKHR& capabilities );

	tiny_list<tiny_uint> GetSwapchainQueues( const TinyGraphicQueueManager& queues );

	VkExtent2D GetSwapchainExtent( 
		const TinyGraphicBoundaries& boundaries, 
		const VkSurfaceCapabilitiesKHR& capabilities 
	) const;

public:
	operator const VkSwapchainKHR ( ) const;

	operator const VkSwapchainKHR* ( ) const;

};
