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

#include <TinyMicro/ImGui/Fonts/TinyImGuiFontManager.h>

tm_class TinyImGuiWindow {

protected:
	bool m_is_visible;
	tiny_string m_name;
	ImGuiWindowFlags m_flags;

public:
	TinyImGuiWindow( );

	TinyImGuiWindow( const tiny_string& name );

	TinyImGuiWindow( const tiny_string& name, ImGuiWindowFlags flags );

	TinyImGuiWindow( const tiny_string& name, bool is_visible );

	TinyImGuiWindow( const tiny_string& name, bool is_visible, ImGuiWindowFlags flags );

	virtual ~TinyImGuiWindow( ) = default;

	tiny_virtual( void OnCreate( native_pointer user_data ) );

	void AddFlag( ImGuiWindowFlags flag );

	void DeleteFlag( ImGuiWindowFlags flag );

	void SetFlags( ImGuiWindowFlags flag );

	void Show( native_pointer user_data );

	void Hide( native_pointer user_data );

	void Toggle( native_pointer user_data );

	virtual void Tick(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	);

	tiny_virtual( void Delete( native_pointer user_data ) );

protected:
	tiny_virtual( void OnShow( native_pointer user_data ) );
	
	tiny_virtual( void OnHide( native_pointer user_data ) );

	tiny_virtual( void OnTick(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	) );

public:
	virtual bool GetIsVisible( ) const;

	const tiny_string GetName( ) const;

	bool GetHasFlag( ImGuiWindowFlags flags ) const;

	ImGuiWindowFlags GetFlags( ) const;

};
