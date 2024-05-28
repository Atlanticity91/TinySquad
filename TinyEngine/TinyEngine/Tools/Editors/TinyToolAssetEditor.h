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
	bool			_in_use;
	ImVec2			_min_size;
	tiny_string		_name;
	TinyAssetHandle	_asset;
	tiny_string		_asset_name;

public:
	TinyToolAssetEditor( const tiny_string& name );

	TinyToolAssetEditor( const tiny_string& name, const ImVec2& min_size );

	virtual ~TinyToolAssetEditor( ) = default;

	bool Open( TinyGame* game, const tiny_string& name, TinyAssetHandle& asset );

	tiny_virtual( void Save( TinyGame* game ) );

	void Tick( TinyGame* game, TinyAssetManager& assets );

	void Close( TinyGame* game );

protected:
	tiny_virtualv( true, bool OnOpen(
		TinyGame* game, 
		const tiny_string& name, 
		native_pointer asset 
	) );

	tiny_virtual( void OnTick( TinyGame* game, TinyAssetManager& assets ) );

	virtual void OnClose( TinyGame* game, TinyAssetManager& assets );

};
