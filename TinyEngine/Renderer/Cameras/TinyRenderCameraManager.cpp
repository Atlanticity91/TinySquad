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
TinyRenderCameraManager::TinyRenderCameraManager( )
	: _projections{ },
	_cameras{ },
	_current_camera{ }
{ }

TinyRenderProjection& TinyRenderCameraManager::CreateProjection( 
	const tiny_string& alias
) {
	if ( !_projections.find( alias ) )
		_projections.emplace( alias, { } );

	return _projections[ alias ];
}

void TinyRenderCameraManager::RemoveProjection( const tiny_string& alias ) {
	_projections.erase( alias );
}

void TinyRenderCameraManager::RemoveProjection( const tiny_hash hash ) {
	_projections.erase( hash );
}

TinyRenderCamera& TinyRenderCameraManager::CreateCamera( const tiny_string& entity_name ) {
	if ( !_cameras.find( entity_name ) )
		_cameras.emplace( entity_name, { } );

	return _cameras[ entity_name ];
}

bool TinyRenderCameraManager::RemoveCamera( const tiny_string& entity_name ) {
	auto entity_hash = tiny_hash{ entity_name };

	return RemoveCamera( entity_hash );
}

bool TinyRenderCameraManager::RemoveCamera( const tiny_hash entity_hash ) {
	auto state = entity_hash != _current_camera;

	if ( state )
		_cameras.erase( entity_hash );

	return state;
}

void TinyRenderCameraManager::Prepare( TinyGraphicBoundaries& boundaries ) {
	for ( auto& projection : _projections )
		projection.Data.ReCalculate( boundaries );
}

void TinyRenderCameraManager::ReCalculate( ) {
	for ( auto& camera : _cameras )
		camera.Data.ReCalculate( _projections );
}

void TinyRenderCameraManager::ReCalculate( const tiny_hash entity_hash ) {
	auto camera_id = tiny_cast( 0, tiny_uint );

	if ( _cameras.find( entity_hash, camera_id ) ) {
		auto& camera = _cameras.at( camera_id );
		
		camera.ReCalculate( _projections );
	}
}

void TinyRenderCameraManager::ReCalculateCurrent( ) { ReCalculate( _current_camera ); }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderProjection& TinyRenderCameraManager::GetProjection( const tiny_string& alias ) {
	return _projections[ alias ];
}

TinyRenderProjection& TinyRenderCameraManager::GetProjection( const tiny_hash hash ) {
	return _projections[ hash ];
}

TinyRenderCamera& TinyRenderCameraManager::GetCamera( const tiny_string& entity_name ) {
	return _cameras[ entity_name ];
}

TinyRenderCamera& TinyRenderCameraManager::GetCamera( const tiny_hash entity_hash ) {
	return _cameras[ entity_hash ];
}

TinyRenderCamera& TinyRenderCameraManager::GetCurrent( ) { 
	return _cameras[ _current_camera ]; 
}
const tiny_mat4& TinyRenderCameraManager::GetCurrentMatrix( ) const { 
	return _cameras[ _current_camera ].GetProjView( );
}
