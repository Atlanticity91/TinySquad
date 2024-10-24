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
	m_location{ .0f },
	m_rotation{ .0f },
	m_layer{ .0f },
	m_scale{ 1.f },
	m_transform{ 1.f }
{ }

TinyTransform2D& TinyTransform2D::SetLocationX( float scalar ) {
	m_location.x = scalar;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetLocationY( float scalar ) {
	m_location.y = scalar;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetLocation( const tiny_vec2& location ) {
	m_location = location;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetLocation( float x, float y ) {
	m_location.x = x;
	m_location.y = y;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetLayer( float layer ) {
	m_layer = layer;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetRotation( float rotation ) {
	m_rotation = rotation;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetScaleX( float scalar ) {
	m_scale.x = scalar;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetScaleY( float scalar ) {
	m_scale.y = scalar;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::SetScale( float scalar ) {
	return SetScale( scalar, scalar );
}

TinyTransform2D& TinyTransform2D::SetScale( const tiny_vec2& scale ) {
	return SetScale( scale.x, scale.y );
}

TinyTransform2D& TinyTransform2D::SetScale( float x, float y ) {
	m_scale.x = x;
	m_scale.y = y;

	return tiny_self;
}

void TinyTransform2D::Set( 
	const tiny_vec2& location, 
	float rotation, 
	const tiny_vec2& scale 
) {
	m_location = location;
	m_rotation = rotation;
	m_scale	  = scale;
}

void TinyTransform2D::Set(
	const tiny_vec3& location,
	const tiny_vec3& rotation,
	const tiny_vec3& scale
) {
	m_location = location;
	m_rotation = glm::degrees( rotation.z );
	m_scale	  = scale;
}

TinyTransform2D& TinyTransform2D::Move( const tiny_vec2& offset ) {
	return Move( offset.x, offset.y );
}

TinyTransform2D& TinyTransform2D::Move( float x, float y ) {
	m_location.x += x;
	m_location.y += y;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::Rotate( float offset ) {
	m_rotation += offset;

	return tiny_self;
}

TinyTransform2D& TinyTransform2D::Scale( float scalar ) {
	return Scale( scalar, scalar );
}

TinyTransform2D& TinyTransform2D::Scale( const tiny_vec2& scale ) {
	return Scale( scale.x, scale.y );
}

TinyTransform2D& TinyTransform2D::Scale( float x, float y ) {
	m_scale.x *= x;
	m_scale.y *= y;

	return tiny_self;
} 

TinyTransform2D& TinyTransform2D::ReCalculate( ) {
	auto half_scale = m_scale * .5f;

	m_transform  = glm::translate( tiny_vec3{ m_location.x + half_scale.x, m_location.y + half_scale.y, m_layer } );
	m_transform *= glm::rotate( glm::radians( m_rotation ), tiny_vec3{ .0f, .0f, 1.f } );
	m_transform *= glm::scale( tiny_vec3{ m_scale.x, m_scale.y, 1.f } );

	return tiny_self;
}

void TinyTransform2D::Delete( TinyGame* game ) {
	auto& ecs  = game->GetECS( );
	auto* skin = ecs.GetComponentAs<TinySkin2D>( m_owner );

	if ( skin )
		skin->Disable( game );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		=== PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyTransform2D::OnTickWidget(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	TinyGame* game
) {
	TinyImGui::InputVec2( "Location", m_location );
	TinyImGui::InputScalar( "Layer", m_layer );
	TinyImGui::InputScalar( "Rotation", m_rotation );
	TinyImGui::InputVec2( "Scale", m_scale );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_vec2& TinyTransform2D::GetLocation( ) { return m_location; }

const tiny_vec2& TinyTransform2D::GetLocation( ) const { return m_location; }

float TinyTransform2D::GetLayer( ) const { return m_layer; }

float TinyTransform2D::GetRotation( ) { return m_rotation; }

tiny_vec2& TinyTransform2D::GetScale( ) { return m_scale; }

tiny_vec2 TinyTransform2D::GetHalfScale( ) const { return m_scale * .5f; }

const tiny_vec2& TinyTransform2D::GetScale( ) const { return m_scale; }

tiny_vec3 TinyTransform2D::GetRotator( ) const {
	return { .0f,.0f, glm::radians( m_rotation ) };
}

const tiny_mat4& TinyTransform2D::GetTransform( ) const { return m_transform; }
