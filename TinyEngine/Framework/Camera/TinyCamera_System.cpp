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
 * @creation : 15/12/2023
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
TinyCameraSystem::TinyCameraSystem( ) 
	: TinySystem{ false, true },
	_projection{ },
	_view{ 1.f },
	_proj_view{ 1.f },
	_camera_comp{ TINY_UINT_MAX }
{ }

void TinyCameraSystem::SetProjectionType( TinyProjectionTypes type ) {
	_projection.SetType( type );
}

void TinyCameraSystem::SetProjecrionParameter( float value ) {
	_projection.SetParameter( value );
}

void TinyCameraSystem::SetProjection( TinyProjectionTypes type, float scalar ) {
	_projection.Set( type, scalar );
}

void TinyCameraSystem::SetCamera( const tiny_string& entity_name ) {
	auto entity_hash = tiny_hash{ entity_name };

	SetCamera( entity_hash );
}

void TinyCameraSystem::SetCamera( const tiny_hash entity_hash ) {
	_camera_comp = GetComponentID( entity_hash );
}

void TinyCameraSystem::PostTick( TinyGame* game ) {
	auto& graphics   = game->GetGraphics( );
	auto& boundaries = graphics.GetBoundaries( );
	auto* camera	 = tiny_cast( nullptr, TinyComponent* );
	
	_projection.Calculate( boundaries );

	if ( GetComponent( _camera_comp, camera ) ) {
		auto& ecs = game->GetECS( );

		_view = tiny_cast( camera, TinyCamera* )->Calculate( ecs );
	} else
		_view = tiny_mat4{ 1.f };

	_proj_view = _projection.GetMatrix( ) * _view;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const TinyCameraProjection& TinyCameraSystem::GetProjection( ) const { return _projection; }

const tiny_mat4& TinyCameraSystem::GetProjectionMatrtix( ) const {
	return _projection.GetMatrix( );
}

const tiny_mat4& TinyCameraSystem::GetViewMatrix( ) const { return _view; }

const tiny_mat4& TinyCameraSystem::GetProjViewMatrix( ) const { return _proj_view; }
