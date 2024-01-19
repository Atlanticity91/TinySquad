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

tiny_enum( TinyToolboxWidgetGuizmoModes ) {

	TTWG_MODE_LOCAL = 0,
		TTWG_MODE_WORLD

};

tiny_enum( TinyToolboxWidgetGuizmoTools ) {

	TTWG_TOOL_TRANSLATE_2D = 0,
	TTWG_TOOL_ROTATE_2D,
	TTWG_TOOL_SCALE_2D,

	TTWG_TOOL_TRANSLATE_3D,
	TTWG_TOOL_ROTATE_3D,
	TTWG_TOOL_SCALE_3D,

};

te_class TinyToolCommon final : tiny_inherit( TinyToolCategory ) { 

private:
	bool						 _show_guizmo;
	bool						 _use_snap;
	TinyToolboxWidgetGuizmoModes _mode;
	TinyToolboxWidgetGuizmoTools _tool;
	tiny_vec3					 _snap_translate;
	tiny_vec3					 _snap_rotate;
	tiny_vec3					 _snap_scale;
	TinyImGui::DropdownContext	 _modes;
	TinyImGui::DropdownContext	 _tools;

public:
	TinyToolCommon( );

	~TinyToolCommon( ) = default;

	void SetGuizmoMode( TinyToolboxWidgetGuizmoModes mode );

	void SetGuizmoTool( TinyToolboxWidgetGuizmoTools tool );

	void SetGuizmo( TinyToolboxWidgetGuizmoModes mode, TinyToolboxWidgetGuizmoTools tool );

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

};
