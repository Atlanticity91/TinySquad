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
 * @creation : 26/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Renderer/Textures/TinyTextureAtlasManager.h>

te_struct TinyCharVertice {

	tiny_vec4 Location;
	tiny_vec2 UV;

};

te_struct TinyCharGeometry {

	float Advance = 0.f;
	TinyCharVertice Vertices[ 4 ];

};

te_class TinyFont final {

public:
	TinyFont( );

	~TinyFont( ) = default;

	const TinyCharGeometry& GetGeometry( char character ) const;

	const TinyGraphicPipelineBindpoint& GetTexure( ) const;

};
