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
#include <TinyLibs/GLFW/glfw3.h>

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyNutWindow::TinyNutWindow( const tiny_string& name, bool enable_dockspace )
	: _is_over{ false },
	_has_dockspace{ enable_dockspace },
	_name{ name },
	_icons{ }
{ }

void TinyNutWindow::Create( TinyNut* nut_game ) {
	_RegisterIcon( nut_game, "Logo"	   , TinyWindowIcon, []( auto* ) { }		   );
	_RegisterIcon( nut_game, "Minimize", TinyWindowMinimizeIcon, TinyNutWindow::Minimize );
	_RegisterIcon( nut_game, "Restore" , TinyWindowRestoreIcon , TinyNutWindow::Restore  );
	_RegisterIcon( nut_game, "Maximize", TinyWindowMaximizeIcon, TinyNutWindow::Maximize );
	_RegisterIcon( nut_game, "Close"   , TinyWindowCloseIcon   , TinyNutWindow::Close    );

	Initialize( nut_game );
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
		if ( _has_dockspace )
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
void TinyNutWindow::Initialize( TinyNut* nut_game ) {
	auto channels = 0;
	auto height   = 0;
	auto width    = 0;
	auto* texels  = stbi_load_from_memory( TinyWindowIcon, tiny_sizeof( TinyWindowIcon ), tiny_rvalue( width ), tiny_rvalue( height ), tiny_rvalue( channels ), 4 );
	auto& window  = nut_game->GetWindow( );

	window.SetCallback( TWC_WINDOW_HIT, TinyNutWindow::TitlebarHit );
	window.SetIcon( 512, 512, texels );

	stbi_image_free( texels );
}

void TinyNutWindow::DrawBorder( ) {
	auto window		 = ImGui::GetCurrentWindow( );
	auto* draw_list  = window->DrawList;
	auto rounding	 = window->WindowRounding;
	auto border_size = window->WindowBorderSize;
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

	ImGui::PushStyleColor( ImGuiCol_Border, IM_COL32( 50, 50, 50, 255 ) );

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

	ImGui::PopStyleColor( );
}

void TinyNutWindow::DrawTitlebarBorder(
	float height, 
	const ImVec2& padding,
	const ImVec2& cursor
) {
	ImGui::SetCursorPos( cursor );
	
	auto window		= ImGui::GetCurrentWindow( );
	auto* draw_list = window->DrawList;
	auto title_min	= ImGui::GetCursorScreenPos( );
	auto title_max  = ImVec2{
		title_min.x + ImGui::GetWindowWidth( ) - padding.y * 2.0f,
		title_min.y + height
	};

	draw_list->AddRectFilled( title_min, title_max, TinyImGui::Theme::Titlebar );
}

void TinyNutWindow::DrawTitlebarLogo( bool is_maximized, const ImVec2& padding ) {
	auto window		= ImGui::GetCurrentWindow( );
	auto* draw_list = window->DrawList;
	auto logo_size  = 48.f;
	auto offset		= ImVec2{
		16.f + padding.x,
		 5.f + padding.y - 6.f
	};
	auto logo_min	= ImVec2{ 
		ImGui::GetItemRectMin( ).x + offset.x,
		ImGui::GetItemRectMin( ).y + offset.y
	};
	auto logo_max	= ImVec2{ 
		logo_min.x + logo_size, 
		logo_min.y + logo_size 
	};

	draw_list->AddImage( _icons[ "Logo" ], logo_min, logo_max );
}

void TinyNutWindow::DrawMenubar( TinyNut* nut_game, bool is_maximized ) {
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
		_is_over = false;

	ImGui::ResumeLayout( );
}

void TinyNutWindow::DrawTitlebarText( const ImVec2& padding ) {
	auto* name_str = _name.as_chars( );
	auto cursor	   = ImGui::GetCursorPos( );
	auto size	   = ImGui::CalcTextSize( name_str );

	ImGui::SetCursorPos( { ImGui::GetWindowWidth( ) * 0.5f - size.x * 0.5f, 8.0f + padding.y } );
	ImGui::Text( "%s", name_str );
	ImGui::SetCursorPos( { cursor.x + size.x, cursor.y } );
}

void TinyNutWindow::DrawTitlebarIcon(
	TinyNut* nut_game,
	const ImVec2& spring,
	const ImVec2& padding,
	const ImVec2& expand,
	const tiny_string& name
) {
	/*
	auto& icon = _icons[ name ];
	auto size = ImVec2{ 14.f, 14.f };

	ImGui::ImageButton( icon.Icon.Descriptor, size );
	*/
	
	auto* name_str = name.as_chars( );
	auto col_n	   = TinyImGui::ColorWithMultipliedValue( TinyImGui::Theme::Text,  .9f );
	auto col_h	   = TinyImGui::ColorWithMultipliedValue( TinyImGui::Theme::Text, 1.2f );
	auto col_p	   = TinyImGui::Theme::TextDarker;
	auto& icon	   = _icons[ name ];
	auto size	   = ImVec2{ 14.f, 14.f };

	//ImGui::Spring( spring );
	//ImGui::SetCursorPosY( 8.f );

	if ( ImGui::InvisibleButton( name_str, size ) )
		std::invoke( icon.Callback, nut_game );

	auto bound_min = ImGui::GetItemRectMin( );
	auto bound_max = ImGui::GetItemRectMax( );
	auto bounding = ImRect{
		{ bound_min.x - expand.x, bound_min.y - expand.y },
		{ bound_max.x + expand.x, bound_max.y - expand.y }
	};

	TinyNutUI::ButtonImage( icon.Icon, col_n, col_h, col_p, bounding );
	
}

void TinyNutWindow::DrawTitlebar( TinyNut* nut_game, bool is_maximized ) {
	auto padding = ImGui::GetCurrentWindow( )->WindowPadding;
	auto height  = 58.f;
	auto cursor  = ImVec2{ padding.x, padding.y + is_maximized ? -6.f : 0.f };

	DrawTitlebarBorder( height, padding, cursor );
	DrawTitlebarLogo( is_maximized, padding );
	
	ImGui::BeginHorizontal( "Titlebar", { ImGui::GetWindowWidth( ) - padding.y * 2.0f, ImGui::GetFrameHeightWithSpacing( ) } );

	auto width = ImGui::GetContentRegionAvail( ).x - 84.f;

	ImGui::SetCursorPos( cursor );
	ImGui::InvisibleButton( "##__TinyTitleDragZone", { width, height } );

	_is_over = ImGui::IsItemHovered( );

	if ( is_maximized ) {
		auto mouse_y = ImGui::GetMousePos( ).y - ImGui::GetCursorScreenPos( ).y;
		
		if ( mouse_y >= 0.f && mouse_y <= 5.f )
			_is_over = true;
	}

	DrawMenubar( nut_game, is_maximized );
	DrawTitlebarText( padding );

	ImGui::SetCursorPos( { width, padding.y + 6.f } );

	DrawTitlebarIcon( nut_game, { -1.f, 19.f }, padding, { 0.f, -6.f }, "Minimize" );
	DrawTitlebarIcon( nut_game, { -1.f, 17.f }, padding, { 0.f, 0.f }, is_maximized ? "Restore" : "Maximize" );
	DrawTitlebarIcon( nut_game, { -1.f, 15.f }, padding, { 0.f, 0.f }, "Close" );
	

	ImGui::Spring( -1.f, 18.f );
	ImGui::EndHorizontal( );
	ImGui::SetCursorPosY( height );
}

bool TinyNutWindow::Prepare( TinyNut* nut_game, TinyWindow& window ) {
	auto window_flags = tiny_cast(
		ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
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
	ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, is_maximized ? ImVec2{ 6.f, 6.f } : ImVec2{ 2.f, 2.f } );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 3.f );

	ImGui::PushStyleColor( ImGuiCol_MenuBarBg, (ImU32)TinyImGui::Theme::Titlebar );

	auto state = ImGui::Begin( name_str, nullptr, window_flags );

	ImGui::PopStyleColor( );
	ImGui::PopStyleVar( 4 );

	if ( state ) {
		if ( !is_maximized )
			DrawBorder( );

		DrawTitlebar( nut_game, is_maximized );
	}

	return state;
}

void TinyNutWindow::DockSpace( ) {
	auto dockspace_id = ImGui::GetID( "TinyNutDockspace" );
	
	ImGui::DockSpace( dockspace_id );
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PRIVATE STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyNutWindow::Minimize( TinyNut* nut_game ) { nut_game->Minimize( ); }

void TinyNutWindow::Restore( TinyNut* nut_game ) { nut_game->Restore( ); }

void TinyNutWindow::Maximize( TinyNut* nut_game ) { nut_game->Maximize( ); }

void TinyNutWindow::Close( TinyNut* nut_game ) { nut_game->Stop( ); }

bool TinyNutWindow::TitlebarHit( GLFWwindow* window ) {
	auto* nut_game = tiny_cast( glfwGetWindowUserPointer( window ), TinyNut* );
	auto state	   = false;
	
	if ( nut_game ) {
		auto& nut_window = nut_game->GetNutWindow( );

		state = nut_window.GetIsTitlevarHovered( );
	}

	return state;
}

////////////////////////////////////////////////////////////////////////////////////////////
// === PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyNutWindow::GetIsTitlevarHovered( ) const { return _is_over; }

bool TinyNutWindow::GetHasDockspace( ) const { return _has_dockspace; }

const TinyNutWindow::Icon_t* TinyNutWindow::GetIcon( const tiny_string& alias ) const {
	auto icon_id = tiny_cast( 0, tiny_uint );
	auto* icon   = tiny_cast( nullptr, const TinyNutWindow::Icon_t* );

	if ( _icons.find( alias, icon_id ) )
		icon = tiny_rvalue( _icons.at( icon_id ) );

	return icon;
}
