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
 * @creation : 24/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Framework/Controller/TinyController_System.h>

TINY_FRAMEWORK_COMP( TinyEmitter ) {

public:
	TinyEmitter( );

	TinyEmitter( const tiny_hash entity_hash );

	~TinyEmitter( ) = default;

	tiny_implement( bool Create( TinyGame* game, TinyEngine& engine ) );

	tiny_implement( void Delete( TinyGame* game, TinyEngine& engine ) );

	tiny_implement( void DisplayWidget( 
		TinyGame* game, 
		TinyEngine& engine, 
		TinyToolbox& toolbox 
	) );

public:
	TINY_COMP_NAME( TinyEmitter );

};
