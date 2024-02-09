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
 * @creation : 08/02/2024
 * @version  : 2024.1.3
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyYaml.h"

#define _nRegisterFunc( FUNC ) Register( TINY_STR( FUNC ), FUNC )
#define _nExecute Execute<void>

te_class TinyNativeRegister final {

	template<typename Type>
	using return_type = typename std::conditional<( !std::is_same<Type, void>::value ), std::optional<Type>, bool>::type;

private:
	tiny_map<c_pointer> _functions;

public:
	TinyNativeRegister( );

	~TinyNativeRegister( ) = default;

	void Register( const tiny_string& alias, const c_pointer function );

	void Remove( const tiny_string& function_alias );

	void Remove( const tiny_hash function_hash );

public:
	template<typename Return, typename... Args>
		requires ( !std::is_reference<Return>::value )
	return_type<Return> Execute(
		const tiny_string& function_alias,
		TinyGame* game,
		Args... args
	) {
		auto function_hash = tiny_hash{ function_alias };

		return Execute<Return, Args...>( function_hash, game, args... );
	};

	template<typename Return, typename... Args>
		requires ( !std::is_reference<Return>::value )
	return_type<Return> Execute( const tiny_hash function_hash, TinyGame* game, Args... args ) {
		using Signature = Return(*)( TinyGame*, Args... );

		auto function_id = tiny_cast( 0, tiny_uint );

		if constexpr ( std::is_same<Return, void>::value ) { 
			auto state = _functions.find( function_hash, function_id );

			if ( state ) {
				auto* function = tiny_cast( _functions.at( function_id ), Signature );

				std::invoke( function, game, args... );
			}

			return state;
		} else {
			if ( _functions.find( function_hash, function_id ) ) {
				auto* function = tiny_cast( _functions.at( function_id ), Signature );

				return std::invoke( function, game, args... );
			}

			return { };
		}
	};

public:
	bool GetExist( const tiny_string& function_alias ) const;

	bool GetExist( const tiny_hash function_hash ) const;

	tiny_map<c_pointer>& GetNatives( );

	const tiny_map<c_pointer>& GetNatives( ) const;

};
