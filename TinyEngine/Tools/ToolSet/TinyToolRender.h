#pragma once

#include "TinyToolCommon.h"

te_class TinyToolRender final : tiny_inherit( TinyToolCategory ) {

public:
	TinyToolRender( );

	~TinyToolRender( ) = default;

protected:
	tiny_implement( void OnTick(
		TinyGame* game,
		TinyEngine& engine,
		TinyToolbox& toolbox
	) );

};
