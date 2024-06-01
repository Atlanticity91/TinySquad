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
TinyGraphicBoundaries::TinyGraphicBoundaries( TinyGameOrientations orientation )
	: m_orientation{ orientation },
	m_aspect( ),
	m_depth{ 0.f, 1.f },
	m_viewport{ },
	m_scissor{ },
	m_swap_viewport{ },
	m_swap_scissor{ }
{ }

void TinyGraphicBoundaries::ReCreate( const TinyWindow& window ) {
	m_aspect = CaculateAspect( );

	auto dimensions = window.GetDimensions_v( );
	auto optimal_x  = dimensions.y * m_aspect.x;
	auto optimal_y  = dimensions.x * m_aspect.y;

	if ( optimal_x > dimensions.x ) {
		auto offset = .5f * ( dimensions.y - optimal_y );

		m_viewport = { 0.f, offset, dimensions.x, optimal_y, m_depth.x, m_depth.y };
	} else {
		auto offset = .5f * ( dimensions.x - optimal_x );

		m_viewport = { offset, 0.f, optimal_x, dimensions.y, m_depth.x, m_depth.y };
	}

	m_scissor = { 
		{ 0, 0 }, 
		{ 
			tiny_cast( tiny_cast( m_viewport.width, tiny_int ), tiny_uint ),
			tiny_cast( tiny_cast( m_viewport.height , tiny_int ), tiny_uint )
		} 
	};
	m_swap_viewport = { 0.f, 0.f, dimensions.x, dimensions.y, m_depth.x, m_depth.y };
	m_swap_scissor  = {
		{ 0, 0 },
		{
			tiny_cast( tiny_cast( m_swap_viewport.width , tiny_int ), tiny_uint ),
			tiny_cast( tiny_cast( m_swap_viewport.height , tiny_int ), tiny_uint )
		}
	};
}

void TinyGraphicBoundaries::SetOrientation( const TinyWindow& window, TinyGameOrientations orientation ) {
	m_orientation = orientation;

	ReCreate( window );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVAE ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_vec2 TinyGraphicBoundaries::CaculateAspect( ) {
	auto aspect = tiny_vec2{ };

	switch ( m_orientation ) {
		case TGO_PAYSAGE_16x9  : aspect = { 16.f /  9.f,  9.f / 16.f }; break;
		case TGO_PAYSAGE_4x3   : aspect = {  4.f /  3.f,  3.f /  4.f }; break;
		case TGO_PORTRAIT_9x16 : aspect = {  9.f / 16.f, 16.f /  9.f }; break;
		case TGO_PORTRAIT_3x4  : aspect = {  3.f /  4.f,  4.f /  3.f }; break;

		default: break;
	};

	return aspect;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGameOrientations TinyGraphicBoundaries::GetOrientation( ) const { return m_orientation; }

const tiny_vec2& TinyGraphicBoundaries::GetAspect( ) const { return m_aspect; };

const VkViewport& TinyGraphicBoundaries::GetViewport( ) const { return m_viewport; }

const VkScissor& TinyGraphicBoundaries::GetScissor( ) const { return m_scissor; }

const VkViewport& TinyGraphicBoundaries::GetSwapViewport( ) const { return m_swap_viewport; }

const VkScissor& TinyGraphicBoundaries::GetSwapScissor( ) const { return m_swap_scissor; }
