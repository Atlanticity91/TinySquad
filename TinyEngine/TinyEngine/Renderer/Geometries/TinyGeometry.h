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

#pragma once

#include "TinyGeometryBundle.h"

te_class TinyGeometry {

private:
	TinyGraphicBuffer _index;
	TinyGraphicBuffer _vertex;

public:
	TinyGeometry( );

	~TinyGeometry( ) = default;

	bool Create( 
		TinyGraphicContext& context, 
		const TinyGeometryBundle& bundle 
	);

	tiny_inline void Bind(
		TinyGraphicWorkContext& work_context,
		TinyGraphicPipeline& pipeline 
	);

	void Terminate( TinyGraphicContext& context );

public:
	TinyGraphicBuffer& GetIndex( );
	
	TinyGraphicBuffer& GetVertex( );

};
