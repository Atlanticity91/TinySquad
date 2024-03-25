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
 * @creation : 18/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "MsdfBitmap.h"

class MsdfAtlasGenerator final {

	using Bitmap_t = msdfgen::BitmapConstRef<uint8_t, 3>;

private:
	msdfgen::FreetypeHandle*	 _freetype;
	msdfgen::FontHandle*		 _font;
	msdf_atlas::Charset			 _charset;
	msdf_atlas::TightAtlasPacker _packer;
public:
	MsdfAtlasGenerator( );

	~MsdfAtlasGenerator( );

	bool Prepare( const uint8_t* buffer, size_t length );

	MsdfAtlasGenerator& AddCharset( uint32_t start, uint32_t stop );

	bool GenerateCharset( MsdfAtlas& atlas, MsdfBitmap& bitmap );

	bool Process( const MsdfParameters& parameters, MsdfAtlas& atlas, MsdfBitmap& bitmap );

private:
	void PreProcess( const MsdfParameters& parameters, MsdfAtlas& atlas, MsdfBitmap& bitmap );

};
