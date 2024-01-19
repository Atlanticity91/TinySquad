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

#include "TinyToolboxImGuiScopeVars.h"

namespace TinyImGui { 

	te_struct Color {

		ImGuiCol Label = ImGuiCol_COUNT;
		ImColor Value{ };

	};

	te_class ScopeColors final {

	private:
		tiny_int _count;

	public:
		ScopeColors( );

		ScopeColors( const Color& color );

		ScopeColors( tiny_init<Color> colors );

		ScopeColors( ImGuiCol label, const ImColor& value );

		~ScopeColors( );

		tiny_inline void Push( const Color& color );
		
		void Push( tiny_init<Color> colors );

		tiny_inline void Push( ImGuiCol label, const ImColor& value );

		tiny_inline void Pop( );

		void Pop( tiny_int count );

	};

};
