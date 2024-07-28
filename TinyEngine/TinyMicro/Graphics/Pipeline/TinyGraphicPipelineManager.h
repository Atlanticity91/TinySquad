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
 * @creation : 20/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicPipeline.h"

tm_class TinyGraphicPipelineManager final {

private:
	TinyGraphicPipelineCache m_cache;
	TinyLimitsStack	m_limits;

public:
	TinyGraphicPipelineManager( );

	~TinyGraphicPipelineManager( ) = default;

	bool Initialize( 
		TinyFilesystem& filesystem,
		TinyGraphicPhysical& physical,
		TinyGraphicLogical& logical 
	);

	tiny_inline void EnableCache( );

	tiny_inline void DisableCache( );

	TinyGraphicPipelineSpecification Create( const TinyGraphicPipelineTypes type );

	void Terminate( 
		TinyFilesystem& filesystem,
		TinyGraphicPhysical& physical, 
		TinyGraphicLogical& logical 
	);

private:
	void CreateDescriptorLimits( );

	TinyGraphicPipelineSpecification CreatePipeline2D( );

	TinyGraphicPipelineSpecification CreatePipeline3D( );

	TinyGraphicPipelineSpecification CreatePipelineCompute( );

public:
	tiny_inline bool GetUseCache( ) const;

	tiny_inline const VkPipelineCache& GetCache( ) const;

	const TinyLimitsStack& GetLimits( ) const;

};
