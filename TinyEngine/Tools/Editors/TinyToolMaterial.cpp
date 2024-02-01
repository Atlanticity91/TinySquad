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
 * @creation : 23/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolMaterial::TinyToolMaterial( )
	: TinyToolAssetEditor{ "Material" },
	_material{ nullptr }
{ }

void TinyToolMaterial::Save( TinyGame* game ) {
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PROTECTED ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyToolMaterial::OnOpen( TinyGame* game, const tiny_string& name, c_pointer asset ) {
	_material = tiny_cast( asset, TinyMaterial* );

	return _material;
}

void TinyToolMaterial::OnTick( TinyGame* game, TinyAssetManager& assets ) {
	TinyImGui::BeginVars( );
	
	DrawGenerals( );
	
	TinyImGui::EndVars( );

	if ( ImGui::CollapsingHeader( "Dynamic States" ) ) {
		TinyImGui::BeginVars( );

		DrawDynamics( );

		TinyImGui::EndVars( );
	}

	if ( ImGui::CollapsingHeader( "Inputs" ) ) {
		TinyImGui::BeginVars( );

		DrawInputs( );

		TinyImGui::EndVars( );
	}

	if ( ImGui::CollapsingHeader( "Color Blends" ) ) {
		TinyImGui::BeginVars( );

		DrawColorBlends( );

		TinyImGui::EndVars( );
	}

	if ( ImGui::CollapsingHeader( "Depth/Stencil" ) ) {
		TinyImGui::BeginVars( );

		DrawDepthStencil( );

		TinyImGui::EndVars( );
	}

	if ( ImGui::CollapsingHeader( "Descriptors" ) ) {
		TinyImGui::BeginVars( );

		DrawDescriptors( );

		TinyImGui::EndVars( );
	}

	if ( ImGui::CollapsingHeader( "Constants" ) ) {
		TinyImGui::BeginVars( );

		DrawConstants( );

		TinyImGui::EndVars( );
	}

	if ( ImGui::CollapsingHeader( "Shaders" ) ) {
		TinyImGui::BeginVars( );

		DrawShaders( );

		TinyImGui::EndVars( );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolMaterial::DrawGenerals( ) {
	//TinyImGui::Dropdown( "Type", );
	//TinyImGui::InputText( "Pass Name",  );
	//TinyImGui::Dropdown( "Pass Type", );
	//TinyImGui::InputScalar( "Pass Index", );
	//TinyImGui::InputVulkan( "Topology", );
	//TinyImGui::InputScalar( "Tessellation", );
}

void TinyToolMaterial::DrawDynamics( ) {
}

void TinyToolMaterial::DrawInputs( ) {
}

void TinyToolMaterial::DrawColorBlends( ) {
}

void TinyToolMaterial::DrawDepthStencil( ) {
	//TinyImGui::Checkbox( "Depth", );
	//TinyImGui::Checkbox( "Stencil", );
	//TinyImGui::InputVulkan( "Operation", );
	//TinyImGui::InputVulkan( "Front", );
	//TinyImGui::InputVulkan( "Back", );
}

void TinyToolMaterial::DrawDescriptors( ) {
}

void TinyToolMaterial::DrawConstants( ) {
}

void TinyToolMaterial::DrawShaders( ) {
	if ( 0 < TGP_TYPE_COMPUTE ) {
			//TinyImGui::Dropdown( "Vertex", );
			//TinyImGui::Dropdown( "Fragment", );
			//TinyImGui::Dropdown( "Geometry", );
	} else {
		//TinyImGui::Dropdown( "Compute", );
	}
}
