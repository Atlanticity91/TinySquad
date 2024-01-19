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
 * @creation : 21/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyCameraProjection::TinyCameraProjection( )
	: _type{ },
	_parameter{ 1.f },
	_matrix{ 1.f }
{ }

void TinyCameraProjection::SetType( TinyProjectionTypes type ) { _type = type; }

void TinyCameraProjection::SetParameter( float value ) { _parameter = value; }

void TinyCameraProjection::Set( TinyProjectionTypes type, float parameter ) {
	_type	   = type;
	_parameter = parameter;
}

void TinyCameraProjection::Calculate( TinyGraphicBoundaries& boundaries ) {
	auto aspect_ratio = boundaries.GetAspect( );
	auto& viewport	  = boundaries.GetViewport( );

	switch ( _type ) {
		case TP_TYPE_ORTHOGRAPHIC :
			_matrix = glm::ortho(
				.0f, viewport.width * _parameter,
				.0f, viewport.height * _parameter,
				viewport.minDepth, viewport.maxDepth
			);
			break;

		case TP_TYPE_PERSPECTIVE :
			_matrix = glm::perspective(
				glm::radians( _parameter ),
				aspect_ratio.x,
				viewport.minDepth, viewport.maxDepth
			);
			break;

		default : break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyProjectionTypes TinyCameraProjection::GetType( ) const { return _type; }

float TinyCameraProjection::GetParamter( ) const { return _parameter; }

const tiny_mat4& TinyCameraProjection::GetMatrix( ) const { return _matrix; }
