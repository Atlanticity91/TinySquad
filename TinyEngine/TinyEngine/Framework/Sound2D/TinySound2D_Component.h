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
 * @creation : 24/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Framework/Skin2D/TinySkin2D_System.h>

TINY_FRAMEWORK_COMP( TinySound2D ) {

private:
	TinyAssetHandle m_cue;
	tiny_uint m_handle;
	float m_volume;

public:
	TinySound2D( );

	TinySound2D( const tiny_hash entity_hash );

	~TinySound2D( ) = default;

	tiny_implement( bool Create( TinyGame* game ) );

	tiny_implement( void Delete( TinyGame* game ) );

	bool SetCue( TinyGame* game, const tiny_string& cue_name );

	tiny_inline bool Play( TinyGame* game );

	bool Play( TinyGame* game, bool imediate );

	void Stop( TinyGame* game );

protected:
	tiny_implement( void OnTickWidget(
		TinyGraphicManager & graphics,
		TinyInputManager & inputs,
		TinyGame * game
	) );

public:
	TINY_COMP_NAME( TinySound2D );

	TinyAssetHandle& GetCue( );

	float GetVolume( ) const;

};
