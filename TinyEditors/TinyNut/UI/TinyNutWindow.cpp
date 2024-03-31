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

#include <TinyNut/__tiny_nut_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNutWindow::TinyNutWindow( const tiny_string& name )
	: _name{ name },
	_icons{ }
{ }

void TinyNutWindow::Create( TinyNut* nut_game ) {
	_RegisterIcon( nut_game, "Logo"	   , g_WindowMinimizeIcon, []( auto* ) { }		   );
	_RegisterIcon( nut_game, "Minimize", g_WindowMinimizeIcon, TinyNutWindow::Minimize );
	_RegisterIcon( nut_game, "Restore" , g_WindowRestoreIcon , TinyNutWindow::Restore  );
	_RegisterIcon( nut_game, "Maximize", g_WindowMaximizeIcon, TinyNutWindow::Maximize );
	_RegisterIcon( nut_game, "Close"   , g_WindowCloseIcon	 , TinyNutWindow::Close    );
}

void TinyNutWindow::RegisterIcon(
	TinyNut* nut_game,
	const tiny_string& name,
	tiny_uint length, 
	const tiny_ubyte* image,
	const Icon_t::Callback_t& callback
) {
	if ( !name.is_empty( ) && !_icons.find( name ) ) {
		auto icon_ = TinyNutUI::CreateImage( nut_game, length, image );

		_icons.emplace( name, { icon_, callback } );
	}
}

void TinyNutWindow::Tick( TinyNut* nut_game ) {
	auto& window = nut_game->GetWindow( );

	ImGui::SetCurrentContext( nut_game->GetToolbox( ).GetContext( ) );

	if ( Prepare( nut_game, window ) ) {
		DockSpace( );

		nut_game->TickUI( );
	}

	ImGui::End( );
}

void  TinyNutWindow::Terminate( TinyNut* nut_game ) {
	for ( auto& icon : _icons )
		TinyNutUI::DeleteImage( nut_game, icon.Data.Icon );
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyNutWindow::DrawBorder( ) {
	auto window		 = ImGui::GetCurrentWindow( );
	auto* draw_list  = window->DrawList;
	auto rounding	 = window->WindowRounding;
	auto border_size = 1.f; // window->WindowBorderSize;
	auto& style		 = ImGui::GetStyle( );

	struct ImGuiResizeBorderDef {
		ImVec2 InnerDir;
		ImVec2 SegmentN1; 
		ImVec2 SegmentN2;
		float  OuterAngle;
	};

	static const ImGuiResizeBorderDef resize_border_def[ 4 ] = {
		{ {  1.f,  0.f }, { 0.f, 1.f }, { 0.f, 0.f }, IM_PI * 1.00f }, // Left
		{ { -1.f,  0.f }, { 1.f, 0.f }, { 1.f, 1.f }, IM_PI * 0.00f }, // Right
		{ {  0.f,  1.f }, { 0.f, 0.f }, { 1.f, 0.f }, IM_PI * 1.50f }, // Up
		{ {  0.f, -1.f }, { 1.f, 1.f }, { 0.f, 1.f }, IM_PI * 0.50f }  // Down
	};

	auto GetResizeBorderRect = []( ImGuiWindow* window, int border_n, float perp_padding, float thickness ) {
		auto rect = window->Rect( );
		
		if ( thickness == 0.0f ) {
			rect.Max.x -= 1;
			rect.Max.y -= 1;
		}

		if ( border_n == ImGuiDir_Left  ) { return ImRect{ rect.Min.x - thickness   , rect.Min.y + perp_padding, rect.Min.x + thickness   , rect.Max.y - perp_padding }; }
		if ( border_n == ImGuiDir_Right ) { return ImRect{ rect.Max.x - thickness   , rect.Min.y + perp_padding, rect.Max.x + thickness   , rect.Max.y - perp_padding }; }
		if ( border_n == ImGuiDir_Up    ) { return ImRect{ rect.Min.x + perp_padding, rect.Min.y - thickness   , rect.Max.x - perp_padding, rect.Min.y + thickness    }; }
		if ( border_n == ImGuiDir_Down  ) { return ImRect{ rect.Min.x + perp_padding, rect.Max.y - thickness   , rect.Max.x - perp_padding, rect.Max.y + thickness    }; }
			
		IM_ASSERT( 0 );

		return ImRect{ };
	};

	if ( border_size > 0.f && !( window->Flags & ImGuiWindowFlags_NoBackground ) )
		draw_list->AddRect( window->Pos, { window->Pos.x + window->Size.x,  window->Pos.y + window->Size.y }, ImGui::GetColorU32( ImGuiCol_Border ), rounding, 0, border_size );

	int border_held = window->ResizeBorderHeld;

	if ( border_held != -1 ) {
		const ImGuiResizeBorderDef& def = resize_border_def[ border_held ];

		auto border_r = GetResizeBorderRect( window, border_held, rounding, 0.f );
		auto offset_x = def.InnerDir.x * rounding;
		auto offset_y = def.InnerDir.y * rounding;
		auto p1		  = ImLerp( border_r.Min, border_r.Max, def.SegmentN1 );
		auto p2		  = ImLerp( border_r.Min, border_r.Max, def.SegmentN2 );

		p1.x += 0.5f + offset_x;
		p1.y += 0.5f + offset_y;

		p2.x += 0.5f + offset_x;
		p2.y += 0.5f + offset_y;

		draw_list->PathArcTo( p1, rounding, def.OuterAngle - IM_PI * 0.25f, def.OuterAngle );
		draw_list->PathArcTo( p2, rounding, def.OuterAngle, def.OuterAngle + IM_PI * 0.25f );
		draw_list->PathStroke( ImGui::GetColorU32( ImGuiCol_SeparatorActive ), 0, ImMax( 2.0f, border_size ) );
	}

	if ( style.FrameBorderSize > 0 && !( window->Flags & ImGuiWindowFlags_NoTitleBar ) && !window->DockIsActive ) {
		auto y = window->Pos.y + window->TitleBarHeight( ) - 1;

		draw_list->AddLine( { window->Pos.x + border_size, y }, { window->Pos.x + window->Size.x - border_size, y }, ImGui::GetColorU32( ImGuiCol_Border ), style.FrameBorderSize );
	}
}

void TinyNutWindow::DrawTitlebarBorder(
	float height, 
	const ImVec2& padding,
	const ImVec2& cursor
) {
	ImGui::SetCursorPos( cursor );
	
	auto* draw_list = ImGui::GetBackgroundDrawList( );
	auto title_min	= ImGui::GetCursorScreenPos( );
	auto title_max  = ImVec2{
		title_min.x + ImGui::GetWindowWidth( ) - padding.y * 2.0f,
		title_min.y + height
	};

	draw_list->AddRectFilled( title_min, title_max, TinyImGui::Theme::Titlebar );
}

void TinyNutWindow::DrawTitlebarLogo( bool is_maximized, const ImVec2& padding ) {
	auto* draw_list = ImGui::GetForegroundDrawList( );
	auto logo_size  = 48.f;
	auto offset		= ImVec2{
		16.f + padding.x,
		 5.f + padding.y + is_maximized ? -6.f : 0.f
	};
	auto logo_min	= ImVec2{ 
		ImGui::GetItemRectMin( ).x + offset.x,
		ImGui::GetItemRectMin( ).y + offset.y
	};
	auto logo_max	= ImVec2{ logo_min.x + logo_size, logo_min.y + logo_size };

	draw_list->AddRectFilled( logo_min, logo_max, TinyImGui::Theme::ActivePurple );
	draw_list->AddImage( _icons[ "Logo" ].Icon.Descriptor, logo_min, logo_max );
}

void TinyNutWindow::DrawTitlebarText( const ImVec2& padding ) {
	auto* name_str = _name.as_chars( );
	auto cursor = ImGui::GetCursorPos( );
	auto size = ImGui::CalcTextSize( name_str );

	ImGui::SetCursorPos( { ImGui::GetWindowWidth( ) * 0.5f - size.x * 0.5f, 8.0f + padding.y } );
	ImGui::Text( "%s", name_str );
	ImGui::SetCursorPos( cursor );
}

void TinyNutWindow::DrawTitlebarIcon(
	TinyNut* nut_game,
	const ImVec2& offset, 
	const ImVec2& padding,
	const tiny_string& name
) {
	auto* name_str = name.as_chars( );
	auto col_n	   = TinyImGui::ColorWithMultipliedValue( TinyImGui::Theme::Text,  .9f );
	auto col_h	   = TinyImGui::ColorWithMultipliedValue( TinyImGui::Theme::Text, 1.2f );
	auto col_p	   = TinyImGui::Theme::TextDarker;
	auto& icon	   = _icons[ name ];
	auto size	   = ImVec2{ 14.f, 14.f };

	//ImGui::Spring( offset );

	//TinyImGui::ShiftCursorY( 8.f );
	
	if ( ImGui::InvisibleButton( name_str, size ) ) 
		std::invoke( icon.Callback, nut_game );

	auto* draw_list = ImGui::GetCurrentWindow( )->DrawList;

	auto bound_min = ImGui::GetItemRectMin( );
	auto bound_max = ImGui::GetItemRectMax( );

	TinyNutUI::ButtonImage( icon.Icon, col_n, col_h, col_p );
}

void TinyNutWindow::DrawTitlebar( TinyNut* nut_game, bool is_maximized ) {
	auto padding = ImGui::GetCurrentWindow( )->WindowPadding;
	auto height  = 58.f;
	auto cursor  = ImVec2{ padding.x, padding.y + is_maximized ? -6.f : 0.f };

	DrawTitlebarLogo( is_maximized, padding );
	DrawTitlebarBorder( height, padding, cursor );

	ImGui::BeginHorizontal( "Titlebar", { ImGui::GetWindowWidth( ) - padding.y * 2.0f, ImGui::GetFrameHeightWithSpacing( ) } );

	auto width = ImGui::GetContentRegionAvail( ).x;

	ImGui::SetCursorPos( cursor );
	ImGui::InvisibleButton( "##__TinyTitleDragZone", { width - 94.f, height } );

	auto is_overed = ImGui::IsItemHovered( );

	if ( is_maximized ) {
		auto mouse_y = ImGui::GetMousePos( ).y - ImGui::GetCursorScreenPos( ).y;
		
		if ( mouse_y >= 0.f && mouse_y <= 5.f )
			is_overed = true;
	}

	DrawMenubar( nut_game, is_maximized, is_overed );

	DrawTitlebarText( padding );
	DrawTitlebarIcon( nut_game, {  0.f,  0.f }, padding, "Minimize" );
	DrawTitlebarIcon( nut_game, { -1.f, 17.f }, padding, is_maximized ? "Restore" : "Maximize" );
	DrawTitlebarIcon( nut_game, { -1.f, 15.f }, padding, "Close" );

	ImGui::Spring( -1.f, 18.f );
	ImGui::EndHorizontal( );
	ImGui::SetCursorPosY( height );
}

void TinyNutWindow::DrawMenubar( TinyNut* nut_game, bool is_maximized, bool& is_overed ) {
	auto padding  = ImGui::GetCurrentWindow( )->WindowPadding;
	auto offset_x = 80.f + padding.x;

	ImGui::SuspendLayout( );
	ImGui::SetItemAllowOverlap( );
	ImGui::SetCursorPos( { offset_x, is_maximized ? 0.f : 6.f } );
	ImGui::BeginGroup( );

	auto bounding = ImRect{
		ImGui::GetCursorPos( ),
		{
			ImGui::GetContentRegionAvail( ).x + ImGui::GetCursorScreenPos( ).x,
			ImGui::GetFrameHeightWithSpacing( )
		}
	};

	if ( TinyNutUI::BeginMenubar( bounding ) )
		nut_game->TickMenubar( );

	TinyNutUI::EndMenubar( );

	ImGui::EndGroup( );

	if ( ImGui::IsItemHovered( ) )
		is_overed = false;

	ImGui::ResumeLayout( );
}

bool TinyNutWindow::Prepare( TinyNut* nut_game, TinyWindow& window ) {
	auto window_flags = tiny_cast(
		ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse			  |
		ImGuiWindowFlags_NoResize  | ImGuiWindowFlags_NoMove	 | ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus,
		ImGuiWindowFlags
	);
	auto is_maximized = window.GetIsMaximized( );
	auto* name_str	  = _name.as_chars( );
	auto* viewport	  = ImGui::GetMainViewport( );

	ImGui::SetNextWindowPos( viewport->Pos );
	ImGui::SetNextWindowSize( viewport->Size );
	ImGui::SetNextWindowViewport( viewport->ID );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.f );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.f );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, is_maximized ? ImVec2{ 6.f, 6.f } : ImVec2{ 1.f, 1.f } );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 3.f );

	ImGui::PushStyleColor( ImGuiCol_MenuBarBg, { 0.f, 0.f, 0.f, 0.f } );

	auto state = ImGui::Begin( name_str, nullptr, window_flags );

	if ( state ) {
		ImGui::PopStyleColor( );
		ImGui::PopStyleVar( 2 );

		if ( !is_maximized )
			DrawBorder( );

		DrawTitlebar( nut_game, is_maximized );
	}

	ImGui::PopStyleVar( 2 );

	return state;
}

void TinyNutWindow::DockSpace( ) {
	auto dockspace_id = ImGui::GetID( "TinyNutDockspace" );
	auto& style		  = ImGui::GetStyle( );
	auto size_x		  = style.WindowMinSize.x;

	style.WindowMinSize.x = 370.f;

	ImGui::DockSpace( dockspace_id );

	style.WindowMinSize.x = size_x;
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PRIVATE STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyNutWindow::Minimize( TinyNut* nut_game ) { nut_game->Minimize( ); }

void TinyNutWindow::Restore( TinyNut* nut_game ) { nut_game->Restore( ); }

void TinyNutWindow::Maximize( TinyNut* nut_game ) { nut_game->Maximize( ); }

void TinyNutWindow::Close( TinyNut* nut_game ) { nut_game->Stop( ); }
