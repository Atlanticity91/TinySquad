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
 * @creation : 21/12/2023
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
TinyRenderUniformManager::TinyRenderUniformManager( ) 
	: _uniforms{ }
{ }

bool TinyRenderUniformManager::Create( TinyGraphicManager& graphics ) {
	auto core = TinyRenderUniformBuilder{
		TGB_TYPE_UNIFORM, tiny_sizeof( TinyRenderCore ),
		"ubo_core", TRS_ID_CORE, 0
	}; 
	auto transforms = TinyRenderUniformBuilder{
		TGB_TYPE_UNIFORM, TinyRenderBatchManager::BatchTransform_t::Size,
		"ubo_transforms", TRS_ID_RENDER, 0
	};
	auto sprites = TinyRenderUniformBuilder{
		TGB_TYPE_UNIFORM, TinyRenderBatchManager::BatchSprite_t::Size,
		"ubo_sprites", TRS_ID_RENDER, 1
	};
	auto lights = TinyRenderUniformBuilder{
		TGB_TYPE_UNIFORM, TinyRenderBatchManager::BatchLight_t::Size,
		"ubo_lights", TRS_ID_LIGHT, 0
	};
	auto vertex = TinyRenderUniformBuilder{
		TGB_TYPE_VERTEX, TinyRenderBatchManager::BatchVertex_t::Size, "ib_vertex"
	};

	return  Create( graphics, core		 ) &&
			Create( graphics, transforms ) &&
			Create( graphics, sprites	 ) &&
			Create( graphics, lights	 ) &&
			Create( graphics, vertex );
}

bool TinyRenderUniformManager::Create(
	TinyGraphicManager& graphics, 
	const TinyRenderUniformBuilder& builder 
) {
	auto state = !builder.Name.is_empty( ) && !_uniforms.find( builder.Name );
	
	if ( state ) {
		auto uniform = TinyRenderUniform{ };
		auto context = graphics.GetContext( );

		state = uniform.Create( context, builder );

		if ( state )
			_uniforms.emplace( builder.Name, uniform );
	}

	return state;
}

void TinyRenderUniformManager::Destroy(
	TinyGraphicManager& graphics, 
	const tiny_string& name 
) {
	auto uniform_id = tiny_cast( 0, tiny_uint );

	if ( _uniforms.find( name, uniform_id ) ) {
		auto& uniform = _uniforms.at( uniform_id );
		auto context  = graphics.GetContext( );

		uniform.Terminate( context );

		_uniforms.erase( name );
	}
}

void TinyRenderUniformManager::Terminate( TinyGraphicManager& graphics ) {
	auto context = graphics.GetContext( );

	for ( auto& uniform : _uniforms )
		uniform.Data.Terminate( context );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyRenderUniformManager::GetExist( const tiny_string& name ) const {
	return _uniforms.find( name );
}

TinyRenderUniform& TinyRenderUniformManager::GetUniform( const tiny_string& name ) {
	return _uniforms[ name ];
}
