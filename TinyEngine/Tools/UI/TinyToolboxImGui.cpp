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

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
static c_str vec_axises[] = { "X", "Y", "Z", "W" };
static ImU32 vec_colors[] = {

    IM_COL32( 168,  46,   2, 255 ),
    IM_COL32( 112, 162,  22, 255 ),
    IM_COL32(  51, 122, 210, 255 ),
    IM_COL32( 210, 183,  51, 255 )

};

ImVec2 Internal_CalcTextSize( c_str text ) { 
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

TinyImGui::DropdownContext::DropdownContext( tiny_init<c_str> values )
    : Index{ 0 },
    Values{ values }
{ }

TinyImGui::DropdownContext::DropdownContext(
    tiny_init<c_str> values,
    const tiny_string& value
) : DropdownContext{ values, tiny_hash{ value } }
{ }

TinyImGui::DropdownContext::DropdownContext( 
    tiny_init<c_str> values, 
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

bool TinyImGui::RightButton( const tiny_string& label ) {
    auto offset = Internal_CalcTextSize( "############" ).x;
    auto cursor = ImGui::GetCursorPosX( ) + ImGui::GetContentRegionAvail( ).x;

    ImGui::SetCursorPosX( cursor - offset );

    return ImGui::Button( label.get( ), { -1.f, .0f } );
}

void TinyImGui::Text( const tiny_string& text ) { ImGui::Text( text.get( ) ); }

void TinyImGui::Text( const std::string_view& text ) { ImGui::Text( text.data( ) ); }

void TinyImGui::BeginVars( ) {
    auto size = Internal_CalcTextSize( "################" ).x;

    ImGui::Columns( 2 );
    ImGui::SetColumnWidth( 0, size );
}

void TinyImGui::EndVars( ) { ImGui::EndColumns( ); }

void TinyImGui::InputBegin( const tiny_string& label ) {
    const auto* name = label.get( );

    ImGui::TableSetColumnIndex( 0 );
    ImGui::AlignTextToFramePadding( );
    ImGui::TextUnformatted( name );
    ImGui::NextColumn( );
    ImGui::PushItemWidth( -1 );
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
        auto state = ImGui::InputInt( IMGUI_NO_LABEL, &scalar );
    );

    TinyImGui::InputEnd( );

    return state;
}

bool TinyImGui::InputScalar( const tiny_string& label, const tiny_int& scalar ) {
    ImGui::BeginDisabled( );

    auto value = tiny_cast( scalar, tiny_int );
    auto state = InputScalar( label, value );

    ImGui::EndDisabled( );

    return state;
}

bool TinyImGui::InputScalar( const tiny_string& label, tiny_uint& scalar ) {
    TinyImGui::InputBegin( label );

    TINY_IMGUI_SCOPE_ID(
        auto state = ImGui::InputScalar( IMGUI_NO_LABEL, ImGuiDataType_U32, &scalar );
    );
    
    TinyImGui::InputEnd( );

    return false;
}

bool TinyImGui::InputScalar( const tiny_string& label, const tiny_uint& scalar ) {
    ImGui::BeginDisabled( );

    auto value = tiny_cast( scalar, tiny_uint );
    auto state = InputScalar( label, value );

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
    auto state = InputScalar( label, value );

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

bool TinyImGui::InputPoint( const tiny_string& label, tiny_point& point ) {
    return TinyImGui::InputVector( label, 2, &point.x );
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

bool TinyImGui::InputVec2( const tiny_string& label, tiny_vec2& vector ) {
    return TinyImGui::InputVector( label, 2, &vector.x );
}

bool TinyImGui::InputVec3( const tiny_string& label, tiny_vec3& vector ) {
    return TinyImGui::InputVector( label, 3, &vector.x );
}

bool TinyImGui::InputVec4( const tiny_string& label, tiny_vec4& vector ) {
    return TinyImGui::InputVector( label, 4, &vector.x );
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

bool TinyImGui::Dropdown( const tiny_string& label, TinyImGui::DropdownContext& context ) {
    TinyImGui::InputBegin( label );

    ImGui::BeginDisabled( context.Values.size( ) < 2 );
    TINY_IMGUI_SCOPE_ID(
        auto state = ImGui::Combo( 
            IMGUI_NO_LABEL, 
            &context.Index, 
            context.Values.data( ),
            context.Values.size( ) 
        );
    ); 
    ImGui::EndDisabled( );

    TinyImGui::InputEnd( );

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
