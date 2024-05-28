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

#pragma once

#include "TinyToolboxImGui.h"

namespace TinyImGui::Theme { 

	static constexpr auto FramePadding	  = ImVec2{ 4.f, 4.f };
	static constexpr auto FrameRounding   = 2.5f;
	static constexpr auto FrameBorderSize = 1.f;
	static constexpr auto IndentSpacing	  = 11.f;

	static constexpr auto Dark			  = ImColor{   0,   0,   0,   0 };
	static constexpr auto Highlight		  = ImColor{  39, 185, 242, 255 };
	static constexpr auto NiceBlue		  = ImColor{  83, 232, 254, 255 };
	static constexpr auto Compliment	  = ImColor{  78, 151, 166, 255 };
	static constexpr auto Background	  = ImColor{  36,  36,  36, 255 };
	static constexpr auto BackgroundDark  = ImColor{  26,  26,  26, 255 };
	static constexpr auto Titlebar		  = ImColor{  21,  21,  21, 255 };
	static constexpr auto PropertyField   = ImColor{  15,  15,  15, 255 };
	static constexpr auto Text			  = ImColor{ 192, 192, 192, 255 };
	static constexpr auto TextBrighter	  = ImColor{ 210, 210, 210, 255 };
	static constexpr auto TextDarker	  = ImColor{ 128, 128, 128, 255 };
	static constexpr auto TextError		  = ImColor{ 230,  51,  51, 255 };
	static constexpr auto Muted			  = ImColor{  77,  77,  77, 255 };
	static constexpr auto GroupHeader	  = ImColor{  47,  47,  47, 255 };
	static constexpr auto Selection		  = ImColor{ 237, 192, 119, 255 };
	static constexpr auto SelectionMuted  = ImColor{ 237, 201, 142,  23 };
	static constexpr auto BackgroundPopup = ImColor{  50,  50,  50, 255 };
	static constexpr auto NotifBlue		  = ImColor{  82, 179, 222, 255 };
	static constexpr auto NotifYellow	  = ImColor{ 236, 158,  36, 255 };
	static constexpr auto NotifOrange	  = ImColor{ 250, 101,  23, 255 };
	static constexpr auto NotifRed		  = ImColor{ 222,  43,  43, 255 };
	static constexpr auto MissingMesh	  = ImColor{ 230, 102,  76, 255 };
	static constexpr auto HoverPurple	  = ImColor{ 125,  95, 255, 255 };
	static constexpr auto ActivePurple	  = ImColor{ 113,  88, 226, 255 };
	static constexpr auto HoverNeutral	  = ImColor{ 255, 225, 135,  30 };
	static constexpr auto ActiveNeutral   = ImColor{ 255, 225, 135,  60 };
	
};
