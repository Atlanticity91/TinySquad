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
 * @creation : 02/08/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyDebugTabInputs.h"

te_class TinyDebugTabScene final : tiny_inherit( TinyImGuiTab ) {

private:
	tiny_buffer<32> m_new_entity;
	tiny_uint m_new_entity_id;
	tiny_hash m_delete_hash;

public:
	TinyDebugTabScene( );

	~TinyDebugTabScene( ) = default;

	tiny_implement( void OnCreate( native_pointer user_data ) );

protected:
	tiny_implement( void OnTick(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	) );

private:
	void DrawSystems( TinyGame* game, TinyECS& ecs );

	void DrawNewEntity( TinyECS& ecs );

	void DrawEntity( TinyGame* game, TinyImGuizmo& guizmo, TinyECS& ecs, tiny_map_node<TinyEntity>& entity );

	void DrawEntities( TinyGame* game, TinyImGuizmo& guizmo, TinyECS& ecs );

};
