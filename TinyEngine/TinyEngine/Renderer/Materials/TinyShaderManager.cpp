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
	: TinyAssetContainer{ }
{ }

bool TinyShaderManager::Create(
	TinyGame* game,
	const tiny_string& alias,
	const native_pointer builder
) {
	auto state = false;

	if ( builder ) {
		auto* builder_ = tiny_cast( builder, TinyGraphicShaderSpecification* );
		auto& graphics = game->GetGraphics( );
		auto context   = graphics.GetContext( );
		auto& shader   = Emplace( alias );

		state = shader.Create( context, tiny_lvalue( builder_ ) );
	}

	return state;
}

bool TinyShaderManager::Load(
	TinyGame* game,
	const tiny_string& alias,
	TinyFile& file
) {
	auto builder = TinyGraphicShaderSpecification{ };

	file.Read( builder.Type );
	file.Read( builder.Entry );
	file.Read( builder.Code );

	return Create( game, alias, tiny_rvalue( builder ) );
}
