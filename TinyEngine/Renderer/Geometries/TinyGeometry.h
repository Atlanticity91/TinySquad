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

	void Bind( TinyGraphicWorkContext& work_context );

	void Terminate( TinyGraphicContext& context );

public:
	TinyGraphicBuffer& GetIndex( );
	
	TinyGraphicBuffer& GetVertex( );

};
