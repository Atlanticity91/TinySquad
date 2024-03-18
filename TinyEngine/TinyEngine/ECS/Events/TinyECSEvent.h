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
 * @creation : 22/02/2024
 * @version  : 2024.2.3
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/ECS/Entities/TinyEntityManager.h>

class TinyECS;

te_class TinyECSEvent {

private:
	tiny_uint _type;

public:
	TinyECSEvent( tiny_uint type );

	virtual ~TinyECSEvent( ) = default;

	tiny_abstract( void Execute( TinyGame* game, TinyECS& ecs ) );

public:
	tiny_uint GetType( ) const;

};
