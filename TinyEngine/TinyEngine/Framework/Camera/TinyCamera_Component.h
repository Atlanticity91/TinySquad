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

#include <TinyEngine/Framework/Anim2D/TinyAnim2D_System.h>

TINY_FRAMEWORK_COMP( TinyCamera ) {

private:
	bool	  _use_local;
	tiny_vec3 _location;
	tiny_vec3 _rotation;
	tiny_vec3 _scale;

public:
	TinyCamera( );

	TinyCamera( const tiny_hash entity_hash );

	~TinyCamera( ) = default;

	tiny_implement( bool Create( TinyGame* game ) );

	tiny_implement( void Delete( TinyGame* game ) );

	tiny_implement( void DisplayWidget( TinyGame* game, TinyToolbox& toolbox ) );

	tiny_mat4 Calculate( TinyECS& ecs );

public:
	TINY_COMP_NAME( TinyCamera );

	bool GetUseLocal( ) const;

	const tiny_vec3& GetLocation( ) const;
	
	const tiny_vec3& GetRotation( ) const;
	
	const tiny_vec3& GetScale( ) const;

};
