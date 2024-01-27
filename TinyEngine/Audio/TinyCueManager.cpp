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
 * @creation : 03/01/2024
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
TinyCueManager::TinyCueManager( )
	: TinyAssetList{ }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyCueManager::OnLoad( TinyGame* game, TinyFile& file, TinyCue& sound_cue ) {
	auto header = TinyAssetHeader{ };
	auto state  = false;

	file.Read( header );

	if ( header.Type == TA_TYPE_CUE ) {
		auto& storage = sound_cue.GetStorage( );
		auto size	  = tiny_cast( 0, tiny_uint );

		file.Read( sound_cue.GetFormat( ) );
		file.Read( sound_cue.GetContext( ) );
		file.Read( size );

		state = tiny_allocate( storage, size );

		if ( state ) {
			auto* address = storage.GetAddress( );

			state = file.Read( size, address ) == size;
		}
	}
	
	return state;
}

void TinyCueManager::OnUnLoad( TinyGame* game, TinyCue& sound_cue ) {
	tiny_deallocate( sound_cue.GetStorage( ) );
}

bool TinyCueManager::OnCreate( TinyGame* game, c_pointer asset_builder, TinyCue& cue ) {
	auto* builder = tiny_cast( asset_builder, TinyCueBuilder* );
	auto state	  = builder != nullptr && builder->Size > 0;

	if ( state ) {
		Tiny::Memcpy( tiny_rvalue( builder->Format ), tiny_rvalue( cue.GetFormat( ) ) );
		Tiny::Memcpy( tiny_rvalue( builder->Context ), tiny_rvalue( cue.GetContext( ) ) );

		state = tiny_allocate( cue.GetStorage( ), builder->Size );
	}

	return state;
}
