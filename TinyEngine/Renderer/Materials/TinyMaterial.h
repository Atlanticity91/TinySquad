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
 * @creation : 16/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyMaterialBuilder.h"

te_class TinyMaterial : tiny_inherit( TinyGraphicPipeline ) {

private:
	tiny_list<TinyAsset> _shaders;

public:
	TinyMaterial( );

	~TinyMaterial( ) = default;

	bool Create( 
		TinyGame* game,
		TinyGraphicManager& graphic,
		TinyMaterialBuilder& builder 
	);

	void Terminate(
		TinyGame* game,
		TinyAssetManager& assets, 
		TinyGraphicContext& context 
	);

};
