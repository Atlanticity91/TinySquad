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
 * @creation : 21/12/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyRenderUniformUtils.h"

te_class TinyRenderUniformManager final {

private:
	tiny_map<TinyRenderUniform> _uniforms;

public:
	TinyRenderUniformManager( );

	~TinyRenderUniformManager( ) = default;

	bool Create( TinyGraphicManager& graphics );

	bool Create( TinyGraphicManager& graphics, const TinyRenderUniformBuilder& builder );

	void Destroy( TinyGraphicManager& graphics, const tiny_string& name );

	void Terminate( TinyGraphicManager& graphics );

public:
	bool GetExist( const tiny_string& name ) const;

	TinyRenderUniform& GetUniform( const tiny_string& name );

};
