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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolDialog::TinyToolDialog( const std::string& filters )
	: _dialog_filters{ filters },
	_dialog_path{ }
{ }

bool TinyToolDialog::OpenDialog( TinyFilesystem& filesystem ) {
	return filesystem.OpenDialog( TD_TYPE_OPEM_FILE, _dialog_filters, _dialog_path );
}

bool TinyToolDialog::SaveDialog( TinyFilesystem& filesystem ) {
	return filesystem.OpenDialog( TD_TYPE_SAVE_FILE, _dialog_filters, _dialog_path );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const std::string& TinyToolDialog::GetFilters( ) const { return _dialog_filters; }

const std::string& TinyToolDialog::GetPath( ) const { return _dialog_path; }
