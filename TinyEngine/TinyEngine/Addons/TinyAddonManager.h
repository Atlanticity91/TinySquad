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
 * @creation : 22/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Tools/TinyToolbox.h>

te_class TinyAddon final : tiny_inherit( TinyAsset ) { 

public:
	TinyAddon( ) : TinyAsset{ TA_TYPE_ADDON } { };

};

te_class TinyAddonManager final : tiny_inherit( TinyAssetContainer<TinyAddon> ) {

public:
	TinyAddonManager( );

	~TinyAddonManager( ) = default;

	bool Initialize( TinyGame* game );

	void PreTick( TinyGame* game );

	void PostTick( TinyGame* game );

	void Terminate( TinyGame* game );

};
