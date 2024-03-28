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
 * @creation : 02/02/2024
 * @version  : 2024.1.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyToolboxImGuiTheme.h"

tiny_enum( TinyGuizmoModes ) { 

	TG_MODE_LOCAL = ImGuizmo::LOCAL,
	TG_MODE_WORLD = ImGuizmo::WORLD

};

tiny_enum( TinyGuizmoTools ) { 

	TGT_TRANSLATE_X  = ImGuizmo::TRANSLATE_X,
	TGT_TRANSLATE_Y  = ImGuizmo::TRANSLATE_Y,
	TGT_TRANSLATE_2D = TGT_TRANSLATE_X | TGT_TRANSLATE_Y,

	TGT_ROTATE_2D = ImGuizmo::ROTATE_Z,
	
	TGT_SCALE_X  = ImGuizmo::SCALE_X,
	TGT_SCALE_Y  = ImGuizmo::SCALE_Y,
	TGT_SCALE_2D = TGT_SCALE_X | TGT_SCALE_Y,

};

te_class TinyToolboxGuizmo final { 

private:
	tiny_hash				   _selection;
	bool					   _is_orthographic;
	bool					   _use_snap;
	tiny_uint				   _mode;
	tiny_uint				   _tool;
	tiny_vec3				   _snap_translate;
	tiny_vec3				   _snap_rotate;
	tiny_vec3				   _snap_scale;
	TinyImGui::DropdownContext _modes;
	TinyImGui::DropdownContext _tools;

public:
	TinyToolboxGuizmo( );

	~TinyToolboxGuizmo( ) = default;

	void SetGuizmoMode( TinyGuizmoModes mode );

	void SetGuizmoTool( TinyGuizmoTools tool );

	void SetGuizmo( TinyGuizmoModes mode, TinyGuizmoTools tool );

	void Show( const tiny_hash entity_hash, bool is_orthographic );

	void Hide( );

	void DrawWidget( );

	void DrawUI( TinyGame* game );

private:
	void ApplyManipulation( TinyTransform2D* transform, tiny_mat4& matrix );

public:
	const tiny_hash GetSelection( ) const;

	TinyGuizmoModes GetMode( ) const;

	TinyGuizmoTools GetTool( ) const;

	tiny_vec3& GetSnapTranslate( );

	tiny_vec3& GetSnapRotate( );

	tiny_vec3& GetSnapScale( );

private:
	tiny_uint PeekTool( tiny_uint selection );

	float* PeekSnapTarget( );

	TinyMath::GrabSignature PeekGrabSignature( );

};
