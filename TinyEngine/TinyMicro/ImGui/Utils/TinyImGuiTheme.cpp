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

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyImGuiTheme::TinyImGuiTheme( ) 
{ }

void TinyImGuiTheme::Initialize( ) {
    ImGui::StyleColorsDark( );

    auto& style  = ImGui::GetStyle( );
    auto* colors = style.Colors;

    style.FramePadding    = FramePadding;
    style.FrameRounding   = FrameRounding;
    style.FrameBorderSize = FrameRounding;
    style.IndentSpacing   = IndentSpacing;

    colors[ ImGuiCol_Text                  ] = Text;
    colors[ ImGuiCol_TextDisabled          ] = TextDarker;
    colors[ ImGuiCol_WindowBg              ] = Background;
    colors[ ImGuiCol_ChildBg               ] = Background;
    colors[ ImGuiCol_PopupBg               ] = BackgroundPopup;
    colors[ ImGuiCol_Border                ] = BackgroundDark;
    colors[ ImGuiCol_BorderShadow          ] = Dark;
    colors[ ImGuiCol_FrameBg               ] = PropertyField;
    colors[ ImGuiCol_FrameBgHovered        ] = PropertyField;
    colors[ ImGuiCol_FrameBgActive         ] = PropertyField;
    colors[ ImGuiCol_TitleBg               ] = Titlebar;
    colors[ ImGuiCol_TitleBgActive         ] = Titlebar;
    colors[ ImGuiCol_TitleBgCollapsed      ] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ ImGuiCol_MenuBarBg             ] = ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f };
    colors[ ImGuiCol_ScrollbarBg           ] = ImVec4{ 0.02f, 0.02f, 0.02f, 0.53f };
    colors[ ImGuiCol_ScrollbarGrab         ] = ImVec4{ 0.31f, 0.31f, 0.31f, 1.0f };
    colors[ ImGuiCol_ScrollbarGrabHovered  ] = HoverPurple;
    colors[ ImGuiCol_ScrollbarGrabActive   ]  = ActivePurple;
    colors[ ImGuiCol_CheckMark             ] = ActivePurple;
    colors[ ImGuiCol_SliderGrab            ] = ImVec4{ 0.51f, 0.51f, 0.51f, 0.7f };
    colors[ ImGuiCol_SliderGrabActive      ] = ActivePurple;
    colors[ ImGuiCol_Button                ] = ImColor{ 56, 56, 56, 200 };
    colors[ ImGuiCol_ButtonHovered         ] = HoverPurple;
    colors[ ImGuiCol_ButtonActive          ] = ActivePurple;
    colors[ ImGuiCol_Header                ] = GroupHeader;
    colors[ ImGuiCol_HeaderHovered         ] = HoverPurple;
    colors[ ImGuiCol_HeaderActive          ] = ActivePurple;
    colors[ ImGuiCol_Separator             ] = BackgroundDark;
    colors[ ImGuiCol_SeparatorHovered      ] = HoverPurple;
    colors[ ImGuiCol_SeparatorActive       ] = Highlight;
    colors[ ImGuiCol_ResizeGrip            ] = ImVec4{ 0.91f, 0.91f, 0.91f, 0.25f };
    colors[ ImGuiCol_ResizeGripHovered     ] = ImVec4{ 0.81f, 0.81f, 0.81f, 0.67f };
    colors[ ImGuiCol_ResizeGripActive      ] = ImVec4{ 0.46f, 0.46f, 0.46f, 0.95f };
    colors[ ImGuiCol_Tab                   ] = Titlebar;
    colors[ ImGuiCol_TabHovered            ] = HoverPurple;
    colors[ ImGuiCol_TabActive             ] = ActivePurple;
    colors[ ImGuiCol_TabUnfocused          ] = Titlebar;
    colors[ ImGuiCol_TabUnfocusedActive    ] = HoverPurple;
    colors[ ImGuiCol_DockingPreview        ] = HoverPurple;
    colors[ ImGuiCol_DockingEmptyBg        ] = Background;
    colors[ ImGuiCol_PlotLines             ] = ActivePurple;
    colors[ ImGuiCol_PlotLinesHovered      ] = HoverPurple;
    colors[ ImGuiCol_PlotHistogram         ] = ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
    colors[ ImGuiCol_PlotHistogramHovered  ] = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
    colors[ ImGuiCol_TableHeaderBg         ] = GroupHeader;
    colors[ ImGuiCol_TableBorderStrong     ] = ImVec4( 0.31f, 0.31f, 0.35f, 1.00f );
    colors[ ImGuiCol_TableBorderLight      ] = BackgroundDark;
    colors[ ImGuiCol_TableRowBg            ] = Dark;
    colors[ ImGuiCol_TableRowBgAlt         ] = ImVec4( 1.00f, 1.00f, 1.00f, 0.07f );
    colors[ ImGuiCol_TextSelectedBg        ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.35f );
    colors[ ImGuiCol_DragDropTarget        ] = ImVec4( 1.00f, 1.00f, 0.00f, 0.90f );
    colors[ ImGuiCol_NavHighlight          ] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
    colors[ ImGuiCol_NavWindowingHighlight ] = ImVec4( 1.00f, 1.00f, 1.00f, 0.70f );
    colors[ ImGuiCol_NavWindowingDimBg     ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.20f );
    colors[ ImGuiCol_ModalWindowDimBg      ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.35f );
}

TinyImGuiTheme& TinyImGuiTheme::Set( ImGuiStyleVar variable, const float value ) {
    auto& style = ImGui::GetStyle( );
    
    switch ( variable ) {
        case ImGuiStyleVar_Alpha                   : style.Alpha                   = value; break;
        case ImGuiStyleVar_WindowRounding          : style.WindowRounding          = value; break;
        case ImGuiStyleVar_WindowBorderSize        : style.WindowBorderSize        = value;  break;
        case ImGuiStyleVar_ChildRounding           : style.ChildRounding           = value; break;
        case ImGuiStyleVar_ChildBorderSize         : style.ChildBorderSize         = value; break;
        case ImGuiStyleVar_PopupRounding           : style.PopupRounding           = value; break;
        case ImGuiStyleVar_PopupBorderSize         : style.PopupBorderSize         = value; break;
        case ImGuiStyleVar_FrameRounding           : style.FrameRounding           = value; break;
        case ImGuiStyleVar_FrameBorderSize         : style.FrameBorderSize         = value; break;
        case ImGuiStyleVar_IndentSpacing           : style.IndentSpacing           = value; break;
        case ImGuiStyleVar_ScrollbarSize           : style.ScrollbarSize           = value; break;
        case ImGuiStyleVar_ScrollbarRounding       : style.ScrollbarRounding       = value; break;
        case ImGuiStyleVar_GrabMinSize             : style.GrabMinSize             = value; break;
        case ImGuiStyleVar_GrabRounding            : style.GrabRounding            = value; break;
        case ImGuiStyleVar_TabRounding             : style.TabRounding             = value; break;
        case ImGuiStyleVar_TabBarBorderSize        : style.TabBarBorderSize        = value; break;
        case ImGuiStyleVar_SeparatorTextBorderSize : style.SeparatorTextBorderSize = value; break;
        case ImGuiStyleVar_DockingSeparatorSize    : style.DockingSeparatorSize    = value; break;

        default : break;
    }

    return tiny_self;
}

TinyImGuiTheme& TinyImGuiTheme::Set( ImGuiStyleVar variable, const ImVec2& value ) {
    auto& style = ImGui::GetStyle( );

    switch ( variable ) {
        case ImGuiStyleVar_WindowPadding        : style.WindowPadding        = value; break;
        case ImGuiStyleVar_WindowMinSize        : style.WindowMinSize        = value; break;
        case ImGuiStyleVar_WindowTitleAlign     : style.WindowTitleAlign     = value; break;
        case ImGuiStyleVar_FramePadding         : style.FramePadding         = value; break;
        case ImGuiStyleVar_ItemSpacing          : style.ItemSpacing          = value; break;
        case ImGuiStyleVar_ItemInnerSpacing     : style.ItemInnerSpacing     = value; break;
        case ImGuiStyleVar_CellPadding          : style.CellPadding          = value; break;
        case ImGuiStyleVar_ButtonTextAlign      : style.ButtonTextAlign      = value; break;
        case ImGuiStyleVar_SelectableTextAlign  : style.SelectableTextAlign  = value; break;
        case ImGuiStyleVar_SeparatorTextAlign   : style.SeparatorTextAlign   = value; break;
        case ImGuiStyleVar_SeparatorTextPadding : style.SeparatorTextPadding = value; break;

        default : break;
    }

    return tiny_self;
}

TinyImGuiTheme& TinyImGuiTheme::Set( ImGuiCol color, const ImVec4& value ) {
    GetColor( color ) = value;

    return tiny_self;
}

TinyImGuiTheme& TinyImGuiTheme::Reset( ) {
    Initialize( );

    return tiny_self;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
ImVec4& TinyImGuiTheme::GetColor( ImGuiCol color ) const { 
    auto& style = ImGui::GetStyle( );

    return style.Colors[ color ];
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
ImVec4& TinyImGuiTheme::operator[]( ImGuiCol color ) { return GetColor( color ); }
