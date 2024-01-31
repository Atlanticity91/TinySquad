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
	tiny_buffer<32> _new_entity;
	tiny_uint		_new_entity_id;
	tiny_hash		_selection_hash;
	tiny_hash		_query_hash;

public:
	TinyToolWorld( );

	~TinyToolWorld( ) = default;

protected:
	tiny_implement( void OnTick(
		TinyGame* game,
		TinyEngine& engine,
		TinyToolbox& toolbox
	) );

private:
	void DrawAddComp( TinyGame* game, TinyEngine& engine, TinyECS& ecs );

	void DrawEntity( TinyGame* game, TinyECS& ecs, tiny_map_node<TinyEntity>& entity );

	void DrawNewEntity( TinyECS& ecs );

private:
	static void DrawSystems( TinyGame* game, TinyEngine& engine, TinyECS& ecs );

};
