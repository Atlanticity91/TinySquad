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
	_current_camera{ TinyRenderDefaultCamera }
{ }

void TinyRenderCameraManager::Initialize( ) {
	CreateProjection( "Scene2D" );
	CreateCamera( TinyRenderDefaultCamera, "Scene2D" );
}

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

TinyRenderCamera& TinyRenderCameraManager::CreateCamera(
	const tiny_string& entity_name,
	const tiny_string& projection
) {
	auto projection_hash = tiny_hash{ projection };
	auto& camera		 = CreateCamera( entity_name );

	return camera.SetProjection( projection_hash );
}

void TinyRenderCameraManager::RemoveCamera( const tiny_string& entity_name ) {
	auto entity_hash = tiny_hash{ entity_name };

	RemoveCamera( entity_hash );
}

void TinyRenderCameraManager::RemoveCamera( const tiny_hash entity_hash ) {
	if ( entity_hash == _current_camera ) {
		auto default_camera = tiny_hash{ TinyRenderDefaultCamera };

		_cameras[ default_camera ].Set( _cameras[ entity_hash ] );

		_current_camera = default_camera;
	}

	_cameras.erase( entity_hash );
}

void TinyRenderCameraManager::Prepare( 
	TinyGraphicManager& graphics,
	TinyGraphicBufferStaging& staging,
	TinyRenderUniformManager& uniforms
) {
	auto& boundaries = graphics.GetBoundaries( );

	for ( auto& projection : _projections )
		projection.Data.ReCalculate( boundaries );

	ReCalculate( _current_camera );

	{
		auto uniform = uniforms.GetUniform( "ubo_core" );
		auto context = graphics.GetContext( );
		auto burner  = TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };
		auto copie   = VkBufferCopy{ 0, 0, tiny_sizeof( TinyRenderCore ) };

		staging.Map( context, tiny_cast( copie.size, tiny_uint ) );
		
		auto* projection = GetProjectionBuffer( );
		auto* camera	 = GetCameraBuffer( );
		auto* map		 = tiny_cast( staging.GetAccess( ), float* );

		Tiny::Memcpy( projection, map,			tiny_sizeof( tiny_mat4 ) );
		Tiny::Memcpy( camera,	  map + 16, 3 * tiny_sizeof( tiny_mat4 ) );

		staging.UnMap( context );

		burner.Upload( staging, uniform, copie );
	}
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
bool TinyRenderCameraManager::FindProjection( const tiny_string& alias ) const {
	return _projections.find( alias );
}

bool TinyRenderCameraManager::FindProjection( const tiny_hash hash ) const {
	return _projections.find( hash );
}

bool TinyRenderCameraManager::FindCamera( const tiny_string& entity_name ) const {
	return _cameras.find( entity_name );
}

bool TinyRenderCameraManager::FindCamera( const tiny_hash entity_hash ) const {
	return _cameras.find( entity_hash );
}

TinyRenderProjection& TinyRenderCameraManager::GetProjection( 
	const tiny_string& alias 
) {
	return _projections[ alias ];
}

const TinyRenderProjection& TinyRenderCameraManager::GetProjection(
	const tiny_string& alias
) const {
	return _projections[ alias ];
}

TinyRenderProjection& TinyRenderCameraManager::GetProjection( const tiny_hash hash ) {
	return _projections[ hash ];
}

const TinyRenderProjection& TinyRenderCameraManager::GetProjection( 
	const tiny_hash hash 
) const {
	return _projections[ hash ];
}

TinyRenderCamera& TinyRenderCameraManager::GetCamera( const tiny_string& entity_name ) {
	return _cameras[ entity_name ];
}

const TinyRenderCamera& TinyRenderCameraManager::GetCamera( 
	const tiny_string& entity_name 
) const {
	return _cameras[ entity_name ];
}

TinyRenderCamera& TinyRenderCameraManager::GetCamera( const tiny_hash entity_hash ) {
	return _cameras[ entity_hash ];
}

const TinyRenderCamera& TinyRenderCameraManager::GetCamera( 
	const tiny_hash entity_hash 
) const {
	return _cameras[ entity_hash ];
}

TinyRenderProjection& TinyRenderCameraManager::GetCurrentProjection( ) {
	auto& camera    = GetCurrentCamera( );
	auto projection = camera.GetProjection( );

	return _projections[ projection ];
}

const TinyRenderProjection& TinyRenderCameraManager::GetCurrentProjection( ) const {
	auto& camera    = GetCurrentCamera( );
	auto projection = camera.GetProjection( );

	return _projections[ projection ];
}

TinyRenderCamera& TinyRenderCameraManager::GetCurrentCamera( ) {
	return _cameras[ _current_camera ]; 
}

const TinyRenderCamera& TinyRenderCameraManager::GetCurrentCamera( ) const {
	return _cameras[ _current_camera ];
}

const tiny_mat4& TinyRenderCameraManager::GetCurrentMatrix( ) const { 
	return _cameras[ _current_camera ].GetProjView( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const float* TinyRenderCameraManager::GetProjectionBuffer( ) const {
	auto& projection = GetCurrentProjection( );
	
	return projection.GetBuffer( );
}

const float* TinyRenderCameraManager::GetCameraBuffer( ) const {
	auto& camera = GetCurrentCamera( );
	
	return camera.GetBuffer( );
}
