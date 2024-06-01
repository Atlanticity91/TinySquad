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
 * @creation : 15/03/2024
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
TinyRenderProjection::TinyRenderProjection( )
	: m_type{ TRP_TYPE_ORTHOGRAPHIC },
	m_parameter{ 1.f },
	m_matrix{ 1.f }
{ }

TinyRenderProjection& TinyRenderProjection::SetType( TinyRenderProjectionTypes type ) {
	m_type = type;

	return tiny_self;
}

TinyRenderProjection& TinyRenderProjection::SetOrthographic( float zoom ) {
	m_type	    = TRP_TYPE_ORTHOGRAPHIC;
	m_parameter = zoom;

	return tiny_self;
}

TinyRenderProjection& TinyRenderProjection::SetPerspective( float fov ) {
	m_type	    = TRP_TYPE_PERSPECTIVE;
	m_parameter = fov;

	return tiny_self;
}

TinyRenderProjection& TinyRenderProjection::SetCustom( const tiny_mat4& projection ) {
	m_type    = TRP_TYPE_CUSTOM;
	m_matrix = projection;

	return tiny_self;
}

void TinyRenderProjection::ReCalculate( TinyGraphicBoundaries& boundaries ) {
	if ( m_type < TRP_TYPE_CUSTOM ) {
		auto aspect_ratio = boundaries.GetAspect( );
		auto& viewport    = boundaries.GetViewport( );

		switch ( m_type ) {
			case TRP_TYPE_ORTHOGRAPHIC:
				m_matrix = glm::ortho(
					.0f, viewport.width  * m_parameter,
					.0f, viewport.height * m_parameter,
					viewport.minDepth, viewport.maxDepth
				);
				break;

			case TRP_TYPE_PERSPECTIVE:
				m_matrix = glm::perspective(
					glm::radians( m_parameter ),
					aspect_ratio.x,
					viewport.minDepth, viewport.maxDepth
				);
				break;

			default: break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderProjectionTypes TinyRenderProjection::GetType( ) const { return m_type; }

const tiny_mat4& TinyRenderProjection::Get( ) const { return m_matrix; }

const float* TinyRenderProjection::GetBuffer( ) const { return glm::value_ptr( m_matrix ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderProjection::operator const tiny_mat4& ( ) const { return Get( ); }

TinyRenderProjection::operator const float* ( ) const { return GetBuffer( ); }
