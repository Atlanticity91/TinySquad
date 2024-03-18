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
 * @creation : 13/11/2023
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyComponent::TinyComponent( )
	: TinyComponent{ { } }
{ }

TinyComponent::TinyComponent( const tiny_hash owner )
	: _is_active{ true },
	_owner{ owner } 
{ }

void TinyComponent::Enable( TinyGame* game ) {
	if ( !_is_active ) {
		_is_active = true;

		OnEnable( game );
	}
}

void TinyComponent::Disable( TinyGame* game ) {
	if ( _is_active ) {
		_is_active = false;

		OnDisable( game );
	}
}

void TinyComponent::Toggle( TinyGame* game ) {
	if ( _is_active )
		Disable( game );
	else
		Enable( game );
}

void TinyComponent::DisplayWidget( TinyGame* game, TinyToolbox& toolbox ) {
	TinyImGui::Checkbox( "Is Active", _is_active );

	ImGui::Separator( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyComponent::GetIsActive( ) const { return _is_active; }

tiny_hash TinyComponent::GetOwner( ) const { return _owner; }
