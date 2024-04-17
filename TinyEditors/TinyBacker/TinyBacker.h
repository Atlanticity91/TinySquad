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
 * @creation : 26/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyNut/TinyNut.h>

class TinyBacker final : tiny_inherit( TinyNut ) {

private:
	tiny_list<std::string> _history;

public:
	TinyBacker( );

	~TinyBacker( ) = default;

protected:
	tiny_implement( void TickMenubar( ) );

	tiny_implement( void TickUI( ) );

private:
	c_string TypeToStr( const tiny_uint type ) const;

};
