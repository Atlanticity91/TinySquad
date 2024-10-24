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
 * @creation : 02/08/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Debug/Utils/TinyImGuiGuizmo.h>

te_class TinyDebugTabAssets final : tiny_inherit( TinyImGuiTab ) {

	typedef native_string( *AssetTypeToString )( tiny_uint );

private:
	tiny_uint m_type_count;
	AssetTypeToString m_type_to_string;

public:
	TinyDebugTabAssets( );

	~TinyDebugTabAssets( ) = default;

	tiny_implement( void OnCreate( native_pointer user_data ) );

protected:
	tiny_implement( void OnTick(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	) );

private:
	static native_string TypeToString( tiny_uint type );

};
