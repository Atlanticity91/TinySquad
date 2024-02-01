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

#pragma once

#include <TinyEngine/Tools/Categories/TinyToolManager.h>

#define TinyGuizmoTranslate2D ( ImGuizmo::OPERATION::TRANSLATE_X |ImGuizmo::OPERATION::TRANSLATE_Y )
#define TinyGuizmoRotate2D ( ImGuizmo::OPERATION::ROTATE_Z )
#define TinyGuizmoScale2D ( ImGuizmo::OPERATION::SCALE_X | ImGuizmo::OPERATION::SCALE_Y )

te_struct TinyToolGuizmo {

	bool Show;
	bool UseSnap;
	ImGuizmo::MODE Mode;
	ImGuizmo::OPERATION Tool;
	tiny_vec3 SnapTranslate;
	tiny_vec3 SnapRotate;
	tiny_vec3 SnapScale;

};

te_class TinyToolCommon final : tiny_inherit( TinyToolCategory ) { 

private:
	TinyToolGuizmo			   _guizmo;
	TinyImGui::DropdownContext _modes;
	TinyImGui::DropdownContext _tools;

public:
	TinyToolCommon( );

	~TinyToolCommon( ) = default;

	void SetGuizmoMode( ImGuizmo::MODE mode );

	void SetGuizmoTool( ImGuizmo::OPERATION tool );

	void SetGuizmo( ImGuizmo::MODE mode, ImGuizmo::OPERATION tool );

protected:
	tiny_implement( void OnTick( 
		TinyGame* game,
		TinyEngine& engine,
		TinyToolbox& toolbox 
	) );

private:
	void DrawHardware( TinyGraphicManager& graphics );

	void DrawBoundaries( TinyGraphicManager& graphics );

	void DrawSwapchain( TinyGraphicManager& graphics );

	void DrawPasses( TinyGraphicManager& graphics );

public:
	TinyToolGuizmo& GetGuizmo( );

};
