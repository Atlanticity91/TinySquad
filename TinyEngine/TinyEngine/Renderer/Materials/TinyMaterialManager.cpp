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
	: TinyAssetContainer{ }
{ }

bool TinyMaterialManager::Create(
	TinyGame* game,
	const tiny_string& alias,
	const c_pointer builder
) {
	auto* builder_ = tiny_cast( builder, TinyMaterialBuilder* );
	auto& material = Emplace( alias );
	auto& graphics = game->GetGraphics( );

	return  builder_->ShaderStages.size( ) > 1 && 
			material.Create( game, graphics, tiny_lvalue( builder_ ) );
}

bool TinyMaterialManager::Load(
	TinyGame* game,
	const tiny_string& alias,
	TinyFile& file
) {
	auto builder = TinyMaterialBuilder{ };

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
	file.Read( builder.Descriptors );
	file.Read( builder.Constants );

	return Create( game, alias, tiny_rvalue( builder ) );
}
