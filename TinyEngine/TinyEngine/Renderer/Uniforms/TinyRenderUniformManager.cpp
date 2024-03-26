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

bool TinyRenderUniformManager::Create( 
	TinyGraphicManager& graphics,
	TinyGraphicBufferStaging& staging
) {
	auto core = TinyRenderUniformBuilder{
		TGB_TYPE_UNIFORM, tiny_sizeof( TinyRenderCore ),
		TinyCoreUniform, TRS_ID_CORE, 0
	};
	auto indexes = TinyRenderUniformBuilder{ TGB_TYPE_INDEX, TINY_QUAD_INDEX_SIZE, TinyQuadIndexBuffer };
	auto state   = Create( graphics, core ) && Create( graphics, indexes );

	if ( state )
		GenerateIndexBuffer( graphics, staging );

	return state;
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
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void TinyRenderUniformManager::GenerateIndexBuffer( 
	TinyGraphicManager& graphics,
	TinyGraphicBufferStaging& staging
) {
	auto indexes = tiny_list<TinyRenderQuadIndex>{ };
	auto count   = TINY_MAX_VERTEX;

	indexes = count;

	while ( count-- > 0 ) {
		auto index_id = TINY_QUAD_INDEX_COUNT;
		auto offset   = TINY_QUAD_VERTICE_COUNT * count;

		while ( index_id-- > 0 )
			indexes[ count ].Index[ index_id ] = TinyQuadIndex[ index_id ] + offset;
	}

	{
		auto context = graphics.GetContext( );
		auto size	 = TINY_QUAD_INDEX_SIZE;

		staging.Map( context, size );
		Tiny::Memcpy( indexes.data( ), staging.GetAccess( ), size );
		staging.UnMap( context );

		auto burner = TinyGraphicBurner{ context, VK_QUEUE_TYPE_TRANSFER };
		auto copie  = VkBufferCopy{ 0, 0, size };

		burner.Upload( staging, _uniforms[ TinyQuadIndexBuffer ], copie );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool TinyRenderUniformManager::GetExist( const tiny_string& name ) const {
	return _uniforms.find( name );
}

bool TinyRenderUniformManager::GetExist( const tiny_hash hash ) const {
	return _uniforms.find( hash );
}

TinyRenderUniform& TinyRenderUniformManager::GetUniform( const tiny_string& name ) {
	return _uniforms[ name ];
}

TinyRenderUniform& TinyRenderUniformManager::GetUniform( const tiny_hash hash ) {
	return _uniforms[ hash ];
}

TinyGraphicBuffer& TinyRenderUniformManager::GetBuffer( const tiny_string& name ) {
	auto& uniform = GetUniform( name );

	return uniform.GetBuffer( );
}

TinyGraphicBuffer& TinyRenderUniformManager::GetBuffer( const tiny_hash hash ) {
	auto& uniform = GetUniform( hash );

	return uniform.GetBuffer( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyRenderUniform& TinyRenderUniformManager::operator[]( const tiny_string& name ) {
	return GetUniform( name );
}

TinyRenderUniform& TinyRenderUniformManager::operator[]( const tiny_hash hash ) {
	return GetUniform( hash );
}
