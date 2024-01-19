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
 * @creation : 24/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyCameraProjection.h"

te_class TinyCameraSystem : tiny_inherit( TinySystem<TinyCamera> ) { 

private:
	TinyCameraProjection _projection;
	tiny_mat4			 _view;
	tiny_mat4			 _proj_view;
	tiny_uint			 _camera_comp;

public:
	TinyCameraSystem( );

	tiny_inline void SetProjectionType( TinyProjectionTypes type );

	tiny_inline void SetProjecrionParameter( float value );

	tiny_inline void SetProjection( TinyProjectionTypes type, float parameter );

	void SetCamera( const tiny_string& entity_name );

	void SetCamera( const tiny_hash entity_hash );

protected:
	tiny_implement( void PostTick( TinyGame* game, TinyEngine& engine ) );

public:
	const TinyCameraProjection& GetProjection( ) const;

	const tiny_mat4& GetProjectionMatrtix( ) const;

	const tiny_mat4& GetViewMatrix( ) const;

	const tiny_mat4& GetProjViewMatrix( ) const;

};
