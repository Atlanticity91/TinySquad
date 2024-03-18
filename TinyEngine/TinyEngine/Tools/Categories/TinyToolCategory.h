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

#include <TinyEngine/Tools/UI/TinyToolboxGuizmo.h>

te_class TinyToolCategory {

private:
	tiny_string _name;

public:
	TinyToolCategory( const tiny_string& name );

	virtual ~TinyToolCategory( ) = default;

	tiny_virtual( void Create( TinyGame* game, TinyToolbox& toolbox ) );

	virtual bool Tick( TinyGame* game, TinyToolbox& toolbox );

	tiny_virtual( void Terminate( TinyGame* game ) );

protected:
	tiny_virtual( void OnTick( TinyGame* game, TinyToolbox& toolbox ) );

};
