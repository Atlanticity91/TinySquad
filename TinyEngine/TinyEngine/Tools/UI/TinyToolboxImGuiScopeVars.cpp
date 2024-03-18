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
 * @creation : 19/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace TinyImGui {

	ScopeVars::ScopeVars( )
		: _count{ 0 }
	{ }

	ScopeVars::ScopeVars( const Var& var )
		: ScopeVars{ { var } }
	{ }

	ScopeVars::ScopeVars( tiny_init<Var> vars )
		: ScopeVars{ }
	{ 
		Push( vars );
	}

	ScopeVars::ScopeVars( ImGuiStyleVar label, const ImVec2& value )
		: ScopeVars{ { label, value } }
	{ }

	ScopeVars::~ScopeVars( ) { Pop( _count ); };

	void ScopeVars::Push( const Var& var ) { Push( { var } ); }

	void ScopeVars::Push( tiny_init<Var> vars ) {
		if ( vars.size( ) > 0 ) {
			_count += (tiny_int)vars.size( );

			for ( auto& var : vars )
				ImGui::PushStyleVar( var.Label, var.Value );
		}
	}

	void ScopeVars::Push( ImGuiStyleVar label, const ImVec2& value ) {
		return Push( { label, value } );
	}

	void ScopeVars::Pop( ) { Pop( 1 ); }

	void ScopeVars::Pop( tiny_int count ) {
		if ( _count > 0 ) {
			auto claim = _count - count > -1 ? count : _count;

			ImGui::PopStyleVar( claim );

			_count -= claim;
		}
	}

};
