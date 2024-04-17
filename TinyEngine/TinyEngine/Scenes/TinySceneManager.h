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
 * @creation : 16/04/2024
 * @version  : 2024.2.8
 * @licence  : MIT
 * @project  : Micro library use for C++ basic game dev, produce for
 *			   Tiny Squad team use originaly.
 *
 ******************************************************************************************/

#include "TinyScene.h"

template<typename Factory>
concept TinyIsFactory = tiny_is_child_of( Factory, TinySceneFactory );

te_class TinySceneManager final : tiny_inherit( TinyAssetContainer<TinyScene> ) {

public:
	TinySceneManager( );

	~TinySceneManager( ) = default;

	tiny_implement( bool Create(
		TinyGame* game,
		const tiny_string& alias,
		const c_pointer builder
	) );

	tiny_implement( bool Load(
		TinyGame* game,
		const tiny_string& alias,
		TinyFile& file
	) );

	void Spawn(
		TinyGame* game, 
		const tiny_string& entity_name, 
		std::function<void( const tiny_uint, TinyGame*, TinyECS& )> entity_factory
	);

public:
	template<typename Factory>
		requires TinyIsFactory<Factory>
	void Spawn( TinyGame* game, const tiny_string& entity_name ) { 
		Spawn( 
			game,
			entity_name, 
			[]( const tiny_uint entity_id, TinyGame* game, TinyECS& ecs ) {
				auto factory = Factory{ };

				factory.Spawn( entity_id, game, ecs );
			} 
		);
	};

};
