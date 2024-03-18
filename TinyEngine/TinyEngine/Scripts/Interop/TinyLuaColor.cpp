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
 * @creation : 12/01/2024
 * @version  : 2024.2
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include <TinyEngine/__tiny_engine_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
#define TINY_COLOR_NAME "TinyColor"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
tli_implementfn( TinyLua::Color::New ) {
	auto param_count = lua_gettop( context );
	auto r = lua_Number{ 0.0 };
	auto g = lua_Number{ 0.0 };
	auto b = lua_Number{ 0.0 };
	auto a = lua_Number{ 1.0 };

	if ( param_count == 1 && lua_istable( context, tli_param_one ) ) {
		tli_get_field( tli_param_one, "r", r );
		tli_get_field( tli_param_one, "g", g );
		tli_get_field( tli_param_one, "b", b );
		tli_get_field( tli_param_one, "a", a );
	} else if ( param_count == 1 && lua_isnumber( context, tli_param_one ) ) {
		r = lua_tonumber( context, tli_param_one );
		g = r;
		b = r;
		a = r;
	} else if (
		param_count == 2					   &&
		lua_isnumber( context, tli_param_one ) &&
		lua_isnumber( context, tli_param_two )
	) {
		r = lua_tonumber( context, tli_param_one );
		g = r;
		b = r;
		a = lua_tonumber( context, tli_param_two );
	} else if (
		param_count == 4						 &&
		lua_isnumber( context, tli_param_one )   &&
		lua_isnumber( context, tli_param_two )   &&
		lua_isnumber( context, tli_param_three ) &&
		lua_isnumber( context, tli_param_four )
	) {
		r = lua_tonumber( context, tli_param_one );
		g = lua_tonumber( context, tli_param_two );
		b = lua_tonumber( context, tli_param_three );
		a = lua_tonumber( context, tli_param_two );
	}

	Create( context, r, g, b, a );

	return 1;
}

tli_implementfn( TinyLua::Color::Delete ) { return 0; }

tli_implementfn( TinyLua::Color::Clone ) {
	if ( lua_istable( context, tli_param_one ) ) {
		auto r = lua_Number{ };
		auto g = lua_Number{ };
		auto b = lua_Number{ };
		auto a = lua_Number{ };

		tli_get_field( tli_self, "r", r );
		tli_get_field( tli_self, "g", g );
		tli_get_field( tli_self, "b", b );
		tli_get_field( tli_self, "a", a );

		TinyLua::Color::Create( context, r, g, b, a );
	} else
		lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Color::SetR ) {
	if ( 
		lua_istable( context, tli_param_one ) &&
		lua_isnumber( context, tli_param_two )
	)
		tli_set_field( "r", lua_tonumber( context, tli_param_two ) );

	return 0;
}

tli_implementfn( TinyLua::Color::SetG ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_isnumber( context, tli_param_two )
	)
		tli_set_field( "g", lua_tonumber( context, tli_param_two ) );

	return 0;
}

tli_implementfn( TinyLua::Color::SetB ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_isnumber( context, tli_param_two )
	)
		tli_set_field( "b", lua_tonumber( context, tli_param_two ) );

	return 0;
}

tli_implementfn( TinyLua::Color::SetA ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_isnumber( context, tli_param_two )
	)
		tli_set_field( "a", lua_tonumber( context, tli_param_two ) );

	return 0;
}

tli_implementfn( TinyLua::Color::Set ) {
	auto param_count = lua_gettop( context );

	if ( lua_istable( context, tli_param_one ) ) {
		if ( param_count == 2 && lua_istable( context, tli_param_two ) ) {
			c_string channels[ 4 ] = { "r", "g", "b", "a" };

			auto value = lua_Number{ };

			for ( auto channel : channels ) {
				tli_get_field( tli_param_two, channel, value );
				tli_set_field( channel, value );
			}
		} else if ( param_count == 2 && lua_isnumber( context, tli_param_two ) ) {
			c_string channels[ 4 ] = { "r", "g", "b", "a" };

			auto value = lua_tonumber( context, tli_param_two );

			for ( auto channel : channels ) 
				tli_set_field( channel, value );
		} else if ( 
			param_count == 5 &&
			lua_isnumber( context, tli_param_two )   &&
			lua_isnumber( context, tli_param_three ) &&
			lua_isnumber( context, tli_param_four )  &&
			lua_isnumber( context, tli_param_five )
		) {
			tli_set_field( "r", lua_tonumber( context, tli_param_two ) );
			tli_set_field( "g", lua_tonumber( context, tli_param_three ) );
			tli_set_field( "b", lua_tonumber( context, tli_param_four ) );
			tli_set_field( "a", lua_tonumber( context, tli_param_five ) );
		}
	}

	return 0;
}

tli_implementfn( TinyLua::Color::Add ) {
	if ( lua_istable( context, tli_param_one ) ) {
		c_string channels[ 4 ] = { "r", "g", "b", "a" };
		
		auto value_1 = lua_Number{ };

		if ( lua_istable( context, tli_param_two ) ) {
			auto value_2 = lua_Number{ };

			for ( auto channel : channels ) {
				tli_get_field( tli_param_one, channel, value_1 );
				tli_get_field( tli_param_two, channel, value_2 );
				tli_set_field( channel, value_1 + value_2 );
			}
		} else if ( lua_isnumber( context, tli_param_two ) ) {
			auto value_2 = lua_tonumber( context, tli_param_two );

			for ( auto channel : channels ) {
				tli_get_field( tli_param_one, channel, value_1 );
				tli_set_field( channel, value_1 + value_2 );
			}
		}
	}

	return 0;
}

tli_implementfn( TinyLua::Color::Sub ) {
	if ( lua_istable( context, tli_param_one ) ) {
		c_string channels[ 4 ] = { "r", "g", "b", "a" };

		auto value_1 = lua_Number{ };

		if ( lua_istable( context, tli_param_two ) ) {
			auto value_2 = lua_Number{ };

			for ( auto channel : channels ) {
				tli_get_field( tli_param_one, channel, value_1 );
				tli_get_field( tli_param_two, channel, value_2 );
				tli_set_field( channel, value_1 - value_2 );
			}
		} else if ( lua_isnumber( context, tli_param_two ) ) {
			auto value_2 = lua_tonumber( context, tli_param_two );

			for ( auto channel : channels ) {
				tli_get_field( tli_param_one, channel, value_1 );
				tli_set_field( channel, value_1 - value_2 );
			}
		}
	}

	return 0;
}

tli_implementfn( TinyLua::Color::Lerp ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_istable( context, tli_param_two ) &&
		lua_isnumber( context, tli_param_three )
	) {
		auto scalar   = lua_tonumber( context, tli_param_three );
		auto scalar_n = 1.0 - scalar;
		auto r_1	  = lua_Number{ };
		auto g_1	  = lua_Number{ };
		auto b_1	  = lua_Number{ };
		auto a_1	  = lua_Number{ };
		auto r_2	  = lua_Number{ };
		auto g_2	  = lua_Number{ };
		auto b_2	  = lua_Number{ };
		auto a_2	  = lua_Number{ };

		tli_get_field( tli_param_one, "r", r_1 );
		tli_get_field( tli_param_two, "r", r_2 );
		tli_get_field( tli_param_one, "r", g_1 );
		tli_get_field( tli_param_two, "r", g_2 );
		tli_get_field( tli_param_one, "r", b_1 );
		tli_get_field( tli_param_two, "r", b_2 );
		tli_get_field( tli_param_one, "r", a_1 );
		tli_get_field( tli_param_two, "r", a_2 );

		Create( 
			context, 
			r_1 * scalar_n + scalar * r_2,
			g_1 * scalar_n + scalar * g_2,
			b_1 * scalar_n + scalar * b_2,
			a_1 * scalar_n + scalar * a_2
		);
	} else
		lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Color::Interpolate ) {
	return 0;
}

tli_implementfn( TinyLua::Color::ToVec3 ) {
	if ( lua_istable( context, tli_self ) ) {
		auto r = lua_Number{ };
		auto g = lua_Number{ };
		auto b = lua_Number{ };

		tli_get_field( tli_self, "r", r );
		tli_get_field( tli_self, "g", g );
		tli_get_field( tli_self, "b", b );

		TinyLua::Vec3::Create( context, r, g, b );
	} else
		lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Color::ToVec4 ) {
	if ( lua_istable( context, tli_self ) ) {
		auto r = lua_Number{ };
		auto g = lua_Number{ }; 
		auto b = lua_Number{ }; 
		auto a = lua_Number{ };

		tli_get_field( tli_self, "r", r );
		tli_get_field( tli_self, "g", g );
		tli_get_field( tli_self, "b", b );
		tli_get_field( tli_self, "a", a );

		TinyLua::Vec4::Create( context, r, g, b, a );
	} else
		lua_pushnil( context );

	return 1;
}

tli_implementfn( TinyLua::Color::ToString ) {
	if ( lua_istable( context, tli_self ) ) {
		auto r = lua_Number{ };
		auto g = lua_Number{ };
		auto b = lua_Number{ };
		auto a = lua_Number{ };
		
		tli_get_field( tli_self, "r", r );
		tli_get_field( tli_self, "g", g );
		tli_get_field( tli_self, "b", b );
		tli_get_field( tli_self, "a", a );

		lua_pushfstring( 
			context, "[ %f, %f, %f, %f ]", 
			tiny_cast( r, float ), 
			tiny_cast( g, float ),
			tiny_cast( b, float ),
			tiny_cast( a, float )
		);
	} else
		lua_pushfstring( context, "" );

	return 1;
}

tli_implementfn( TinyLua::Color::Equal ) {
	if ( 
		lua_istable( context, tli_param_one ) && 
		lua_istable( context, tli_param_two )
	) {
		c_string channels[ 4 ] = { "r", "g", "b", "a" };

		auto state = true;
		auto col_0 = lua_Number{ };
		auto col_1 = lua_Number{ };

		for ( auto channel : channels ) {
			tli_get_field( tli_param_one, channel, col_0 );
			tli_get_field( tli_param_two, channel, col_1 );

			state = col_0 == col_1;

			if ( !state ) break;
		}
		
		lua_pushboolean( context, state );
	} else
		lua_pushboolean( context, false );

	return 1;
}

tli_implementfn( TinyLua::Color::Less ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_istable( context, tli_param_two )
	) {
		c_string channels[ 4 ] = { "r", "g", "b", "a" };
		
		auto state = true;
		auto col_0 = lua_Number{ };
		auto col_1 = lua_Number{ };

		for ( auto channel : channels ) {
			tli_get_field( tli_param_one, channel, col_0 );
			tli_get_field( tli_param_two, channel, col_1 );

			state = col_0 < col_1;

			if ( !state ) break;
		}

		lua_pushboolean( context, state );
	} else
		lua_pushboolean( context, false );

	return 1;
}

tli_implementfn( TinyLua::Color::LessEqual ) {
	if (
		lua_istable( context, tli_param_one ) &&
		lua_istable( context, tli_param_two )
	) {
		c_string channels[ 4 ] = { "r", "g", "b", "a" };

		auto state = true;
		auto col_0 = lua_Number{ };
		auto col_1 = lua_Number{ };

		for ( auto channel : channels ) {
			tli_get_field( tli_param_one, channel, col_0 );
			tli_get_field( tli_param_two, channel, col_1 );

			state = col_0 <= col_1;

			if ( !state ) break;
		}

		lua_pushboolean( context, state );
	} else
		lua_pushboolean( context, false );

	return 1;
}

void TinyLua::Color::Create( TinyLuaContext& context, const tiny_color& color ) {
	Create( 
		context, 
		tiny_cast( color.GetR( ), lua_Number ),
		tiny_cast( color.GetG( ), lua_Number ),
		tiny_cast( color.GetB( ), lua_Number ),
		tiny_cast( color.GetA( ), lua_Number )
	);
}

void TinyLua::Color::Create(
	lua_State* context,
	lua_Number r,
	lua_Number g,
	lua_Number b,
	lua_Number a
) {
	tli_create_new(
		TINY_COLOR_NAME,
		tli_create_field( "r", r );
		tli_create_field( "g", g );
		tli_create_field( "b", b );
		tli_create_field( "a", a );
	);
}

void TinyLua::Color::Register( TinyLuaContext& context ) {
	tli_create( TINY_COLOR_NAME );

	tli_createfn( "new", New );
	tli_createfn( "clone", Clone );
	tli_createfn( "set_r", SetR );
	tli_createfn( "set_g", SetG );
	tli_createfn( "set_b", SetB );
	tli_createfn( "set_a", SetA );
	tli_createfn( "set", Set );
	tli_createfn( "add", Add );
	tli_createfn( "sub", Sub );
	tli_createfn( "lerp", Lerp );
	tli_createfn( "interpolate", Interpolate );
	tli_createfn( "to_vec3", ToVec3 );
	tli_createfn( "to_vec4", ToVec4 );
	tli_createfn( "to_string", ToString );
	tli_createfn( "equal", Equal );
	tli_createfn( "less", Less );
	tli_createfn( "less_equal", LessEqual );

	if ( tli_createmeta( TINY_COLOR_NAME ) ) {
		tli_createop( "__gc", Delete );
		tli_createop( "__add", Add );
		tli_createop( "__sub", Sub );

		tli_createop( "__eq", Equal );
		tli_createop( "__lt", Less );
		tli_createop( "__le", LessEqual );

		tli_createop( "__tostring", ToString );
	}
}
