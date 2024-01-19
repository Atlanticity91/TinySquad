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
 * @creation : 24/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyMaterial.h"

te_class TinyMaterialManager final 
	: tiny_inherit( TinyAssetList<TA_TYPE_MATERIAL, TinyMaterial> )
{ 

public:
	TinyMaterialManager( );

	~TinyMaterialManager( ) = default;

protected:
	tiny_implement( bool OnLoad(
		TinyGame* game,
		TinyFile& file,
		TinyMaterial& material
	) );

	tiny_implement( void OnUnLoad( TinyGame* game, TinyMaterial& material ) );

	tiny_implement( bool OnCreate(
		TinyGame* game,
		c_ptr asset_builder,
		TinyMaterial& material
	) );

};
