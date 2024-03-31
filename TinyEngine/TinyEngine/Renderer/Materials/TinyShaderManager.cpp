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
TinyShaderManager::TinyShaderManager( ) 
	: TinyAssetList{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyShaderManager::OnLoad(
	TinyGame* game,
	TinyFile& file,
	TinyGraphicShader& shader
) { 
	auto header = TinyAssetHeader{ };
	auto state  = false;

	file.Read( header );

	if ( header.Type == TA_TYPE_SHADER ) {
		auto& graphics = game->GetGraphics( );
		auto context   = graphics.GetContext( );
		auto builder   = TinyGraphicShaderSpecification{ };

		file.Read( builder.Type );
		file.Read( builder.Entry );
		file.Read( builder.Code );

		state = shader.Create( context, builder );
	}

	return state;
}

void TinyShaderManager::OnUnLoad( TinyGame* game, TinyGraphicShader& shader ) {
	auto& graphics = game->GetGraphics( );
	auto context   = graphics.GetContext( );

	shader.Terminate( context );
}

bool TinyShaderManager::OnCreate(
	TinyGame* game,
	c_pointer asset_builder,
	TinyGraphicShader& shader
) {
	auto& graphics = game->GetGraphics( );
	auto* builder  = tiny_cast( asset_builder, TinyGraphicShaderSpecification* );
	auto context   = graphics.GetContext( );

	return builder && shader.Create( context, *builder );
}
