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

#include "TinyGraphicSwapchain.h"

class TinyGraphicSwapchainTarget final { 

private:
	VkImage		_image;
	VkImageView _view;

public:
	TinyGraphicSwapchainTarget( );

	~TinyGraphicSwapchainTarget( ) = default;

	bool Create( const TinyGraphicLogical& logical, const TinyGraphicSwapchainProperties& properties, VkImage image );

	void Terminate( const TinyGraphicLogical& logical );

public:
	const VkImage GetImage( ) const;

	const VkImageView GetView( ) const;

};
