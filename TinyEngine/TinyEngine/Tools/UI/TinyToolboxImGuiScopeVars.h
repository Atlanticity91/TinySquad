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

#include <TinyEngine/States/TinyGameStateManager.h>

namespace TinyImGui {

	te_struct Var {

		ImGuiStyleVar Label;
		ImVec2 Value;

	};

	te_class ScopeVars final {

	private:
		tiny_int m_count;

	public:
		ScopeVars( );

		ScopeVars( const Var& var );

		ScopeVars( tiny_init<Var> vars );

		ScopeVars( ImGuiStyleVar label, const ImVec2& value );

		~ScopeVars( );

		tiny_inline void Push( const Var& var );

		void Push( tiny_init<Var> vars );

		tiny_inline void Push( ImGuiStyleVar label, const ImVec2& value );

		tiny_inline void Pop( );

		void Pop( tiny_int count );

	};

};
