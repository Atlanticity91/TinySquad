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
	_use_local{ true },
	_location{ .0f },
	_rotation{ .0f },
	_scale{ 1.f }
{ }

bool TinyCamera::Create( TinyGame* game, TinyEngine& engine ) { return true; }

void TinyCamera::Delete( TinyGame* game, TinyEngine& engine ) { }

void TinyCamera::DisplayWidget(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) { 
	TinyComponent::DisplayWidget( game, engine, toolbox );

	auto& ecs = engine.GetECS( );

	if ( TinyImGui::Checkbox( "Use Local", _use_local ) ) {
		if ( !_use_local )
			_use_local = ecs.GetHasComponent<TinyTransform2D>( _owner );
	}

	TinyImGui::InputVec3( "Location", _location );
	TinyImGui::InputVec3( "Rotation", _rotation );
	TinyImGui::InputVec3( "Scale", _scale );
}

tiny_mat4 TinyCamera::Calculate( TinyECS& ecs ) {
	if ( !_use_local ) { }

	auto quat_vec = tiny_vec3{
		glm::radians( _rotation.x ),
		glm::radians( _rotation.y ),
		glm::radians( _rotation.z )
	};
	auto quat = tiny_quat{ quat_vec };
	auto view = glm::toMat4( quat );

	view *= glm::translate( _location );
	view *= glm::scale( _scale );

	return view;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyCamera::GetUseLocal( ) const { return _use_local; }

const tiny_vec3& TinyCamera::GetLocation( ) const { return _location; }

const tiny_vec3& TinyCamera::GetRotation( ) const { return _rotation; }

const tiny_vec3& TinyCamera::GetScale( ) const { return _scale; }
