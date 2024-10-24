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

#include "TinyDebugTabCommon.h"

te_class TinyDebugTabInputs final : tiny_inherit( TinyImGuiTab ) {

private:
	tiny_buffer<128> m_new_input;
	TinyInputQuery m_new_query;
	tiny_hash m_input_remove;
	tiny_uint m_input_query;
	tiny_list<native_string> m_input_devices;
	tiny_string_view m_input_states;
	tiny_string_view m_input_modifier;

public:
	TinyDebugTabInputs( );

	~TinyDebugTabInputs( ) = default;

	tiny_implement( void OnCreate( native_pointer user_data ) );

protected:
	tiny_implement( void OnTick(
		TinyGraphicManager& graphics,
		TinyInputManager& inputs,
		native_pointer user_data
	) );

private:
	void DrawControls( TinyGame* game, TinyInputManager& inputs );

	void DrawNewInput( TinyInputManager& inputs );

	void DrawInputQwery( TinyInputQuery& query );

	void DrawInputMap( tiny_map<TinyInputQueries>&inputs );

};
