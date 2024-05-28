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
	const native_pointer builder
) {
	auto& graphics = game->GetGraphics( );
	auto& builder_ = tiny_lvalue( tiny_cast( builder, const TinyTexture2DBuilder* ) );
	auto context   = graphics.GetContext( );
	auto staging   = TinyGraphicBufferStaging{ };
	auto state	   = false;
	auto size	   = builder_.Texels.size( );
	auto* data	   = tiny_cast( builder_.Texels.data( ), const native_pointer );

	if ( staging.CreateMap( context, size, data ) ) {
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
	file.Read( builder.Texels );

	return Create( game, alias, tiny_rvalue( builder ) );
};
