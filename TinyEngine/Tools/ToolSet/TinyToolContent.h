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

#include <TinyEngine/Tools/Editors/TinyToolTexture2D.h>

te_class TinyToolContent final : tiny_inherit( TinyToolCategory ) {

	typedef c_str ( *AssetTypeToString )( tiny_uint );

private:
	bool							_has_changed;
	tiny_uint						_type_count;
	AssetTypeToString				_type_to_string;
	tiny_list<TinyToolAssetEditor*> _type_editors;
	tiny_buffer<256>				_path_buffer;

public:
	TinyToolContent( );

	~TinyToolContent( ) = default;

	tiny_implement( void Create( 
		TinyGame* game, 
		TinyEngine& engine, 
		TinyToolbox& toolbox 
	) );

	bool OpenAssetEditor( TinyGame* game, tiny_uint type, TinyAssetMetadata& metadata );

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
			_type_editors.insert( AssetType, editor );
	};

private:
	static c_str TypeToString( tiny_uint type );

};
