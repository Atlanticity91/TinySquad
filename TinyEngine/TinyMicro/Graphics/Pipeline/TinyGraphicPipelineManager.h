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
	VkPipelineCache			  _cache;
	TinyLimitsStack			  _limits;

public:
	TinyGraphicPipelineManager( );

	~TinyGraphicPipelineManager( ) = default;

	bool Initialize( TinyFilesystem& filesystem, TinyGraphicLogical& logical );

	TinyGraphicPipelineBundle Create( TinyGraphicPipelineTypes type );

	void Terminate( TinyFilesystem& filesystem, TinyGraphicLogical& logical );

private:
	tiny_list<tiny_ubyte> LoadCache( TinyFilesystem& filesystem );

	void WriteCache( TinyFilesystem& filesystem, TinyGraphicLogical& logical );

	bool CreateCache( TinyFilesystem& filesystem, TinyGraphicLogical& logical );

	void CreateDescriptorLimits( );

	TinyGraphicPipelineBundle CreatePipeline2D( );

	TinyGraphicPipelineBundle CreatePipeline3D( );

	TinyGraphicPipelineBundle CreatePipelineCompute( );

public:
	const VkPipelineCache& GetCache( ) const;

	const TinyLimitsStack& GetLimits( ) const;

};
