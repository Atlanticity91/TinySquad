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
	: TinyAsset{ TA_TYPE_GEOMETRY },
	m_index{ },
	m_vertex{ }
{ }

bool TinyGeometry::Create( 
	TinyGraphicWrapper& wrapper,
	const TinyGeometryBuilder& builder
) {
	auto state = m_index.Create( wrapper, { TGB_TYPE_INDEX, 0 } ) &&
				 m_vertex.Create( wrapper, { TGB_TYPE_VERTEX, 0 } );

	return state;
}

void TinyGeometry::Bind( 
	TinyGraphicWorkContext& work_context,
	TinyGraphicPipeline& pipeline 
) {
	pipeline.BindVertex( work_context, m_vertex );
	pipeline.BindIndex( work_context, m_index );
}

void TinyGeometry::Terminate( TinyGame* game ) {
	auto& graphics = game->GetGraphics( );
	auto graphic   = graphics.GetWrapper( );

	m_index.Terminate( graphic );
	m_vertex.Terminate( graphic );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
TinyGraphicBuffer& TinyGeometry::GetIndex( ) { return m_index; }

TinyGraphicBuffer& TinyGeometry::GetVertex( ) { return m_vertex; }
