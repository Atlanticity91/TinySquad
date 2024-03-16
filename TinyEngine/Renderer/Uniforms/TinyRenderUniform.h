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

#pragma once

#include "TinyRenderUniformBuilder.h"

te_class TinyRenderUniform final {

private:
	TinyGraphicBuffer			 _buffer;
	mutable TinyGraphicPipelineBindpoint _bind_point;

public:
	TinyRenderUniform( );

	~TinyRenderUniform( ) = default;

	bool Create( TinyGraphicContext& context, const TinyRenderUniformBuilder& builder );

	void Terminate( TinyGraphicContext& context );

public:
	tiny_uint GetSet( ) const;

	tiny_uint GetBinding( ) const;

	TinyGraphicBuffer& GetBuffer( );

	TinyGraphicPipelineBindpoint& GetBindpoint( );

	const TinyGraphicPipelineBindpoint& GetBindpoint( ) const;

public:
	operator TinyGraphicBuffer& ( );

	operator TinyGraphicPipelineBindpoint& ( );

	operator const TinyGraphicPipelineBindpoint& ( ) const;

};
