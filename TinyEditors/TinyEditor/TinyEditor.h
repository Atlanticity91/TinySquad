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
 * @creation : 26/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/TinyGameEntry.h>

class TinyEditor final : public TinyGame { 

public:
	TinyEditor( );

	~TinyEditor( ) = default;

protected:
	virtual bool Initialize( TinyEngine& engine ) override;

	virtual void SetupBundles( TinyGraphicManager& graphics ) override;

	virtual void LoadInterop( TinyLuaContext& lua_context ) override;

	virtual void LoadContent( TinyAssetManager& assets ) override;

	virtual void LoadECS( TinyECS& ecs ) override;

	virtual void Tick( ) override;

	virtual void Terminate( ) override;

};
