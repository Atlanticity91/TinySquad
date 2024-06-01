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
 * @creation : 13/10/2023
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
TinyInputManager::TinyInputManager( )
	: m_is_active{ true },
	m_timestep{ },
	m_map{ },
	m_devices{ }
{ }

bool TinyInputManager::Initialize( TinyFilesystem& file_system, TinyWindow& window ) {
	m_timestep.Initialize( );

	return true;
}

void TinyInputManager::Lock( ) { m_is_active = false; }

void TinyInputManager::UnLock( ) { m_is_active = true; }

void TinyInputManager::Toggle( bool state ) { m_is_active = state; }

void TinyInputManager::Clear( ) { m_map.Clear( ); }

void TinyInputManager::Register(
	const tiny_string& input_alias, 
	tiny_init<TinyInputQuery> querys 
) {
	m_map.Register( input_alias, querys );
}

void TinyInputManager::Register( 
	const tiny_string& input_alias, 
	const tiny_list<TinyInputQuery>& querys 
) {
	m_map.Register( input_alias, querys );
}

void TinyInputManager::Lock( const tiny_string& input_alias ) {
	auto input_hash = tiny_hash{ input_alias };

	m_map.Lock( input_hash );
}

void TinyInputManager::UnLock( const tiny_string& input_alias ) {
	auto input_hash = tiny_hash{ input_alias };

	m_map.UnLock( input_hash );
}

void TinyInputManager::Toggle( const tiny_string& input_alias, bool state ) {
	auto input_hash = tiny_hash{ input_alias };

	if ( state )
		m_map.UnLock( input_hash );
	else
		m_map.Lock( input_hash );
}

void TinyInputManager::Notify( const TinyInputNotification& notification ) {
	m_devices.Notify( notification );
}

bool TinyInputManager::Evaluate( const tiny_string& input_alias, bool consume ) {
	auto state = m_is_active;

	if ( state ) {
		state = false;

		auto input_hash = tiny_hash{ input_alias };
		auto* queries   = m_map.Query( input_hash );

		if ( 
			queries != nullptr			&& 
			queries->IsActive			&& 
			queries->Values.size( ) > 0 && 
			!queries->IsConsumed 
		) {
			for ( const auto& query : queries->Values ) {
				state = m_devices.Evaluate( query );

				if ( state ) {
					queries->IsConsumed = consume;

					break;
				}
			}
		}
	}

	return state;
}

void TinyInputManager::Erase( const tiny_string& input ) { m_map.Erase( input ); }

void TinyInputManager::Tick( ) {
	m_timestep.Tick( );
	m_map.Tick( );
	m_devices.Tick( );
}

void TinyInputManager::Terminate( TinyFilesystem& file_system, TinyWindow& window ) { }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyInputManager::GetIsActive( ) const { return m_is_active; }

const TinyTimestep& TinyInputManager::GetTimestep( ) const { return m_timestep; }

tiny_map<TinyInputQueries>& TinyInputManager::GetMap( ) { return m_map.Get( ); }

const tiny_map<TinyInputQueries>& TinyInputManager::GetMap( ) const { return m_map.Get( ); }

bool TinyInputManager::Find( tiny_string input_alias ) const {
	auto input_hash = tiny_hash{ input_alias };

	return m_map.Find( input_hash );
}

tiny_vec2 TinyInputManager::GetCursor( ) const { return m_devices.GetCursor( ); }

tiny_vec2 TinyInputManager::GetScroll( ) const { return m_devices.GetScroll( ); }

std::optional<TinyInputJoystick> TinyInputManager::Get( ) const { 
	return m_devices.GetJoystick( ); 
}

TinyInputValue TinyInputManager::GetValue( const TinyInputDescriptor& descriptor ) const {
	return m_devices.GetValue( descriptor );
}

TinyInputValue TinyInputManager::GetValue( TinyInputDevices device, TinyInputKeys key ) const {
	return m_devices.GetValue( device, key );
}

bool TinyInputManager::GetButton( const TinyInputDescriptor& descriptor ) const {
	return GetValue( descriptor ).AsButton;
}

bool TinyInputManager::GetButton( bool& button, const TinyInputDescriptor& descriptor ) const {
	button = GetButton( descriptor );

	return descriptor.Type == TI_TYPE_BUTTON;
}

float TinyInputManager::GetAxis1D( const TinyInputDescriptor& descriptor ) const {
	return GetValue( descriptor ).AsAxis1D;
}

bool TinyInputManager::GetAxis1D( float& axis_1d, const TinyInputDescriptor& descriptor ) const {
	axis_1d = GetAxis1D( descriptor );

	return descriptor.Type == TI_TYPE_AXIS_1D;
}

tiny_vec2 TinyInputManager::GetAxis2D( const TinyInputDescriptor& descriptor ) const {
	return GetValue( descriptor ).AsAxis2D;
}

bool TinyInputManager::GetAxis2D( tiny_vec2& axis_2d, const TinyInputDescriptor& descriptor ) const {
	axis_2d = GetAxis2D( descriptor );

	return descriptor.Type == TI_TYPE_AXIS_2D;
}
