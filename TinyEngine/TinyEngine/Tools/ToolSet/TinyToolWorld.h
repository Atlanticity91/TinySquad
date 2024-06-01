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
 * @creation : 19/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyToolScene.h"

te_class TinyToolWorld final : tiny_inherit( TinyToolCategory ) {

private:
	tiny_buffer<32> m_new_entity;
	tiny_uint m_new_entity_id;
	tiny_hash m_delete_hash;

public:
	TinyToolWorld( );

	~TinyToolWorld( ) = default;

protected:
	tiny_implement( void OnTick( TinyGame* game, TinyToolbox& toolbox ) );

private:
	void DrawEntity( TinyGame* game, TinyECS& ecs, tiny_map_node<TinyEntity>& entity );

	void DrawNewEntity( TinyECS& ecs );

};
