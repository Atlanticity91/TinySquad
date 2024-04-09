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

#include "TinyFontBuilder.h"

te_class TinyFont final : tiny_inherit( TinyAsset ) {

private:
	tiny_vec2					_range;
	tiny_vec2					_miter;
	TinyGraphicTexture			_texture;
	tiny_list<TinyCharGeometry> _geometry;

public:
	TinyFont( );

	~TinyFont( ) = default;

	void Terminate( TinyGame* game );

public:
	const tiny_vec2& GetRange( ) const;

	const tiny_vec2& GetMiter( ) const;

	const TinyCharGeometry& GetGeometry( char character ) const;

	const VkDescriptorImageInfo& GetTexure( ) const;

};
