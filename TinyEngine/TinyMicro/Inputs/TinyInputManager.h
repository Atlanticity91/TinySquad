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
 * @creation : 11/10/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "Devices/TinyInputDeviceManager.h"

tm_class TinyInputManager final : tiny_inherit( ITinyManager ) {

private:
	bool				   _is_active;
	TinyTimestep		   _timestep;
	TinyInputMap		   _map;
	TinyInputDeviceManager _devices;

public:
	TinyInputManager( );

	~TinyInputManager( ) = default;

	tiny_implement( bool Initialize( TinyFilesystem& file_system, TinyWindow& window ) );

	void Lock( );

	void UnLock( );

	void Toggle( bool state );

	tiny_inline void Clear( );

	tiny_inline void Register( 
		const tiny_string& input_alias, 
		tiny_init<TinyInputQuery> querys 
	);

	tiny_inline void Register( 
		const tiny_string& input_alias, 
		const tiny_list<TinyInputQuery>& querys 
	);

	tiny_inline void Lock( const tiny_string& input_alias );

	tiny_inline void UnLock( const tiny_string& input_alias );

	void Toggle( const tiny_string& input_alias, bool state );

	tiny_inline void Notify( const TinyInputNotification& notification );

	bool Evaluate( const tiny_string& input_alias, bool consume );

	void Erase( const tiny_string& input );

	void Tick( );

	tiny_implement( void Terminate( TinyFilesystem& file_system, TinyWindow& window ) );

public:
	bool GetIsActive( ) const;

	const TinyTimestep& GetTimestep( ) const;

	tiny_map<TinyInputQueries>& GetMap( );

	const tiny_map<TinyInputQueries>& GetMap( ) const;

	bool Find( tiny_string input_alias ) const;

	tiny_inline tiny_vec2 GetCursor( ) const;

	tiny_inline tiny_vec2 GetScroll( ) const;

	tiny_inline std::optional<TinyInputJoystick> Get( ) const;

	tiny_inline TinyInputValue GetValue( const TinyInputDescriptor& descriptor ) const;

	tiny_inline TinyInputValue GetValue( TinyInputDevices device, TinyInputKeys key ) const;

	tiny_inline bool GetButton( const TinyInputDescriptor& descriptor ) const;

	bool GetButton( bool& button, const TinyInputDescriptor& descriptor ) const;

	tiny_inline float GetAxis1D( const TinyInputDescriptor& descriptor ) const;

	bool GetAxis1D( float& axis_1d, const TinyInputDescriptor& descriptor ) const;

	tiny_inline tiny_vec2 GetAxis2D( const TinyInputDescriptor& descriptor ) const;

	bool GetAxis2D( tiny_vec2& axis_2d, const TinyInputDescriptor& descriptor ) const;

};
