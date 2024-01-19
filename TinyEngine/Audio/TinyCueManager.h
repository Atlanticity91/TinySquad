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
 * @creation : 03/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyCue.h"

te_class TinyCueManager final 
	: tiny_inherit( TinyAssetList<TA_TYPE_CUE, TinyCue> )
{

public:
	TinyCueManager( );

	~TinyCueManager( ) = default;

protected:
	tiny_implement( bool OnLoad(
		TinyGame* game,
		TinyFile& file,
		TinyCue& sound_cue
	) );

	tiny_implement( void OnUnLoad( TinyGame* game, TinyCue& sound_cue ) );

	tiny_implement( bool OnCreate(
		TinyGame* game,
		c_ptr asset_builder,
		TinyCue& element
	) );

};
