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

te_class TinyRenderCameraManager final {

private:
	tiny_map<TinyRenderProjection> _projections;
	tiny_map<TinyRenderCamera>	   _cameras;
	tiny_hash					   _current_camera;

public:
	TinyRenderCameraManager( );

	~TinyRenderCameraManager( ) = default;

	TinyRenderProjection& CreateProjection( const tiny_string& alias );

	void RemoveProjection( const tiny_string& alias );

	void RemoveProjection( const tiny_hash hash );

	TinyRenderCamera& CreateCamera( const tiny_string& entity_name );

	tiny_inline bool RemoveCamera( const tiny_string& entity_name );

	bool RemoveCamera( const tiny_hash entity_hash );

	void Prepare( TinyGraphicBoundaries& boundaries );

	void ReCalculate( );

	void ReCalculate( const tiny_hash entity_hash );

	tiny_inline  void ReCalculateCurrent( );

public:
	TinyRenderProjection& GetProjection( const tiny_string& alias );

	TinyRenderProjection& GetProjection( const tiny_hash hash );

	TinyRenderCamera& GetCamera( const tiny_string& entity_name );

	TinyRenderCamera& GetCamera( const tiny_hash entity_hash );

	TinyRenderCamera& GetCurrent( );

	tiny_inline const tiny_mat4& GetCurrentMatrix( ) const;

};
