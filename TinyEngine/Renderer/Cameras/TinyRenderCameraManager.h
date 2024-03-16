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

#pragma once

#include "TinyRenderCamera.h"

#define TinyRenderDefaultCamera "_DefaultCamera"

class TinyRenderUniformManager;

te_class TinyRenderCameraManager final {

private:
	tiny_map<TinyRenderProjection> _projections;
	tiny_map<TinyRenderCamera>	   _cameras;
	tiny_hash					   _current_camera;

public:
	TinyRenderCameraManager( );

	~TinyRenderCameraManager( ) = default;

	void Initialize( );

	TinyRenderProjection& CreateProjection( const tiny_string& alias );

	void RemoveProjection( const tiny_string& alias );

	void RemoveProjection( const tiny_hash hash );

	TinyRenderCamera& CreateCamera( const tiny_string& entity_name );

	TinyRenderCamera& CreateCamera( 
		const tiny_string& entity_name, 
		const tiny_string& projection
	);

	tiny_inline void RemoveCamera( const tiny_string& entity_name );

	void RemoveCamera( const tiny_hash entity_hash );

	void Prepare( 
		TinyGraphicManager& graphics,
		TinyGraphicBufferStaging& staging,
		TinyRenderUniformManager& uniforms
	);

	void ReCalculate( );

	void ReCalculate( const tiny_hash entity_hash );

	tiny_inline void ReCalculateCurrent( );

public:
	bool FindProjection( const tiny_string& alias ) const;

	bool FindProjection( const tiny_hash hash ) const;

	bool FindCamera( const tiny_string& entity_name ) const;

	bool FindCamera( const tiny_hash entity_hash ) const;

	TinyRenderProjection& GetProjection( const tiny_string& alias );

	const TinyRenderProjection& GetProjection( const tiny_string& alias ) const;

	TinyRenderProjection& GetProjection( const tiny_hash hash );

	const TinyRenderProjection& GetProjection( const tiny_hash hash ) const;

	TinyRenderCamera& GetCamera( const tiny_string& entity_name );

	const TinyRenderCamera& GetCamera( const tiny_string& entity_name ) const;

	TinyRenderCamera& GetCamera( const tiny_hash entity_hash );

	const TinyRenderCamera& GetCamera( const tiny_hash entity_hash ) const;

	TinyRenderProjection& GetCurrentProjection( );

	const TinyRenderProjection& GetCurrentProjection( ) const;

	TinyRenderCamera& GetCurrentCamera( );

	const TinyRenderCamera& GetCurrentCamera( ) const;

	tiny_inline const tiny_mat4& GetCurrentMatrix( ) const;

private:
	const float* GetProjectionBuffer( ) const;

	const float* GetCameraBuffer( ) const;

};
