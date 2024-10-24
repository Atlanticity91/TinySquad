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
 * @creation : 29/07/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyImGuiFont.h"

tm_class TinyImGuiFontManager final {

private:
	tiny_map<ImFont*> m_fonts;

public:
	TinyImGuiFontManager( );

	~TinyImGuiFontManager( ) = default;

	void Initialize( );
	
	bool LoadFont(
		TinyFilesystem& filesystem,
		TinyGraphicManager& graphics,
		const TinyImGuiFont& font
	);

	bool LoadFonts(
		TinyFilesystem& filesystem,
		TinyGraphicManager& graphics,
		tiny_init<TinyImGuiFont> fonts
	);

	bool AddFont(
		const tiny_string& alias,
		tiny_int length,
		const tiny_uint* data,
		float size
	);

	bool CreateFont(
		const tiny_string& name,
		float size,
		tiny_init<TinyImGuiFontEmbedded> fonts
	);

	void SetFont( const tiny_string& name );

public:
	bool GetHasFont( const tiny_string& name ) const;

};
