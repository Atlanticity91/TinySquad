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
 * @creation : 16/03/2024
 * @version  : 2024.2.6
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderCamera::TinyRenderCamera( )
	: _projection{ },
	_view{ 1.f },
	_proj_view{ 1.f },
	_inverse{ 1.f }
{ }

void TinyRenderCamera::SetTransform(
	const tiny_vec2& location,
	float rotation,
	const tiny_vec2& scale
) {
}

void TinyRenderCamera::SetTransform(
	const tiny_vec3& location,
	const tiny_vec3& rotation,
	const tiny_vec3& scale
) {
	_view = glm::translate( location );
}

void TinyRenderCamera::ReCalculate( const tiny_map<TinyRenderProjection>& projections ) {
	auto& projection = projections[ _projection ].Get( );

	_proj_view = projection * _view;
	_inverse   = glm::inverse( _proj_view );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const tiny_hash TinyRenderCamera::GetProjection( ) const { return _projection; }

const tiny_mat4& TinyRenderCamera::Get( ) const { return _view; }

const tiny_mat4& TinyRenderCamera::GetProjView( ) const { return _proj_view; }

const tiny_mat4& TinyRenderCamera::GetInverse( ) const { return _inverse; }

const float* TinyRenderCamera::GetBuffer( ) const { return glm::value_ptr( _view ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderCamera::operator const tiny_mat4& ( ) const { return Get( ); }

TinyRenderCamera::operator const float* ( ) const { return GetBuffer( ); }
