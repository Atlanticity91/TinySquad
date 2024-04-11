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
 * @creation : 06/04/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Assets/TinyAssetHandle.h>

te_class TinyAsset {

protected:
	tiny_uint _type;
	tiny_uint _reference;

public:
	TinyAsset( TinyAssetTypes type );

	TinyAsset( tiny_uint type );

	virtual ~TinyAsset( ) = default;

	bool Acquire( TinyGame* game );

	bool Release( TinyGame* game );

	tiny_virtual( void Terminate( TinyGame* game ) );

protected:
	tiny_virtualv( true, bool OnAcquire( TinyGame* game ) );

	tiny_virtualv( true, bool OnRelease( TinyGame* game ) );

public:
	tiny_uint GetType( ) const;

	tiny_uint GetReference( ) const;

};
