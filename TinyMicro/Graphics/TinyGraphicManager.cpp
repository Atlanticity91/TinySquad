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
	_work_context{ }
{ }

bool TinyGraphicManager::Initialize( TinyFilesystem& file_system, TinyWindow& window ) {
	_boundaries.ReCreate( window );

	auto context = GetContext( );

	return  _instance.Create( window.GetTitle( ) )		&&
			_surface.Create( window, _instance )		&&
			_physical.Initialize( _instance, _surface )	&&
			_surface.Initialize( _physical )			&&
			_logical.Create( _physical )				&&
			_queues.Create( _physical, _logical )		&& 
			_memory.Create( context )					&&
			_swapchain.Create( context )				&&
			_passes.Create( context )					&&
			_pipelines.Initialize( file_system, _logical );
}

bool TinyGraphicManager::CompileShader(
	const TinyPathInformation& path,
	tiny_storage& file, 
	TinyGraphicShaderProperties& properties 
) {
	return _compiler.Compile( path, file, properties );
}

bool TinyGraphicManager::CompileShader(
	TinyGraphicShaderProperties& properties,
	const TinyGraphicShaderCompilationContext& context
) {
	return _compiler.Compile( properties, context );
}

TinyGraphicPipelineBundle TinyGraphicManager::CreatePipeline(
	TinyGraphicPipelineTypes type,
	const tiny_string& renderpass,
	tiny_uint subpass
) {
	auto pipeline = _pipelines.Create( type );

	pipeline.PassIndex		 = subpass;
	pipeline.Pass			 = _passes.GetPass( renderpass );
	pipeline.DescriptorCount = _swapchain.GetProperties( ).Capacity;

	return pipeline;
}

void TinyGraphicManager::ReCreate( ) { _need_recreation = true; }

TinyGraphicWorkContext& TinyGraphicManager::Acquire( const TinyWindow& window ) {
	_work_context.Acquire( _logical, _queues, VK_QUEUE_TYPE_GRAPHIC );
	
	if ( _need_recreation )
		ReCreate( window );

	if ( !_swapchain.Acquire( _logical, _work_context ) )
		ReCreate( window );

	return _work_context;
}

bool TinyGraphicManager::BeginPass( const tiny_string& pass_name ) {
	auto pass_hash = tiny_hash{ pass_name };

	return BeginPass( pass_hash );
}

bool TinyGraphicManager::BeginPass( const tiny_hash pass_hash ) {
	EndPass( );

	return _passes.Begin( pass_hash, _work_context );
}

void TinyGraphicManager::SetViewport( const VkViewport& viewport ) {
	SetViewport( { viewport } );
}

void TinyGraphicManager::SetViewport( tiny_init<VkViewport> viewports ) {
	if ( viewports.size( ) > 0 ) {
		vkCmdSetViewport(
			_work_context.Queue->CommandBuffer,
			0, tiny_cast( viewports.size( ), tiny_uint ),
			viewports.begin( )
		);
	}
}

void TinyGraphicManager::SetScissor( const VkScissor& scissor ) {
	SetScissor( { scissor } );
}

void TinyGraphicManager::SetScissor( tiny_init<VkScissor> scissors ) {
	if ( scissors.size( ) > 0 ) {
		vkCmdSetScissor(
			_work_context.Queue->CommandBuffer,
			0, tiny_cast( scissors.size( ), tiny_uint ),
			scissors.begin( )
		);
	}
}

void TinyGraphicManager::SetCullMode( VkCullModeFlags cull_mode ) {
	vkCmdSetCullMode( _work_context.Queue->CommandBuffer, cull_mode );
}

void TinyGraphicManager::SetFrontFace( VkFrontFace front_face ) {
	vkCmdSetFrontFace( _work_context.Queue->CommandBuffer, front_face );
}

void TinyGraphicManager::SetPrimitiveRestartEnable( bool is_active ) {
	vkCmdSetPrimitiveRestartEnable( _work_context.Queue->CommandBuffer, is_active ? VK_TRUE : VK_FALSE );
}

void TinyGraphicManager::SetPrimitiveTopology( VkPrimitiveTopology topology ) {
	vkCmdSetPrimitiveTopology( _work_context.Queue->CommandBuffer, topology );
}

void TinyGraphicManager::SetRasterizerDiscardEnable( bool is_active ) {
	vkCmdSetRasterizerDiscardEnable( _work_context.Queue->CommandBuffer, is_active ? VK_TRUE : VK_FALSE );
}

void TinyGraphicManager::SetBlendConstants( const float* constants ) {
	vkCmdSetBlendConstants( _work_context.Queue->CommandBuffer, constants );
}

void TinyGraphicManager::SetBlendConstants( const tiny_vec4& constant ) {
	vkCmdSetBlendConstants( _work_context.Queue->CommandBuffer, tiny_rvalue( constant.r ) );
}

void TinyGraphicManager::SetDepthTestEnable( bool is_active ) {
	vkCmdSetDepthTestEnable( _work_context.Queue->CommandBuffer, is_active ? VK_TRUE : VK_FALSE );
}

void TinyGraphicManager::SetDepthCompareOp( VkCompareOp operation ) {
	vkCmdSetDepthCompareOp( _work_context.Queue->CommandBuffer, operation );
}

void TinyGraphicManager::SetDepthWriteEnable( bool is_active ) {
	vkCmdSetDepthWriteEnable( _work_context.Queue->CommandBuffer, is_active ? VK_TRUE : VK_FALSE );
}

void TinyGraphicManager::SetDepthBias( float constant, float clamp, float slope ) {
	vkCmdSetDepthBias( _work_context.Queue->CommandBuffer, constant, clamp, slope );
}

void TinyGraphicManager::SetDepthBounds( float minimum, float maximum ) {
	vkCmdSetDepthBounds( _work_context.Queue->CommandBuffer, minimum, maximum );
}

void TinyGraphicManager::SetDeviceMask( tiny_uint mask ) {
	vkCmdSetDeviceMask( _work_context.Queue->CommandBuffer, mask );
}

void TinyGraphicManager::SetLineWidth( float width ) {
	vkCmdSetLineWidth( _work_context.Queue->CommandBuffer, width );
}

void TinyGraphicManager::SetStencilOp( 
	VkStencilFaceFlags face_mask,
	VkStencilOp fail_operation,
	VkStencilOp pass_operation,
	VkStencilOp depth_fail_operation,
	VkCompareOp compare_operation
) {
	vkCmdSetStencilOp( 
		_work_context.Queue->CommandBuffer,
		face_mask,
		fail_operation,
		pass_operation,
		depth_fail_operation,
		compare_operation
	);
}

void TinyGraphicManager::SetStencilCompareMask( 
	VkStencilFaceFlags face_mask, 
	tiny_uint compare_mask 
) {
	vkCmdSetStencilCompareMask( _work_context.Queue->CommandBuffer, face_mask, compare_mask );
}

void TinyGraphicManager::SetStencilReference( 
	VkStencilFaceFlags face_mask, 
	tiny_uint reference 
) {
	vkCmdSetStencilReference( _work_context.Queue->CommandBuffer, face_mask, reference );
}

void TinyGraphicManager::SetStencilWriteMask( 
	VkStencilFaceFlags face_mask,
	tiny_uint write_mask 
) {
	vkCmdSetStencilWriteMask( _work_context.Queue->CommandBuffer, face_mask, write_mask );
}

void TinyGraphicManager::Draw(
	const TinyGraphicPipelineDrawcall& draw_call,
	TinyGraphicPipeline& pipeline,
	tiny_init<TinyGraphicPipelineBindpoint> bindpoints
) {
	pipeline.Mount( _work_context );
	pipeline.Bind( _logical, _work_context, bindpoints );
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
	
	auto state = !_swapchain.Present( _logical, _queues, _work_context );

	if ( !_need_recreation )
		_need_recreation = state;
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
