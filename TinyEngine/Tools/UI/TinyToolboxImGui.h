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
 * @creation : 18/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyToolboxImGuiScopeColors.h"

#define IMGUI_NO_FLAGS 0 
#define IMGUI_NO_LABEL "##imgui_no_label"
#define IMGUI_FLOAT_FORMAT "%.2f"

#define TINY_IMGUI_SCOPE_ID( ... )\
    ImGui::PushID( static_cast<int>( ImGui::GetCursorPosX( ) + ImGui::GetCursorPosY( ) ) );\
    __VA_ARGS__\
    ImGui::PopID( )

namespace TinyImGui {

	te_struct DropdownContext {

		tiny_uint Index;
		tiny_list<c_string> Values;

		DropdownContext( );

		DropdownContext( tiny_init<c_string> values );

		DropdownContext( tiny_init<c_string> values, const tiny_string& value );

		DropdownContext( tiny_init<c_string> values, const tiny_hash value );

		DropdownContext( const tiny_list<tiny_string>& values );

		DropdownContext( const tiny_list<tiny_string>& values, const tiny_string& value );

		DropdownContext( const tiny_list<tiny_string>& values, const tiny_hash value );

		DropdownContext( tiny_uint index, tiny_init<c_string> values );

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

		TK_TYPE_WIPER   = ImGuiKnobVariant_WiperOnly,
		TK_TYPE_DOT		= ImGuiKnobVariant_WiperDot,
		TK_TYPE_STEPPED = ImGuiKnobVariant_Stepped

	};

	te_struct KnobContext {

		KnobTypes Type = TK_TYPE_WIPER;
		float Min	   = -6.f;
		float Max	   =  6.f;

	};

	te_struct GridContext {

		tiny_uint Columns;
		tiny_uint Rows;
		ImColor Color;
		float Thickness;

		GridContext( );

		GridContext( tiny_uint columns, tiny_uint rows );

		GridContext( tiny_uint columns, tiny_uint rows, float thickness );

		GridContext( tiny_uint columns, tiny_uint rows, ImColor color, float thickness );

	};

	tiny_dll bool BeginModal( const tiny_string& label );

	tiny_dll void EndModal( );

	tiny_dll void BeginVars( );

	tiny_dll void EndVars( );

	template<typename Func, typename... Args>
	void Collapsing( const tiny_string& name, Func&& draw, Args&... args ) {
		auto* name_str = name.as_chars( );

		if ( ImGui::CollapsingHeader( name_str, IMGUI_NO_FLAGS ) ) {
			draw( args... );

			ImGui::Separator( );
		}
	};

	template<typename Func, typename... Args>
	void CollapsingOpen( const tiny_string& name, Func&& draw, Args&... args ) {
		auto* name_str = name.as_chars( );

		if ( ImGui::CollapsingHeader( name_str, ImGuiTreeNodeFlags_DefaultOpen ) ) {
			draw( args... );

			ImGui::Separator( );
		}
	};

	tiny_dll void SeparatorText( const tiny_string& label );

	tiny_dll bool Button( const tiny_string& label );

	tiny_dll bool Button( const tiny_string& label, const ImVec2& size );

	tiny_dll bool RightButton( const tiny_string& label );

	tiny_dll ImVec2 ButtonSpanLeft( tiny_uint button_count );

	tiny_dll ImVec2 ButtonSpanRight( tiny_uint button_count );

	tiny_dll void Text( const tiny_string& text );

	tiny_dll void Text( const std::string_view& text );

	tiny_dll void InputBegin( const tiny_string& label );

	tiny_dll void InputEnd( );

	tiny_dll bool Checkbox( const tiny_string& label, bool& value );

	tiny_dll bool Checkbox( const tiny_string& label, const bool& value );

	tiny_dll bool InputText( const tiny_string& label, tiny_uint length, char* buffer );

	tiny_dll bool InputScalar( const tiny_string& label, tiny_int& scalar );

	tiny_dll bool InputScalar( const tiny_string& label, const tiny_int& scalar );

	tiny_dll bool InputScalar( const tiny_string& label, tiny_uint& scalar );

	tiny_dll bool InputScalar( const tiny_string& label, const tiny_uint& scalar );

	tiny_dll bool InputScalar( const tiny_string& label, float& scalar );

	tiny_dll bool InputScalar( const tiny_string& label, const float& scalar );

	tiny_dll bool InputVector( 
		const tiny_string& label,
		tiny_uint component,
		tiny_int* vector 
	);

	tiny_dll bool InputVector(
		const tiny_string& label, 
		tiny_uint component,
		const tiny_int* vector 
	);

	tiny_dll bool InputPoint( const tiny_string& label, tiny_point& point );

	tiny_dll bool InputPoint( const tiny_string& label, const tiny_point& point );

	tiny_dll bool InputVector(
		const tiny_string& label,
		tiny_uint component,
		float* vector 
	);
	
	tiny_dll bool InputVector( 
		const tiny_string& label,
		tiny_uint component,
		const float* vector
	);

	tiny_dll bool InputVec2( const tiny_string& label, tiny_vec2& vector );

	tiny_dll bool InputVec2( const tiny_string& label, const tiny_vec2& vector );

	tiny_dll bool InputVec3( const tiny_string& label, tiny_vec3& vector );

	tiny_dll bool InputVec3( const tiny_string& label, const tiny_vec3& vector );

	tiny_dll bool InputVec4( const tiny_string& label, tiny_vec4& vector );

	tiny_dll bool InputVec4( const tiny_string& label, const tiny_vec4& vector );

	tiny_dll bool InputDrag(
		const tiny_string& label, 
		tiny_uint component, 
		float* vector, 
		float speed, 
		float min, 
		float max 
	);

	tiny_dll bool InputDrag(
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
	) { return false; };

	template<>
	bool InputDrag<float>(
		const tiny_string& label,
		tiny_uint component,
		float* vector,
		const DragContext<float>& context
	) {
		return InputDrag( label, component, vector, context.Speed, context.Max, context.Max );
	};

	template<>
	bool InputDrag<tiny_int>(
		const tiny_string& label,
		tiny_uint component,
		tiny_int* vector,
		const DragContext<tiny_int>& context
	) {
		return InputDrag( label, component, vector, context.Speed, context.Max, context.Max );
	};

	tiny_dll bool InputSlider( const tiny_string& label, float& scalar, float min, float max );

	tiny_dll bool InputSlider( const tiny_string& label, float* scalar, float min, float max );

	tiny_dll bool InputSlider( const tiny_string& label, tiny_uint component, float* values, float min, float max );

	tiny_dll bool InputSlider( const tiny_string& label, tiny_vec2& vector, float min, float max );

	tiny_dll bool InputSlider( const tiny_string& label, tiny_vec3& vector, float min, float max );

	tiny_dll bool InputSlider( const tiny_string& label, tiny_vec4& vector, float min, float max );

	tiny_dll bool InputSlider( const tiny_string& label, tiny_int* scalar, tiny_int min, tiny_int max );

	tiny_dll bool InputSlider( const tiny_string& label, tiny_int& scalar, tiny_int min, tiny_int max );

	tiny_dll bool InputSlider( const tiny_string& label, tiny_uint component, tiny_int* values, tiny_int min, tiny_int max );

	tiny_dll bool InputSlider( const tiny_string& label, tiny_point& point, tiny_int min, tiny_int max );

	tiny_dll bool InputColor( const tiny_string& label, float* color );

	tiny_dll bool InputColor( const tiny_string& label, tiny_color& color );

	tiny_dll bool InputColor( const tiny_string& label, const VkClearColorValue& color );

	template<typename... Args>
	void TextVar( const tiny_string& label, const tiny_string& format, Args... args ) {
		TinyImGui::InputBegin( label );

		ImGui::Text( format.get( ), args... );

		TinyImGui::InputEnd( );
	};

	tiny_dll bool InputText( tiny_uint length, char* buffer );

	template<tiny_uint Length>
	bool InputText( tiny_buffer<Length>& buffer ) {
		auto* buffer_chars = buffer.as_chars( );

		return InputText( Length, buffer_chars );
	};

	tiny_dll bool Dropdown( const tiny_string& label, DropdownContext& context );

	tiny_dll bool InputVulkan( const tiny_string& label, VkFormat& format );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkFormat& format );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkColorSpaceKHR& color_space );

	tiny_dll bool InputVulkan( const tiny_string& label, VkImageLayout& layout );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkImageLayout& layout );

	tiny_dll bool InputVulkan( const tiny_string& label, VkImageAspectFlags& aspect );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkImageAspectFlags& aspect );

	tiny_dll bool InputVulkan( const tiny_string& label, VkSampleCountFlagBits& samples );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkSampleCountFlagBits& samples );

	tiny_dll bool InputVulkan( const tiny_string& label, VkImageTiling& tiling );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkImageTiling& tiling );

	tiny_dll bool InputVulkan( const tiny_string& label, TinyGraphicTextureUsages& usage );

	tiny_dll bool InputVulkan( const tiny_string& label, const TinyGraphicTextureUsages& usage );

	tiny_dll bool InputVulkan( const tiny_string& label, VkFilter& filter );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkFilter& filter );

	tiny_dll bool InputVulkan( const tiny_string& label, VkSamplerMipmapMode& mipmap_mode );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkSamplerMipmapMode& mipmap_mode );

	tiny_dll bool InputVulkan( const tiny_string& label, TinyGraphicWrapModes& wrap_modes );

	tiny_dll bool InputVulkan( const tiny_string& label, const TinyGraphicWrapModes& wrap_modes );

	tiny_dll bool InputVulkan( const tiny_string& label, VkCompareOp& compare_op );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkCompareOp& compare_op );

	tiny_dll bool InputVulkan( const tiny_string& label, VkBorderColor& border_color );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkBorderColor& border_color );

	tiny_dll bool InputVulkan( const tiny_string& label, VkViewport& viewport );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkViewport& viewport );

	tiny_dll bool InputVulkan( const tiny_string& label, VkScissor& scissor );

	tiny_dll bool InputVulkan( const tiny_string& label, const VkScissor& scissor );

	tiny_dll bool Knob( const tiny_string& label, float& scalar );

	tiny_dll bool Knob( 
		const tiny_string& label,
		float& scalar,
		const KnobContext& context 
	);

	tiny_dll ImTextureID CreateTextureID( TinyTexture2D* texture );

	tiny_dll ImTextureID CreateTextureID( TinyTexture2D& texture );

	tiny_dll void DestroyTextureID( ImTextureID& texture_id );

	tiny_dll void Grid( ImVec2 cursor, ImVec2 dimensions, const GridContext& context );

};
