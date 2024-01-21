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
 * @creation : 16/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include "TinyToolCategory.h"

tiny_enum( TinyToolCategories ) {

	TT_CATEGORY_COMMON = 0,
	TT_CATEGORY_INPUTS,
	TT_CATEGORY_RENDER,
	TT_CATEGORY_CONTENT,
	TT_CATEGORY_WORLD,
	TT_CATEGORY_TERRAIN,

};

te_class TinyToolManager final {

private:
	tiny_uint					 _current;
	tiny_list<TinyToolCategory*> _categories;

public:
	TinyToolManager( );

	~TinyToolManager( ) = default;

	bool Initialize( TinyGame* game, TinyToolbox& toolbox );

	void Tick( TinyGame* game, TinyEngine& engine, TinyToolbox& toolbox );

	void Terminate( TinyGame* game );

public:
	template<typename Type, tiny_uint Alias>
		requires tiny_is_child_of( Type, TinyToolCategory )
	void Register( TinyGame* game, TinyEngine& engine, TinyToolbox& toolbox ) { 
		auto* category = new Type{ };

		if ( category ) {
			category->Create( game, engine, toolbox );
			
			_categories.insert( Alias, category );
		}
	};

public:
	tiny_inline TinyToolCategory* GetCurrent( );

	TinyToolCategory* GetCategory( tiny_uint category );

public:
	template<typename Type>
		requires tiny_is_child_of( Type, TinyToolCategory )
	Type* GetCurrentAs( ) { 
		return tiny_cast( GetCurrent( ), Type );
	};

	template<typename Type>
		requires tiny_is_child_of( Type, TinyToolCategory )
	Type* GetCategoryAs( tiny_uint category ) {
		return tiny_cast( GetCategory( category ), Type );
	};

};
