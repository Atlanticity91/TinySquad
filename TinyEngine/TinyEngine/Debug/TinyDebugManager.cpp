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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyDebugManager::TinyDebugManager( ) 
	: m_imgui{ }
{
	m_imgui.ShowExemples( );
}

bool TinyDebugManager::Initialize(
	TinyWindow& window,
	TinyGraphicManager& graphics,
	TinyGame* game
) {
	auto specification = TinyImGuiSpecification{ TINY_OUTPASS_NAME, 1, 512 };
	auto state		   = m_imgui.Initialize( window, graphics, specification, game );

	if ( state ) {
		m_imgui.Create<TinyImGuizmo>( game );
		m_imgui.Create<TinyDebugTabManager>( game );
	}

	return state;
}

void TinyDebugManager::Tick(
	TinyGraphicManager& graphics,
	TinyInputManager& inputs,
	TinyGame* game
) {
	if ( inputs.Evaluate( "Show Dev", true ) )
		m_imgui.Toggle( );

	m_imgui.Tick( graphics, inputs, game );
}

void TinyDebugManager::Terminate( TinyGraphicManager& graphics, TinyGame* game ) {
	m_imgui.Terminate( graphics, game );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyImGuiManager& TinyDebugManager::GetImGui( ) { return m_imgui; }

TinyImGuizmo& TinyDebugManager::GetGuizmo( ) {
	return tiny_lvalue( m_imgui.GetWindowAs<TinyImGuizmo>( 0 ) );
}
