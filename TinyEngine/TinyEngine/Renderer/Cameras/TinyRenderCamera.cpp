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
	: m_projection{ },
	m_view{ 1.f },
	m_proj_view{ 1.f },
	m_inverse{ 1.f }
{ }

TinyRenderCamera& TinyRenderCamera::SetProjection( const tiny_hash& projection ) {
	m_projection = projection;

	return tiny_self;
}

void TinyRenderCamera::Set( const TinyRenderCamera& other ) {
	auto* src_buffer = other.GetBuffer( );
	auto* dst_buffer = glm::value_ptr( m_view );

	m_projection = other.GetProjection( );

	Tiny::Memcpy( src_buffer, dst_buffer, 3 * tiny_sizeof( tiny_mat4 ) );
}

void TinyRenderCamera::SetTransform(
	const tiny_vec2& location,
	float rotation,
	const tiny_vec2& scale
) {
	auto radians = glm::radians( rotation );

	m_view  = glm::translate( tiny_vec3{ location.x, location.y, 0.f } );
	m_view *= glm::rotate( radians, tiny_vec3{ .0f, .0f, 1.f } );
	m_view *= glm::scale( tiny_vec3{ scale.x, scale.y, 1.f } );
}

void TinyRenderCamera::SetTransform(
	const tiny_vec3& location,
	const tiny_vec3& rotation,
	const tiny_vec3& scale
) {
	auto half_scale = scale * .5f;
	
	m_view = glm::translate( location + half_scale );
	//m_view *= glm::rotate( glm::radians( _rotation ), tiny_vec3{ .0f, .0f, 1.f } );
	m_view *= glm::scale( scale );
}

void TinyRenderCamera::ReCalculate( const tiny_map<TinyRenderProjection>& projections ) {
	auto& projection = projections[ m_projection ].Get( );

	m_proj_view = projection * m_view;
	m_inverse   = glm::inverse( m_proj_view );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const tiny_hash TinyRenderCamera::GetProjection( ) const { return m_projection; }

const tiny_mat4 TinyRenderCamera::GetProjection( TinyRenderer& renderer ) const {
	return renderer.GetProjection( m_projection );
}

const tiny_mat4& TinyRenderCamera::Get( ) const { return m_view; }

const tiny_mat4& TinyRenderCamera::GetProjView( ) const { return m_proj_view; }

const tiny_mat4& TinyRenderCamera::GetInverse( ) const { return m_inverse; }

const float* TinyRenderCamera::GetBuffer( ) const { return glm::value_ptr( m_view ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderCamera::operator const tiny_mat4& ( ) const { return Get( ); }

TinyRenderCamera::operator const float* ( ) const { return GetBuffer( ); }
