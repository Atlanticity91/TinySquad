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
static c_string vec_axises[] = { "X", "Y", "Z", "W" };
static ImU32 vec_colors[] = {

    IM_COL32( 168,  46,   2, 255 ),
    IM_COL32( 112, 162,  22, 255 ),
    IM_COL32(  51, 122, 210, 255 ),
    IM_COL32( 210, 183,  51, 255 )

};

ImVec2 Internal_CalcTextSize( c_string text ) { 
    auto& style = ImGui::GetStyle( );
    auto size   = ImGui::CalcTextSize( text );
    
    size.x += style.FramePadding.x * 2.f;
    size.y += style.FramePadding.y * 2.f;

    return size;
}

template<typename ImFunc>
void Internal_Input( tiny_uint axis, ImFunc&& im_function ) {
    auto text_size = Internal_CalcTextSize( vec_axises[ axis ] );
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
TinyImGui::DropdownContext::DropdownContext( ) 
    : DropdownContext{ { } }
{ }

TinyImGui::DropdownContext::DropdownContext( tiny_init<c_string> values )
    : Index{ 0 },
    Values{ values }
{ }

TinyImGui::DropdownContext::DropdownContext(
    tiny_init<c_string> values,
    const tiny_string& value
) : DropdownContext{ values, tiny_hash{ value } }
{ }

TinyImGui::DropdownContext::DropdownContext( 
    tiny_init<c_string> values, 
    const tiny_hash value 
) : DropdownContext{ values } 
{ 
    Find( value );
}

TinyImGui::DropdownContext::DropdownContext( const tiny_list<tiny_string>& values ) 
    : DropdownContext{ { } }
{
    auto count = values.size( );

    if ( count > 0 ) {
        Values = count;

        while ( count-- > 0 )
            Values[ count ] = values[ count ].as_chars( );
    }
}

TinyImGui::DropdownContext::DropdownContext( 
    const tiny_list<tiny_string>& values, 
    const tiny_string& value 
) : DropdownContext{ values, tiny_hash{ value } }
{ }

TinyImGui::DropdownContext::DropdownContext( 
    const tiny_list<tiny_string>& values, 
    const tiny_hash value 
) : DropdownContext{ values }
{ 
    Find( value );
}

TinyImGui::DropdownContext::DropdownContext( tiny_uint index, tiny_init<c_string> values ) 
    : Index{ index < values.size( ) ? index : 0 },
    Values{ values }
{ }

TinyImGui::GridContext::GridContext( )
    : GridContext{ 2, 2, ImGui::GetColorU32( ImGuiCol_Separator ), 1.f }
{ }

TinyImGui::GridContext::GridContext( tiny_uint columns, tiny_uint rows )
    : GridContext{ columns, rows, 1.f } 
{ }

TinyImGui::GridContext::GridContext( tiny_uint columns, tiny_uint rows, float thickness ) 
    : GridContext{ 
        columns,
        rows, 
        ImGui::GetColorU32( ImGuiCol_Separator ), 
        thickness
    }
{ }

TinyImGui::GridContext::GridContext(
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

void TinyImGui::DropdownContext::Find( const tiny_hash& hash ) {
    Index = Values.size( );

    while ( Index-- > 1 ) {
        if ( hash == tiny_hash{ Values[ Index ] } )
            break;
    }
}

TinyImGui::DropdownContext& TinyImGui::DropdownContext::operator=( const tiny_list<tiny_string>& values ) {
    auto count = values.size( );

    Values = count;

    while ( count-- > 0 )
        Values[ count ] = values[ count ].as_chars( );

    return tiny_self;
}

bool TinyImGui::BeginModal( const tiny_string& label ) {
    auto center = ImGui::GetMainViewport( )->GetCenter( );

    ImGui::SetNextWindowPos( center, ImGuiCond_Appearing, { .5f, .5f } );

    return ImGui::BeginPopupModal( label.get( ), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
}

void TinyImGui::EndModal( ) { ImGui::EndPopup( ); }

void TinyImGui::BeginVars( ) {
    auto size = Internal_CalcTextSize( "################" ).x;

    ImGui::Columns( 2 );
    ImGui::SetColumnWidth( 0, size );
}

void TinyImGui::EndVars( ) { ImGui::EndColumns( ); }

void TinyImGui::SeparatorText( const tiny_string& label ) {
    auto label_str = label.as_chars( );

    TinyImGui::EndVars( );

    ImGui::SeparatorText( label_str );

    TinyImGui::BeginVars( );
}

bool TinyImGui::Button( const tiny_string& label ) { 
    return TinyImGui::Button( label, { 0.f, 0.f } );
}

bool TinyImGui::Button( const tiny_string& label, const ImVec2& size ) {
    TINY_IMGUI_SCOPE_ID(
        auto* label_str = label.as_chars( );
        auto state      = ImGui::Button( label_str, size );
    );

    return state;
}

bool TinyImGui::RightButton( const tiny_string& label ) {
    auto offset = Internal_CalcTextSize( "############" ).x;
    auto cursor = ImGui::GetCursorPosX( ) + ImGui::GetContentRegionAvail( ).x;

    ImGui::SetCursorPosX( cursor - offset );

    return ImGui::Button( label.get( ), { -1.f, .0f } );
}

ImVec2 TinyImGui::ButtonSpanLeft( tiny_uint button_count ) {
    auto& style      = ImGui::GetStyle( );
    auto button_size = ImGui::CalcTextSize( "##############" ).x + style.FramePadding.x * 2.f;

    return { button_size, 0.f };
}

ImVec2 TinyImGui::ButtonSpanRight( tiny_uint button_count ) {
    auto& style       = ImGui::GetStyle( );
    auto button_size  = ImGui::CalcTextSize( "##############" ).x + style.FramePadding.x * 2.f;
    auto span_width   = ( button_size + style.ItemSpacing.x ) * button_count - style.ItemSpacing.x;
    auto cusor_offset = ImGui::GetCursorPosX( ) + ImGui::GetContentRegionAvail( ).x - span_width;

    ImGui::SetCursorPosX( cusor_offset );

    return { button_size, 0.f };
}

void TinyImGui::Text( const tiny_string& text ) { ImGui::Text( text.get( ) ); }

void TinyImGui::Text( const std::string_view& text ) { ImGui::Text( text.data( ) ); }

void TinyImGui::InputBegin( const tiny_string& label ) {
    const auto* name = label.get( );

    ImGui::TableSetColumnIndex( 0 );
    ImGui::AlignTextToFramePadding( );
    ImGui::TextUnformatted( name );
    ImGui::NextColumn( );
    ImGui::PushItemWidth( -1.f );
}

void TinyImGui::InputEnd( ) {
    ImGui::PopItemWidth( );
    ImGui::NextColumn( );
}

bool TinyImGui::Checkbox( const tiny_string& label, bool& value ) {
    TinyImGui::InputBegin( label );

    TINY_IMGUI_SCOPE_ID(
        auto state = ImGui::Checkbox( IMGUI_NO_LABEL, &value ); 
    );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::Checkbox( const tiny_string& label, const bool& value ) {
    ImGui::BeginDisabled( );

    auto _value = tiny_cast( value, bool );
    auto state  = TinyImGui::Checkbox( label, _value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputText( const tiny_string& label, tiny_uint length, char* buffer ) {
    TinyImGui::InputBegin( label );

    TINY_IMGUI_SCOPE_ID(
        auto state = ImGui::InputText( IMGUI_NO_LABEL, buffer, length );
    );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputScalar( const tiny_string& label, tiny_int& scalar ) {
    TinyImGui::InputBegin( label );

    TINY_IMGUI_SCOPE_ID( 
        auto state = ImGui::InputScalar( IMGUI_NO_LABEL, ImGuiDataType_S32, tiny_rvalue( scalar ) );
    );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputScalar( const tiny_string& label, const tiny_int& scalar ) {
    ImGui::BeginDisabled( );

    auto value = tiny_cast( scalar, tiny_int );
    auto state = TinyImGui::InputScalar( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputScalar( const tiny_string& label, tiny_uint& scalar ) {
    TinyImGui::InputBegin( label );

    TINY_IMGUI_SCOPE_ID(
        auto state = ImGui::InputScalar( IMGUI_NO_LABEL, ImGuiDataType_U32, tiny_rvalue( scalar ), nullptr, nullptr, "%u", 0 );
    );
    
    TinyImGui::InputEnd( );

    return false;
}

bool TinyImGui::InputScalar( const tiny_string& label, const tiny_uint& scalar ) {
    ImGui::BeginDisabled( );

    auto value = tiny_cast( scalar, tiny_uint );
    auto state = TinyImGui::InputScalar( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputScalar( const tiny_string& label, float& scalar ) {
    TinyImGui::InputBegin( label );

    TINY_IMGUI_SCOPE_ID(
        auto state = ImGui::InputFloat( IMGUI_NO_LABEL, &scalar );
    );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputScalar( const tiny_string& label, const float& scalar ) {
    ImGui::BeginDisabled( );

    auto value = tiny_cast( scalar, float );
    auto state = TinyImGui::InputScalar( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVector( const tiny_string& label, tiny_uint component, tiny_int* vector ) {
    auto state = false;

    TinyImGui::InputBegin( label );

    for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
        Internal_Input(
            i,
            [ & ]( ) { state = ImGui::InputInt( IMGUI_NO_LABEL, &vector[ i ], 0, 0 ); }
        );
    }

    if ( component > 1 )
        Internal_Separator( );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputVector( const tiny_string& label, tiny_uint component, const tiny_int* vector ) { 
    ImGui::BeginDisabled( );

    auto state = TinyImGui::InputVector( label, component, tiny_cast( vector, tiny_int* ) );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputPoint( const tiny_string& label, tiny_point& point ) {
    return TinyImGui::InputVector( label, 2, tiny_rvalue( point.x ) );
}

bool TinyImGui::InputPoint( const tiny_string& label, const tiny_point& point ) {
    return TinyImGui::InputVector( label, 2, tiny_rvalue( point.x ) );
}

bool TinyImGui::InputVector( const tiny_string& label, tiny_uint component, float* vector ) {
    auto state = false;

    TinyImGui::InputBegin( label );

    for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
        Internal_Input(
            i,
            [ & ]( ) { state = ImGui::InputFloat( IMGUI_NO_LABEL, &vector[ i ], 0.f, 0.f, IMGUI_FLOAT_FORMAT ); }
        );
    }

    if ( component > 1 )
        Internal_Separator( );
    
    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputVector( const tiny_string& label, tiny_uint component, const float* vector ) { 
    ImGui::BeginDisabled( );

    auto state = InputVector( label, component, tiny_cast( vector, float* ) );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVec2( const tiny_string& label, tiny_vec2& vector ) {
    return TinyImGui::InputVector( label, 2, tiny_rvalue( vector.x ) );
}

bool TinyImGui::InputVec2( const tiny_string& label, const tiny_vec2& vector ) {
    return TinyImGui::InputVector( label, 2, tiny_rvalue( vector.x ) );
}

bool TinyImGui::InputVec3( const tiny_string& label, tiny_vec3& vector ) {
    return TinyImGui::InputVector( label, 3, tiny_rvalue( vector.x ) );
}

bool TinyImGui::InputVec3( const tiny_string& label, const tiny_vec3& vector ) {
    return TinyImGui::InputVector( label, 3, tiny_rvalue( vector.x ) );
}

bool TinyImGui::InputVec4( const tiny_string& label, tiny_vec4& vector ) {
    return TinyImGui::InputVector( label, 4, tiny_rvalue( vector.x ) );
}

bool TinyImGui::InputVec4( const tiny_string& label, const tiny_vec4& vector ) {
    return TinyImGui::InputVector( label, 4, tiny_rvalue( vector.x ) );
}

bool TinyImGui::InputDrag( 
    const tiny_string& label,
    tiny_uint component, 
    float* vector, 
    float speed,
    float min, 
    float max 
) {
    auto state = false;

    TinyImGui::InputBegin( label );

    for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
        Internal_Input(
            i,
            [ & ]( ) { state = ImGui::DragFloat( IMGUI_NO_LABEL, &vector[ i ], speed, min, max, IMGUI_FLOAT_FORMAT ); }
        );
    }

    if ( component > 1 )
        Internal_Separator( );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputDrag(
    const tiny_string& label,
    tiny_uint component,
    tiny_int* vector,
    tiny_int speed,
    tiny_int min,
    tiny_int max
) {
    auto state = false;

    TinyImGui::InputBegin( label );

    for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
        Internal_Input(
            i,
            [ & ]( ) { state = ImGui::DragInt( IMGUI_NO_LABEL, &vector[ i ], (float)speed, min, max ); }
        );
    }

    if ( component > 1 )
        Internal_Separator( );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputSlider( const tiny_string& label, float* scalar, float min, float max ) {
    TinyImGui::InputBegin( label );

    TINY_IMGUI_SCOPE_ID(
        auto state = ImGui::SliderFloat( IMGUI_NO_LABEL, scalar, min, max, IMGUI_FLOAT_FORMAT );
    );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputSlider( const tiny_string& label, float& scalar, float min, float max ) {
    return TinyImGui::InputSlider( label, &scalar, min, max );
}

bool TinyImGui::InputSlider( const tiny_string& label, tiny_uint component, float* values, float min, float max ) {
    auto state = false;

    TinyImGui::InputBegin( label );

    for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
        Internal_Input( 
            i,
            [ & ]( ) { state = ImGui::SliderFloat( IMGUI_NO_LABEL, &values[ i ], min, max, IMGUI_FLOAT_FORMAT ); }
        );
    }

    if ( component > 1 )
        Internal_Separator( );
    
    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputSlider( const tiny_string& label, tiny_vec2& vector, float min, float max ) {
    return TinyImGui::InputSlider( label, 2, &vector.x, min, max );
}

bool TinyImGui::InputSlider( const tiny_string& label, tiny_vec3& vector, float min, float max ) {
    return TinyImGui::InputSlider( label, 3, &vector.x, min, max );
}

bool TinyImGui::InputSlider( const tiny_string& label, tiny_vec4& vector, float min, float max ) {
    return TinyImGui::InputSlider( label, 4, &vector.x, min, max );
}

bool TinyImGui::InputSlider( const tiny_string& label, tiny_int* scalar, tiny_int min, tiny_int max ) {
    TinyImGui::InputBegin( label );

    TINY_IMGUI_SCOPE_ID(
        auto state = ImGui::SliderInt( IMGUI_NO_LABEL, scalar, min, max );
    );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputSlider( const tiny_string& label, tiny_int& scalar, tiny_int min, tiny_int max ) {
    return TinyImGui::InputSlider( label, &scalar, min, max );
}

bool TinyImGui::InputSlider( const tiny_string& label, tiny_uint component, tiny_int* values, tiny_int min, tiny_int max ) {
    auto state = false;

    TinyImGui::InputBegin( label );

    for ( auto i = tiny_cast( 0, tiny_uint ); i < component; i++ ) {
        Internal_Input(
            i,
            [ & ]( ) { state = ImGui::SliderInt( IMGUI_NO_LABEL, &values[ i ], min, max ); }
        );
    }

    if ( component > 1 )
        Internal_Separator( );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputSlider( const tiny_string& label, tiny_point& point, tiny_int min, tiny_int max ) {
    return TinyImGui::InputSlider( label, 2, &point.x, min, max );
}

bool TinyImGui::InputColor( const tiny_string& label, float* color ) {
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

bool TinyImGui::InputColor( const tiny_string& label, tiny_color& color ) {
    return TinyImGui::InputColor( label, color.Get( ) );
}

bool TinyImGui::InputColor( const tiny_string& label, const VkClearColorValue& color ) {
    auto* _color = tiny_rvalue( color.float32[ 0 ] );

    return TinyImGui::InputColor( label, tiny_cast( _color, float* ) );
}

bool TinyImGui::InputText( tiny_uint length, char* buffer ) {
    TINY_IMGUI_SCOPE_ID(
        auto state = ImGui::InputText( IMGUI_NO_LABEL, buffer, length + 1 );
    );

    return state;
}

bool TinyImGui::Dropdown( const tiny_string& label, TinyImGui::DropdownContext& context ) {
    TinyImGui::InputBegin( label );

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

    TinyImGui::InputEnd( );

    return state; 
}

bool TinyImGui::InputVulkan( const tiny_string& label, VkFormat& format ) {
    auto context = TinyImGui::DropdownContext{
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
    auto state = TinyImGui::Dropdown( label, context );

    if ( state )
        format = tiny_cast( context.Index, VkFormat );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, const VkFormat& format ) {
    ImGui::BeginDisabled( );

    auto value = VkFormat{ format };
    auto state = TinyImGui::InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan(
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

    auto context = TinyImGui::DropdownContext{
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
    
    return TinyImGui::Dropdown( label, context );
}

bool TinyImGui::InputVulkan( const tiny_string& label, VkImageLayout& layout ) {
    auto context = TinyImGui::DropdownContext{
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
    auto state = TinyImGui::Dropdown( label, context );

    if ( state )
        layout = tiny_cast( context.Index, VkImageLayout );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, const VkImageLayout& layout ) {
    ImGui::BeginDisabled( );

    auto value = VkImageLayout{ layout };
    auto state = TinyImGui::InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, VkImageAspectFlags& aspect ) {
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

    auto context = TinyImGui::DropdownContext{
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
    auto state = TinyImGui::Dropdown( label, context );
    
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

bool TinyImGui::InputVulkan( const tiny_string& label, const VkImageAspectFlags& aspect ) {
    ImGui::BeginDisabled( );

    auto value = VkImageAspectFlags{ aspect };
    auto state = TinyImGui::InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, VkSampleCountFlagBits& samples ) {
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

    auto context = TinyImGui::DropdownContext{ sample_id, { "None", "2", "4", "8", "16", "32", "64" } };
    auto state   = TinyImGui::Dropdown( label, context );

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

bool TinyImGui::InputVulkan( const tiny_string& label, const VkSampleCountFlagBits& samples ) {
    ImGui::BeginDisabled( );

    auto value = VkSampleCountFlagBits{ samples };
    auto state = TinyImGui::InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, VkImageTiling& tiling ) {
    auto context = TinyImGui::DropdownContext{ tiny_cast( tiling, tiny_uint ), { "Optimal", "Linear" } };
    auto state   = TinyImGui::Dropdown( label, context );

    if ( state )
        tiling = tiny_cast( context.Index, VkImageTiling );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, const VkImageTiling& tiling ) {
    ImGui::BeginDisabled( );

    auto value = VkImageTiling{ tiling };
    auto state = TinyImGui::InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, TinyGraphicTextureUsages& usage ) {
    auto index = tiny_cast( 0, tiny_uint );

    switch ( usage ) {
        case TGT_USAGE_TARGET : index = 1; break;
        case TGT_USAGE_DEPTH  : index = 2; break;

        default : break;
    }

    auto context = TinyImGui::DropdownContext{ index, { "Texture", "Render Target", "Depth Target" } };
    auto state   = TinyImGui::Dropdown( label, context );

    if ( state )
        usage = tiny_cast( context.Index, TinyGraphicTextureUsages );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, const TinyGraphicTextureUsages& usage ) {
    ImGui::BeginDisabled( );

    auto value = TinyGraphicTextureUsages{ usage };
    auto state = InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, VkFilter& filter ) {
    auto context = TinyImGui::DropdownContext{ tiny_cast( filter, tiny_uint ), { "Nearest", "Linear" } };
    auto state   = TinyImGui::Dropdown( label, context );

    if ( state )
        filter = tiny_cast( context.Index, VkFilter );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, const VkFilter& filter ) {
    ImGui::BeginDisabled( );

    auto value = VkFilter{ filter };
    auto state = InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, VkSamplerMipmapMode& mipmap_mode ) {
    auto context = TinyImGui::DropdownContext{ tiny_cast( mipmap_mode, tiny_uint ), { "Nearest", "Linear" } };
    auto state   = TinyImGui::Dropdown( label, context );

    if ( state )
        mipmap_mode = tiny_cast( context.Index, VkSamplerMipmapMode );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, const VkSamplerMipmapMode& mipmap_mode ) {
    ImGui::BeginDisabled( );

    auto value = VkSamplerMipmapMode{ mipmap_mode };
    auto state = InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, TinyGraphicWrapModes& wrap_modes ) {
    auto context = TinyImGui::DropdownContext{
        tiny_cast( wrap_modes, tiny_uint ),
        {
            "Repeat",
            "Mirror Repeat",
            "Clamp To Edge",
            "Clamp To Border",
            "Clamp Mirror Edge"
        }
    };

    auto state = TinyImGui::Dropdown( label, context );

    if ( state )
        wrap_modes = tiny_cast( context.Index, TinyGraphicWrapModes );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, const TinyGraphicWrapModes& wrap_modes ) {
    ImGui::BeginDisabled( );

    auto value = TinyGraphicWrapModes{ wrap_modes };
    auto state = InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, VkCompareOp& compare_op ) {
    auto context = TinyImGui::DropdownContext{
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

    auto state = TinyImGui::Dropdown( label, context );

    if ( state )
        compare_op = tiny_cast( context.Index, VkCompareOp );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, const VkCompareOp& compare_op ) {
    ImGui::BeginDisabled( );

    auto value = VkCompareOp{ compare_op };
    auto state = InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, VkBorderColor& border_color ) {
    auto context = TinyImGui::DropdownContext{
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

    auto state = TinyImGui::Dropdown( label, context );

    if ( state )
        border_color = tiny_cast( context.Index, VkBorderColor );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, const VkBorderColor& border_color ) {
    ImGui::BeginDisabled( );

    auto value = VkBorderColor{ border_color };
    auto state = InputVulkan( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputVulkan( const tiny_string& label, VkViewport& viewport ) {
    return TinyImGui::InputVector( label, 4, tiny_rvalue( viewport.x ) );
}

bool TinyImGui::InputVulkan( const tiny_string& label, const VkViewport& viewport ) {
    ImGui::BeginDisabled( );

    auto state = TinyImGui::InputVector( label, 4, tiny_rvalue( viewport.x ) );

    ImGui::EndDisabled( );

    return state;
};

bool TinyImGui::InputVulkan( const tiny_string& label, VkScissor& scissor ) {
    return TinyImGui::InputVector( label, 4, tiny_rvalue( scissor.offset.x ) );
}

bool TinyImGui::InputVulkan( const tiny_string& label, const VkScissor& scissor ) {
    ImGui::BeginDisabled( );

    auto state = TinyImGui::InputVector( label, 4, tiny_rvalue( scissor.offset.x ) );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::Knob( const tiny_string& label, float& scalar ) {
    return TinyImGui::Knob( label, scalar, { } );
}

bool TinyImGui::Knob( const tiny_string& label, float& scalar, const KnobContext& context ) {
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

ImTextureID TinyImGui::CreateTextureID( TinyTexture2D* texture ) {
    auto texture_id = tiny_cast( nullptr, VkDescriptorSet );

    if ( texture ) {
        auto sampler = texture->GetSampler( );
        auto view    = texture->GetView( );
        
        texture_id = ImGui_ImplVulkan_AddTexture( sampler, view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL );
    }

    return tiny_cast( texture_id, ImTextureID );
}

ImTextureID TinyImGui::CreateTextureID( TinyTexture2D& texture ) {
    return CreateTextureID( tiny_rvalue( texture ) );
}

void TinyImGui::DestroyTextureID( ImTextureID& texture_id ) {
    if ( texture_id ) {
        ImGui_ImplVulkan_RemoveTexture( tiny_cast( texture_id, VkDescriptorSet ) );

        texture_id = nullptr;
    }
}

void TinyImGui::Grid( ImVec2 cursor, ImVec2 dimensions, const GridContext& context ) {
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
