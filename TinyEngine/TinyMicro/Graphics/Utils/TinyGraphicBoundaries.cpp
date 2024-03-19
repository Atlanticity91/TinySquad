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
	: _orientation{ orientation },
	_aspect( ),
	_depth{ 0.f, 1.f },
	_viewport{ },
	_scissor{ },
	_swap_viewport{ },
	_swap_scissor{ }
{ }

void TinyGraphicBoundaries::ReCreate( const TinyWindow& window ) {
	_aspect = CaculateAspect( );

	auto dimensions = window.GetDimensions_v( );
	auto optimal_x  = dimensions.y * _aspect.x;
	auto optimal_y  = dimensions.x * _aspect.y;

	if ( optimal_x > dimensions.x ) {
		auto offset = .5f * ( dimensions.y - optimal_y );

		_viewport = { 0.f, offset, dimensions.x, optimal_y, _depth.x, _depth.y };
	} else {
		auto offset = .5f * ( dimensions.x - optimal_x );

		_viewport = { offset, 0.f, optimal_x, dimensions.y, _depth.x, _depth.y };
	}

	_scissor = { 
		{ 0, 0 }, 
		{ 
			tiny_cast( tiny_cast( _viewport.width, tiny_int ), tiny_uint ),
			tiny_cast( tiny_cast( _viewport.height , tiny_int ), tiny_uint )
		} 
	};
	_swap_viewport = { 0.f, 0.f, dimensions.x, dimensions.y, _depth.x, _depth.y };
	_swap_scissor  = {
		{ 0, 0 },
		{
			tiny_cast( tiny_cast( _swap_viewport.width , tiny_int ), tiny_uint ),
			tiny_cast( tiny_cast( _swap_viewport.height , tiny_int ), tiny_uint )
		}
	};
}

void TinyGraphicBoundaries::SetOrientation( const TinyWindow& window, TinyGameOrientations orientation ) {
	_orientation = orientation;

	ReCreate( window );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVAE ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_vec2 TinyGraphicBoundaries::CaculateAspect( ) {
	auto aspect = tiny_vec2{ };

	switch ( _orientation ) {
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
TinyGameOrientations TinyGraphicBoundaries::GetOrientation( ) const { return _orientation; }

const tiny_vec2& TinyGraphicBoundaries::GetAspect( ) const { return _aspect; };

const VkViewport& TinyGraphicBoundaries::GetViewport( ) const { return _viewport; }

const VkScissor& TinyGraphicBoundaries::GetScissor( ) const { return _scissor; }

const VkViewport& TinyGraphicBoundaries::GetSwapViewport( ) const { return _swap_viewport; }

const VkScissor& TinyGraphicBoundaries::GetSwapScissor( ) const { return _swap_scissor; }
