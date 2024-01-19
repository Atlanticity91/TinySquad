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
 * @creation : 22/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyGraphicRenderBarrier.h"

tm_class TinyGraphicRenderBarrierManager final { 

private:
	tiny_map<TinyGraphicRenderBarrier> _barriers;

public:
	TinyGraphicRenderBarrierManager( );

	~TinyGraphicRenderBarrierManager( ) = default;

	void Create( const tiny_string& pass, const tiny_list<TinyGraphicRenderBarrierBundle>& bundles );

	void Transit( TinyGraphicWorkContext& work_context );

	void Terminate( );

};
