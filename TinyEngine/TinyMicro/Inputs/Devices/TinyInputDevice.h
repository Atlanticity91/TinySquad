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

#pragma once

#include <TinyMicro/Inputs/Mappings/TinyInputMap.h>

template<typename KeyMeta, tiny_uint KeyCount>
tm_abstract_class TinyInputDevice {

	const tiny_uint MetaSize = tiny_sizeof( KeyMeta ) * KeyCount;

protected:
	KeyMeta m_news[ KeyCount ];
	KeyMeta m_olds[ KeyCount ];

public:
	TinyInputDevice( )
		: m_news{ },
		m_olds{ } 
	{ };

	virtual ~TinyInputDevice( ) = default;

	tiny_abstract( void Notify( const TinyInputNotification& notification ) );

	tiny_abstract( bool Evaluate( const TinyInputQuery& query ) );

	virtual void Tick( ) { Tiny::Memcpy( m_news, m_olds, MetaSize ); };

public:
	tiny_abstract( TinyInputValue GetValue( const TinyInputDescriptor& descriptor ) const );

	tiny_abstract( TinyInputValue GetValue( TinyInputKeys key ) const );

protected:
	TinyInputStates ProcessButton( bool old_state, bool new_state ) const { 
		auto value = TI_STATE_DOWN;

		if ( !old_state && !new_state )
			value = TI_STATE_UP;

		if ( !old_state && new_state )
			value = TI_STATE_PRESSED;

		if ( old_state && !new_state )
			value = TI_STATE_RELEASED;

		return value;
	};

};
