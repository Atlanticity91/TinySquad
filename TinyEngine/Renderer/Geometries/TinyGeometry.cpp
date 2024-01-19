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
 * @creation : 28/11/2023
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
TinyGeometry::TinyGeometry( )
	: _index{ },
	_vertex{ }
{ }

bool TinyGeometry::Create( 
	TinyGraphicContext& context, 
	const TinyGeometryBundle& bundle 
) {
	auto state = _index.Create( context, { TGB_TYPE_INDEX, 0 } ) && 
				 _vertex.Create( context, { TGB_TYPE_VERTEX, 0 } );

	return state;
}

void TinyGeometry::Bind( TinyGraphicWorkContext& work_context ) {
	if ( work_context.Queue ) {
		auto* vertex = _vertex.Get( );
		auto offset = VkDeviceSize{ 0 };

		/*
		if ( _vertex )
			vkCmdBindVertexBuffers( work_context.Queue->CommandBuffer, 0, 1, &vertex, &offset );

		if ( _index )
			vkCmdBindIndexBuffer( work_context.Queue->CommandBuffer, _index, offset, VK_INDEX_TYPE_UINT32 );
		*/
	}
}

void TinyGeometry::Terminate( TinyGraphicContext& context ) {
	_index.Terminate( context );
	_vertex.Terminate( context );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBuffer& TinyGeometry::GetIndex( ) { return _index; }

TinyGraphicBuffer& TinyGeometry::GetVertex( ) { return _vertex; }
