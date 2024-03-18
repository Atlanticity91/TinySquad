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
 * @creation : 21/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyToolCommon.h"

te_class TinyToolInputs final 
	: tiny_inherit( TinyToolCategory ),
	tiny_inherit( TinyToolDialog )
{

private:
	tiny_buffer<128>	_new_input;
	TinyInputQuery		_new_query;
	tiny_hash			_input_remove;
	tiny_uint			_input_query;
	tiny_list<c_string> _input_devices;
	tiny_string_view	_input_states;
	tiny_string_view	_input_modifier;

public:
	TinyToolInputs( );

	~TinyToolInputs( ) = default;

protected:
	tiny_implement( void OnTick( TinyGame* game, TinyToolbox& toolbox ) );

private:
	void DrawControls( TinyGame* game, TinyInputManager& inputs );

	void DrawNewInput( TinyInputManager& inputs );

	void DrawInputQwery( TinyInputQuery& query );

	void DrawInputMap( tiny_map<TinyInputQueries>& inputs );

};
