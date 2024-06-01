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
 * @creation : 23/02/2024
 * @version  : 2024.2.3
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyECSEvent.h"

te_class TinyECSDispatch final {

	using CallbackList = tiny_list<native_pointer>;

private:
	tiny_list<CallbackList> m_callbacks;

public:
	TinyECSDispatch( );

	~TinyECSDispatch( ) = default;

	void Register( tiny_uint type, native_pointer callback );

	void Register( tiny_uint type, tiny_init<native_pointer> callbacks );

public:
	template<typename Event, typename... Args>
		requires tiny_is_child_of( Event, TinyECSEvent )
	void Raise( TinyGame* game, Args... args ) {
		using Signature = void(*)( TinyGame*, TinyECSEvent* );

		auto _event = Event{ args... };

		if ( _event.GetType( ) < m_callbacks.size( ) ) {
			for ( auto& callback : m_callbacks )
				std::invoke( tiny_cast( callback, Signature ), game, tiny_rvalue( _event ) );
		}
	};

};
