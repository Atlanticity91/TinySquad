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
 * @creation : 15/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyMaterialManager::TinyMaterialManager( ) 
	: TinyAssetList{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyMaterialManager::OnLoad(
	TinyGame* game,
	TinyFile& file,
	TinyMaterial& material
) {
	auto header = TinyAssetHeader{ };
	auto state  = false;

	file.Read( header );

	if ( header.Type == TA_TYPE_MATERIAL ) {
		auto descriptor_count = (tiny_uint)0;
		auto& graphics		  = game->GetGraphics( );
		auto builder		  = TinyMaterialBuilder{ };

		file.Read( builder.PassType );
		file.Read( builder.PassName );
		file.Read( builder.Subpass );
		file.Read( builder.ShaderStages );
		file.Read( builder.InputBinding );
		file.Read( builder.InputAttributes );
		file.Read( builder.Topology );
		file.Read( builder.Tessellation );
		file.Read( builder.DepthEnable );
		file.Read( builder.StencilEnable );
		file.Read( builder.DepthOperation );
		file.Read( builder.DepthStencilFront );
		file.Read( builder.DepthStencilBack );
		file.Read( builder.ColorBlends );
		file.Read( builder.Dynamics );
		file.Read( descriptor_count );

		if ( descriptor_count > 0 ) {
			builder.Descriptors = descriptor_count;

			for ( auto& descriptor : builder.Descriptors )
				file.Read( descriptor );
		}

		file.Read( builder.Constants );

		state = builder.ShaderStages.size( ) > 1 && material.Create( game, graphics, builder );
	}

	return state;
}

void TinyMaterialManager::OnUnLoad( TinyGame* game, TinyMaterial& material ) {
	auto& graphics = game->GetGraphics( );
	auto& assets   = game->GetAssets( );
	auto context   = graphics.GetContext( );

	material.Terminate( game, assets, context );
}

bool TinyMaterialManager::OnCreate(
	TinyGame* game,
	c_pointer asset_builder,
	TinyMaterial& material
) {
	auto& graphics = game->GetGraphics( );
	auto* builder  = tiny_cast( asset_builder, TinyMaterialBuilder* );

	return builder && material.Create( game, graphics, *builder );
}
