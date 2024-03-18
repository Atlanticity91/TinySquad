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
 * @creation : 29/01/2024
 * @version  : 2024.1.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyToolContent.h"

te_class TinyToolScene final 
	: tiny_inherit( TinyToolCategory ),
	tiny_inherit( TinyToolDialog )
{

private:
	bool _has_changed;

public:
	TinyToolScene( );

	~TinyToolScene( ) = default;

	void MarkUnSaved( );

protected:
	tiny_implement( void OnTick( TinyGame* game, TinyToolbox& toolbox ) );

private:
	void DrawSystems( TinyGame* game, TinyECS& ecs );

	void DrawGenerals( );

public:
	bool GetHasChanged( ) const;

};
