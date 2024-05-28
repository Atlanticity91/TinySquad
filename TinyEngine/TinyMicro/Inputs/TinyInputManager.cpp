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
	: _is_active{ true },
	_timestep{ },
	_map{ },
	_devices{ }
{ }

bool TinyInputManager::Initialize( TinyFilesystem& file_system, TinyWindow& window ) {
	_timestep.Initialize( );

	return true;
}

void TinyInputManager::Lock( ) { _is_active = false; }

void TinyInputManager::UnLock( ) { _is_active = true; }

void TinyInputManager::Toggle( bool state ) { _is_active = state; }

void TinyInputManager::Clear( ) { _map.Clear( ); }

void TinyInputManager::Register(
	const tiny_string& input_alias, 
	tiny_init<TinyInputQuery> querys 
) {
	_map.Register( input_alias, querys );
}

void TinyInputManager::Register( 
	const tiny_string& input_alias, 
	const tiny_list<TinyInputQuery>& querys 
) {
	_map.Register( input_alias, querys );
}

void TinyInputManager::Lock( const tiny_string& input_alias ) {
	auto input_hash = tiny_hash{ input_alias };

	_map.Lock( input_hash );
}

void TinyInputManager::UnLock( const tiny_string& input_alias ) {
	auto input_hash = tiny_hash{ input_alias };

	_map.UnLock( input_hash );
}

void TinyInputManager::Toggle( const tiny_string& input_alias, bool state ) {
	auto input_hash = tiny_hash{ input_alias };

	if ( state )
		_map.UnLock( input_hash );
	else
		_map.Lock( input_hash );
}

void TinyInputManager::Notify( const TinyInputNotification& notification ) {
	_devices.Notify( notification );
}

bool TinyInputManager::Evaluate( const tiny_string& input_alias, bool consume ) {
	auto state = _is_active;

	if ( state ) {
		state = false;

		auto input_hash = tiny_hash{ input_alias };
		auto* queries   = _map.Query( input_hash );

		if ( 
			queries != nullptr			&& 
			queries->IsActive			&& 
			queries->Values.size( ) > 0 && 
			!queries->IsConsumed 
		) {
			for ( const auto& query : queries->Values ) {
				state = _devices.Evaluate( query );

				if ( state ) {
					queries->IsConsumed = consume;

					break;
				}
			}
		}
	}

	return state;
}


void TinyInputManager::Erase( const tiny_string& input ) { _map.Erase( input ); }

void TinyInputManager::Tick( ) {
	_timestep.Tick( );
	_map.Tick( );
	_devices.Tick( );
}

void TinyInputManager::Terminate( TinyFilesystem& file_system, TinyWindow& window ) { }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyInputManager::GetIsActive( ) const { return _is_active; }

const TinyTimestep& TinyInputManager::GetTimestep( ) const { return _timestep; }

tiny_map<TinyInputQueries>& TinyInputManager::GetMap( ) { return _map.Get( ); }

const tiny_map<TinyInputQueries>& TinyInputManager::GetMap( ) const { return _map.Get( ); }

bool TinyInputManager::Find( tiny_string input_alias ) const {
	auto input_hash = tiny_hash{ input_alias };

	return _map.Find( input_hash );
}

tiny_vec2 TinyInputManager::GetCursor( ) const { return _devices.GetCursor( ); }

tiny_vec2 TinyInputManager::GetScroll( ) const { return _devices.GetScroll( ); }

std::optional<TinyInputJoystick> TinyInputManager::Get( ) const { 
	return _devices.GetJoystick( ); 
}

TinyInputValue TinyInputManager::GetValue( const TinyInputDescriptor& descriptor ) const {
	return _devices.GetValue( descriptor );
}

TinyInputValue TinyInputManager::GetValue( TinyInputDevices device, TinyInputKeys key ) const {
	return _devices.GetValue( device, key );
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
