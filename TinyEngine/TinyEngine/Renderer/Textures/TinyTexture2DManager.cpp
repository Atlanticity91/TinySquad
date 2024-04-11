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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyTexture2DManager::TinyTexture2DManager( )
	: TinyAssetContainer{ }
{ }

bool TinyTexture2DManager::Create(
	TinyGame* game, 
	const tiny_string& alias, 
	const c_pointer builder
) {
	auto& graphics = game->GetGraphics( );
	auto& builder_ = tiny_lvalue( tiny_cast( builder, const TinyTexture2DBuilder* ) );
	auto context   = graphics.GetContext( );
	auto staging   = TinyGraphicBufferStaging{ };
	auto state	   = false;

	if ( staging.CreateMap( context, builder_.Size, builder_.Texels ) ) {
		auto& texture = Emplace( alias );

		state = texture.Create( graphics, builder_, staging );
	}

	staging.Terminate( context );

	return state;
}

bool TinyTexture2DManager::Load(
	TinyGame* game,
	const tiny_string& alias,
	TinyFile& file
) {
	auto builder = TinyTexture2DBuilder{ };

	file.Read( builder.Rows );
	file.Read( builder.Columns );
	file.Read( builder.Properties );
	file.Read( builder.Size );
	//file.Read( builder.Size, staging );

	return Create( game, alias, tiny_rvalue( builder ) );
};
