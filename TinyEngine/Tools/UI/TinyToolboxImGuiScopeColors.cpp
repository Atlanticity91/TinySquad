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

	ScopeColors::ScopeColors( )
		: _count{ 0 }
	{ }

	ScopeColors::ScopeColors( const Color& color )
		: ScopeColors{ { color } }
	{ }

	ScopeColors::ScopeColors( tiny_init<Color> colors )
		: ScopeColors{ }
	{
		Push( colors );
	}

	ScopeColors::ScopeColors( ImGuiCol label, const ImColor& value )
		: ScopeColors{ { label, value } }
	{ }

	ScopeColors::~ScopeColors( ) { Pop( _count ); }

	void ScopeColors::Push( const Color& color ) { Push( { color } ); }

	void ScopeColors::Push( tiny_init<Color> colors ) {
		if ( colors.size( ) > 0 ) {
			_count += (tiny_int)colors.size( );

			for ( auto& color : colors ) {
				auto convert_color = ImGui::ColorConvertFloat4ToU32( color.Value );

				ImGui::PushStyleColor( color.Label, convert_color );
			}
		}
	}

	void ScopeColors::Push( ImGuiCol label, const ImColor& value ) {
		Push( { { label, value } } );
	}

	void ScopeColors::Pop( ) { Pop( 1 ); }

	void ScopeColors::Pop( tiny_int count ) {
		if ( _count > 0 ) {
			auto claim = _count - count > -1 ? count : _count;

			ImGui::PopStyleColor( claim );

			_count -= claim;
		}
	}

};
