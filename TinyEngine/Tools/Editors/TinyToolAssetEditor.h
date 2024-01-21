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

#include <TinyEngine/Tools/ToolSet/TinyToolRender.h>

te_class TinyToolAssetEditor {

protected:
	bool		_in_use;
	c_ptr		_asset;
	tiny_string _name;

public:
	TinyToolAssetEditor( const tiny_string& name );

	virtual ~TinyToolAssetEditor( ) = default;

	tiny_virtualv( false, bool Open( TinyGame* game, c_ptr asset ) );

	void Close( );

	virtual void Tick( TinyGame* game );

protected:
	tiny_virtual( void OnTick( TinyGame* game ) );

	tiny_virtual( void OnClose( ) );

};
