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
 * @creation : 11/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Shaders/TinyGraphicShaderCompiler.h"

tm_struct TinyGraphicMSAA {

	VkSampleCountFlagBits MinSamples;
	VkSampleCountFlagBits MaxSamples;

};

tm_class TinyGraphicManager final : tiny_inherit( ITinyManager ) {

private:
	bool						_need_recreation;
	TinyGraphicBoundaries		_boundaries;
	TinyGraphicInstance			_instance;
	TinyGraphicSurface			_surface;
	TinyGraphicPhysical			_physical;
	TinyGraphicLogical			_logical;
	TinyGraphicQueueManager		_queues;
	TinyGraphicMemoryManager	_memory;
	TinyGraphicSwapchainManager	_swapchain;
	TinyGraphicRenderManager	_passes;
	TinyGraphicPipelineManager  _pipelines;
	TinyGraphicShaderCompiler   _compiler;
	TinyGraphicWorkContext		_work_context;

public:
	TinyGraphicManager( TinyGameOrientations orientation );

	~TinyGraphicManager( ) = default;

	TinyGraphicManager& AddBundle(
		const tiny_string& name,
		const TinyGraphicRenderBundle& bundle 
	);

	tiny_implement( bool Initialize( TinyFilesystem& file_system, TinyWindow& window ) );

	tiny_inline void AddCompilerMacro(
		const tiny_string& name, 
		const tiny_string& value 
	);

	tiny_inline void AddCompilerMacro( const TinyGraphicShaderMacro& macro );

	tiny_inline void AddCompilerMacros( tiny_init<TinyGraphicShaderMacro> macros );

	tiny_inline bool CompileShader(
		const TinyGraphicShaderCompilationContext& context,
		TinyGraphicShaderProperties& properties
	);

	TinyGraphicPipelineBundle CreatePipeline(
		TinyGraphicPipelineTypes type,
		const tiny_string& renderpass,
		tiny_uint subpass
	);

	void ReCreate( );

	void Acquire( const TinyWindow& window );

	tiny_inline bool BeginPass( const tiny_string& pass_name );

	bool BeginPass( const tiny_hash pass_hash );

	void Clear(
		const tiny_hash pass_name,
		TinyGraphicWorkContext& work_context,
		tiny_init<TinyGraphicClearRegion> attachements
	);

	void Clear(
		const tiny_hash pass_name,
		TinyGraphicWorkContext& work_context,
		tiny_init<TinyGraphicClearAttachement> attachements
	);

	void Draw(
		const TinyGraphicPipelineDrawcall & drawcall,
		TinyGraphicPipeline & pipeline,
		tiny_init<TinyGraphicPipelineBindpoint> bindpoints
	);

	bool NextSubpass( );

	void EndPass( );

	void Present( const TinyWindow& window );

	tiny_implement( void Terminate( TinyFilesystem& file_system, TinyWindow& window ) );

private:
	void ReCreate( const TinyWindow& window );

public:
	TinyGraphicContext GetContext( );

	bool GetNeedRecreation( ) const;

	TinyGraphicWorkContext& GetWorkdContext( );

	TinyGraphicBoundaries& GetBoundaries( );

	TinyGraphicInstance& GetInstance( );

	TinyGraphicSurface& GetSurface( );

	TinyGraphicPhysical& GetPhysical( );

	TinyGraphicLogical& GetLogical( );

	TinyGraphicQueueManager& GetQueues( );

	TinyGraphicMemoryManager& GetMemory( );

	tiny_inline tiny_uint GetSwapchainCapacity( ) const;

	TinyGraphicSwapchainManager& GetSwapchain( );

	TinyGraphicRenderManager& GetPasses( );

	tiny_inline const TinyLimitsStack& GetPipelineLimits( ) const;

	TinyGraphicPipelineManager& GetPipelines( );

	tiny_uint GetMinImageCount( ) const;

	tiny_uint GetImageCount( ) const;

	TinyGraphicMSAA GetMSAA( ) const;

	VkPipelineCache GetPipelineCache( );

	TinyGraphicRenderpass& GetRenderPass( const tiny_string& pass_name );

	tiny_inline const shaderc::CompileOptions& GetCompilerOptions( ) const;
	
};
