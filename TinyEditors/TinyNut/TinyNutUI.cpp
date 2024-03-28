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
 * @creation : 28/03/2024
 * @version  : 2024.2.7
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include "TinyNut.h"

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace TinyNutUI {

	ImRect GetItemRect( ) { return { ImGui::GetItemRectMin( ), ImGui::GetItemRectMax( ) }; }

	ImRect RectExpanded( const ImRect& rect, float x, float y ) {
		auto result = rect;
		
		result.Min.x -= x;
		result.Min.y -= y;
		result.Max.x += x;
		result.Max.y += y;

		return result;
	}

	ImRect RectOffset( const ImRect& rect, float x, float y ) {
		auto result = rect;
		
		result.Min.x += x;
		result.Min.y += y;
		result.Max.x += x;
		result.Max.y += y;

		return result;
	}

	ImRect RectOffset( const ImRect& rect, ImVec2 xy ) {
		return RectOffset( rect, xy.x, xy.y );
	}

	bool BeginMenubar( const ImRect& barRectangle ) {
		auto* window = ImGui::GetCurrentWindow( );

		if ( window->SkipItems )
			return false;

		IM_ASSERT( !window->DC.MenuBarAppending );
		ImGui::BeginGroup( );
		ImGui::PushID( "##menubar" );

		auto padding   = window->WindowPadding;
		auto bar_rect  = RectOffset( barRectangle, 0.f, padding.y );
		auto clip_rect = ImRect{
			IM_ROUND( ImMax( window->Pos.x, bar_rect.Min.x + window->WindowBorderSize + window->Pos.x - 10.f ) ),
			IM_ROUND( bar_rect.Min.y + window->WindowBorderSize + window->Pos.y ),
			IM_ROUND( ImMax( bar_rect.Min.x + window->Pos.x, bar_rect.Max.x - ImMax( window->WindowRounding, window->WindowBorderSize ) ) ),
			IM_ROUND( bar_rect.Max.y + window->Pos.y )
		};

		clip_rect.ClipWith( window->OuterRectClipped );

		ImGui::PushClipRect( clip_rect.Min, clip_rect.Max, false );

		window->DC.CursorMaxPos		= ImVec2{ bar_rect.Min.x + window->Pos.x, bar_rect.Min.y + window->Pos.y };
		window->DC.CursorPos		= window->DC.CursorMaxPos;
		window->DC.LayoutType		= ImGuiLayoutType_Horizontal;
		window->DC.NavLayerCurrent  = ImGuiNavLayer_Menu;
		window->DC.MenuBarAppending = true;
		
		ImGui::AlignTextToFramePadding( );

		return true;
	}

	void EndMenubar( ) {
		auto* window = ImGui::GetCurrentWindow( );
		auto& g		 = tiny_lvalue( GImGui );

		if ( window->SkipItems )
			return;

		if ( ImGui::NavMoveRequestButNoResultYet( ) && ( g.NavMoveDir == ImGuiDir_Left || g.NavMoveDir == ImGuiDir_Right ) && ( g.NavWindow->Flags & ImGuiWindowFlags_ChildMenu ) ) {
			auto* nav_earliest_child = g.NavWindow;
			
			while ( nav_earliest_child->ParentWindow && ( nav_earliest_child->ParentWindow->Flags & ImGuiWindowFlags_ChildMenu ) )
				nav_earliest_child = nav_earliest_child->ParentWindow;
			
			if ( nav_earliest_child->ParentWindow == window && nav_earliest_child->DC.ParentLayoutType == ImGuiLayoutType_Horizontal && ( g.NavMoveFlags & ImGuiNavMoveFlags_Forwarded ) == 0 ) {
				const ImGuiNavLayer layer = ImGuiNavLayer_Menu;
				
				IM_ASSERT( window->DC.NavLayersActiveMaskNext & ( 1 << layer ) );
				
				ImGui::FocusWindow( window );
				ImGui::SetNavID( window->NavLastIds[ layer ], layer, 0, window->NavRectRel[ layer ] );
				
				g.NavDisableHighlight  = true;
				g.NavMousePosDirty	   = true;
				g.NavDisableMouseHover = g.NavMousePosDirty;
				
				ImGui::NavMoveRequestForward( g.NavMoveDir, g.NavMoveClipDir, g.NavMoveFlags, g.NavMoveScrollFlags );
			}
		}

		IM_MSVC_WARNING_SUPPRESS( 6011 );
		IM_ASSERT( window->DC.MenuBarAppending );

		ImGui::PopClipRect( );
		ImGui::PopID( );

		window->DC.MenuBarOffset.x = window->DC.CursorPos.x - window->Pos.x;
		
		g.GroupStack.back( ).EmitItem = false;
		
		ImGui::EndGroup( );
		
		window->DC.LayoutType		= ImGuiLayoutType_Vertical;
		window->DC.NavLayerCurrent  = ImGuiNavLayer_Main;
		window->DC.MenuBarAppending = false;
	}

};