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

#include "TinyImGuiBackend.h"

tm_class TinyImGuiContext final {

private:
	bool m_is_visible;
	ImGuiContext* m_context;

public:
	TinyImGuiContext( );

	~TinyImGuiContext( ) = default;

	bool Create( TinyGraphicManager& graphics );

	void Show( );

	void Hide( );

	void Toggle( );

	void Prepare( );

	void Terminate( );
	
public:
	bool GetIsVisible( ) const;

	ImGuiContext* Get( ) const;

public:
	operator ImGuiContext* ( ) const;

};
