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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicManager::TinyGraphicManager( TinyGameOrientations orientation )
	: _need_recreation{ false },
	_boundaries{ orientation },
	_instance{ },
	_surface{ },
	_physical{ },
	_logical{ },
	_queues{ },
	_memory{ },
	_swapchain{ },
	_passes{ },
	_pipelines{ },
	_compiler{ },
	_work_context{ _logical }
{ }

TinyGraphicManager& TinyGraphicManager::AddBundle(
	const tiny_string& name,
	const TinyGraphicRenderBundle& bundle
) {
	_passes.AddBundle( name, bundle );

	return tiny_self;
}

bool TinyGraphicManager::Initialize( TinyFilesystem& file_system, TinyWindow& window ) {
	_boundaries.ReCreate( window );

	auto context = GetContext( );

	return  _instance.Create( window.GetTitle( ) )		   &&
			_surface.Create( window, _instance )		   &&
			_physical.Initialize( _instance, _surface )	   &&
			_surface.Initialize( _physical )			   &&
			_logical.Create( _physical )				   &&
			_queues.Create( _physical, _logical )		   && 
			_memory.Create( context )					   &&
			_swapchain.Create( context )				   &&
			_passes.Create( context )					   &&
			_pipelines.Initialize( file_system, _logical ) &&
			_compiler.Initialize( );
}

void TinyGraphicManager::AddCompilerMacro(
	const tiny_string& name,
	const tiny_string& value
) {
	_compiler.AddMacro( name, value );
}

void TinyGraphicManager::AddCompilerMacro( const TinyGraphicShaderMacro& macro ) {
	_compiler.AddMacro( macro.Name, macro.Value );
}

void TinyGraphicManager::AddCompilerMacros( tiny_init<TinyGraphicShaderMacro> macros ) {
	_compiler.AddMacros( macros );
}

bool TinyGraphicManager::CompileShader(
	const TinyGraphicShaderCompilationContext& context,
	TinyGraphicShaderSpecification& specification
) {
	return _compiler.Compile( context, specification );
}

TinyGraphicPipelineSpecification TinyGraphicManager::CreatePipeline(
	TinyGraphicPipelineTypes type,
	const tiny_string& renderpass,
	tiny_uint subpass
) {
	auto pipeline = _pipelines.Create( type );

	pipeline.Subpass		 = subpass;
	pipeline.Pass			 = _passes.GetPass( renderpass );
	pipeline.DescriptorCount = _swapchain.GetProperties( ).Capacity;

	return pipeline;
}

void TinyGraphicManager::ReCreate( ) { _need_recreation = true; }

void TinyGraphicManager::Acquire( const TinyWindow& window ) {
	_work_context.Acquire( _queues, VK_QUEUE_TYPE_GRAPHIC );
	
	if ( _need_recreation )
		ReCreate( window );

	_need_recreation = !_swapchain.Acquire( _logical, _work_context );
}

bool TinyGraphicManager::BeginPass( const tiny_string& pass_name ) {
	auto pass_hash = tiny_hash{ pass_name };

	return BeginPass( pass_hash );
}

bool TinyGraphicManager::BeginPass( const tiny_hash pass_hash ) {
	EndPass( );

	return _passes.Begin( pass_hash, _work_context );
}

void TinyGraphicManager::Clear(
	const tiny_hash pass_name,
	TinyGraphicWorkContext& work_context,
	tiny_init<TinyGraphicClearRegion> attachements
) {
	_passes.Clear( pass_name, work_context, attachements );
}

void TinyGraphicManager::Clear(
	const tiny_hash pass_name,
	TinyGraphicWorkContext& work_context,
	tiny_init<TinyGraphicClearAttachement> attachements
) {
	_passes.Clear( pass_name, work_context, attachements );
}

void TinyGraphicManager::Draw(
	const TinyGraphicPipelineDrawcall& draw_call,
	TinyGraphicPipeline& pipeline,
	tiny_init<TinyGraphicPipelineBindpoint> bindpoints
) {
	auto graphics = GetContext( );

	pipeline.Mount( _work_context );
	pipeline.Bind( _work_context, bindpoints );
	pipeline.Draw( _work_context, draw_call );
}

bool TinyGraphicManager::NextSubpass( ) { 
	auto state = _work_context.WorkRender.is_valid( );

	if ( state )
		state = _passes.NextSubpass( _work_context );

	return state;
}

void TinyGraphicManager::EndPass( ) { 
	if ( _work_context.WorkRender )
		_passes.End( _work_context ); 
}

void TinyGraphicManager::Present( const TinyWindow& window ) {
	EndPass( );
	
	if ( !_need_recreation )
		_need_recreation = !_swapchain.Present( _logical, _queues, _work_context );
}

void TinyGraphicManager::Terminate( TinyFilesystem& file_system, TinyWindow& window ) {
	_logical.Wait( );

	auto context = GetContext( );

	_pipelines.Terminate( file_system, _logical );
	_passes.Terminate( context );
	_swapchain.Terminate( _logical, _queues );
	_memory.Terminate( context );
	_queues.Terminate( _logical );
	_logical.Terminate( );
	_physical.Terminate( );
	_surface.Terminate( _instance );
	_instance.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicManager::ReCreate( const TinyWindow& window ) {
	_logical.Wait( );

	auto context = GetContext( );

	_boundaries.ReCreate( window );
	_swapchain.ReCreate( context );
	_passes.ReCreate( context );

	_work_context.WorkID = 0;

	_need_recreation = false;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicContext TinyGraphicManager::GetContext( ) {
	return {
		_boundaries,
		_instance,
		_surface,
		_physical,
		_logical,
		_queues,
		_memory,
		_swapchain,
		_passes,
		_pipelines
	};
}

bool TinyGraphicManager::GetNeedRecreation( ) const { return _need_recreation; }

TinyGraphicWorkContext& TinyGraphicManager::GetWorkdContext( ) { return _work_context; }

TinyGraphicBoundaries& TinyGraphicManager::GetBoundaries( ) { return _boundaries; }

TinyGraphicInstance& TinyGraphicManager::GetInstance( ) { return _instance; }

TinyGraphicSurface& TinyGraphicManager::GetSurface( ) { return _surface; }

TinyGraphicPhysical& TinyGraphicManager::GetPhysical( ) { return _physical; }

TinyGraphicLogical& TinyGraphicManager::GetLogical( ) { return _logical; }

TinyGraphicQueueManager& TinyGraphicManager::GetQueues( ) { return _queues; }

TinyGraphicMemoryManager& TinyGraphicManager::GetMemory( ) { return _memory; }

tiny_uint TinyGraphicManager::GetSwapchainCapacity( ) const { 
	return _swapchain.GetProperties( ).Capacity;
}

TinyGraphicSwapchainManager& TinyGraphicManager::GetSwapchain( ) { return _swapchain; }

TinyGraphicRenderManager& TinyGraphicManager::GetPasses( ) { return _passes; }

const TinyLimitsStack& TinyGraphicManager::GetPipelineLimits( ) const {
	return _pipelines.GetLimits( );
}

TinyGraphicPipelineManager& TinyGraphicManager::GetPipelines( ) { return _pipelines; }

tiny_uint TinyGraphicManager::GetMinImageCount( ) const { 
	return _surface.GetCapabilities( _physical ).minImageCount;
}

tiny_uint TinyGraphicManager::GetImageCount( ) const { 
	return _swapchain.GetProperties( ).Capacity;
}

TinyGraphicMSAA TinyGraphicManager::GetMSAA( ) const {
	return  { VK_SAMPLE_COUNT_1_BIT, _physical.GetSamplesLimit( ) };
}

VkPipelineCache TinyGraphicManager::GetPipelineCache( ) { return _pipelines.GetCache( ); }

TinyGraphicRenderpass& TinyGraphicManager::GetRenderPass( const tiny_string& pass_name ) {
	return _passes.GetPass( pass_name );
}

const shaderc::CompileOptions& TinyGraphicManager::GetCompilerOptions( ) const {
	return _compiler.GetCompilerOptions( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicManager::operator TinyGraphicContext ( ) { return GetContext( ); }
