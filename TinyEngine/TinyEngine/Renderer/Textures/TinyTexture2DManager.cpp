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
	: TinyAssetList{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyTexture2DManager::OnLoad(
	TinyGame* game,
	TinyFile& file,
	TinyTexture2D& texture
) {
	auto header = TinyAssetHeader{ };
	auto state  = false;

	file.Read( header );

	if ( header.Type == TA_TYPE_TEXTURE_2D ) {
		auto& graphics = game->GetGraphics( );
		auto context   = graphics.GetContext( );
		auto builder   = TinyTexture2DBuilder{ };
		auto staging   = TinyGraphicBufferStaging{ };

		file.Read( builder.Rows );
		file.Read( builder.Columns );
		file.Read( builder.Properties );
		file.Read( builder.Size );

		state = staging.Create2( context, builder.Size );

		if ( state ) {
			file.Read( builder.Size, staging );

			staging.UnMap( context );

			state = texture.Create( graphics, builder, staging );

			staging.Terminate( context );
		}
	}

	return state;
}

void TinyTexture2DManager::OnUnLoad( TinyGame* game, TinyTexture2D& texture ) {
	auto& graphics = game->GetGraphics( );
	auto context   = graphics.GetContext( );

	texture.Terminate( context );
}

bool TinyTexture2DManager::OnCreate(
	TinyGame* game,
	c_pointer asset_builder,
	TinyTexture2D& texture
) {
	auto& graphics = game->GetGraphics( );
	auto* builder  = tiny_cast( asset_builder, TinyTexture2DBuilder* );
	auto staging   = TinyGraphicBufferStaging{ };
	auto context   = graphics.GetContext( );
	auto state	   = staging.Create2( context, builder->Size );

	if ( state ) {
		Tiny::Memcpy( tiny_cast( builder->Texels, const c_pointer ), staging, builder->Size );

		staging.UnMap( context );

		state = texture.Create( graphics, tiny_lvalue( builder ), staging );

		staging.Terminate( context );
	}

	return state;
}
