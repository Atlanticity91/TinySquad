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

#pragma once

#include "Utils/TinyImGuiTheme.h"

#define IMGUI_NO_FLAGS 0 
#define IMGUI_NO_LABEL "##imgui_no_label"
#define IMGUI_FLOAT_FORMAT "%.2f"

#define TINY_IMGUI_SCOPE_ID( ... )\
    ImGui::PushID( static_cast<int>( ImGui::GetCursorPosX( ) + ImGui::GetCursorPosY( ) ) );\
    __VA_ARGS__\
    ImGui::PopID( )

namespace TinyImGui {

	tm_struct DropdownContext {

		tiny_uint Index;
		tiny_list<native_string> Values;

		DropdownContext( );

		DropdownContext( tiny_init<native_string> values );

		DropdownContext( tiny_init<native_string> values, const tiny_string& value );

		DropdownContext( tiny_init<native_string> values, const tiny_hash value );

		DropdownContext( const tiny_list<native_string>& values );

		DropdownContext( const tiny_list<native_string>& values, const tiny_string& value );

		DropdownContext( const tiny_list<tiny_string>& values );

		DropdownContext( const tiny_list<tiny_string>& values, const tiny_string& value );

		DropdownContext( const tiny_list<tiny_string>& values, const tiny_hash value );

		DropdownContext( tiny_uint index, tiny_init<native_string> values );

		void Find( const tiny_hash& hash );

		DropdownContext& operator=( const tiny_list<tiny_string>& values );

	};

	template<typename Type>
	struct DragContext {

		Type Speed{ };
		Type Min{ };
		Type Max{ };

	};

	tiny_enum( KnobTypes ) {

		TK_TYPE_WIPER = ImGuiKnobVariant_WiperOnly,
			TK_TYPE_DOT = ImGuiKnobVariant_WiperDot,
			TK_TYPE_STEPPED = ImGuiKnobVariant_Stepped

	};

	tm_struct KnobContext{

		KnobTypes Type = TK_TYPE_WIPER;
		float Min = -6.f;
		float Max = 6.f;

	};

	tm_struct GridContext{

		tiny_uint Columns;
		tiny_uint Rows;
		ImColor Color;
		float Thickness;

		GridContext( );

		GridContext( tiny_uint columns, tiny_uint rows );

		GridContext( tiny_uint columns, tiny_uint rows, float thickness );

		GridContext( tiny_uint columns, tiny_uint rows, ImColor color, float thickness );

	};

	tm_dll void ShiftCursorX( float distance );

	tm_dll void ShiftCursorY( float distance );

	tm_dll void ShiftCursor( float x, float y );

	tm_dll bool BeginModal( const tiny_string& label );

	tm_dll void EndModal( );

	tm_dll ImVec2 CalcTextSize( const tiny_string& text );

	tm_dll void BeginVars( );

	tm_dll void EndVars( );

	template<typename Func, typename... Args>
	void Collapsing( const tiny_string& name, Func&& draw, Args&... args ) {
		auto* name_str = name.get( );

		if ( ImGui::CollapsingHeader( name_str, IMGUI_NO_FLAGS ) ) {
			draw( args... );

			ImGui::Separator( );
		}
	};

	template<typename Func, typename... Args>
	void CollapsingOpen( const tiny_string& name, Func&& draw, Args&... args ) {
		auto* name_str = name.get( );

		if ( ImGui::CollapsingHeader( name_str, ImGuiTreeNodeFlags_DefaultOpen ) ) {
			draw( args... );

			ImGui::Separator( );
		}
	};

	tm_dll void SeparatorText( const tiny_string& label );

	tm_dll bool Button( const tiny_string& label );

	tm_dll bool Button( const tiny_string& label, const ImVec2& size );

	tm_dll bool ButtonIcon( native_string icon, const tiny_string& label );

	tm_dll bool ButtonIcon( native_string icon, const tiny_string& label, const ImVec2& size );

	tm_dll bool RightButton( const tiny_string& label );

	tm_dll ImVec2 ButtonSpanLeft( tiny_uint button_count );

	tm_dll ImVec2 ButtonSpanRight( tiny_uint button_count );

	tm_dll void Text( const tiny_string& text );

	tm_dll void Text( const std::string_view& text );

	tm_dll void InputBegin( const tiny_string& label );

	tm_dll void InputEnd( );

	tm_dll bool Checkbox( const tiny_string& label, bool& value );

	tm_dll bool Checkbox( const tiny_string& label, const bool& value );

	tm_dll bool InputText( const tiny_string& label, tiny_uint length, char* buffer );

	tm_dll bool InputScalar( const tiny_string& label, tiny_int& scalar );

	tm_dll bool InputScalar( const tiny_string& label, const tiny_int& scalar );

	tm_dll bool InputScalar( const tiny_string& label, tiny_uint& scalar );

	tm_dll bool InputScalar( const tiny_string& label, const tiny_uint& scalar );

	tm_dll bool InputScalar( const tiny_string& label, float& scalar );

	tm_dll bool InputScalar( const tiny_string& label, const float& scalar );

	tm_dll bool InputVector(
		const tiny_string& label,
		tiny_uint component,
		tiny_int* vector
	);

	tm_dll bool InputVector(
		const tiny_string& label,
		tiny_uint component,
		const tiny_int* vector
	);

	tm_dll bool InputPoint( const tiny_string& label, tiny_point& point );

	tm_dll bool InputPoint( const tiny_string& label, const tiny_point& point );

	tm_dll bool InputVector(
		const tiny_string& label,
		tiny_uint component,
		float* vector
	);

	tm_dll bool InputVector(
		const tiny_string& label,
		tiny_uint component,
		const float* vector
	);

	tm_dll bool InputVec2( const tiny_string& label, tiny_vec2& vector );

	tm_dll bool InputVec2( const tiny_string& label, const tiny_vec2& vector );

	tm_dll bool InputVec3( const tiny_string& label, tiny_vec3& vector );

	tm_dll bool InputVec3( const tiny_string& label, const tiny_vec3& vector );

	tm_dll bool InputVec4( const tiny_string& label, tiny_vec4& vector );

	tm_dll bool InputVec4( const tiny_string& label, const tiny_vec4& vector );

	tm_dll bool InputDrag(
		const tiny_string& label,
		tiny_uint component,
		float* vector,
		float speed,
		float min,
		float max
	);

	tm_dll bool InputDrag(
		const tiny_string& label,
		tiny_uint component,
		tiny_int* vector,
		tiny_int speed,
		tiny_int min,
		tiny_int max
	);

	template<typename Type>
	bool InputDrag(
		const tiny_string& label,
		tiny_uint component,
		Type* vector,
		const DragContext<Type>& context
	) {
		return InputDrag( label, component, vector, context.Speed, context.Max, context.Max );
	};

	tm_dll bool InputSlider( const tiny_string& label, float& scalar, float min, float max );

	tm_dll bool InputSlider( const tiny_string& label, float* scalar, float min, float max );

	tm_dll bool InputSlider( const tiny_string& label, tiny_uint component, float* values, float min, float max );

	tm_dll bool InputSlider( const tiny_string& label, tiny_vec2& vector, float min, float max );

	tm_dll bool InputSlider( const tiny_string& label, tiny_vec3& vector, float min, float max );

	tm_dll bool InputSlider( const tiny_string& label, tiny_vec4& vector, float min, float max );

	tm_dll bool InputSlider( const tiny_string& label, tiny_int* scalar, tiny_int min, tiny_int max );

	tm_dll bool InputSlider( const tiny_string& label, tiny_int& scalar, tiny_int min, tiny_int max );

	tm_dll bool InputSlider( const tiny_string& label, tiny_uint component, tiny_int* values, tiny_int min, tiny_int max );

	tm_dll bool InputSlider( const tiny_string& label, tiny_point& point, tiny_int min, tiny_int max );

	tm_dll bool InputColor( const tiny_string& label, float* color );

	tm_dll bool InputColor( const tiny_string& label, tiny_color& color );

	tm_dll bool InputColor( const tiny_string& label, const VkClearColorValue& color );

	template<typename... Args>
	void TextVar( const tiny_string& label, const tiny_string& format, Args... args ) {
		TinyImGui::InputBegin( label );

		ImGui::Text( format.get( ), args... );

		TinyImGui::InputEnd( );
	};

	tm_dll bool InputText( tiny_uint length, char* buffer );

	template<tiny_uint Length>
		requires ( Length > 0 )
	bool InputText( const tiny_string& label, tiny_buffer<Length>& buffer ) {
		auto* buffer_chars = buffer.as_chars( );

		return InputText( label, Length, buffer_chars );
	};

	template<tiny_uint Length>
		requires ( Length > 0 )
	bool InputText( tiny_buffer<Length>& buffer ) {
		auto* buffer_chars = buffer.as_chars( );

		return InputText( Length, buffer_chars );
	};

	tm_dll bool Combo( tiny_uint& index, const tiny_list<native_string>& list, const float width );

	tm_dll bool Combo( tiny_uint& index, const tiny_string_view& view, const float width );

	tm_dll bool Dropdown( const tiny_string& label, DropdownContext& context );

	tm_dll bool InputVulkan( const tiny_string& label, VkFormat& format );

	tm_dll bool InputVulkan( const tiny_string& label, const VkFormat& format );

	tm_dll bool InputVulkan( const tiny_string& label, const VkColorSpaceKHR& color_space );

	tm_dll bool InputVulkan( const tiny_string& label, VkImageLayout& layout );

	tm_dll bool InputVulkan( const tiny_string& label, const VkImageLayout& layout );

	tm_dll bool InputVulkan( const tiny_string& label, VkImageAspectFlags& aspect );

	tm_dll bool InputVulkan( const tiny_string& label, const VkImageAspectFlags& aspect );

	tm_dll bool InputVulkan( const tiny_string& label, VkSampleCountFlagBits& samples );

	tm_dll bool InputVulkan( const tiny_string& label, const VkSampleCountFlagBits& samples );

	tm_dll bool InputVulkan( const tiny_string& label, VkImageTiling& tiling );

	tm_dll bool InputVulkan( const tiny_string& label, const VkImageTiling& tiling );

	tm_dll bool InputVulkan( const tiny_string& label, TinyGraphicTextureUsages& usage );

	tm_dll bool InputVulkan( const tiny_string& label, const TinyGraphicTextureUsages& usage );

	tm_dll bool InputVulkan( const tiny_string& label, VkFilter& filter );

	tm_dll bool InputVulkan( const tiny_string& label, const VkFilter& filter );

	tm_dll bool InputVulkan( const tiny_string& label, VkSamplerMipmapMode& mipmap_mode );

	tm_dll bool InputVulkan( const tiny_string& label, const VkSamplerMipmapMode& mipmap_mode );

	tm_dll bool InputVulkan( const tiny_string& label, TinyGraphicWrapModes& wrap_modes );

	tm_dll bool InputVulkan( const tiny_string& label, const TinyGraphicWrapModes& wrap_modes );

	tm_dll bool InputVulkan( const tiny_string& label, VkCompareOp& compare_op );

	tm_dll bool InputVulkan( const tiny_string& label, const VkCompareOp& compare_op );

	tm_dll bool InputVulkan( const tiny_string& label, VkBorderColor& border_color );

	tm_dll bool InputVulkan( const tiny_string& label, const VkBorderColor& border_color );

	tm_dll bool InputVulkan( const tiny_string& label, VkViewport& viewport );

	tm_dll bool InputVulkan( const tiny_string& label, const VkViewport& viewport );

	tm_dll bool InputVulkan( const tiny_string& label, VkScissor& scissor );

	tm_dll bool InputVulkan( const tiny_string& label, const VkScissor& scissor );

	tm_dll bool Knob( const tiny_string& label, float& scalar );

	tm_dll bool Knob(
		const tiny_string& label,
		float& scalar,
		const KnobContext& context
	);

	tm_dll ImTextureID CreateTextureID( TinyGraphicTexture* texture );

	tm_dll ImTextureID CreateTextureID( TinyGraphicTexture& texture );

	tm_dll void DestroyTextureID( ImTextureID& texture_id );

	tm_dll void SetImageTooltipSize( const ImVec2& size );

	tm_dll void Grid( ImVec2 cursor, ImVec2 dimensions, const GridContext& context );

	tm_dll float Convert_sRGB_FromLinear( float theLinearValue );

	tm_dll float Convert_sRGB_ToLinear( float thesRGBValue );

	tm_dll ImVec4 ConvertFromSRGB( ImVec4 colour );

	tm_dll ImVec4 ConvertToSRGB( ImVec4 colour );

	tm_dll ImU32 ColorWithValue( const ImColor& color, float value );

	tm_dll ImU32 ColorWithSaturation( const ImColor& color, float saturation );

	tm_dll ImU32 ColorWithHue( const ImColor& color, float hue );

	tm_dll ImU32 ColorWithMultipliedValue( const ImColor& color, float multiplier );

	tm_dll ImU32 ColorWithMultipliedSaturation( const ImColor& color, float multiplier );

	tm_dll ImU32 ColorWithMultipliedHue( const ImColor& color, float multiplier );

};
