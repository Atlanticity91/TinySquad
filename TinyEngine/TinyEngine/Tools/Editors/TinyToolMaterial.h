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
 * @creation : 23/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyToolAnim2D.h"

te_class TinyToolMaterial final : tiny_inherit( TinyToolAssetEditor ) {

private:
	TinyMaterial* _material;

public:
	TinyToolMaterial( );

	~TinyToolMaterial( ) = default;

	tiny_implement( void Save( TinyGame* game ) );

protected:
	tiny_implement( bool OnOpen( TinyGame* game, const tiny_string& name, native_pointer asset ) );

	tiny_implement( void OnTick( TinyGame* game, TinyAssetManager& assets ) );

private:
	void DrawGenerals( );

	void DrawDynamics( );

	void DrawInputs( );

	void DrawColorBlends( );

	void DrawDepthStencil( );

	void DrawDescriptors( );

	void DrawConstants( );

	void DrawShaders( );

};
