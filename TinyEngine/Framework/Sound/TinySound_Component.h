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

TINY_FRAMEWORK_COMP( TinySound ) {

private:
	TinyAsset _cue;
	tiny_uint _handle;
	float	  _volume;

public:
	TinySound( );

	TinySound( const tiny_hash entity_hash );

	~TinySound( ) = default;

	tiny_implement( bool Create( TinyGame* game, TinyEngine& engine ) );

	tiny_implement( void Delete( TinyGame* game, TinyEngine& engine ) );

	bool SetCue( TinyGame* game, const tiny_string& cue_name );

	tiny_inline bool Play( TinyGame* game );

	bool Play( TinyGame* game, bool imediate );

	void Stop( TinyGame* game );

	tiny_implement( void DisplayWidget(
		TinyGame* game,
		TinyEngine& engine,
		TinyToolbox& toolbox
	) );

public:
	TINY_COMP_NAME( TinySound );

	TinyAsset& GetCue( );

	float GetVolume( ) const;

};
