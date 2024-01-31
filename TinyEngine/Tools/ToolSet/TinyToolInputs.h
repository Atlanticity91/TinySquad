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
 * @creation : 21/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyToolCommon.h"

te_class TinyToolInputs final 
	: tiny_inherit( TinyToolCategory ),
	tiny_inherit( TinyToolDialog )
{

public:
	TinyToolInputs( );

	~TinyToolInputs( ) = default;

protected:
	tiny_implement( void OnTick(
		TinyGame* game,
		TinyEngine& engine,
		TinyToolbox& toolbox
	) );

};
