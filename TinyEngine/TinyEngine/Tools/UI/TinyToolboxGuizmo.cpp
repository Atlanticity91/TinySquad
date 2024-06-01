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
 * @creation : 02/02/2024
 * @version  : 2024.1.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyToolboxGuizmo::TinyToolboxGuizmo( )
    : m_selection{ },
    m_is_orthographic{ false },
    m_use_snap{ false },
    m_mode{ TG_MODE_WORLD },
    m_tool{ TGT_TRANSLATE_2D },
    m_snap_translate{ 1.f },
    m_snap_rotate{ 1.f },
    m_snap_scale{ 1.f },
    m_modes{
        "Local", "World"
    },
    m_tools{
        2, 
        {
            "Translate X",
            "Translate Y",
            "Translate 2D",
            "Rotate 2D",
            "Scale X",
            "Scale Y",
            "Scale 2D"
        }
    }
{ }

void TinyToolboxGuizmo::SetGuizmoMode( TinyGuizmoModes mode ) { m_mode = mode; }

void TinyToolboxGuizmo::SetGuizmoTool( TinyGuizmoTools tool ) { m_tool = tool; }

void TinyToolboxGuizmo::SetGuizmo( TinyGuizmoModes mode, TinyGuizmoTools tool ) {
    m_mode = mode;
    m_tool = tool;
}

void TinyToolboxGuizmo::Show( 
    const tiny_hash entity_hash,
    bool is_orthographic
) {
    m_selection       = entity_hash; 
    m_is_orthographic = is_orthographic;
}

void TinyToolboxGuizmo::Hide( ) { m_selection.undefined( ); }

void TinyToolboxGuizmo::DrawWidget( ) {
    TinyImGui::BeginVars( );

    m_modes.Index = m_mode;
    if ( TinyImGui::Dropdown( "Mode", m_modes ) )
        m_mode = m_modes.Index;

    if ( TinyImGui::Dropdown( "Tool", m_tools ) )
        m_tool = PeekTool( m_tools.Index );

    TinyImGui::SeparatorText( "Snap Targets" );
    TinyImGui::Checkbox( "Use Snap", m_use_snap );

    TinyImGui::InputVec3( "Translate", m_snap_translate );
    TinyImGui::InputVec3( "Rotate", m_snap_rotate );
    TinyImGui::InputVec3( "Scale", m_snap_scale );

    TinyImGui::EndVars( );
}

void TinyToolboxGuizmo::DrawUI( TinyGame* game ) {
    auto& ecs = game->GetECS( );

    if ( ecs.GetIsAlive( m_selection ) ) {
        auto* snap_target = PeekSnapTarget( );
        auto& io          = ImGui::GetIO( );
        auto& renderer    = game->GetRenderer( );
        auto& cameras     = renderer.GetCurrentCamera( );
        auto* transform   = ecs.GetComponentAs<TinyTransform2D>( m_selection );
        auto& view        = cameras.Get( );
        auto proj         = tiny_mat4{ renderer.GetCurrentProjection( ) };
        auto matrix       = transform->GetTransform( );

        ImGuizmo::BeginFrame( );
        ImGuizmo::SetOrthographic( m_is_orthographic );
        ImGuizmo::SetRect( .0f, -io.DisplaySize.y, io.DisplaySize.x, io.DisplaySize.y );

        proj[ 1 ][ 1 ] *= -1.f;

        if (
            ImGuizmo::Manipulate(
            glm::value_ptr( view ),
            glm::value_ptr( proj ),
            tiny_cast( m_tool, ImGuizmo::OPERATION ),
            tiny_cast( m_mode, ImGuizmo::MODE ),
            glm::value_ptr( matrix ),
            nullptr,
            snap_target,
            nullptr
            )
        )
            ApplyManipulation( transform, matrix );
    } else
        m_selection.undefined( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyToolboxGuizmo::ApplyManipulation( TinyTransform2D* transform, tiny_mat4& matrix ) {
    auto* grab_signature = PeekGrabSignature( );
    auto grab_result     = std::invoke( grab_signature, matrix );
    auto half_scale      = transform->GetHalfScale( );

    switch ( m_tool ) {
        case TGT_TRANSLATE_X  : transform->SetLocationX( grab_result.x - half_scale.x ); break;
        case TGT_TRANSLATE_Y  : transform->SetLocationY( grab_result.y - half_scale.y ); break;
        case TGT_TRANSLATE_2D : 
            transform->SetLocation( grab_result.x - half_scale.x, grab_result.y - half_scale.y ); 
            break;

        case TGT_ROTATE_2D : transform->SetRotation( grab_result.z ); break;

        case TGT_SCALE_X  : transform->SetScaleX( grab_result.x ); break;
        case TGT_SCALE_Y  : transform->SetScaleY( grab_result.x ); break;
        case TGT_SCALE_2D : transform->SetScale( grab_result.x, grab_result.y ); break;

        default : break;
    }

    transform->ReCalculate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
const tiny_hash TinyToolboxGuizmo::GetSelection( ) const { return m_selection; }

TinyGuizmoModes TinyToolboxGuizmo::GetMode( ) const { 
    return tiny_cast( m_mode, TinyGuizmoModes ); 
}

TinyGuizmoTools TinyToolboxGuizmo::GetTool( ) const { 
    return tiny_cast( m_tool, TinyGuizmoTools ); 
}

tiny_vec3& TinyToolboxGuizmo::GetSnapTranslate( ) { return m_snap_translate; }

tiny_vec3& TinyToolboxGuizmo::GetSnapRotate( ) { return m_snap_rotate; }

tiny_vec3& TinyToolboxGuizmo::GetSnapScale( ) { return m_snap_scale; }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
tiny_uint TinyToolboxGuizmo::PeekTool( tiny_uint selection ) {
    auto tool = tiny_cast( 0, tiny_uint );
    
    switch ( selection ) {
        case 0 : tool = TGT_TRANSLATE_X;  break;
        case 1 : tool = TGT_TRANSLATE_Y;  break;
        case 2 : tool = TGT_TRANSLATE_2D; break;
        case 3 : tool = TGT_ROTATE_2D;    break;
        case 4 : tool = TGT_SCALE_X;      break;
        case 5 : tool = TGT_SCALE_Y;      break;
        case 6 : tool = TGT_SCALE_2D;     break;

        default : break;
    }

    return tool;
}

float* TinyToolboxGuizmo::PeekSnapTarget( ) {
    auto* snap_target = tiny_cast( nullptr, float* );

    switch ( m_tool ) {
        case TGT_TRANSLATE_X  :
        case TGT_TRANSLATE_Y  :
        case TGT_TRANSLATE_2D : snap_target = tiny_rvalue( m_snap_translate.x ); break;

        case TGT_ROTATE_2D : snap_target = tiny_rvalue( m_snap_rotate.x ); break;

        case TGT_SCALE_X  : 
        case TGT_SCALE_Y  :
        case TGT_SCALE_2D : snap_target = tiny_rvalue( m_snap_scale.x ); break;

        default : break;
    }

    return snap_target;
}

TinyMath::GrabSignature TinyToolboxGuizmo::PeekGrabSignature( ) {
    auto grab_signature = tiny_cast( nullptr, TinyMath::GrabSignature );

    switch ( m_tool ) {
        case TGT_TRANSLATE_X  :
        case TGT_TRANSLATE_Y  :
        case TGT_TRANSLATE_2D : grab_signature = &TinyMath::GrabTransform; break;

        case TGT_ROTATE_2D : grab_signature = &TinyMath::GrabRotation; break;

        case TGT_SCALE_X  :
        case TGT_SCALE_Y  :
        case TGT_SCALE_2D : grab_signature = &TinyMath::GrabScale; break;

        default: break;
    }

    return grab_signature;
}
