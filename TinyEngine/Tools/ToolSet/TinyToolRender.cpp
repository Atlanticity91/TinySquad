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
 * @creation : 19/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolRender::TinyToolRender( ) 
	: TinyToolCategory{ "Render" }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolRender::OnTick(
	TinyGame* game,
	TinyEngine& engine,
	TinyToolbox& toolbox
) {
	TinyImGui::BeginVars( );

	TinyImGui::InputScalar( "Pixelization", 0 );
	TinyImGui::InputScalar( "Sharpen", 0.f );
	TinyImGui::InputScalar( "Min Depth of Field", 0.f );
	TinyImGui::InputScalar( "Max Depth of Field", 0.f );
	TinyImGui::InputScalar( "Chromatic Aberration", 0.f ); // Vec3
	TinyImGui::InputScalar( "Bloom Factor", 0.f );
	TinyImGui::InputScalar( "Grain", 0.f );
	TinyImGui::InputScalar( "LUT", 0.f );
	TinyImGui::InputScalar( "Gamma", 2.2f );

	TinyImGui::EndVars( );

	TinyImGui::Collapsing( 
		"Outlines", 
		[ & ]( ) { 
			TinyImGui::BeginVars( );

			TinyImGui::InputScalar( "Min Separation", 0.f );
			TinyImGui::InputScalar( "Max Separation", 0.f );
			TinyImGui::InputScalar( "Min Distance", 0.f );
			TinyImGui::InputScalar( "Max Distance", 0.f );
			TinyImGui::InputScalar( "Size", 0.f );
			TinyImGui::InputScalar( "Color", 0.f );

			TinyImGui::EndVars( );
		} 
	);
}
