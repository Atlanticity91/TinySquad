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

#include <TinyEngine/Renderer/Cameras/TinyRenderCameraManager.h>

te_struct TinyRenderUniformBuilder : tiny_inherit( TinyGraphicBufferProperties ) {

	tiny_string Name  = "";
	tiny_uint Set	  = 0;
	tiny_uint Binding = 0;

};

te_struct TinyUBOContext {

	tiny_mat4 Projection;
	tiny_mat4 View;
	tiny_mat4 ProjView;
	float Time_f;
	double Time_d;

};

te_class TinyRenderUniform final {

private:
	TinyGraphicBuffer			 _buffer;
	TinyGraphicPipelineBindpoint _bind_point;

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

public:
	operator TinyGraphicBuffer& ( );

	operator TinyGraphicPipelineBindpoint& ( );

};
