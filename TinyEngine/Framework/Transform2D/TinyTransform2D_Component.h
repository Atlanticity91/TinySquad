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

#include <TinyEngine/ECS/TinyECS.h>

TINY_FRAMEWORK_COMP( TinyTransform2D ) {

private:
	tiny_vec2 _location;
	float	  _rotation;
	tiny_vec2 _scale;
	tiny_mat4 _transform;

public:
	TinyTransform2D( );

	TinyTransform2D( const tiny_hash entity_hash );

	~TinyTransform2D( ) = default;
	
	tiny_inline TinyTransform2D& SetLocation( const tiny_vec2& location );

	TinyTransform2D& SetLocation( float x, float y );

	TinyTransform2D& SetRotation( float rotation );

	tiny_inline TinyTransform2D& SetScale( float scalar );

	tiny_inline TinyTransform2D& SetScale( const tiny_vec2& scale );

	TinyTransform2D& SetScale( float x, float y );

	void Set( const tiny_vec2& location, float rotation, const tiny_vec2& scale );

	tiny_inline TinyTransform2D& Move( const tiny_vec2& offset );

	TinyTransform2D& Move( float x, float y );

	TinyTransform2D& Rotate( float offset );

	tiny_inline TinyTransform2D& Scale( float scalar );

	tiny_inline TinyTransform2D& Scale( const tiny_vec2& scale );

	TinyTransform2D& Scale( float x, float y );

	TinyTransform2D& ReCalculate( );

	tiny_implement( void DisplayWidget(
		TinyGame* game,
		TinyEngine& engine,
		TinyToolbox& toolbox
	) );

public:
	TINY_COMP_NAME( TinyTransform2D );

	tiny_vec2& GetLocation( );

	const tiny_vec2& GetLocation( ) const;
	
	float GetRotation( );

	tiny_vec2& GetScale( );

	const tiny_vec2& GetScale( ) const;

	tiny_vec2 GetCenter( ) const;

	float GetRotator( ) const;

	const tiny_mat4& GetTransform( ) const;

};
