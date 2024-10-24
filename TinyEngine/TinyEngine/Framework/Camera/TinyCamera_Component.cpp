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
TinyCamera::TinyCamera( ) 
	: TinyCamera{ TINY_NO_ENTITY }
{ }

TinyCamera::TinyCamera( const tiny_hash entity_hash )
	: TinyComponent{ entity_hash },
	m_use_local{ true },
	m_location{ .0f },
	m_rotation{ .0f },
	m_scale{ 1.f }
{ }

bool TinyCamera::Create( TinyGame* game ) { return true; }

void TinyCamera::Delete( TinyGame* game ) { }

tiny_mat4 TinyCamera::Calculate( TinyECS& ecs ) {
	if ( !m_use_local ) { }

	auto quat_vec = tiny_vec3{
		glm::radians( m_rotation.x ),
		glm::radians( m_rotation.y ),
		glm::radians( m_rotation.z )
	};
	auto quat = tiny_quat{ quat_vec };
	auto view = glm::toMat4( quat );

	view *= glm::translate( m_location );
	view *= glm::scale( m_scale );

	return view;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyCamera::OnTickWidget(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	TinyGame* game
) {
	auto& ecs = game->GetECS( );

	if ( TinyImGui::Checkbox( "Use Local", m_use_local ) ) {
		if ( !m_use_local )
			m_use_local = ecs.GetHasComponent<TinyTransform2D>( m_owner );
	}

	TinyImGui::InputVec3( "Location", m_location );
	TinyImGui::InputVec3( "Rotation", m_rotation );
	TinyImGui::InputVec3( "Scale", m_scale );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyCamera::GetUseLocal( ) const { return m_use_local; }

const tiny_vec3& TinyCamera::GetLocation( ) const { return m_location; }

const tiny_vec3& TinyCamera::GetRotation( ) const { return m_rotation; }

const tiny_vec3& TinyCamera::GetScale( ) const { return m_scale; }
