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

#pragma once

#include "TinyGraphicPhysical.h"

tm_class TinyGraphicLogical final {

private:
	VkDevice _handle;

public:
	TinyGraphicLogical( );

	~TinyGraphicLogical( ) = default;

	bool Create( const TinyGraphicPhysical& physical );

	bool Wait( );

	void Terminate( );

public:
	VkDevice Get( ) const;

private:
	tiny_list<VkDeviceQueueCreateInfo> GetQueuesCreateInfos( const TinyGraphicPhysical& physical );
	
public:
	operator VkDevice ( ) const;

};
