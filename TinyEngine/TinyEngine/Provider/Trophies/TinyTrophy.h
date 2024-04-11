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
 * @creation : 11/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Framework/TinyFramework.h>

te_class TinyTrophy final : tiny_inherit( TinyAsset ) { 

private:
	bool			_is_locked;
	TinyAssetHandle _icon;

public:
	TinyTrophy( );

	~TinyTrophy( ) = default;

	tiny_implement( void Terminate( TinyGame* game ) );

public:
	bool GetIsLocked( ) const;

	const TinyAssetHandle& GetIcon( ) const;

};
