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
	: m_need_recreation{ false },
	m_boundaries{ orientation },
	m_instance{ },
	m_surface{ },
	m_physical{ },
	m_logical{ },
	m_queues{ },
	m_memory{ },
	m_swapchain{ },
	m_passes{ },
	m_pipelines{ },
	m_compiler{ },
	m_work_context{ tiny_rvalue( m_logical ) }
{ }

TinyGraphicManager& TinyGraphicManager::AddBundle(
	const tiny_string& name,
	const TinyGraphicRenderBundle& bundle
) {
	m_passes.AddBundle( name, bundle );

	return tiny_self;
}

bool TinyGraphicManager::Initialize( TinyFilesystem& file_system, TinyWindow& window ) {
	m_boundaries.ReCreate( window );

	auto wrapper = GetWrapper( );
	auto title   = window.GetTitle( );

	return  m_instance.Create( title )									 &&
			m_surface.Create( window, m_instance )						 &&
			m_physical.Initialize( m_instance, m_surface )				 &&
			m_surface.Initialize( m_physical )							 &&
			m_logical.Create( m_physical )								 &&
			m_queues.Create( m_physical, m_logical )					 &&
			m_memory.Create( wrapper )									 &&
			m_swapchain.Create( wrapper )								 &&
			m_passes.Create( wrapper )									 &&
			m_pipelines.Initialize( file_system, m_physical, m_logical ) &&
			m_compiler.Initialize( );
}

void TinyGraphicManager::EnableCache( ) { m_pipelines.EnableCache( ); }

void TinyGraphicManager::DisableCache( ) { m_pipelines.DisableCache( ); }

void TinyGraphicManager::AddCompilerMacro(
	const tiny_string& name,
	const tiny_string& value
) {
	m_compiler.AddMacro( name, value );
}

void TinyGraphicManager::AddCompilerMacro( const TinyGraphicShaderMacro& macro ) {
	m_compiler.AddMacro( macro.Name, macro.Value );
}

void TinyGraphicManager::AddCompilerMacros( tiny_init<TinyGraphicShaderMacro> macros ) {
	m_compiler.AddMacros( macros );
}

bool TinyGraphicManager::CompileShader(
	const TinyGraphicShaderCompilationContext& context,
	TinyGraphicShaderSpecification& specification
) {
	return m_compiler.Compile( context, specification );
}

TinyGraphicPipelineSpecification TinyGraphicManager::CreatePipeline(
	TinyGraphicPipelineTypes type,
	const tiny_string& renderpass,
	tiny_uint subpass
) {
	auto pipeline = m_pipelines.Create( type );

	pipeline.Subpass		 = subpass;
	pipeline.Pass			 = m_passes.GetPass( renderpass );
	pipeline.DescriptorCount = m_swapchain.GetProperties( ).Capacity;

	return pipeline;
}

void TinyGraphicManager::ReCreate( ) { m_need_recreation = true; }

void TinyGraphicManager::Acquire( const TinyWindow& window ) {
	m_work_context.Acquire( m_queues, VK_QUEUE_TYPE_GRAPHIC );
	
	if ( m_need_recreation )
		ReCreate( window );

	m_need_recreation = !m_swapchain.Acquire( m_logical, m_work_context );
}

bool TinyGraphicManager::BeginPass( const tiny_string& pass_name ) {
	auto pass_hash = tiny_hash{ pass_name };

	return BeginPass( pass_hash );
}

bool TinyGraphicManager::BeginPass( const tiny_hash pass_hash ) {
	EndPass( );

	return m_passes.Begin( pass_hash, m_work_context );
}

void TinyGraphicManager::Clear(
	const tiny_hash pass_name,
	TinyGraphicWorkContext& work_context,
	tiny_init<TinyGraphicClearRegion> attachements
) {
	m_passes.Clear( pass_name, work_context, attachements );
}

void TinyGraphicManager::Clear(
	const tiny_hash pass_name,
	TinyGraphicWorkContext& work_context,
	tiny_init<TinyGraphicClearAttachement> attachements
) {
	m_passes.Clear( pass_name, work_context, attachements );
}

void TinyGraphicManager::Draw(
	const TinyGraphicPipelineDrawcall& draw_call,
	TinyGraphicPipeline& pipeline,
	tiny_init<TinyGraphicPipelineBindpoint> bindpoints
) {
	pipeline.Mount( m_work_context );
	pipeline.Bind( m_work_context, bindpoints );
	pipeline.Draw( m_work_context, draw_call );
}

bool TinyGraphicManager::NextSubpass( ) { 
	auto state = false;

	if ( m_work_context.WorkRender.get_is_valid( ) )
		state = m_passes.NextSubpass( m_work_context );

	return state;
}

void TinyGraphicManager::EndPass( ) { 
	if ( m_work_context.WorkRender )
		m_passes.End( m_work_context );
}

void TinyGraphicManager::Present( const TinyWindow& window ) {
	EndPass( );
	
	if ( !m_need_recreation )
		m_need_recreation = !m_swapchain.Present( m_logical, m_queues, m_work_context );
}

void TinyGraphicManager::Terminate( TinyFilesystem& file_system, TinyWindow& window ) {
	m_logical.Wait( );

	auto wrapper = GetWrapper( );

	m_pipelines.Terminate( file_system, m_physical, m_logical );
	m_passes.Terminate( wrapper );
	m_swapchain.Terminate( m_logical, m_queues );
	m_memory.Terminate( wrapper );
	m_queues.Terminate( m_logical );
	m_logical.Terminate( );
	m_physical.Terminate( );
	m_surface.Terminate( m_instance );
	m_instance.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyGraphicManager::ReCreate( const TinyWindow& window ) {
	m_logical.Wait( );

	auto context = GetWrapper( );

	m_boundaries.ReCreate( window );
	m_swapchain.ReCreate( context );
	m_passes.ReCreate( context );

	m_work_context.WorkID = 0;

	m_need_recreation = false;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicWrapper TinyGraphicManager::GetWrapper( ) {
	return {
		m_boundaries,
		m_instance,
		m_surface,
		m_physical,
		m_logical,
		m_queues,
		m_memory,
		m_swapchain,
		m_passes,
		m_pipelines
	};
}

bool TinyGraphicManager::GetNeedRecreation( ) const { return m_need_recreation; }

TinyGraphicWorkContext& TinyGraphicManager::GetWorkdContext( ) { return m_work_context; }

TinyGraphicBoundaries& TinyGraphicManager::GetBoundaries( ) { return m_boundaries; }

TinyGraphicInstance& TinyGraphicManager::GetInstance( ) { return m_instance; }

TinyGraphicSurface& TinyGraphicManager::GetSurface( ) { return m_surface; }

TinyGraphicPhysical& TinyGraphicManager::GetPhysical( ) { return m_physical; }

TinyGraphicLogical& TinyGraphicManager::GetLogical( ) { return m_logical; }

TinyGraphicQueueManager& TinyGraphicManager::GetQueues( ) { return m_queues; }

TinyGraphicMemoryManager& TinyGraphicManager::GetMemory( ) { return m_memory; }

tiny_uint TinyGraphicManager::GetSwapchainCapacity( ) const { 
	return m_swapchain.GetProperties( ).Capacity;
}

TinyGraphicSwapchainManager& TinyGraphicManager::GetSwapchain( ) { return m_swapchain; }

TinyGraphicRenderManager& TinyGraphicManager::GetPasses( ) { return m_passes; }

const TinyLimitsStack& TinyGraphicManager::GetPipelineLimits( ) const {
	return m_pipelines.GetLimits( );
}

TinyGraphicPipelineManager& TinyGraphicManager::GetPipelines( ) { return m_pipelines; }

tiny_uint TinyGraphicManager::GetMinImageCount( ) const { 
	return m_surface.GetCapabilities( m_physical ).minImageCount;
}

tiny_uint TinyGraphicManager::GetImageCount( ) const { 
	return m_swapchain.GetProperties( ).Capacity;
}

TinyGraphicMSAA TinyGraphicManager::GetMSAA( ) const {
	return  { VK_SAMPLE_COUNT_1_BIT, m_physical.GetSamplesLimit( ) };
}

VkPipelineCache TinyGraphicManager::GetPipelineCache( ) { return m_pipelines.GetCache( ); }

TinyGraphicRenderpass& TinyGraphicManager::GetRenderPass( const tiny_string& pass_name ) {
	return m_passes.GetPass( pass_name );
}

const shaderc::CompileOptions& TinyGraphicManager::GetCompilerOptions( ) const {
	return m_compiler.GetCompilerOptions( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicManager::operator TinyGraphicWrapper ( ) { return GetWrapper( ); }
