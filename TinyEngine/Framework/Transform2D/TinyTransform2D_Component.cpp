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
 * @creation : 14/11/2023
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
TinyTransform2D::TinyTransform2D( )
	: TinyTransform2D{ TINY_NO_ENTITY }
{ }

TinyTransform2D::TinyTransform2D( const tiny_hash entity_hash )
	: TinyComponent{ entity_hash },
	_location{ },
	_rotation{ .0f },
	_scale{ 1.f },
	_transform{ 1.f }
{ }

TinyTransform2D& TinyTransform2D::SetLocation( const tiny_vec2& location ) {
	_location = location;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetLocation( float x, float y ) {
	_location.x = x;
	_location.y = y;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetRotation( float rotation ) {
	_rotation = rotation;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetScale( float scalar ) {
	return SetScale( scalar, scalar );
}

TinyTransform2D& TinyTransform2D::SetScale( const tiny_vec2& scale ) {
	return SetScale( scale.x, scale.y );
}

TinyTransform2D& TinyTransform2D::SetScale( float x, float y ) {
	_scale.x = x;
	_scale.y = y;

	return tiny_self;
}

void TinyTransform2D::Set( 
	const tiny_vec2& location, 
	float rotation, 
	const tiny_vec2& scale 
) {
	_location = location;
	_rotation = rotation;
	_scale	  = scale;

	ReCalculate( );
}

TinyTransform2D& TinyTransform2D::Move( const tiny_vec2& offset ) {
	return Move( offset.x, offset.y );
}

TinyTransform2D& TinyTransform2D::Move( float x, float y ) {
	_location.x += x;
	_location.y += y;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::Rotate( float offset ) {
	_rotation += offset;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::Scale( float scalar ) {
	return Scale( scalar, scalar );
}

TinyTransform2D& TinyTransform2D::Scale( const tiny_vec2& scale ) {
	return Scale( scale.x, scale.y );
}

TinyTransform2D& TinyTransform2D::Scale( float x, float y ) {
	_scale.x *= x;
	_scale.y *= y;

	return tiny_self;
} 

TinyTransform2D& TinyTransform2D::ReCalculate( ) {
	auto offset = GetCenter( );

	_transform = glm::translate( tiny_vec3{ _location.x + _scale.x, _location.y + _scale.y, .0f } );
	_transform = glm::rotate( _transform, glm::radians( _rotation ), tiny_vec3{ .0f, .0f, 1.f } );
	_transform = glm::translate( _transform, tiny_vec3{ -offset.x, -offset.y, .0f } );
	_transform = glm::scale( _transform, tiny_vec3{ _scale.x, _scale.y, 1.f } );

	return tiny_self;
}

void TinyTransform2D::DisplayWidget(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) { 
	TinyComponent::DisplayWidget( game, engine, toolbox );

	TinyImGui::InputVec2( "Location", _location );
	TinyImGui::InputScalar( "Rotation", _rotation );
	TinyImGui::InputVec2( "Scale", _scale );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_vec2& TinyTransform2D::GetLocation( ) { return _location; }

const tiny_vec2& TinyTransform2D::GetLocation( ) const { return _location; }

float TinyTransform2D::GetRotation( ) { return _rotation; }

tiny_vec2& TinyTransform2D::GetScale( ) { return _scale; }

tiny_vec2 TinyTransform2D::GetCenter( ) const { return _scale * .5f; }

const tiny_vec2& TinyTransform2D::GetScale( ) const { return _scale; }

float TinyTransform2D::GetRotator( ) const { return glm::radians( _rotation ); }

const tiny_mat4& TinyTransform2D::GetTransform( ) const { return _transform; }
