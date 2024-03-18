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

#include "TinyGraphicSwapchainSync.h"

struct TinyGraphicWorkContext;

tm_class TinyGraphicSwapchainManager final {

private:
	TinyGraphicSwapchain				  _swapchain;
	TinyGraphicTextureProperties		  _properties;
	tiny_list<TinyGraphicSwapchainTarget> _targets;
	tiny_list<TinyGraphicSwapchainSync>   _syncs;

public:
	TinyGraphicSwapchainManager( );

	~TinyGraphicSwapchainManager( ) = default;

	bool Create( TinyGraphicContext& graphic );

	void ReCreate( TinyGraphicContext& graphic );
	
	bool Acquire( const TinyGraphicLogical& logical, TinyGraphicWorkContext& work_context );

	bool Present( 
		const TinyGraphicLogical& logical,
		TinyGraphicQueueManager& queues, 
		TinyGraphicWorkContext& work_context 
	);

	void Terminate( const TinyGraphicLogical& logical, const TinyGraphicQueueManager& queues );

private:
	bool CreateSwapchainTargets( const TinyGraphicLogical& logical );

	bool CreateSwapchainSyncs( const TinyGraphicLogical& logical );

	tiny_inline bool CreateSwapchain( TinyGraphicContext& graphic );

	tiny_inline void TerminateSwapchain( const TinyGraphicLogical& logical );

public:
	const TinyGraphicSwapchain& Get( ) const;

	const TinyGraphicSwapchainTarget& GetTarget( tiny_uint target ) const;

	TinyGraphicTextureProperties GetTargetProperties( tiny_uint target ) const;

	tiny_inline const TinyGraphicSwapchainProperties& GetProperties( ) const;

private:
	void GetProperties( const TinyGraphicBoundaries& boundaries );

};
