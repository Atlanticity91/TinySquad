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
	: _type{ TRP_TYPE_ORTHOGRAPHIC },
	_matrix{ 1.f }
{ }

TinyRenderProjection& TinyRenderProjection::SetType( TinyRenderProjectionTypes type ) {
	_type = type;

	return tiny_self;
}

TinyRenderProjection& TinyRenderProjection::SetOrthographic(
) {
	_type = TRP_TYPE_ORTHOGRAPHIC;

	return tiny_self;
}

TinyRenderProjection& TinyRenderProjection::SetPerspective(
) {
	_type = TRP_TYPE_PERSPECTIVE;

	return tiny_self;
}

TinyRenderProjection& TinyRenderProjection::SetCustom( const tiny_mat4& projection ) {
	_type   = TRP_TYPE_CUSTOM;
	_matrix = projection;

	return tiny_self;
}

void TinyRenderProjection::ReCalculate( TinyGraphicBoundaries& boundaries ) {
	if ( _type < TRP_TYPE_CUSTOM ) {
		auto aspect_ratio = boundaries.GetAspect( );
		auto& viewport    = boundaries.GetViewport( );

		/*
		switch ( _type ) {
			case TRP_TYPE_ORTHOGRAPHIC:
				_matrix = glm::ortho(
					.0f, viewport.width * _parameter,
					.0f, viewport.height * _parameter,
					viewport.minDepth, viewport.maxDepth
				);
				break;

			case TRP_TYPE_PERSPECTIVE:
				_matrix = glm::perspective(
					glm::radians( _parameter ),
					aspect_ratio.x,
					viewport.minDepth, viewport.maxDepth
				);
				break;

			default: break;
		}
		*/
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderProjectionTypes TinyRenderProjection::GetType( ) const { return _type; }

const tiny_mat4& TinyRenderProjection::Get( ) const { return _matrix; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderProjection::operator const tiny_mat4& ( ) const { return Get( ); }
