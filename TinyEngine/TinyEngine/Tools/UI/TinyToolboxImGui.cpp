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
 * @creation : 21/01/2024
 * @version  : 2024.1.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   tiny_Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
static ImVec2 img_tooltip    = ImVec2{ 128.f, 128.f };
static native_string vec_axises[] = { "X", "Y", "Z", "W" };
static ImU32 vec_colors[]    = {

    IM_COL32( 168,  46,   2, 255 ),
    IM_COL32( 112, 162,  22, 255 ),
    IM_COL32(  51, 122, 210, 255 ),
    IM_COL32( 210, 183,  51, 255 )

};

template<typename ImFunc>
void Internal_Input( tiny_uint axis, ImFunc&& im_function ) {
    auto text_size = TinyImGui::CalcTextSize( vec_axises[ axis ] );
    auto style     = ImGui::GetStyle( );

    ImGui::AlignTextToFramePadding( );
    ImGui::TextUnformatted( vec_axises[ axis ] );
    ImGui::SameLine( text_size.x + style.ItemSpacing.x * 1.25f );

    auto cursor      = ImGui::GetCursorScreenPos( );
    auto axis_offset = tiny_vec2{

        cursor.x - style.FramePadding.x,
        cursor.y

    };
    auto axis_background = ImRect{

       axis_offset.x,
       axis_offset.y,
       axis_offset.x + text_size.x * .25f,
       axis_offset.y + text_size.y

    };

    ImGui::GetWindowDrawList( )->AddRectFilled( axis_background.Min, axis_background.Max, vec_colors[ axis ], style.FrameRounding );

    ImGui::PushItemWidth( -1 );

    TINY_IMGUI_SCOPE_ID( im_function( ); );

    ImGui::PopItemWidth( );
}

void Internal_Separator( ) {
    ImGui::NextColumn( );
    ImGui::NextColumn( );

    auto cursor = ImGui::GetCursorScreenPos( );
    auto size   = ImGui::GetItemRectMax( );
    auto min    = ImVec2{ cursor.x, cursor.y };
    auto max    = ImVec2{ cursor.x + size.x, cursor.y + 1.f };

    ImGui::GetWindowDrawList( )->AddRectFilled( min, max, ImGui::GetColorU32( ImGuiCol_Separator ) );
    ImGui::Dummy( { 0.f, 2.f } );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace TinyImGui { 

    DropdownContext::DropdownContext( ) 
        : DropdownContext{ { } }
    { }

    DropdownContext::DropdownContext( tiny_init<native_string> values )
        : Index{ 0 },
        Values{ values }
    { }

    DropdownContext::DropdownContext(
        tiny_init<native_string> values,
        const tiny_string& value
    ) : DropdownContext{ values, tiny_hash{ value } }
    { }

    DropdownContext::DropdownContext( 
        tiny_init<native_string> values, 
        const tiny_hash value 
    ) : DropdownContext{ values } 
    { 
        Find( value );
    }

    DropdownContext::DropdownContext( const tiny_list<native_string>& values )
        : DropdownContext{ { } }
    { 
        Values = values;
    }

    DropdownContext::DropdownContext( const tiny_list<tiny_string>& values ) 
        : DropdownContext{ { } }
    {
        auto count = values.size( );

        if ( count > 0 ) {
            Values = count;

            while ( count-- > 0 )
                Values[ count ] = values[ count ].get( );
        }
    }

    DropdownContext::DropdownContext(
        const tiny_list<native_string>& values, 
        const tiny_string& value
    )
        : DropdownContext{ values }
    { 
        auto hash = tiny_hash{ value };

        Find( hash );
    }

    DropdownContext::DropdownContext( 
        const tiny_list<tiny_string>& values, 
        const tiny_string& value 
    ) : DropdownContext{ values, tiny_hash{ value } }
    { }

    DropdownContext::DropdownContext( 
        const tiny_list<tiny_string>& values, 
        const tiny_hash value 
    ) : DropdownContext{ values }
    { 
        Find( value );
    }

    DropdownContext::DropdownContext( tiny_uint index, tiny_init<native_string> values ) 
        : Index{ index < values.size( ) ? index : 0 },
        Values{ values }
    { }

    GridContext::GridContext( )
        : GridContext{ 2, 2, ImGui::GetColorU32( ImGuiCol_Separator ), 1.f }
    { }

    GridContext::GridContext( tiny_uint columns, tiny_uint rows )
        : GridContext{ columns, rows, 1.f } 
    { }

    GridContext::GridContext( tiny_uint columns, tiny_uint rows, float thickness ) 
        : GridContext{ 
            columns,
            rows, 
            ImGui::GetColorU32( ImGuiCol_Separator ), 
            thickness
        }
    { }

    GridContext::GridContext(
        tiny_uint columns,
        tiny_uint rows,
        ImColor color,
        float thickness
    )
        : Columns{ columns },
        Rows{ rows },
        Color{ color },
        Thickness{ thickness }
    { }

    void DropdownContext::Find( const tiny_hash& hash ) {
        Index = Values.size( );

        while ( Index-- > 1 ) {
            if ( hash == tiny_hash{ Values[ Index ] } )
                break;
        }
    }

    DropdownContext& DropdownContext::operator=( const tiny_list<tiny_string>& values ) {
        auto count = values.size( );

        Values = count;

        while ( count-- > 0 )
            Values[ count ] = values[ count ].get( );

        return tiny_self;
    }

    void ShiftCursorX( float distance ) {
        auto cursor_x = ImGui::GetCursorPosX( );

        ImGui::SetCursorPosX( cursor_x + distance );
    }

    void ShiftCursorY( float distance ) {
        auto cursor_y = ImGui::GetCursorPosY( );

        ImGui::SetCursorPosY( cursor_y + distance );
    }

    void ShiftCursor( float x, float y ) {
        auto cursor = ImGui::GetCursorPos( );

        ImGui::SetCursorPos( { cursor.x + x, cursor.y + y } );
    }

    bool BeginModal( const tiny_string& label ) {
        auto center = ImGui::GetMainViewport( )->GetCenter( );

        ImGui::SetNextWindowPos( center, ImGuiCond_Appearing, { .5f, .5f } );

        return ImGui::BeginPopupModal( label.get( ), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
    }

    void EndModal( ) { ImGui::EndPopup( ); }

    ImVec2 CalcTextSize( const tiny_string& text ) {
        auto* text_str = text.get( );
        auto& style    = ImGui::GetStyle( );
        auto size      = ImGui::CalcTextSize( text_str );

        size.x += style.FramePadding.x * 2.f;
        size.y += style.FramePadding.y * 2.f;

        return size;
    }

    void BeginVars( ) {
        auto size = CalcTextSize( "################" ).x;

        ImGui::Columns( 2 );
        ImGui::SetColumnWidth( 0, size );
    }

    void EndVars( ) { ImGui::EndColumns( ); }

    void SeparatorText( const tiny_string& label ) {
        auto label_str = label.get( );

        EndVars( );

        ImGui::SeparatorText( label_str );

        BeginVars( );
    }

    bool Button( const tiny_string& label ) { 
        return Button( label, { 0.f, 0.f } );
    }

    bool Button( const tiny_string& label, const ImVec2& size ) {
        TINY_IMGUI_SCOPE_ID(
            auto* label_str = label.get( );
            auto state      = ImGui::Button( label_str, size );
        );

        return state;
    }

    bool ButtonIcon( native_string icon, const tiny_string& label ) {
        return ButtonIcon( icon, label, { 0.f, 0.f } );
    }
    
    bool ButtonIcon( native_string icon, const tiny_string& label, const ImVec2& size ) {
        TINY_IMGUI_SCOPE_ID(
            auto label_ = std::string{ icon };

            label_ += " ";
            label_ += label.as_string( );

            auto* label_str = label_.c_str( );
            auto state = ImGui::Button( label_str, size );
            );

        return state;
    }

    bool RightButton( const tiny_string& label ) {
        auto offset = CalcTextSize( "############" ).x;
        auto cursor = ImGui::GetCursorPosX( ) + ImGui::GetContentRegionAvail( ).x;

        ImGui::SetCursorPosX( cursor - offset );

        return ImGui::Button( label.get( ), { -1.f, .0f } );
    }

    ImVec2 ButtonSpanLeft( tiny_uint button_count ) {
        auto& style      = ImGui::GetStyle( );
        auto button_size = ImGui::CalcTextSize( "##############" ).x + style.FramePadding.x * 2.f;

        return { button_size, 0.f };
    }

    ImVec2 ButtonSpanRight( tiny_uint button_count ) {
        auto& style       = ImGui::GetStyle( );
        auto button_size  = ImGui::CalcTextSize( "##############" ).x + style.FramePadding.x * 2.f;
        auto span_width   = ( button_size + style.ItemSpacing.x ) * button_count - style.ItemSpacing.x;
        auto cusor_offset = ImGui::GetCursorPosX( ) + ImGui::GetContentRegionAvail( ).x - span_width;

        ImGui::SetCursorPosX( cusor_offset );

        return { button_size, 0.f };
    }

    void Text( const tiny_string& text ) { ImGui::Text( text.get( ) ); }

    void Text( const std::string_view& text ) { ImGui::Text( text.data( ) ); }

    void InputBegin( const tiny_string& label ) {
        const auto* name = label.get( );

        ImGui::TableSetColumnIndex( 0 );
        ImGui::AlignTextToFramePadding( );
        ImGui::TextUnformatted( name );
        ImGui::NextColumn( );
        ImGui::PushItemWidth( -1.f );
    }

    void InputEnd( ) {
        ImGui::PopItemWidth( );
        ImGui::NextColumn( );
    }

    bool Checkbox( const tiny_string& label, bool& value ) {
        InputBegin( label );

        TINY_IMGUI_SCOPE_ID(
            auto state = ImGui::Checkbox( IMGUI_NO_LABEL, &value ); 
        );

        InputEnd( );

        return state;
    }

    bool Checkbox( const tiny_string& label, const bool& value ) {
        ImGui::BeginDisabled( );

        auto _value = tiny_cast( value, bool );
        auto state  = Checkbox( label, _value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputText( const tiny_string& label, tiny_uint length, char* buffer ) {
        InputBegin( label );

        TINY_IMGUI_SCOPE_ID(
            auto state = ImGui::InputText( IMGUI_NO_LABEL, buffer, length );
        );

        InputEnd( );

        return state;
    }

    bool InputScalar( const tiny_string& label, tiny_int& scalar ) {
        InputBegin( label );

        TINY_IMGUI_SCOPE_ID( 
            auto state = ImGui::InputScalar( IMGUI_NO_LABEL, ImGuiDataType_S32, tiny_rvalue( scalar ) );
        );

        InputEnd( );

        return state;
    }

    bool InputScalar( const tiny_string& label, const tiny_int& scalar ) {
        ImGui::BeginDisabled( );

        auto value = tiny_cast( scalar, tiny_int );
        auto state = InputScalar( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputScalar( const tiny_string& label, tiny_uint& scalar ) {
        InputBegin( label );

        TINY_IMGUI_SCOPE_ID(
            auto state = ImGui::InputScalar( IMGUI_NO_LABEL, ImGuiDataType_U32, tiny_rvalue( scalar ), nullptr, nullptr, "%u", 0 );
        );
    
        InputEnd( );

        return false;
    }

    bool InputScalar( const tiny_string& label, const tiny_uint& scalar ) {
        ImGui::BeginDisabled( );

        auto value = tiny_cast( scalar, tiny_uint );
        auto state = InputScalar( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputScalar( const tiny_string& label, float& scalar ) {
        InputBegin( label );

        TINY_IMGUI_SCOPE_ID(
            auto state = ImGui::InputFloat( IMGUI_NO_LABEL, &scalar );
        );

        InputEnd( );

        return state;
    }

    bool InputScalar( const tiny_string& label, const float& scalar ) {
        ImGui::BeginDisabled( );

        auto value = tiny_cast( scalar, float );
        auto state = InputScalar( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVector( const tiny_string& label, tiny_uint component, tiny_int* vector ) {
        auto state = false;

        InputBegin( label );

        for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
            Internal_Input(
                i,
                [ & ]( ) { state = ImGui::InputInt( IMGUI_NO_LABEL, &vector[ i ], 0, 0 ); }
            );
        }

        if ( component > 1 )
            Internal_Separator( );

        InputEnd( );

        return state;
    }

    bool InputVector( const tiny_string& label, tiny_uint component, const tiny_int* vector ) { 
        ImGui::BeginDisabled( );

        auto state = InputVector( label, component, tiny_cast( vector, tiny_int* ) );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputPoint( const tiny_string& label, tiny_point& point ) {
        return InputVector( label, 2, tiny_rvalue( point.x ) );
    }

    bool InputPoint( const tiny_string& label, const tiny_point& point ) {
        return InputVector( label, 2, tiny_rvalue( point.x ) );
    }

    bool InputVector( const tiny_string& label, tiny_uint component, float* vector ) {
        auto state = false;

        InputBegin( label );

        for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
            Internal_Input(
                i,
                [ & ]( ) { state = ImGui::InputFloat( IMGUI_NO_LABEL, &vector[ i ], 0.f, 0.f, IMGUI_FLOAT_FORMAT ); }
            );
        }

        if ( component > 1 )
            Internal_Separator( );
    
        InputEnd( );

        return state;
    }

    bool InputVector( const tiny_string& label, tiny_uint component, const float* vector ) { 
        ImGui::BeginDisabled( );

        auto state = InputVector( label, component, tiny_cast( vector, float* ) );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVec2( const tiny_string& label, tiny_vec2& vector ) {
        return InputVector( label, 2, tiny_rvalue( vector.x ) );
    }

    bool InputVec2( const tiny_string& label, const tiny_vec2& vector ) {
        return InputVector( label, 2, tiny_rvalue( vector.x ) );
    }

    bool InputVec3( const tiny_string& label, tiny_vec3& vector ) {
        return InputVector( label, 3, tiny_rvalue( vector.x ) );
    }

    bool InputVec3( const tiny_string& label, const tiny_vec3& vector ) {
        return InputVector( label, 3, tiny_rvalue( vector.x ) );
    }

    bool InputVec4( const tiny_string& label, tiny_vec4& vector ) {
        return InputVector( label, 4, tiny_rvalue( vector.x ) );
    }

    bool InputVec4( const tiny_string& label, const tiny_vec4& vector ) {
        return InputVector( label, 4, tiny_rvalue( vector.x ) );
    }

    bool InputDrag( 
        const tiny_string& label,
        tiny_uint component, 
        float* vector, 
        float speed,
        float min, 
        float max 
    ) {
        auto state = false;

        InputBegin( label );

        for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
            Internal_Input(
                i,
                [ & ]( ) { state = ImGui::DragFloat( IMGUI_NO_LABEL, &vector[ i ], speed, min, max, IMGUI_FLOAT_FORMAT ); }
            );
        }

        if ( component > 1 )
            Internal_Separator( );

        InputEnd( );

        return state;
    }

    bool InputDrag(
        const tiny_string& label,
        tiny_uint component,
        tiny_int* vector,
        tiny_int speed,
        tiny_int min,
        tiny_int max
    ) {
        auto state = false;

        InputBegin( label );

        for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
            Internal_Input(
                i,
                [ & ]( ) { state = ImGui::DragInt( IMGUI_NO_LABEL, &vector[ i ], (float)speed, min, max ); }
            );
        }

        if ( component > 1 )
            Internal_Separator( );

        InputEnd( );

        return state;
    }

    bool InputSlider( const tiny_string& label, float* scalar, float min, float max ) {
        InputBegin( label );

        TINY_IMGUI_SCOPE_ID(
            auto state = ImGui::SliderFloat( IMGUI_NO_LABEL, scalar, min, max, IMGUI_FLOAT_FORMAT );
        );

        InputEnd( );

        return state;
    }

    bool InputSlider( const tiny_string& label, float& scalar, float min, float max ) {
        return InputSlider( label, &scalar, min, max );
    }

    bool InputSlider( const tiny_string& label, tiny_uint component, float* values, float min, float max ) {
        auto state = false;

        InputBegin( label );

        for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
            Internal_Input( 
                i,
                [ & ]( ) { state = ImGui::SliderFloat( IMGUI_NO_LABEL, &values[ i ], min, max, IMGUI_FLOAT_FORMAT ); }
            );
        }

        if ( component > 1 )
            Internal_Separator( );
    
        InputEnd( );

        return state;
    }

    bool InputSlider( const tiny_string& label, tiny_vec2& vector, float min, float max ) {
        return InputSlider( label, 2, &vector.x, min, max );
    }

    bool InputSlider( const tiny_string& label, tiny_vec3& vector, float min, float max ) {
        return InputSlider( label, 3, &vector.x, min, max );
    }

    bool InputSlider( const tiny_string& label, tiny_vec4& vector, float min, float max ) {
        return InputSlider( label, 4, &vector.x, min, max );
    }

    bool InputSlider( const tiny_string& label, tiny_int* scalar, tiny_int min, tiny_int max ) {
        InputBegin( label );

        TINY_IMGUI_SCOPE_ID(
            auto state = ImGui::SliderInt( IMGUI_NO_LABEL, scalar, min, max );
        );

        InputEnd( );

        return state;
    }

    bool InputSlider( const tiny_string& label, tiny_int& scalar, tiny_int min, tiny_int max ) {
        return InputSlider( label, &scalar, min, max );
    }

    bool InputSlider( const tiny_string& label, tiny_uint component, tiny_int* values, tiny_int min, tiny_int max ) {
        auto state = false;

        InputBegin( label );

        for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
            Internal_Input(
                i,
                [ & ]( ) { state = ImGui::SliderInt( IMGUI_NO_LABEL, &values[ i ], min, max ); }
            );
        }

        if ( component > 1 )
            Internal_Separator( );

        InputEnd( );

        return state;
    }

    bool InputSlider( const tiny_string& label, tiny_point& point, tiny_int min, tiny_int max ) {
        return InputSlider( label, 2, &point.x, min, max );
    }

    bool InputColor( const tiny_string& label, float* color ) {
        InputBegin( label );

        TINY_IMGUI_SCOPE_ID(
            auto state = ImGui::ColorEdit4( 
                IMGUI_NO_LABEL, 
                color,
                ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_AlphaPreviewHalf 
            );
        );

        InputEnd( );

        return state;
    }

    bool InputColor( const tiny_string& label, tiny_color& color ) {
        return InputColor( label, color.Get( ) );
    }

    bool InputColor( const tiny_string& label, const VkClearColorValue& color ) {
        auto* _color = tiny_rvalue( color.float32[ 0 ] );

        return InputColor( label, tiny_cast( _color, float* ) );
    }

    bool InputText( tiny_uint length, char* buffer ) {
        TINY_IMGUI_SCOPE_ID(
            auto state = ImGui::InputText( IMGUI_NO_LABEL, buffer, length + 1 );
        );

        return state;
    }

    bool Combo( tiny_uint& index, const tiny_list<native_string>& list, const float width ) {
        auto view = tiny_string_view{ list.data( ), list.size( ) };

        return Combo( index, view, width );
    }

    bool Combo( tiny_uint& index, const tiny_string_view& view, const float width ) {
        auto* _index = tiny_rvalue( index );

        ImGui::PushItemWidth( width );
        ImGui::BeginDisabled( view.Count < 1 );

        TINY_IMGUI_SCOPE_ID(
            auto state = ImGui::Combo( IMGUI_NO_LABEL, tiny_cast( _index, tiny_int* ), view.Address, view.Count );
        );

        ImGui::EndDisabled( );
        ImGui::PopItemWidth( );

        return state;
    }

    bool Dropdown( const tiny_string& label, DropdownContext& context ) {
        InputBegin( label );

        ImGui::BeginDisabled( context.Values.size( ) < 2 );
        TINY_IMGUI_SCOPE_ID(
            auto state = ImGui::Combo( 
                IMGUI_NO_LABEL, 
                tiny_cast( tiny_rvalue( context.Index ), tiny_int* ),
                context.Values.data( ),
                context.Values.size( ) 
            );
        ); 
        ImGui::EndDisabled( );

        InputEnd( );

        return state; 
    }

    bool InputVulkan( const tiny_string& label, VkFormat& format ) {
        auto context = DropdownContext{
            tiny_cast( format, tiny_uint ),
            {
                "Undefined",
                "R4G4 Unorm",
                "R4G4B4A4 Unorm",
                "B4G4R4A4 Unorm",
                "R5G6B5 Unorm",
                "B5G6R5 Unorm",
                "R5G5B5A1 Unorm",
                "B5G5R5A1 Unorm",
                "A1R5G5B5 Unorm",
                "R8 Unorm",
                "R8 Uorm",
                "R8 UScaled",
                "R8 Scaled",
                "R8 Uint",
                "R8 Int",
                "R8 SRGB",
                "R8G8 UNorm",
                "R8G8 Norm",
                "R8G8 UScaled",
                "R8G8 Scaled",
                "R8G8 Uint",
                "R8G8 Int",
                "R8G8 SRGB",
                "R8G8B8 Unorm",
                "R8G8B8 Norm",
                "R8G8B8 UScaled",
                "R8G8B8 Scaled",
                "R8G8B8 Uint",
                "R8G8B8 Int",
                "R8G8B8 SRGB",
                "B8G8R8 Unorm",
                "B8G8R8 Norm",
                "B8G8R8 UScaled",
                "B8G8R8 Scaled",
                "B8G8R8 Uint",
                "B8G8R8 Int",
                "B8G8R8 SRGB",
                "R8G8B8A8 Unorm",
                "R8G8B8A8 Norm",
                "R8G8B8A8 UScaled",
                "R8G8B8A8 Scaled",
                "R8G8B8A8 Uint",
                "R8G8B8A8 Int",
                "R8G8B8A8 SRGB",
                "B8G8R8A8 Unorm",
                "B8G8R8A8 Norm",
                "B8G8R8A8 UScaled",
                "B8G8R8A8 Scaled",
                "B8G8R8A8 Uint",
                "B8G8R8A8 Int",
                "B8G8R8A8 SRGB",
                "A8B8G8R8 Unorm Unorm",
                "A8B8G8R8 Norm Unorm",
                "A8B8G8R8 UScaled Unorm",
                "A8B8G8R8 Scaled Unorm",
                "A8B8G8R8 Uint Unorm",
                "A8B8G8R8 Int Unorm",
                "A8B8G8R8 SRGB Unorm",
                "A2R10G10B10 Unorm Unorm",
                "A2R10G10B10 Norm Unorm",
                "A2R10G10B10 UScaled Unorm",
                "A2R10G10B10 Scaled Unorm",
                "A2R10G10B10 Uint Unorm",
                "A2R10G10B10 Int Unorm",
                "A2B10G10R10 Unorm Unorm",
                "A2B10G10R10 Norm Unorm",
                "A2B10G10R10 UScaled Unorm",
                "A2B10G10R10 Scaled Unorm",
                "A2B10G10R10 Uint Unorm",
                "A2B10G10R10 Int Unorm",
                "R16 Unorm",
                "R16 Norm",
                "R16 UScaled",
                "R16 Scaled",
                "R16 Uint",
                "R16 Int",
                "R16 Float",
                "R16G16 Unorm",
                "R16G16 Norm",
                "R16G16 UScaled",
                "R16G16 Scaled",
                "R16G16 Uint",
                "R16G16 Int",
                "R16G16 Float",
                "R16G16B16 Unorm",
                "R16G16B16 Norm",
                "R16G16B16 UScaled",
                "R16G16B16 Scaled",
                "R16G16B16 Uint",
                "R16G16B16 Int",
                "R16G16B16 Float",
                "R16G16B16A16 Unorm",
                "R16G16B16A16 Norm",
                "R16G16B16A16 UScaled",
                "R16G16B16A16 Scaled",
                "R16G16B16A16 Uint",
                "R16G16B16A16 Int",
                "R16G16B16A16 Float",
                "R32 Uint",
                "R32 Int",
                "R32 Float",
                "R32G32 Uint",
                "R32G32 Int",
                "R32G32 Float",
                "R32G32B32 Uint",
                "R32G32B32 Int",
                "R32G32B32 Float",
                "R32G32B32A32 Uint",
                "R32G32B32A32 Int",
                "R32G32B32A32 Float",
                "R64 Uint",
                "R64 Int",
                "R64 Float",
                "R64G64 Uint",
                "R64G64 Int",
                "R64G64 Float",
                "R64G64B64 Uint",
                "R64G64B64 Int",
                "R64G64B64 Float",
                "R64G64B64A64 Uint",
                "R64G64B64A64 Int",
                "R64G64B64A64 Float",
                "B10G11R11 UFloat Unorm",
                "E5B9G9R9 UFloat Unorm",
                "D16 Unorm",
                "X8 D24 Unorm Unorm",
                "D32 Float",
                "S8 Uint",
                "D16 Unorm S8 Uint",
                "D24 Unorm S8 Uint",
                "D32 Float S8 Uint",
                "BC1 RGB Unorm",
                "BC1 RGB SRGB",
                "BC1 RGBA Unorm",
                "BC1 RGBA SRGB",
                "BC2 Unorm",
                "BC2 SRGB",
                "BC3 Unorm",
                "BC3 SRGB",
                "BC4 Unorm",
                "BC4 Norm",
                "BC5 Unorm",
                "BC5 Norm",
                "BC6H UFloat",
                "BC6H Float",
                "BC7 Unorm",
                "BC7 SRGB",
                "ETC2 R8G8B8 Unorm",
                "ETC2 R8G8B8 SRGB",
                "ETC2 R8G8B8A1 Unorm",
                "ETC2 R8G8B8A1 SRGB",
                "ETC2 R8G8B8A8 Unorm",
                "ETC2 R8G8B8A8 SRGB",
                "EAC R11 Unorm",
                "EAC R11 Norm",
                "EAC R11G11 Unorm",
                "EAC R11G11 Norm",
                "ASTC 4x4 Unorm",
                "ASTC 4x4 SRGB",
                "ASTC 5x4 Unorm",
                "ASTC 5x4 SRGB",
                "ASTC 5x5 Unorm",
                "ASTC 5x5 SRGB",
                "ASTC 6x5 Unorm",
                "ASTC 6x5 SRGB",
                "ASTC 6x6 Unorm",
                "ASTC 6x6 SRGB",
                "ASTC 8x5 Unorm",
                "ASTC 8x5 SRGB",
                "ASTC 8x6 Unorm",
                "ASTC 8x6 SRGB",
                "ASTC 8x8 Unorm",
                "ASTC 8x8 SRGB",
                "ASTC 10x5 Unorm",
                "ASTC 10x5 SRGB",
                "ASTC 10x6 Unorm",
                "ASTC 10x6 SRGB",
                "ASTC 10x8 Unorm",
                "ASTC 10x8 SRGB",
                "ASTC 10x10 Unorm",
                "ASTC 10x10 SRGB",
                "ASTC 12x10 Unorm",
                "ASTC 12x10 SRGB",
                "ASTC 12x12 Unorm",
                "ASTC 12x12 SRGB"
            }
        };
        auto state = Dropdown( label, context );

        if ( state )
            format = tiny_cast( context.Index, VkFormat );

        return state;
    }

    bool InputVulkan( const tiny_string& label, const VkFormat& format ) {
        ImGui::BeginDisabled( );

        auto value = VkFormat{ format };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan(
        const tiny_string& label, 
        const VkColorSpaceKHR& color_space 
    ) {
        auto index = tiny_cast( 0, tiny_uint );

        switch ( color_space ) {
            case VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT    : index =  1; break;
            case VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT    : index =  2; break;
            case VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT       : index =  3; break;
            case VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT        : index =  4; break;
            case VK_COLOR_SPACE_BT709_LINEAR_EXT            : index =  5; break;
            case VK_COLOR_SPACE_BT709_NONLINEAR_EXT         : index =  6; break;
            case VK_COLOR_SPACE_BT2020_LINEAR_EXT           : index =  7; break;
            case VK_COLOR_SPACE_HDR10_ST2084_EXT            : index =  8; break;
            case VK_COLOR_SPACE_DOLBYVISION_EXT             : index =  9; break;
            case VK_COLOR_SPACE_HDR10_HLG_EXT               : index = 10; break;
            case VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT         : index = 11; break;
            case VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT      : index = 12; break;
            case VK_COLOR_SPACE_PASS_THROUGH_EXT            : index = 13; break;
            case VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT : index = 14; break;
            case VK_COLOR_SPACE_DISPLAY_NATIVE_AMD          : index = 15; break;

            default: break;
        }

        auto context = DropdownContext{
            index,
            {
                "SRGB Non Linear",
                "Display P3 Non Linear",
                "Extended SRGB Linear",
                "Display P3 Linear",
                "DCI P3 Non Linear",
                "BT 709 Linear",
                "BT 709 Non Linear",
                "BT 2020 Linear",
                "HDR 10 ST2084",
                "Dolby Vision",
                "HDR 10 HLG",
                "Adobe RGB Linear",
                "Adobe RGB Non Linear",
                "Pass Through",
                "Extended SRGB Non Linear",
                "Display Native AMD"
            }
        };
    
        return Dropdown( label, context );
    }

    bool InputVulkan( const tiny_string& label, VkImageLayout& layout ) {
        auto context = DropdownContext{
            tiny_cast( layout, tiny_uint ),
            {
                "Undefined",
                "General",
                "Color Attachement",
                "Depth Stencil Attachement",
                "Depth Stencil Read Only",
                "Shader Read Only",
                "Transfer Source",
                "Transfer Destination",
                "Pre-Initialized"
            }
        };
        auto state = Dropdown( label, context );

        if ( state )
            layout = tiny_cast( context.Index, VkImageLayout );

        return state;
    }

    bool InputVulkan( const tiny_string& label, const VkImageLayout& layout ) {
        ImGui::BeginDisabled( );

        auto value = VkImageLayout{ layout };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan( const tiny_string& label, VkImageAspectFlags& aspect ) {
        auto aspect_id = tiny_cast( 0, tiny_uint );

        switch ( aspect ) {
            case VK_IMAGE_ASPECT_COLOR_BIT              : aspect_id =  1; break;
            case VK_IMAGE_ASPECT_DEPTH_BIT              : aspect_id =  2; break;
            case VK_IMAGE_ASPECT_STENCIL_BIT            : aspect_id =  3; break;
            case VK_IMAGE_ASPECT_METADATA_BIT           : aspect_id =  4; break;
            case VK_IMAGE_ASPECT_PLANE_0_BIT            : aspect_id =  5; break;
            case VK_IMAGE_ASPECT_PLANE_1_BIT            : aspect_id =  6; break;
            case VK_IMAGE_ASPECT_PLANE_2_BIT            : aspect_id =  7; break;
            case VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT : aspect_id =  8; break;
            case VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT : aspect_id =  9; break;
            case VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT : aspect_id = 10; break;
            case VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT : aspect_id = 11; break;

            default: break;
        }

        auto context = DropdownContext{
            aspect_id,
            {
                "None",
                "Color",
                "Depth",
                "Stencil",
                "Metadata",
                "Plane 0",
                "Plane 1",
                "Plane 2",
                "Plane 3"
            }
        };
        auto state = Dropdown( label, context );
    
        if ( state ) {
            switch ( context.Index ) {
                case  0 : aspect = VK_IMAGE_ASPECT_NONE;                   break;
                case  1 : aspect = VK_IMAGE_ASPECT_COLOR_BIT;              break;
                case  2 : aspect = VK_IMAGE_ASPECT_DEPTH_BIT;              break;
                case  3 : aspect = VK_IMAGE_ASPECT_STENCIL_BIT;            break;
                case  4 : aspect = VK_IMAGE_ASPECT_METADATA_BIT;           break;
                case  5 : aspect = VK_IMAGE_ASPECT_PLANE_0_BIT;            break;
                case  6 : aspect = VK_IMAGE_ASPECT_PLANE_1_BIT;            break;
                case  7 : aspect = VK_IMAGE_ASPECT_PLANE_2_BIT;            break;
                case  8 : aspect = VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT; break;
                case  9 : aspect = VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT; break;
                case 10 : aspect = VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT; break;
                case 11 : aspect = VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT; break;

                default: break;
            }
        }

        return state;
    }

    bool InputVulkan( const tiny_string& label, const VkImageAspectFlags& aspect ) {
        ImGui::BeginDisabled( );

        auto value = VkImageAspectFlags{ aspect };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan( const tiny_string& label, VkSampleCountFlagBits& samples ) {
        auto sample_id = tiny_cast( 0, tiny_uint );

        switch ( samples ) {
            case VK_SAMPLE_COUNT_2_BIT  : sample_id = 1; break;
            case VK_SAMPLE_COUNT_4_BIT  : sample_id = 2; break;
            case VK_SAMPLE_COUNT_8_BIT  : sample_id = 3; break;
            case VK_SAMPLE_COUNT_16_BIT : sample_id = 4; break;
            case VK_SAMPLE_COUNT_32_BIT : sample_id = 5; break;
            case VK_SAMPLE_COUNT_64_BIT : sample_id = 6; break;

            default : break;
        }

        auto context = DropdownContext{ sample_id, { "None", "2", "4", "8", "16", "32", "64" } };
        auto state   = Dropdown( label, context );

        if ( state ) {
            switch ( context.Index ) {
                case 0 : samples = VK_SAMPLE_COUNT_1_BIT;  break;
                case 1 : samples = VK_SAMPLE_COUNT_2_BIT;  break;
                case 2 : samples = VK_SAMPLE_COUNT_4_BIT;  break;
                case 3 : samples = VK_SAMPLE_COUNT_8_BIT;  break;
                case 4 : samples = VK_SAMPLE_COUNT_16_BIT; break;
                case 5 : samples = VK_SAMPLE_COUNT_32_BIT; break;
                case 6 : samples = VK_SAMPLE_COUNT_64_BIT; break;

                default : break;
            }
        }

        return state;
    }

    bool InputVulkan( const tiny_string& label, const VkSampleCountFlagBits& samples ) {
        ImGui::BeginDisabled( );

        auto value = VkSampleCountFlagBits{ samples };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan( const tiny_string& label, VkImageTiling& tiling ) {
        auto context = DropdownContext{ tiny_cast( tiling, tiny_uint ), { "Optimal", "Linear" } };
        auto state   = Dropdown( label, context );

        if ( state )
            tiling = tiny_cast( context.Index, VkImageTiling );

        return state;
    }

    bool InputVulkan( const tiny_string& label, const VkImageTiling& tiling ) {
        ImGui::BeginDisabled( );

        auto value = VkImageTiling{ tiling };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan( const tiny_string& label, TinyGraphicTextureUsages& usage ) {
        auto index = tiny_cast( 0, tiny_uint );

        switch ( usage ) {
            case TGT_USAGE_TARGET : index = 1; break;
            case TGT_USAGE_DEPTH  : index = 2; break;

            default : break;
        }

        auto context = DropdownContext{ index, { "Texture", "Render Target", "Depth Target" } };
        auto state   = Dropdown( label, context );

        if ( state )
            usage = tiny_cast( context.Index, TinyGraphicTextureUsages );

        return state;
    }

    bool InputVulkan( const tiny_string& label, const TinyGraphicTextureUsages& usage ) {
        ImGui::BeginDisabled( );

        auto value = TinyGraphicTextureUsages{ usage };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan( const tiny_string& label, VkFilter& filter ) {
        auto context = DropdownContext{ tiny_cast( filter, tiny_uint ), { "Nearest", "Linear" } };
        auto state   = Dropdown( label, context );

        if ( state )
            filter = tiny_cast( context.Index, VkFilter );

        return state;
    }

    bool InputVulkan( const tiny_string& label, const VkFilter& filter ) {
        ImGui::BeginDisabled( );

        auto value = VkFilter{ filter };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan( const tiny_string& label, VkSamplerMipmapMode& mipmap_mode ) {
        auto context = DropdownContext{ tiny_cast( mipmap_mode, tiny_uint ), { "Nearest", "Linear" } };
        auto state   = Dropdown( label, context );

        if ( state )
            mipmap_mode = tiny_cast( context.Index, VkSamplerMipmapMode );

        return state;
    }

    bool InputVulkan( const tiny_string& label, const VkSamplerMipmapMode& mipmap_mode ) {
        ImGui::BeginDisabled( );

        auto value = VkSamplerMipmapMode{ mipmap_mode };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan( const tiny_string& label, TinyGraphicWrapModes& wrap_modes ) {
        auto context = DropdownContext{
            tiny_cast( wrap_modes, tiny_uint ),
            {
                "Repeat",
                "Mirror Repeat",
                "Clamp To Edge",
                "Clamp To Border",
                "Clamp Mirror Edge"
            }
        };

        auto state = Dropdown( label, context );

        if ( state )
            wrap_modes = tiny_cast( context.Index, TinyGraphicWrapModes );

        return state;
    }

    bool InputVulkan( const tiny_string& label, const TinyGraphicWrapModes& wrap_modes ) {
        ImGui::BeginDisabled( );

        auto value = TinyGraphicWrapModes{ wrap_modes };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan( const tiny_string& label, VkCompareOp& compare_op ) {
        auto context = DropdownContext{
            tiny_cast( compare_op, tiny_uint ),
            {
                "Never",
                "Less",
                "Equal",
                "Less Or Equal",
                "Greater",
                "Not Equal",
                "Greater Or Equal",
                "Always"
            } 
        };

        auto state = Dropdown( label, context );

        if ( state )
            compare_op = tiny_cast( context.Index, VkCompareOp );

        return state;
    }

    bool InputVulkan( const tiny_string& label, const VkCompareOp& compare_op ) {
        ImGui::BeginDisabled( );

        auto value = VkCompareOp{ compare_op };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan( const tiny_string& label, VkBorderColor& border_color ) {
        auto context = DropdownContext{
            tiny_cast( border_color, tiny_uint ),
            {
                "Transparent Black Float",
                "Transparent Black Int",
                "Opaque Black Float",
                "Opaque Black Int",
                "Opaque White Float",
                "Opaque White Int"
            }
        };

        auto state = Dropdown( label, context );

        if ( state )
            border_color = tiny_cast( context.Index, VkBorderColor );

        return state;
    }

    bool InputVulkan( const tiny_string& label, const VkBorderColor& border_color ) {
        ImGui::BeginDisabled( );

        auto value = VkBorderColor{ border_color };
        auto state = InputVulkan( label, value );

        ImGui::EndDisabled( );

        return state;
    }

    bool InputVulkan( const tiny_string& label, VkViewport& viewport ) {
        return InputVector( label, 4, tiny_rvalue( viewport.x ) );
    }

    bool InputVulkan( const tiny_string& label, const VkViewport& viewport ) {
        ImGui::BeginDisabled( );

        auto state = InputVector( label, 4, tiny_rvalue( viewport.x ) );

        ImGui::EndDisabled( );

        return state;
    };

    bool InputVulkan( const tiny_string& label, VkScissor& scissor ) {
        return InputVector( label, 4, tiny_rvalue( scissor.offset.x ) );
    }

    bool InputVulkan( const tiny_string& label, const VkScissor& scissor ) {
        ImGui::BeginDisabled( );

        auto state = InputVector( label, 4, tiny_rvalue( scissor.offset.x ) );

        ImGui::EndDisabled( );

        return state;
    }

    bool Knob( const tiny_string& label, float& scalar ) {
        return Knob( label, scalar, { } );
    }

    bool Knob( const tiny_string& label, float& scalar, const KnobContext& context ) {
        return ImGuiKnobs::Knob(
            label.get( ),
            &scalar,
            context.Min,
            context.Max,
            0.1f,
            "%.1fdB",
            context.Type,
            .0f,
            ImGuiKnobFlags_DragHorizontal
        );
    }

    ImTextureID CreateTextureID( TinyGraphicTexture* texture ) {
        auto texture_id = tiny_cast( nullptr, VkDescriptorSet );

        if ( texture ) {
            auto sampler = texture->GetSampler( );
            auto view    = texture->GetView( );

            texture_id = ImGui_ImplVulkan_AddTexture( sampler, view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL );
        }

        return tiny_cast( texture_id, ImTextureID );
    }

    ImTextureID CreateTextureID( TinyGraphicTexture& texture ) {
        return CreateTextureID( tiny_rvalue( texture ) );
    }


    ImTextureID CreateTextureID( TinyTexture2D* texture ) {
        auto texture_id = tiny_cast( nullptr, VkDescriptorSet );

        if ( texture ) {
            auto sampler = texture->GetSampler( );
            auto view    = texture->GetView( );
        
            texture_id = ImGui_ImplVulkan_AddTexture( sampler, view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL );
        }

        return tiny_cast( texture_id, ImTextureID );
    }

    ImTextureID CreateTextureID( TinyTexture2D& texture ) {
        return CreateTextureID( tiny_rvalue( texture ) );
    }

    void DestroyTextureID( ImTextureID& texture_id ) {
        if ( texture_id ) {
            ImGui_ImplVulkan_RemoveTexture( tiny_cast( texture_id, VkDescriptorSet ) );

            texture_id = nullptr;
        }
    }

    void SetImageTooltipSize( const ImVec2& size ) { img_tooltip = size; }

    void Image( ImTextureID& image, const TinyTexture2D* texture, const ImVec2& dimensions ) {
        ImGui::Image( image, dimensions, { .0f, 0.f }, { 1.f, 1.f } );
    
        auto cursor = ImGui::GetCursorScreenPos( );

        if ( ImGui::BeginItemTooltip( ) ) {
            auto columns = texture->GetColumns( );
            auto rows    = texture->GetRows( );
            auto& io     = ImGui::GetIO( );
            auto uv      = tiny_vec2{ dimensions.x / columns, dimensions.y / rows };

            cursor.y = cursor.y - dimensions.y;
            columns  = tiny_cast( ( io.MousePos.x - cursor.x ) / uv.x, tiny_int );
            rows     = tiny_cast( ( io.MousePos.y - cursor.y ) / uv.y, tiny_int );
            uv       = texture->GetUV( );

            auto uv0 = ImVec2{ columns * uv.x, rows  * uv.y };
            auto uv1 = ImVec2{ uv0.x   + uv.x, uv0.y + uv.y };

            ImGui::Image( image, img_tooltip, uv0, uv1 );

            ImGui::EndTooltip( );
        }
    }

    void Grid( ImVec2 cursor, ImVec2 dimensions, const GridContext& context ) {
        auto* draw_list = ImGui::GetWindowDrawList( );
        auto columns    = context.Columns;
        auto rows       = context.Rows;
        auto size_w     = dimensions.x / columns;
        auto size_h     = dimensions.y / rows;

        columns += 1;
        rows    += 1;

        while ( columns-- > 0 ) {
            draw_list->AddLine( 
                { cursor.x + columns * size_w, cursor.y },
                { cursor.x + columns * size_w, cursor.y + dimensions.y },
                context.Color, 
                context.Thickness 
            );
        }

        while ( rows-- > 0 ) {
            draw_list->AddLine( 
                { cursor.x               , cursor.y + rows * size_h },
                { cursor.x + dimensions.x, cursor.y + rows * size_h },
                context.Color, 
                context.Thickness 
            );
        }
    }

    float Convert_sRGB_FromLinear( float theLinearValue ) {
        return theLinearValue <= 0.0031308f
            ? theLinearValue * 12.92f
            : glm::pow<float>( theLinearValue, 1.0f / 2.2f ) * 1.055f - 0.055f;
    }
    
    float Convert_sRGB_ToLinear( float thesRGBValue ) {
        return thesRGBValue <= 0.04045f
            ? thesRGBValue / 12.92f
            : glm::pow<float>( ( thesRGBValue + 0.055f ) / 1.055f, 2.2f );
    }
    
    ImVec4 ConvertFromSRGB( ImVec4 colour ) {
        return ImVec4( Convert_sRGB_FromLinear( colour.x ),
                       Convert_sRGB_FromLinear( colour.y ),
                       Convert_sRGB_FromLinear( colour.z ),
                       colour.w );
    }
    
    ImVec4 ConvertToSRGB( ImVec4 colour ) {
        return ImVec4( std::pow( colour.x, 2.2f ),
                       glm::pow<float>( colour.y, 2.2f ),
                       glm::pow<float>( colour.z, 2.2f ),
                       colour.w );
    }
    
    ImU32 ColorWithValue( const ImColor& color, float value ) {
        const ImVec4& colRow = color.Value;
        float hue, sat, val;
        
        ImGui::ColorConvertRGBtoHSV( colRow.x, colRow.y, colRow.z, hue, sat, val );

        return ImColor::HSV( hue, sat, std::min( value, 1.0f ) );
    }
    
    ImU32 ColorWithSaturation( const ImColor& color, float saturation ) {
        const ImVec4& colRow = color.Value;
        float hue, sat, val;
        
        ImGui::ColorConvertRGBtoHSV( colRow.x, colRow.y, colRow.z, hue, sat, val );
        
        return ImColor::HSV( hue, std::min( saturation, 1.0f ), val );
    }
    
    ImU32 ColorWithHue( const ImColor& color, float hue ) {
        const ImVec4& colRow = color.Value;
        float h, s, v;
        
        ImGui::ColorConvertRGBtoHSV( colRow.x, colRow.y, colRow.z, h, s, v );
        
        return ImColor::HSV( std::min( hue, 1.0f ), s, v );
    }
    
    ImU32 ColorWithMultipliedValue( const ImColor& color, float multiplier ) {
        const ImVec4& colRow = color.Value;
        float hue, sat, val;
        
        ImGui::ColorConvertRGBtoHSV( colRow.x, colRow.y, colRow.z, hue, sat, val );
        
        return ImColor::HSV( hue, sat, std::min( val * multiplier, 1.0f ) );
    }

    ImU32 ColorWithMultipliedSaturation( const ImColor& color, float multiplier ) {
        const ImVec4& colRow = color.Value;
        float hue, sat, val;
        
        ImGui::ColorConvertRGBtoHSV( colRow.x, colRow.y, colRow.z, hue, sat, val );
        
        return ImColor::HSV( hue, std::min( sat * multiplier, 1.0f ), val );
    }

    ImU32 ColorWithMultipliedHue( const ImColor& color, float multiplier ) {
        const ImVec4& colRow = color.Value;
        float hue, sat, val;
        
        ImGui::ColorConvertRGBtoHSV( colRow.x, colRow.y, colRow.z, hue, sat, val );
        
        return ImColor::HSV( std::min( hue * multiplier, 1.0f ), sat, val );
    }

};
