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
 * @creation : 26/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicPipelineCacheHeader.h"

tm_class TinyGraphicPipelineCache final {

private:
	bool m_use_cache;
	VkPipelineCache	m_cache;

public:
	TinyGraphicPipelineCache( );

	~TinyGraphicPipelineCache( ) = default;

	void Enable( );

	void Disable( );

	bool Create( 
		TinyFilesystem& filesystem, 
		TinyGraphicPhysical& physical, 
		TinyGraphicLogical& logical 
	);

	void Terminate( 
		TinyFilesystem& filesystem, 
		TinyGraphicPhysical& physical, 
		TinyGraphicLogical& logical 
	);

private:
	tiny_storage Load(
		TinyFilesystem& filesystem, 
		TinyGraphicPhysical& physical 
	);

	void Save( 
		TinyFilesystem& filesystem, 
		TinyGraphicPhysical& physical, 
		TinyGraphicLogical& logical 
	);

public:
	bool GetUseCache( ) const;
	
	const VkPipelineCache& Get( ) const;

public:
	operator const VkPipelineCache& ( ) const;

};
