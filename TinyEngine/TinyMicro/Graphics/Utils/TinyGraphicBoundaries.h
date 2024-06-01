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

#include "TinyGraphicWrapper.h"

tiny_enum( TinyGameOrientations ) {

	TGO_PAYSAGE_16x9 = 0,
	TGO_PAYSAGE_4x3,
	TGO_PORTRAIT_9x16,
	TGO_PORTRAIT_3x4

};

tm_class TinyGraphicBoundaries final { 

private:
	TinyGameOrientations m_orientation;
	tiny_vec2 m_aspect;
	tiny_vec2 m_depth;
	VkViewport m_viewport;
	VkScissor m_scissor;
	VkViewport m_swap_viewport;
	VkScissor m_swap_scissor;

public:
	TinyGraphicBoundaries( TinyGameOrientations orientation );

	~TinyGraphicBoundaries( ) = default;

	void ReCreate( const TinyWindow& window );

	void SetOrientation( const TinyWindow& window, TinyGameOrientations orientation );

private:
	tiny_vec2 CaculateAspect( );

public:
	TinyGameOrientations GetOrientation( ) const;

	const tiny_vec2& GetAspect( ) const;

	const VkViewport& GetViewport( ) const;
	
	const VkScissor& GetScissor( ) const;

	const VkViewport& GetSwapViewport( ) const;
	
	const VkScissor& GetSwapScissor( ) const;

};
