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
 * @creation : 14/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyMicro/__tiny_micro_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyInputDeviceJoystick::TinyInputDeviceJoystick( )
    : m_is_present{ false },
    m_joystick{ 0 },
    m_deadzones{ .1f, .1f },
    m_news{ },
    m_olds{ }
{ }

bool TinyInputDeviceJoystick::Evaluate( const TinyInputQuery& query ) {
    auto new_button = m_news.Buttons[ query.Descriptor.Key ];
    auto old_button = m_olds.Buttons[ query.Descriptor.Key ];

    return  query.Descriptor.Type == TI_TYPE_BUTTON && 
            query.State == ProcessButton( old_button, new_button );
}

void TinyInputDeviceJoystick::Tick( ) {
    if ( PeekJoystick( ) ) {
        auto button_count = tiny_cast( 0, tiny_int );
        auto stick_count  = tiny_cast( 0, tiny_int );
        auto* buttons     = glfwGetJoystickButtons( m_joystick, tiny_rvalue( button_count ) );
        auto* sticks      = glfwGetJoystickAxes( m_joystick, tiny_rvalue( stick_count ) );

        Tiny::Memcpy( m_news, m_olds );
        Tiny::Memcpy( buttons, m_news.Buttons, tiny_min( button_count, TINY_JOYSTICK_BUTTONS ) * tiny_sizeof( bool )  );
        Tiny::Memcpy( sticks , m_news.Axis   , tiny_min( stick_count , TINY_JOYSTICK_AXIS    ) * tiny_sizeof( float ) );

        ProcessDeadzone( );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyInputDeviceJoystick::PeekJoystick( ) {
    if ( !m_is_present ) {
        m_joystick = GLFW_JOYSTICK_LAST + 1;

        while ( m_joystick-- > 0 ) {
            if ( !glfwJoystickPresent( m_joystick ) || !glfwGetJoystickName( m_joystick ) )
                continue;

            auto num_axes = 0;
            auto num_buttons = 0;

            glfwGetJoystickAxes( m_joystick, tiny_rvalue( num_axes ) );
            glfwGetJoystickButtons( m_joystick, tiny_rvalue( num_buttons ) );

            break;
        }
    } else
        m_is_present = glfwJoystickPresent( m_joystick );

    return m_is_present;
}

void TinyInputDeviceJoystick::ProcessDeadzone( ) {
    for ( auto i = 0; i < 2; i++ ) {
        auto stick = tiny_vec2{ m_news.Axis[ 2 * i ], m_news.Axis[ 2 * i + 1 ] };
        auto magnitude = stick.length( );

        if ( magnitude < m_deadzones.x ) {
            stick.x = .0f;
            stick.y = .0f;
        } else {
            auto stick_normalized = tiny_vec2{ stick.x / magnitude, stick.y / magnitude };
            auto remap_magnitude  = tiny_remap_f2( m_deadzones.x, 1.f, .0f, 1.f, (float)magnitude );

            stick = stick_normalized * remap_magnitude;

            auto deadzone_x = m_deadzones.x * fabs( stick.y );
            auto deadzone_y = m_deadzones.x * fabs( stick.x );
            auto sign       = tiny_vec2{ tiny_signf( stick.x ), tiny_signf( stick.y ) };
            auto tmp        = tiny_vec2{ .0f };

            //stick.x = .0f;
            //stick.y = .0f;

            if ( fabs( stick.x ) > deadzone_x )
                tmp.x = sign.x * tiny_remap_f2( deadzone_x, 1.f, .0f, 1.f, fabs( stick.x ) );

            if ( fabs( stick.y ) > deadzone_y )
                tmp.y = sign.y * tiny_remap_f2( deadzone_y, 1.f, .0f, 1.f, abs( stick.y ) );

            stick = tmp;
        }

        m_news.Axis[ 2 * i     ] = stick.x;
        m_news.Axis[ 2 * i + 1 ] = stick.y;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
std::optional<TinyInputJoystick> TinyInputDeviceJoystick::Get( ) const {
    if ( m_is_present ) {
        auto axis_count   = 0;
        auto button_count = 0;

        glfwGetJoystickAxes( m_joystick, tiny_rvalue( axis_count ) );
        glfwGetJoystickButtons( m_joystick, tiny_rvalue( button_count ) );

        auto joystick = TinyInputJoystick{ };

        joystick.Underlaying = m_joystick;
        joystick.Name        = glfwGetJoystickName( m_joystick );
        joystick.AxisCount   = tiny_cast( axis_count, tiny_uint );
        joystick.ButtonCount = tiny_cast( button_count, tiny_uint );
        joystick.DeadZone    = m_deadzones;

        return joystick;
    }

    return { };
}

TinyInputValue TinyInputDeviceJoystick::GetValue( const TinyInputDescriptor& descriptor ) const {
    return GetValue( descriptor.Key );
}

TinyInputValue TinyInputDeviceJoystick::GetValue( TinyInputKeys key ) const {
    auto value = TinyInputValue{ };
    
    if ( m_is_present ) {
        if ( key < TIK_GAMEPAD_BUTTON_COUNT )
            value.AsButton = ProcessButton( m_olds.Buttons[ key ], m_news.Buttons[ key ] );
        else if ( key < TIK_GAMEPAD_AXIS_SINGLE ) {
            auto axis = key - TIK_GAMEPAD_AXIS_LEFT_X;

            value.AsAxis1D = m_news.Axis[ axis ];
        } else if ( key < TIK_GAMEPAD_AXIS_DOUBLE ) {
            auto axis = 2 * ( key - TIK_GAMEPAD_AXIS_LEFT );

            value.AsAxis2D = { m_news.Axis[ axis ], m_news.Axis[ axis + 1 ] };
        }
    }

    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyInputStates TinyInputDeviceJoystick::ProcessButton( bool old_state, bool new_state ) const {
    auto value = TI_STATE_DOWN;

    if ( !old_state && !new_state )
        value = TI_STATE_UP;

    if ( !old_state &&  new_state )
        value = TI_STATE_PRESSED;

    if (  old_state && !new_state )
        value = TI_STATE_RELEASED;

    return value;
}
