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
 * @creation : 31/01/2024
 * @version  : 2024.1.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyToolCategory.h"

te_class TinyToolDialog {

protected:
	tiny_string _dialog_filters;
	tiny_string _dialog_path;

public:
	TinyToolDialog( const tiny_string& filters );

	virtual ~TinyToolDialog( ) = default;

	bool OpenDialog( TinyFilesystem& filesystem );

	bool SaveDialog( TinyFilesystem& filesystem );

public:
	const tiny_string& GetFilters( ) const;

	const tiny_string& GetPath( ) const;

};
