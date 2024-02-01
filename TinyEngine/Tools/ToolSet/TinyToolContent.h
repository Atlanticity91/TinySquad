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
 * @creation : 19/01/2024
 * @version  : 2024.1
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#pragma once

#include <TinyEngine/Tools/Editors/TinyToolLua.h>

tiny_enum( TinyToolContentActions ) {

	TTC_ACTION_EDIT = 0, 
	TTC_ACTION_REMOVE

};

te_class TinyToolContent final 
	: tiny_inherit( TinyToolCategory ),
	tiny_inherit( TinyToolDialog )
{

	typedef c_string ( *AssetTypeToString )( tiny_uint );

private:
	bool							_has_changed;
	tiny_uint						_type_count;
	tiny_uint						_asset_count;
	AssetTypeToString				_type_to_string;
	tiny_list<TinyToolAssetEditor*> _type_editors;
	TinyToolContentActions			_action;
	TinyAssetRegistry::MetaNode*	_metadata;

public:
	TinyToolContent( );

	~TinyToolContent( ) = default;

	tiny_implement( void Create( 
		TinyGame* game, 
		TinyEngine& engine, 
		TinyToolbox& toolbox 
	) );

	bool OpenAssetEditor( TinyGame* game, const tiny_string& asset_name );

	bool OpenAssetEditor(
		TinyGame* game,
		const tiny_string& name,
		const TinyAssetMetadata& metadata 
	);

	void RenderEditors( TinyGame* game );

protected:
	tiny_implement( void OnTick(
		TinyGame* game,
		TinyEngine& engine,
		TinyToolbox& toolbox
	) );

public:
	template<typename Type, tiny_uint AssetType>
		requires tiny_is_child_of( Type, TinyToolAssetEditor )
	void Register( ) { 
		auto* editor = new Type{ };

		if ( editor )
			_type_editors.insert( AssetType - 1, editor );
	};

public:
	bool GetHasEditor( tiny_uint asset_type ) const;

private:
	static c_string TypeToString( tiny_uint type );

};
